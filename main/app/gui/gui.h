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