#pragma once
#include "stdbool.h"
#include "calibration.h"
#include "esp_err.h"

typedef struct
{
    int num_decimals;
    double unit_fc;
    sensor_unit_t unit;
    // char *unit_str;
    // char *unitps_str;
    bool is_tara_enabled;
    double tara_val;
    bool is_sensor_enabled;
    bool is_limit_enabled;
} sensor_config_t;

#define SENSOR_CONFIG_DEFAULT       \
    (sensor_config_t)               \
    {                               \
        .num_decimals = 0,          \
        .unit_fc = 1.0,             \
        .unit = SENSOR_UNIT_MAX,    \
        .is_tara_enabled = false,   \
        .tara_val = 0.0,            \
        .is_sensor_enabled = false, \
        .is_limit_enabled = false,  \
    }
esp_err_t config_sensor_save(int index, sensor_config_t *config);
esp_err_t config_sensor_load(int index, sensor_config_t *config);
esp_err_t config_sensor_delete(int index);
esp_err_t config_get_unit_from_str(char *unit_str, sensor_unit_t *unit);
bool config_is_unit_ok(sensor_unit_t unit, sensor_type_t type);
double config_get_fc(sensor_unit_t old_unit, sensor_unit_t new_unit, sensor_type_t type);
