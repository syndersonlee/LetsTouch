
#include "MMA8451.h"
#include "lt_ble.h"
#include "nrf_gpio.h"

#include "SEGGER_RTT.h"

#define RGB_R NRF_GPIO_PIN_MAP(0, 6)
#define RGB_G NRF_GPIO_PIN_MAP(0, 7)
#define RGB_B NRF_GPIO_PIN_MAP(0, 8)

void setPin() {
  bsp_board_init(BSP_INIT_LEDS);
  nrf_gpio_cfg_output(6);
  nrf_gpio_cfg_output(7);
  nrf_gpio_cfg_output(8);

  nrf_gpio_pin_clear(6);
  nrf_gpio_pin_clear(7);
  nrf_gpio_pin_clear(8);


  nrf_gpio_pin_set(8);

//  nrf_delay_ms(1000);

  nrf_gpio_pin_clear(6);
  nrf_gpio_pin_clear(7);
  nrf_gpio_pin_clear(8);


  nrf_gpio_pin_set(7);

//  nrf_delay_ms(1000);

  nrf_gpio_pin_clear(6);
  nrf_gpio_pin_clear(7);
  nrf_gpio_pin_clear(8);


  nrf_gpio_pin_set(6);

//  nrf_delay_ms(1000);

  //LED is qt

  SEGGER_RTT_printf(0, "RGB_R %u\n", nrf_gpio_pin_out_read(RGB_R));
  SEGGER_RTT_printf(0, "RGB_G %u\n", nrf_gpio_pin_out_read(RGB_G));
  SEGGER_RTT_printf(0, "RGB_B %u\n", nrf_gpio_pin_out_read(RGB_B));
}

int main(void) {

#if 1
  bool erase_bonds;
  uart_init(); //==uart_config();
  log_init();

  setPin();
               //  twi_init();  //i2c init
               //  setMode();
  timers_init();
  buttons_leds_init(&erase_bonds);
  power_management_init();
  SEGGER_RTT_WriteString(0,"Start3\n");
  ble_stack_init();
  SEGGER_RTT_WriteString(0,"Start4\n");
  gap_params_init();
  gatt_init();
  services_init();
  advertising_init();
  conn_params_init();

  // Start execution.

  SEGGER_RTT_WriteString(0,"Start");

  advertising_start();

  // Enter main loop.
  twi_init();

  //adc
  //power_management_init~
  //ret_code_t ret_code = nrf_pwr_mgmt_init();
  //APP_ERROR_CHECK(ret_code);

/*
  saadc_init();
  saadc_sampling_event_init();
  saadc_sampling_event_enable();
*/
  // Enter main loop.
  SEGGER_RTT_WriteString(0,"Before MMA INIT!\n");

  initMMA8451();


  SEGGER_RTT_WriteString(0,"Before Loop\n");
  for (;;) {

//    nrf_pwr_mgmt_run();



    //    NRF_LOG_FLUSH();
    //adc

    idle_state_handle();


    sendData();

    
    nrf_delay_ms(5);
    readSen();
  }
#else
  bool erase_bonds;
  uart_init();
  log_init();
  timers_init();
  buttons_leds_init(&erase_bonds);


  power_management_init();
  SEGGER_RTT_printf(0, "Stack init\n");

  ble_stack_init();
  SEGGER_RTT_printf(0, "Stack init~\n");

  gap_params_init();
  gatt_init();
  services_init();
  advertising_init();
  conn_params_init();



  // Start execution.
  printf("\r\nUART started~!\r\n");
  SEGGER_RTT_printf(0, "Debug logging for UART over RTT started.");
  advertising_start();


  // Enter main loop.
  for (;;) {
    idle_state_handle();
    //        static uint8_t data_array[]={'t','e','s','t','\n'};
    //        uint16_t length = (uint16_t)5;
    //        ble_nus_data_send(&m_nus, data_array, &length, m_conn_handle);

    //        app_uart_put('t');
    //        app_uart_put('\n');
  }

#endif
}