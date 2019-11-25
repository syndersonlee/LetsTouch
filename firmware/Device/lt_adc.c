

//ADC START
#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_timer.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define SAMPLES_IN_BUFFER 5
static nrf_ppi_channel_t m_ppi_channel;
static uint32_t m_adc_evt_counter;
static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(0);
//
static nrf_saadc_value_t m_buffer_pool[2][SAMPLES_IN_BUFFER];
void timer_handler(nrf_timer_event_t event_type, void *p_context) {

}
void saadc_callback(nrf_drv_saadc_evt_t const *p_event) {
  if (p_event->type == NRF_DRV_SAADC_EVT_DONE) {
    ret_code_t err_code;

    err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    int i;
    printf("ADC event: %d", (int)m_adc_evt_counter);

    for (i = 0; i < SAMPLES_IN_BUFFER; i++) {
      printf("ACD %d\n", p_event->data.done.p_buffer[i]);
    }
    m_adc_evt_counter++;
  }
}
void saadc_init(void) {
  ret_code_t err_code;
  //saadc pin select
  //02,03,04,05,28,29,30,31
  //0,1,2,3,4,5,6,7

//mux read (0 1) 4 5 6

  nrf_saadc_channel_config_t channel_config =
      NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);

  err_code = nrf_drv_saadc_init(NULL, saadc_callback);
  APP_ERROR_CHECK(err_code);

  err_code = nrf_drv_saadc_channel_init(0, &channel_config);
  APP_ERROR_CHECK(err_code);

  err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
  APP_ERROR_CHECK(err_code);

  err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
  APP_ERROR_CHECK(err_code);
}
void saadc_sampling_event_init(void) {
  ret_code_t err_code;

  err_code = nrf_drv_ppi_init();
  APP_ERROR_CHECK(err_code);

  nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
  timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
  err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
  APP_ERROR_CHECK(err_code);

  /* setup m_timer for compare event every 400ms */
  uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 400);
  nrf_drv_timer_extended_compare(&m_timer,
      NRF_TIMER_CC_CHANNEL0,
      ticks,
      NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
      false);
  nrf_drv_timer_enable(&m_timer);

  uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
      NRF_TIMER_CC_CHANNEL0);
  uint32_t saadc_sample_task_addr = nrf_drv_saadc_sample_task_get();

  /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
  err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
  APP_ERROR_CHECK(err_code);

  err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
      timer_compare_event_addr,
      saadc_sample_task_addr);
  APP_ERROR_CHECK(err_code);
}

void saadc_sampling_event_enable(void) {
  ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);
  APP_ERROR_CHECK(err_code);
}