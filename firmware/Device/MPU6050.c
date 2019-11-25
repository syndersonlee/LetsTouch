#include "MPU6050.h"
long ms = 0;
int address=0x68;

unsigned long last_read_time;
float last_x_angle; // These are the filtered angles
float last_y_angle;
float last_z_angle;
float last_gyro_x_angle; // Store the gyro angles to compare drift
float last_gyro_y_angle;
float last_gyro_z_angle;
float base_x_accel;
float base_y_accel;
float base_z_accel;
float base_x_gyro;
float base_y_gyro;
float base_z_gyro;
void addms(){
  ms+=5;
}
unsigned long millis() {
  return ms;
}
void set_last_read_angle_data(unsigned long time, float x, float y, float z, float x_gyro, float y_gyro, float z_gyro) {
  last_read_time = time;
  last_x_angle = x;
  last_y_angle = y;
  last_z_angle = z;
  last_gyro_x_angle = x_gyro;
  last_gyro_y_angle = y_gyro;
  last_gyro_z_angle = z_gyro;
}

inline unsigned long get_last_time() { return last_read_time; }
inline float get_last_x_angle() { return last_x_angle; }
inline float get_last_y_angle() { return last_y_angle; }
inline float get_last_z_angle() { return last_z_angle; }
inline float get_last_gyro_x_angle() { return last_gyro_x_angle; }
inline float get_last_gyro_y_angle() { return last_gyro_y_angle; }
inline float get_last_gyro_z_angle() { return last_gyro_z_angle; }

int read_gyro_accel_vals(uint8_t *accel_t_gyro_ptr) {
  accel_t_gyro_union *accel_t_gyro = (accel_t_gyro_union *)accel_t_gyro_ptr;
//  int error = MPU6050_read(MPU6050_ACCEL_XOUT_H, (uint8_t *)accel_t_gyro, sizeof(*accel_t_gyro));
  (*accel_t_gyro).reg.x_accel_h=readV(ACCEL_XOUT_H);
  (*accel_t_gyro).reg.y_accel_h=readV(ACCEL_YOUT_H);
  (*accel_t_gyro).reg.z_accel_h=readV(ACCEL_ZOUT_H);
  (*accel_t_gyro).reg.x_accel_l=readV(ACCEL_XOUT_L);
  (*accel_t_gyro).reg.y_accel_l=readV(ACCEL_YOUT_L);
  (*accel_t_gyro).reg.z_accel_l=readV(ACCEL_ZOUT_L);
  (*accel_t_gyro).reg.t_h=readV(TEMP_OUT_H);
  (*accel_t_gyro).reg.t_l=readV(TEMP_OUT_L);
  (*accel_t_gyro).reg.x_gyro_h=readV(GYRO_XOUT_H);
  (*accel_t_gyro).reg.x_gyro_l=readV(GYRO_XOUT_L);
  (*accel_t_gyro).reg.y_gyro_h=readV(GYRO_YOUT_H);
  (*accel_t_gyro).reg.y_gyro_l=readV(GYRO_YOUT_L);
  (*accel_t_gyro).reg.z_gyro_h=readV(GYRO_ZOUT_H);
  (*accel_t_gyro).reg.z_gyro_l=readV(GYRO_ZOUT_L);

/*
  SEGGER_RTT_printf(0,"in %d %d %d %d %d %d => %d %d %d \n",accel_t_gyro->reg.x_accel_h,
  accel_t_gyro->reg.y_accel_h,
  accel_t_gyro->reg.z_accel_h,
  accel_t_gyro->reg.x_accel_l,
  accel_t_gyro->reg.y_accel_l,
  accel_t_gyro->reg.z_accel_l,(int)(get_last_gyro_x_angle()*10),(int)(get_last_gyro_y_angle()*10),
  (int)(get_last_gyro_z_angle()*10));

  */


  uint8_t swap;
#define SWAP(x, y) swap = x;  x = y;   y = swap
  SWAP((*accel_t_gyro).reg.x_accel_h, (*accel_t_gyro).reg.x_accel_l);
  SWAP((*accel_t_gyro).reg.y_accel_h, (*accel_t_gyro).reg.y_accel_l);
  SWAP((*accel_t_gyro).reg.z_accel_h, (*accel_t_gyro).reg.z_accel_l);
  SWAP((*accel_t_gyro).reg.t_h, (*accel_t_gyro).reg.t_l);
  SWAP((*accel_t_gyro).reg.x_gyro_h, (*accel_t_gyro).reg.x_gyro_l);
  SWAP((*accel_t_gyro).reg.y_gyro_h, (*accel_t_gyro).reg.y_gyro_l);
  SWAP((*accel_t_gyro).reg.z_gyro_h, (*accel_t_gyro).reg.z_gyro_l);
  return 0;
}

