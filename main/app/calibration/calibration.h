#pragma once
#include "stdint.h"
#include "project_defines.h"
#include "stddef.h"
#include "esp_err.h"

typedef enum
{
    DISPLACEMENT,
    LOAD,
    PRESSURE,
    VOLUME,
    SENSOR_TYPE_MAX,
} sensor_type_t;
typedef enum
{
    DISPLACEMENT_UNIT_CM,
    DISPLACEMENT_UNIT_IN,
    DISPLACEMENT_UNIT_MM,
    LOAD_UNIT_KN,
    LOAD_UNIT_LBF,
    LOAD_UNIT_N,
    LOAD_UNIT_KGF,
    PRESSURE_UNIT_KPA,
    PRESSURE_UNIT_PSI,
    PRESSURE_UNIT_KSF,
    PRESSURE_UNIT_MPA,
    PRESSURE_UNIT_KGF_CM2,
    VOLUME_UNIT_CM3,
    VOLUME_UNIT_IN3,
    SENSOR_UNIT_MAX,
} sensor_unit_t;
typedef enum
{
    SENSIBILITY_UNIT_MV_V,
    SENSIBILITY_UNIT_V_V,
    SENSIBILITY_UNIT_MAX,
} sensor_sensibility_unit_t;
typedef enum
{
    NUM_POINTS_1 = 1,
    NUM_POINTS_5 = 5,
    NUM_POINTS_10 = 10,
    NUM_POINTS_CUSTOM = 0XFE,
    NUM_POINTS_MAX = 0XFF,
} calib_points_num_t;
typedef struct
{
    sensor_type_t sensor_type;
    double capacity;
    sensor_unit_t unit;
    double sensibility_val;
    sensor_sensibility_unit_t sensibility_unit;
    double limit_val;
    bool limit_enabled;
    double table[11][2];
    calib_points_num_t num_points;
    char name[CALIB_NAME_LEN_MAX + 1];
    int name_len;
    int num_decimals;
} sensor_calib_t;

#define SENSOR_CALIB_DEFAULT                      \
    (sensor_calib_t)                              \
    {                                             \
        .sensor_type = SENSOR_TYPE_MAX,           \
        .capacity = 0.0,                          \
        .unit = SENSOR_UNIT_MAX,                  \
        .sensibility_val = 0.0,                   \
        .sensibility_unit = SENSIBILITY_UNIT_MAX, \
        .limit_val = 0.0,                         \
        .limit_enabled = false,                   \
        .num_points = NUM_POINTS_CUSTOM,          \
        .name_len = 0,                            \
        .num_decimals = 0,                        \
    }

typedef char(row_t)[TABLE_NUM_COLS][15];
typedef row_t *table_t;

typedef enum
{
    ROW_0_TO_FILL,
    ROW_1_TO_FILL,
    ROW_2_TO_FILL,
    ROW_3_TO_FILL,
    ROW_4_TO_FILL,
    ROW_5_TO_FILL,
    ROW_6_TO_FILL,
    ROW_7_TO_FILL,
    ROW_8_TO_FILL,
    ROW_9_TO_FILL,
    ROW_10_TO_FILL,
    ROW_NOT_TO_FILL,
} row_to_fill_t;

void inputCalib_init();
void inputCalib_set_sensor_type(char *type_str);
void inputCalib_set_capacity(char *capacity_str);
void inputCalib_set_unit(char *unit_str);
void inputCalib_set_sensibility(char *sensibility_str);
void inputCalib_set_sensibility_unit(char *unit_str);
void inputCalib_set_limit(char *limit_str);
void inputCalib_set_limit_enable(void *limit_enable);
void inputCalib_set_table(char *table_str);
table_t inputCalib_set_num_points(char *num_points_str);
void inputCalib_set_row_to_fill(void *_row_to_fill);
void inputCalib_set_name(char *name_str);
esp_err_t inputCalib_save(char **info);
esp_err_t inputCalib_load(int i, sensor_calib_t *out);
void inputCalib_delete(int i);
esp_err_t inputCalib_load_last_saved(int *i, sensor_calib_t *out);
int inputCalib_get_num_decimals();
void inputCalib_set_index(void *i);
int inputCalib_get_index();
row_to_fill_t inputCalib_get_row_to_fill();

// AUXILIAR FUNCTIONS
//char *inputCalib_unit_to_str(sensor_unit_t unit, sensor_type_t type);
//char *inputCalib_unitps_to_str(sensor_unit_t unit);
//char *inputCalib_combobox_path_from_type(sensor_type_t type);
//int inputCalib_combobox_val_from_unit(sensor_unit_t unit);
//esp_err_t inputCalib_get_sensor_unit_from_str(char *unit_str, sensor_unit_t *unit, sensor_type_t *type);
//double inputCalib_get_fc(sensor_unit_t unit_from, sensor_unit_t unit_to, sensor_type_t type);
