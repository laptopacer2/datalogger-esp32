#pragma once
#include "stdbool.h"
#include "calibration.h"
#include "esp_err.h"

typedef struct
{
    int decimals_precision;
    double unit_fc;
    char *unit_str;
    char *unitps_str;
    bool is_tara_enabled;
    double tara_val;
    bool is_sensor_enabled;
    bool is_limit_enabled;
} sensor_config_t;

#define SENSOR_CONFIG_DEFAULT           \
    (sensor_config_t)                   \
    {                                   \
        .decimals_precision = 0,        \
        .unit_fc = 1.0,                 \
        .unit_str = "N.A.",             \
        .is_tara_enabled = false,       \
        .tara_val = 0.0,                \
        .is_sensor_enabled = false,     \
        .is_limit_enabled = false,      \
    }

void config_sensor_1_save(sensor_config_t *config);
void config_sensor_2_save(sensor_config_t *config);
void config_sensor_3_save(sensor_config_t *config);
void config_sensor_4_save(sensor_config_t *config);
void config_sensor_5_save(sensor_config_t *config);
void config_sensor_6_save(sensor_config_t *config);
void config_sensor_7_save(sensor_config_t *config);
void config_sensor_8_save(sensor_config_t *config);

esp_err_t config_sensor_1_load(sensor_config_t *config);
esp_err_t config_sensor_2_load(sensor_config_t *config);
esp_err_t config_sensor_3_load(sensor_config_t *config);
esp_err_t config_sensor_4_load(sensor_config_t *config);
esp_err_t config_sensor_5_load(sensor_config_t *config);
esp_err_t config_sensor_6_load(sensor_config_t *config);
esp_err_t config_sensor_7_load(sensor_config_t *config);
esp_err_t config_sensor_8_load(sensor_config_t *config);
