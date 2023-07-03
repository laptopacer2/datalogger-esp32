#pragma once
#include "stdint.h"
typedef struct
{
    float raw;
    float real;
} calib_dot_t;
typedef struct
{
    // name
    char name[30 + 1];
    // multi point curve
    calib_dot_t dot[11];
    int dots_num;
    // sensor details
    int unit;
    int capacity;
    int sensibility_val;
    int sensibility_unit;
    int decimals_num;
} calib_params_t;

typedef enum
{
    CALIB_ERRROR,
    CALIB_OK,
} calib_res_t;
typedef enum
{
    NUM_POINTS_1 = 1,
    NUM_POINTS_5 = 5,
    NUM_POINTS_10 = 10,
    NUM_POINTS_CUSTOM = 0XFE,
    NUM_POINTS_MAX = 0XFF,
} calib_points_num_t;

typedef double (*row_t)[2];
typedef row_t table_t;

calib_res_t calib_storage_init();
calib_res_t calib_sensor_1_get(calib_params_t *out);
calib_res_t calib_sensor_1_set(calib_params_t *in);
calib_res_t calib_sensor_2_get(calib_params_t *out);
calib_res_t calib_sensor_2_set(calib_params_t *in);
calib_res_t calib_sensor_3_get(calib_params_t *out);
calib_res_t calib_sensor_3_set(calib_params_t *in);
calib_res_t calib_sensor_4_get(calib_params_t *out);
calib_res_t calib_sensor_4_set(calib_params_t *in);

void inputCalib_set_sensor_type(char *type_str);
void inputCalib_set_capacity(char *capacity_str);
void inputCalib_set_data_unit(char *unit_str);
void inputCalib_set_sensibility(char *sensibility_str);
void inputCalib_set_sensibility_unit(char *unit_str);
void inputCalib_set_limit(char *limit_str);
void inputCalib_set_limit_enable(void *limit_enable);
void inputCalib_set_table(char *table_str);
table_t inputCalib_set_num_points(char *num_points_str);
void inputCalib_set_row_to_fill(void *row_to_fill);
void inputCalib_set_name(char *name);
void inputCalib_save();
int inputCalib_get_decimals_precision();
void inputCalib_set_sensor_index(void *index);
uint8_t inputCalib_get_sensor_index();
uint8_t inputCalib_get_row_to_fill();