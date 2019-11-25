
#include "MPU6050.h"
#include "lt_ble.h"
#include "lt_adc.h"
#include "nrf_gpio.h"

#include "SEGGER_RTT.h"



void setPin() {
  bsp_board_init(BSP_INIT_LEDS);
  nrf_gpio_cfg_output(RGB_R);
  nrf_gpio_cfg_output(RGB_G);
  nrf_gpio_cfg_output(RGB_B);
  nrf_gpio_cfg_output(SEN);

  nrf_gpio_pin_set(SEN);
//  nrf_gpio_pin_set(RGB_R);
//  nrf_gpio_pin_set(RGB_G);
//  nrf_gpio_pin_set(RGB_B);

//  nrf_gpio_pin_clear(RGB_B);
  nrf_gpio_pin_clear(RGB_G);
//  nrf_gpio_pin_clear(8);

  //LED is qt
//  SEGGER_RTT_printf(0, "RGB_R %u\n", nrf_gpio_pin_out_read(RGB_R));
//  SEGGER_RTT_printf(0, "RGB_G %u\n", nrf_gpio_pin_out_read(RGB_G));
//  SEGGER_RTT_printf(0, "RGB_B %u\n", nrf_gpio_pin_out_read(RGB_B));
  
}

//10hz
//5 level
//



int main(void) {

  bool erase_bonds;
  uart_init(); //==uart_config();
  log_init();


  setPin();
               //  twi_init();  //i2c init
               //  setMode();
  timers_init();


//  init_adc();
  adcinit();
//  init_setting();
  ble_timer_init();
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
  twi_initMPU();
  initMPU();
  SEGGER_RTT_WriteString(0,"Before Loop\n");
  for (;;) {

//    nrf_pwr_mgmt_run();


    NRF_LOG_FLUSH();
    //adc
    idle_state_handle();

    nrf_pwr_mgmt_run();
    
    nrf_delay_ms(5);
    addms();
    readSenMPU();
//    nrf_gpio_pin_set(SEN);
  }
}