void calibrate_sensors() {
  accel_t_gyro_union accel_t_gyro;

  int b_x_accel = 0;
  int b_y_accel = 0;
  int b_z_accel = 0;
  int b_x_gyro = 0;
  int b_y_gyro = 0;
  int b_z_gyro = 0;
  int num_readings = 10;




  read_gyro_accel_vals((uint8_t *)&accel_t_gyro);

  for (int i = 0; i < num_readings; i++) {

    read_gyro_accel_vals((uint8_t *)&accel_t_gyro);

    b_x_accel += accel_t_gyro.value.x_accel;
    b_y_accel += accel_t_gyro.value.y_accel;
    b_z_accel += accel_t_gyro.value.z_accel;
    b_x_gyro += accel_t_gyro.value.x_gyro;
    b_y_gyro += accel_t_gyro.value.y_gyro;
    b_z_gyro += accel_t_gyro.value.z_gyro;

    nrf_delay_ms(100);


  }
  base_x_accel=b_x_accel/num_readings;
  base_y_accel=(float)b_y_accel / num_readings;
  base_z_accel=(float)b_z_accel / num_readings;
  base_x_gyro=(float)b_x_gyro / num_readings;
  base_y_gyro=(float)b_y_gyro / num_readings;
  base_z_gyro=(float)b_z_gyro / num_readings;

//  SEGGER_RTT_printf(0,"base END : %d %d ! %d = %d\n",b_x_accel,num_readings,b_x_accel/num_readings,(int)base_x_accel);


}

float getData() {
  int error;
  accel_t_gyro_union accel_t_gyro;

  error = read_gyro_accel_vals((uint8_t *)&accel_t_gyro);
  unsigned long t_now = millis();

  // Convert gyro values to degrees/sec
  float FS_SEL = 131;

//  SEGGER_RTT_printf(0,"res END : %d %d \n",accel_t_gyro.value.x_gyro,base_x_gyro);


  float gyro_x = (accel_t_gyro.value.x_gyro - base_x_gyro) / FS_SEL;
  float gyro_y = (accel_t_gyro.value.y_gyro - base_y_gyro) / FS_SEL;
  float gyro_z = (accel_t_gyro.value.z_gyro - base_z_gyro) / FS_SEL;

  //float G_CONVERT = 16384;
  float accel_x = accel_t_gyro.value.x_accel;
  float accel_y = accel_t_gyro.value.y_accel;
  float accel_z = accel_t_gyro.value.z_accel;

  float RADIANS_TO_DEGREES = 180 / 3.14159;
  //  float accel_vector_length = sqrt(pow(accel_x,2) + pow(accel_y,2) + pow(accel_z,2));
  float accel_angle_y = atan(-1 * accel_x / sqrt(pow(accel_y, 2) + pow(accel_z, 2))) * RADIANS_TO_DEGREES;
  float accel_angle_x = atan(accel_y / sqrt(pow(accel_x, 2) + pow(accel_z, 2))) * RADIANS_TO_DEGREES;
  float accel_angle_z = 0;

  // Compute the (filtered) gyro angles
  float dt = (t_now - get_last_time()) / 1000.0;
  float gyro_angle_x = gyro_x * dt + get_last_x_angle();
  float gyro_angle_y = gyro_y * dt + get_last_y_angle();
  float gyro_angle_z = gyro_z * dt + get_last_z_angle();

  // Compute the drifting gyro angles

  float dis=200000;
//  SEGGER_RTT_printf(0,"TEST %d %d\n",(int)(gyro_x * dt*10),(int)(10*get_last_gyro_x_angle()));
  int unfiltered_gyro_angle_x = (gyro_x * dt + get_last_gyro_x_angle())*dis;
  int unfiltered_gyro_angle_y = (gyro_y * dt + get_last_gyro_y_angle())*dis;
  int unfiltered_gyro_angle_z = (gyro_z * dt + get_last_gyro_z_angle())*dis;

  // Apply the complementary filter to figure out the change in angle - choice of alpha is
  // estimated now.  Alpha depends on the sampling rate...
  float alpha = 0.96;
  float angle_x = alpha * gyro_angle_x + (1.0 - alpha) * accel_angle_x;
  float angle_y = alpha * gyro_angle_y + (1.0 - alpha) * accel_angle_y;
  float angle_z = gyro_angle_z; //Accelerometer doesn't give z-angle

  // Update the saved data with the latest values
//  SEGGER_RTT_printf(0,"LAST X %d\n", (int)(unfiltered_gyro_angle_x*10));
  set_last_read_angle_data(t_now, angle_x, angle_y, angle_z, unfiltered_gyro_angle_x*(1/dis), unfiltered_gyro_angle_y*(1/dis), unfiltered_gyro_angle_z*(1/dis));

  return dt;
}

//static uint8_t m_sample;

//include

