
#include "hx711_async.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "project_tasks.h"
#include "project_typedefs.h"
#include "project_defines.h"
#include "esp_log.h"
#include "calibration.h"
#include "freertos/semphr.h"
#include "configuration.h"

#define TAG "LOAD_CELL_4"

// mutex
static SemaphoreHandle_t mutex;

// CALIB PARAMS
static calib_params_t calib;

// RAW READINGS AND TIME
static double last_rawps = 0.0;
static int32_t last_raw = 0;
static int32_t last_ms = 0;

// REAL AND REALPS
static double last_real = 0.0;
static double last_realps = 0.0;

// SENSOR CONFIG
static sensor_config_t config;

// FLAGS
static bool is_initialized = false;
static bool is_calibrated = false;

static double calculate_real(uint32_t raw)
{
    // variable
    double y = 0.0;
    double x = (double)raw;

    // get total points
    int total_points;
    if (calib.num_points == NUM_POINTS_1)
        total_points = 1;
    else if (calib.num_points == NUM_POINTS_5)
        total_points = 5;
    else
        total_points = 10;

    // if x got lower than x_min
    double x_min = calib.table[0][1];
    bool out_of_range_lower = (x < x_min);
    if (out_of_range_lower)
    {
        double y1 = calib.table[1][0];
        double y0 = calib.table[0][0];
        double x1 = calib.table[1][1];
        double x0 = calib.table[0][1];
        double m = (y1 - y0) / (x1 - x0);
        double delta_x = x - x0;
        y = y0 + m * delta_x;
        y = (y < 0.0) ? 0.0 : y;
        goto end;
    }

    // if x got higher than x_max
    double x_max = calib.table[total_points][1];
    bool out_of_range_upper = (x > x_max);
    if (out_of_range_upper)
    {
        double y1 = calib.table[total_points][0];
        double y0 = calib.table[total_points - 1][0];
        double x1 = calib.table[total_points][1];
        double x0 = calib.table[total_points - 1][1];
        double m = (y1 - y0) / (x1 - x0);
        double delta_x = x - x0;
        y = y0 + m * delta_x;
        y = (y < 0.0) ? 0.0 : y;
        goto end;
    }

    // if x got in range
    for (int i = 0; i < total_points; i++)
    {
        double x1 = calib.table[i + 1][1];
        double x0 = calib.table[i][1];
        if ((x > x0) && (x < x1))
        {
            double y1 = calib.table[i + 1][0];
            double y0 = calib.table[i][0];
            double m = (y1 - y0) / (x1 - x0);
            double delta_x = x - x0;
            y = y0 + m * delta_x;
            y = (y < 0.0) ? 0.0 : y;
            goto end;
        }
    }

end:
    return y;
}
void load_cell_data_done_4_cb(uint32_t raw)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    // GET RAW PER SECOND
    uint32_t ms = xTaskGetTickCount();
    int32_t delta_raw = (int32_t)raw - last_raw;
    int32_t deltat_ms = (int32_t)ms - last_ms;
    double rawps = (delta_raw * 1000.0) / deltat_ms;

    // SAVE VALUES
    last_raw = (int32_t)raw;
    last_ms = (int32_t)ms;
    last_rawps = rawps;

    if (is_calibrated)
    {
        // GET REAL and REALPS
        double real = calculate_real(raw);
        double delta_real = real - last_real;
        double realps = (delta_real * 1000.0) / deltat_ms;

        // SAVE VALUES
        last_real = real;
        last_realps = realps;
    }

    xSemaphoreGive(mutex);
}

hx711_t load_cell_4 = {
    .mux_pga = HX711_CH_A_GAIN_64,
    .dout_pin = LOADCELL_4_DOUT_PIN,
    .sck_pin = LOADCELL_4_SCK_PIN,
    .data_done_cb = load_cell_data_done_4_cb,
    .rate_pin = -1,
};

void load_cell_4_init()
{
    if (is_initialized)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    is_initialized = true;
    config = SENSOR_CONFIG_DEFAULT;

    hx711_init(&load_cell_4);

    mutex = xSemaphoreCreateMutex();
}

void load_cell_4_enable()
{
    if (config.is_sensor_enabled)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    config.is_sensor_enabled = true;
    hx711_enable(&load_cell_4);
}

void load_cell_4_disable()
{
    if (!config.is_sensor_enabled)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    config.is_sensor_enabled = false;
    hx711_disable(&load_cell_4);
}

bool load_cell_4_is_enabled()
{
   return config.is_sensor_enabled;
}

void load_cell_4_set_tara()
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    config.tara_val = last_real;
    xSemaphoreGive(mutex);
    config.is_tara_enabled = true;
}
double load_cell_4_get_tara()
{
  return config.tara_val;  
}
void load_cell_4_clear_tara()
{
    config.tara_val = 0.0;
    config.is_tara_enabled = false;
}
double load_cell_4_get_real()
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    double r = last_real - config.tara_val;
    xSemaphoreGive(mutex);
    return r;
}
double load_cell_4_get_raw()
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    double r = (double)last_raw;
    xSemaphoreGive(mutex);
    return r;
}
double load_cell_4_get_rawps()
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    double r = last_rawps;
    xSemaphoreGive(mutex);
    return r;
}
double load_cell_4_get_realps()
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    double r = last_realps;
    xSemaphoreGive(mutex);
    return r;
}
bool load_cell_4_is_calibrated()
{
    return is_calibrated;
}
void load_cell_4_set_calib(calib_params_t *in)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    calib = *in;
    xSemaphoreGive(mutex);

    is_calibrated = true;
}
sensor_config_t *load_cell_4_get_config()
{
    return &config;
}
void load_cell_4_set_config(sensor_config_t *in)
{
    config = *in;
}