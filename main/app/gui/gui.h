#pragma once
#include "project_typedefs.h"

void nextion_1_init();
void nextion_1_start_timer();
void nextion_1_stop_timer();
void nextion_1_set_page(page_t new_page);
page_t nextion_1_get_page();

void nextion_1_home_sensor_1_write_data(float data);
void nextion_1_home_sensor_2_write_data(float data);
void nextion_1_home_sensor_3_write_data(float data);
void nextion_1_home_sensor_4_write_data(float data);
void nextion_1_home_sensor_5_write_data(float data, int decimals);
void nextion_1_home_sensor_6_write_data(float data, int decimals);
void nextion_1_home_sensor_7_write_data(float data, int decimals);
void nextion_1_home_sensor_8_write_data(float data, int decimals);

void nextion_1_home_sensor_1_write_dataps(float dataps);
void nextion_1_home_sensor_2_write_dataps(float dataps);
void nextion_1_home_sensor_3_write_dataps(float dataps);
void nextion_1_home_sensor_4_write_dataps(float dataps);

void nextion_1_home_sensor_5_write_dataps(float dataps, int decimals);
void nextion_1_home_sensor_6_write_dataps(float dataps, int decimals);
void nextion_1_home_sensor_7_write_dataps(float dataps, int decimals);
void nextion_1_home_sensor_8_write_dataps(float dataps, int decimals);

void nextion_1_home_sensor_5_write_unit(char *unit);
void nextion_1_home_sensor_6_write_unit(char *unit);
void nextion_1_home_sensor_7_write_unit(char *unit);
void nextion_1_home_sensor_8_write_unit(char *unit);

void nextion_1_home_sensor_5_write_unitps(char *unit);
void nextion_1_home_sensor_6_write_unitps(char *unit);
void nextion_1_home_sensor_7_write_unitps(char *unit);
void nextion_1_home_sensor_8_write_unitps(char *unit);

void nextion_1_calibration_sensor_1_write_data(float data);
void nextion_1_calibration_sensor_2_write_data(float data);
void nextion_1_calibration_sensor_3_write_data(float data);
void nextion_1_calibration_sensor_4_write_data(float data);
void nextion_1_calibration_sensor_5_write_data(float data, int decimals);
void nextion_1_calibration_sensor_6_write_data(float data, int decimals);
void nextion_1_calibration_sensor_7_write_data(float data, int decimals);
void nextion_1_calibration_sensor_8_write_data(float data, int decimals);

void nextion_1_calibration_sensor_5_write_unit(char *unit);
void nextion_1_calibration_sensor_6_write_unit(char *unit);
void nextion_1_calibration_sensor_7_write_unit(char *unit);
void nextion_1_calibration_sensor_8_write_unit(char *unit);

void nextion_1_inputcalibp3_applied0_write(double val, int precision);
void nextion_1_inputcalibp3_applied1_write(double val, int precision);
void nextion_1_inputcalibp3_applied2_write(double val, int precision);
void nextion_1_inputcalibp3_applied3_write(double val, int precision);
void nextion_1_inputcalibp3_applied4_write(double val, int precision);
void nextion_1_inputcalibp3_applied5_write(double val, int precision);
void nextion_1_inputcalibp3_applied6_write(double val, int precision);
void nextion_1_inputcalibp3_applied7_write(double val, int precision);
void nextion_1_inputcalibp3_applied8_write(double val, int precision);
void nextion_1_inputcalibp3_applied9_write(double val, int precision);
void nextion_1_inputcalibp3_applied10_write(double val, int precision);

void nextion_1_inputcalibp3_adc0_write(double val);
void nextion_1_inputcalibp3_adc1_write(double val);
void nextion_1_inputcalibp3_adc2_write(double val);
void nextion_1_inputcalibp3_adc3_write(double val);
void nextion_1_inputcalibp3_adc4_write(double val);
void nextion_1_inputcalibp3_adc5_write(double val);
void nextion_1_inputcalibp3_adc6_write(double val);
void nextion_1_inputcalibp3_adc7_write(double val);
void nextion_1_inputcalibp3_adc8_write(double val);
void nextion_1_inputcalibp3_adc9_write(double val);
void nextion_1_inputcalibp3_adc10_write(double val);
