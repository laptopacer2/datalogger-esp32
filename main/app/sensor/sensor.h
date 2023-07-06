#pragma once

#include "stdbool.h"
#include "dial_big_async.h"
#include "calibration.h"
#include "configuration.h"

void load_cell_1_init();
void load_cell_1_enable();
void load_cell_1_disable();
bool load_cell_1_is_enabled();
void load_cell_1_set_tara();
double load_cell_1_get_tara();
void load_cell_1_clear_tara();
double load_cell_1_get_real();
double load_cell_1_get_raw();
double load_cell_1_get_rawps();
double load_cell_1_get_realps();
bool load_cell_1_is_calibrated();
void load_cell_1_set_calib(calib_params_t *in);
sensor_config_t *load_cell_1_get_config();
void load_cell_1_set_config(sensor_config_t *in);
double load_cell_1_get_capacity();
double load_cell_1_get_calib_decimals();
sensor_unit_t load_cell_1_get_unit_from_calib();

void load_cell_2_init();
void load_cell_2_enable();
void load_cell_2_disable();
bool load_cell_2_is_enabled();
void load_cell_2_set_tara();
double load_cell_2_get_tara();
void load_cell_2_clear_tara();
double load_cell_2_get_real();
double load_cell_2_get_raw();
double load_cell_2_get_rawps();
double load_cell_2_get_realps();
bool load_cell_2_is_calibrated();
void load_cell_2_set_calib(calib_params_t *in);
sensor_config_t *load_cell_2_get_config();
void load_cell_2_set_config(sensor_config_t *in);

void load_cell_3_init();
void load_cell_3_enable();
void load_cell_3_disable();
bool load_cell_3_is_enabled();
void load_cell_3_set_tara();
double load_cell_3_get_tara();
void load_cell_3_clear_tara();
double load_cell_3_get_real();
double load_cell_3_get_raw();
double load_cell_3_get_rawps();
double load_cell_3_get_realps();
bool load_cell_3_is_calibrated();
void load_cell_3_set_calib(calib_params_t *in);
sensor_config_t *load_cell_3_get_config();
void load_cell_3_set_config(sensor_config_t *in);

void load_cell_4_init();
void load_cell_4_enable();
void load_cell_4_disable();
bool load_cell_4_is_enabled();
void load_cell_4_set_tara();
double load_cell_4_get_tara();
void load_cell_4_clear_tara();
double load_cell_4_get_real();
double load_cell_4_get_raw();
double load_cell_4_get_rawps();
double load_cell_4_get_realps();
bool load_cell_4_is_calibrated();
void load_cell_4_set_calib(calib_params_t *in);
sensor_config_t *load_cell_4_get_config();
void load_cell_4_set_config(sensor_config_t *in);

void dial_big_1_init();
void dial_big_1_enable();
void dial_big_1_disable();
bool dial_big_1_is_enabled();
float dial_big_1_get_real();
float dial_big_1_get_realps();
int dial_big_1_get_decimals();
bool dial_big_1_is_calibrated();

void dial_big_2_init();
void dial_big_2_enable();
void dial_big_2_disable();
bool dial_big_2_is_enabled();
float dial_big_2_get_real();
float dial_big_2_get_realps();
int dial_big_2_get_decimals();
bool dial_big_2_is_calibrated();

void dial_big_3_init();
void dial_big_3_enable();
void dial_big_3_disable();
bool dial_big_3_is_enabled();
float dial_big_3_get_real();
float dial_big_3_get_realps();
int dial_big_3_get_decimals();
bool dial_big_3_is_calibrated();

void dial_big_4_init();
void dial_big_4_enable();
void dial_big_4_disable();
bool dial_big_4_is_enabled();
float dial_big_4_get_real();
float dial_big_4_get_realps();
int dial_big_4_get_decimals();
bool dial_big_4_is_calibrated();