#pragma once

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

calib_res_t calib_storage_init();
calib_res_t calib_sensor_1_get(calib_params_t *out);
calib_res_t calib_sensor_1_set(calib_params_t *in);
calib_res_t calib_sensor_2_get(calib_params_t *out);
calib_res_t calib_sensor_2_set(calib_params_t *in);
calib_res_t calib_sensor_3_get(calib_params_t *out);
calib_res_t calib_sensor_3_set(calib_params_t *in);
calib_res_t calib_sensor_4_get(calib_params_t *out);
calib_res_t calib_sensor_4_set(calib_params_t *in);