//SCL 27
//SDA 26
/*
static void read_sensor_data() {
  m_xfer_done = false;

  ret_code_t err_code = nrf_drv_twi_rx(&m_twi, 0x68, MMA8451_REG_OUT_X_MSB, sizeof(MMA8451_REG_OUT_X_MSB));
  APP_ERROR_CHECK(err_code);
}
*/
void twi_handlerMPU(nrf_drv_twi_evt_t const *p_event, void *p_context) {
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

void twi_initMPU(void) {

  ret_code_t err_code;

  const nrf_drv_twi_config_t twi_cmps_10_config = {
      .scl = NRF_GPIO_PIN_MAP(0, 17),
      .sda = NRF_GPIO_PIN_MAP(0, 13),
      .frequency = NRF_TWI_FREQ_100K,
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
      .clear_bus_init = false //add???
  };

  err_code = nrf_drv_twi_init(&m_twi, &twi_cmps_10_config, twi_handlerMPU, NULL);
  APP_ERROR_CHECK(err_code);


  nrf_drv_twi_enable(&m_twi);
}

void initMPU() {
  ret_code_t err_code;

  nrf_delay_ms(50);
  uint8_t reg1[2] = {PWR_MGMT_1, 0x01};
  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg1, sizeof(reg1), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;
  nrf_delay_ms(50);


  calibrate_sensors();


  set_last_read_angle_data(millis(), 0, 0, 0, 0, 0, 0);


  /*uint8_t reg2[2] = {0x1A, 0x03};
  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg2, sizeof(reg2), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);

      nrf_delay_ms(50);
  uint8_t reg3[2] = {SMPLRT_DIV, 0x04};
//  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg3, sizeof(reg3), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);

      nrf_delay_ms(50);
  uint8_t reg4[2] = {GYRO_CONFIG, ~0xE0};
  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg4, sizeof(reg4), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);

  nrf_delay_ms(50);
  uint8_t reg4[2] = {GYRO_CONFIG, ~0xE0};
  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg4, sizeof(reg4), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);*/
}

int bitRead(uint8_t x, int n) { // getbit()
  return (x & (1 << n)) >> n;
}

#define F_READ 1
#include <stdlib.h>

uint8_t readVal() {
  ret_code_t err_code;
  m_xfer_done = false;
  uint8_t reg1[1] = {0x2A};
  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg1, 1, true);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;
  m_xfer_done = false;
  int read_count = 3;
  uint8_t data;

  err_code = nrf_drv_twi_rx(&m_twi, 0x68, &data, sizeof(data));

  while (m_xfer_done == false)
    ;

  return data;
}
#define UINT14_MAX 16383
uint8_t readV(uint8_t v) {
  ret_code_t err_code;
  m_xfer_done = false;
  uint8_t reg1[1] = {v};
  err_code = nrf_drv_twi_tx(&m_twi, 0x68, reg1, 1, false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false)
    ;
  m_xfer_done = false;
  uint8_t data;

  err_code = nrf_drv_twi_rx(&m_twi, 0x68, &data, 1);

  while (m_xfer_done == false)
    ;

  int16_t acc = data;
  /*
  int16_t acc=(data[0]<<6)|(data[1]>>2);
  if(acc>UINT14_MAX/2)
    acc-=UINT14_MAX;*/

  return acc;
}

//#include "lt_ble.h"
accel_t_gyro_union ac;

void readSenMPU() {
/*
  ac.reg.x_accel_h=readV(ACCEL_XOUT_H);
  ac.reg.y_accel_h=readV(ACCEL_YOUT_H);
  ac.reg.z_accel_h=readV(ACCEL_ZOUT_H);
  ac.reg.x_accel_l=readV(ACCEL_XOUT_L);
  ac.reg.y_accel_l=readV(ACCEL_YOUT_L);
  ac.reg.z_accel_l=readV(ACCEL_ZOUT_L);
  ac.reg.t_h=readV(TEMP_OUT_H);
  ac.reg.t_l=readV(TEMP_OUT_L);
  ac.reg.x_gyro_h=readV(GYRO_XOUT_H);
  ac.reg.x_gyro_l=readV(GYRO_XOUT_L);
  ac.reg.y_gyro_h=readV(GYRO_YOUT_H);
  ac.reg.y_gyro_l=readV(GYRO_YOUT_L);
  ac.reg.z_gyro_h=readV(GYRO_ZOUT_H);
  ac.reg.z_gyro_l=readV(GYRO_ZOUT_L);*/

  getData();
  

//  lt_ble_data[17]=(int)get_last_gyro_x_angle();
//  lt_ble_data[18]=(int)get_last_gyro_y_angle();
//  lt_ble_data[19]=(int)get_last_gyro_z_angle();
/*
  SEGGER_RTT_printf(0, "now?? %d %d %d\n",
      (int)get_last_gyro_x_angle(),
      (int)get_last_gyro_y_angle(),
      (int)get_last_gyro_z_angle());
      */
  /*
  SEGGER_RTT_printf(0, "%d %d %d %d %d %d\n",
      readV(ACCEL_XOUT_H),
      readV(ACCEL_YOUT_H),
      readV(ACCEL_ZOUT_H),

      readV(GYRO_XOUT_H),
      readV(GYRO_YOUT_H),
      readV(GYRO_ZOUT_H));*/
  /*sendData(0,readV(ACCEL_XOUT_H));
  sendData(1,readV(0x03));
  sendData(2,readV(0x05));*/
}
