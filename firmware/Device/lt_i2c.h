
//LIS3DH start

#include "LIS3DH.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

static uint8_t m_sample;

//include

//SCL 27
//SDA 26
#define ARDUINO_SCL_PIN 27
#define ARDUINO_SDA_PIN 26
//acc sender obj
#if TWI0_ENABLED
#define TWI_INSTANCE_ID 0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID 1
#endif
//0AI ¢®¡×I¡§I¡§¡Ì¡Ë¢ç¢®¡¿¡Ë¢çI¡Ë¢çE?I¡Ë¢ç¢®¡¿u¢®¡×I¡Ë¢ç¨Ï¡©CO
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

static volatile bool m_xfer_done = false;

__STATIC_INLINE void data_handler(uint8_t temp) {
  //write data
  printf("Temperature: %d Celsius degrees.", temp);
}

static void read_sensor_data() {
  m_xfer_done = false;

  ret_code_t err_code = nrf_drv_twi_rx(&m_twi, LIS3DH_DEFAULT_ADDRESS, LIS3DH_REG_OUTADC1_L, sizeof(LIS3DH_REG_OUTADC1_L));
  APP_ERROR_CHECK(err_code);
}

void twi_handler(nrf_drv_twi_evt_t const *p_event, void *p_context) {
  switch (p_event->type) {
  case NRF_DRV_TWI_EVT_DONE:
    if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX) {
      //      btd();
      printf("SEN %u\n", m_sample);
      //data_handler(m_sample);
    }
    m_xfer_done = true;
    break;
  default:
    break;
  }
}
void twi_init(void) {
  ret_code_t err_code;

  const nrf_drv_twi_config_t twi_cmps_10_config = {
      .scl = ARDUINO_SCL_PIN,
      .sda = ARDUINO_SDA_PIN,
      .frequency = NRF_TWI_FREQ_100K,
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
      .clear_bus_init = false //add???
  };

  err_code = nrf_drv_twi_init(&m_twi, &twi_cmps_10_config, twi_handler, NULL);
  APP_ERROR_CHECK(err_code);

  nrf_drv_twi_enable(&m_twi);
}

void setMode() {
  ret_code_t err_code;

  nrf_delay_ms(50);
  uint8_t reg1[2] = {LIS3DH_REG_CTRL1, 0x57};
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg1, sizeof(reg1), false);

  APP_ERROR_CHECK(err_code);

  while (m_xfer_done == false)
    ;
  nrf_delay_ms(50);
  uint8_t reg2[2] = {LIS3DH_REG_CTRL2, 0x00}; //no high pass filter
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg2, sizeof(reg2), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg3[2] = {LIS3DH_REG_CTRL3, 0x40}; //interrupt on int1
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg3, sizeof(reg3), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg4[2] = {LIS3DH_REG_CTRL4, 0x00}; // +/- 2g, LSB first,
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg4, sizeof(reg4), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg_Ref[2] = {LIS3DH_REG_REFERENCE, 0x00}; //reference reg
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg_Ref, sizeof(reg_Ref), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg5[2] = {LIS3DH_REG_CTRL5, 0x08}; // interrupt request latched
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg5, sizeof(reg5), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg6[2] = {LIS3DH_REG_CTRL6, 0x00};
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg6, sizeof(reg6), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg_ths[2] = {LIS3DH_REG_INT1THS, 0x10}; // threshold 250mg
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg_ths, sizeof(reg_ths), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);

  uint8_t reg_int[2] = {LIS3DH_REG_INT1DUR, 0x00}; // duration =0
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg_int, sizeof(reg_int), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);
  uint8_t reg_int_cfg[2] = {LIS3DH_REG_CLICKCFG, 0x3F}; // AOI=0 and x,y,z events
  err_code = nrf_drv_twi_tx(&m_twi, LIS3DH_DEFAULT_ADDRESS, reg_int_cfg, sizeof(reg_int_cfg), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;
}
