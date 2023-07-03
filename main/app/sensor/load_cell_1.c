
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

#define TAG "LOAD_CELL_1"

// CALIB PARAMS
calib_params_t calib;

// RAW READINGS AND TIME
static double last_rawps = 0.0;
static int32_t last_raw = 0;
static int32_t last_ms = 0;

// TARA
static int32_t tara_raw = 0;
static double tara_real = 0;

// FLAGS
static bool is_enabled = false;
static bool is_initialized = false;
static bool is_calibrated = false;

void load_cell_data_done_1_cb(uint32_t raw)
{
    // GET RAW PER SECOND
    uint32_t ms = xTaskGetTickCount();
    int32_t delta_raw = (int32_t)raw - last_raw;
    int32_t deltat_ms = (int32_t)ms - last_ms;
    double rawps = (delta_raw * 1000.0) / deltat_ms;

    // SAVE VALUES
    last_raw = (int32_t)raw;
    last_ms = (int32_t)ms;
    last_rawps = rawps;
}

hx711_t load_cell_1 = {
    .mux_pga = HX711_CH_A_GAIN_64,
    .dout_pin = LOADCELL_1_DOUT_PIN,
    .sck_pin = LOADCELL_1_SCK_PIN,
    .data_done_cb = load_cell_data_done_1_cb,
    .rate_pin = -1,
};

void load_cell_1_init()
{
    if (is_initialized)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    is_initialized = true;
    is_enabled = false;

    hx711_init(&load_cell_1);
}

void load_cell_1_enable()
{
    if (is_enabled)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    is_enabled = true;
    hx711_enable(&load_cell_1);
}

void load_cell_1_disable()
{
    if (!is_enabled)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    is_enabled = false;
    hx711_disable(&load_cell_1);
}

bool load_cell_1_is_enabled()
{
    return is_enabled;
}

void load_cell_1_set_tara()
{
    tara_raw = last_raw;
    // todo: calibration
    tara_real = (double)tara_raw;
}
void load_cell_1_clear_tara()
{
    tara_raw = 0;
    tara_real = 0.0;
}
double load_cell_1_get_real()
{
    // todo: calibration
    double last_real = (double)last_raw;
    return last_real - tara_real;
}
double load_cell_1_get_raw()
{
    return (double)last_raw;
}
double load_cell_1_get_rawps()
{
    return last_rawps;
}
double load_cell_1_get_realps()
{
    return last_rawps;
}

bool load_cell_1_is_calibrated()
{
    return is_calibrated;
}

void load_cell_1_get_calib()
{
}
void load_cell_1_set_calib()
{
}