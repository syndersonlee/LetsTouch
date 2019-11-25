#include "MMA8451.h"

static uint8_t m_sample;

//include

//SCL 27
//SDA 26

static void read_sensor_data() {
  m_xfer_done = false;

  ret_code_t err_code = nrf_drv_twi_rx(&m_twi, MMA8451_DEFAULT_ADDRESS, MMA8451_REG_OUT_X_MSB, sizeof(MMA8451_REG_OUT_X_MSB));
  APP_ERROR_CHECK(err_code);
}

void twi_handler(nrf_drv_twi_evt_t const *p_event, void *p_context) {
  switch (p_event->type) {

    SEGGER_RTT_WriteString(0, "twi_handler\n");

  case NRF_DRV_TWI_EVT_DONE:
    if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX) {
      //      btd();
      //      SEGGER_RTT_printf(0,"SEN %u\n", m_sample);
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
      .scl = NRF_GPIO_PIN_MAP(0, 17),
      .sda = NRF_GPIO_PIN_MAP(0, 13),
      .frequency = NRF_TWI_FREQ_100K,
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
      .clear_bus_init = false //add???
  };

  err_code = nrf_drv_twi_init(&m_twi, &twi_cmps_10_config, twi_handler, NULL);
  APP_ERROR_CHECK(err_code);

  SEGGER_RTT_printf(0, "twi init : %u\n", err_code);

  nrf_drv_twi_enable(&m_twi);
}

void initMMA8451() {
  SEGGER_RTT_WriteString(0, "initMMA8451 INIT!!\n");
  ret_code_t err_code;
  
  nrf_delay_ms(50);
  uint8_t reg1[2] = {MMA8451_REG_CTRL_REG1, 0x01};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg1, sizeof(reg1), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);
/*
  nrf_delay_ms(50);
  uint8_t reg1[2] = {MMA8451_REG_CTRL_REG2, 0x40};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg1, sizeof(reg1), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);

  nrf_delay_ms(50);
  uint8_t reg2[2] = {MMA8451_REG_XYZ_DATA_CFG, MMA8451_RANGE_4_G};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg2, sizeof(reg2), false);
  APP_ERROR_CHECK(err_code);
  SEGGER_RTT_WriteString(0, "First Before\n");
  while (m_xfer_done == false)
    ;
  SEGGER_RTT_WriteString(0, "First Order Complete\n");

  nrf_delay_ms(50);
  uint8_t reg3[2] = {MMA8451_REG_CTRL_REG2, 0x02};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg3, sizeof(reg3), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);
  uint8_t reg4[2] = {MMA8451_REG_CTRL_REG4, 0x01};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg4, sizeof(reg4), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);
  uint8_t reg5[2] = {MMA8451_REG_CTRL_REG5, 0x01};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg5, sizeof(reg5), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);
  uint8_t reg6[2] = {MMA8451_REG_PL_CFG, 0x40};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg6, sizeof(reg6), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;

  nrf_delay_ms(50);
  uint8_t reg7[2] = {MMA8451_REG_CTRL_REG1, 0x01 | 0x04};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg7, sizeof(reg7), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;*/
}
/*
int bitRead(uint8_t x, int n) { // getbit()
  return (x & (1 << n)) >> n;
}*/

#define F_READ 1
#include <stdlib.h>
/*
uint8_t readVal(){
  ret_code_t err_code;
  m_xfer_done = false;
  uint8_t reg1[1] = {0x2A};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg1, 1, true);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);
  m_xfer_done = false;
  int read_count=3;
  uint8_t data;

  err_code = nrf_drv_twi_rx(&m_twi, MMA8451_DEFAULT_ADDRESS, &data, sizeof(data));


  while (m_xfer_done == false)
    ;


  return data;

}*/
/*
#define UINT14_MAX        16383
int16_t readV(uint8_t v){
  ret_code_t err_code;
  m_xfer_done = false;
  uint8_t reg1[1] = {v};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg1, 1, true);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);
  m_xfer_done = false;
  int read_count=3;
  uint8_t data[2];

  err_code = nrf_drv_twi_rx(&m_twi, MMA8451_DEFAULT_ADDRESS, &data, 2);

  while (m_xfer_done == false);
  int16_t acc=(data[0]<<6)|(data[1]>>2);
  if(acc>UINT14_MAX/2)
    acc-=UINT14_MAX;

  return acc;
}
*/

//#include "lt_ble.h"

void readSen() {
/*
  sendData(0,readV(0x01));
  sendData(1,readV(0x03));
  sendData(2,readV(0x05));*/
//  SEGGER_RTT_printf(0, "MMA8451_REG_OUT_X_MSB %d %d %d\n", readV(0x01),readV(0x03),readV(0x05));

/*


  NRF_LOG_INFO("readSen");

  ret_code_t err_code;

  uint8_t val=readVal();
  int read_count=6;//val==0?6:3;

  m_xfer_done = false;

  uint8_t reg1[1] = {MMA8451_REG_OUT_X_MSB};
  err_code = nrf_drv_twi_tx(&m_twi, MMA8451_DEFAULT_ADDRESS, reg1, 1, true);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;
  m_xfer_done = false;
  

  uint8_t *data=malloc(sizeof(uint8_t)*read_count);

  err_code = nrf_drv_twi_rx(&m_twi, MMA8451_DEFAULT_ADDRESS, data, read_count);


  
  while (m_xfer_done == false)
    ;


//  SEGGER_RTT_printf(0, "MMA8451_REG_OUT_X_MSB %u %d\n", *data,read_count);
  

  int axes[]={0,0,0};

  for (int i = 0; i < 3; i++) {
    axes[i] = data[i * (read_count / 3)] << 8;

    if (bitRead(val, F_READ) == 0)
      axes[i] |= data[(i * 2) + 1];

    axes[i] >>= 4;
  }
  SEGGER_RTT_printf(0, "MMA8451_REG_OUT_X_MSB %d %d %d\n", axes[0],axes[1],axes[2]);

  free(data);*/
}