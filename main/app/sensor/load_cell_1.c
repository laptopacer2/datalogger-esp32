
#include "hx711_async.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "project_tasks.h"
#include "project_typedefs.h"
#include "project_defines.h"

uint32_t last_raw = 0;
uint32_t last_ms = 0;

void IRAM_ATTR data_done_1_cb(uint32_t raw)
{
    // GET RAW PER SECOND
    uint32_t ms = xTaskGetTickCountFromISR();
    int32_t delta_raw = (int32_t)raw - (int32_t)last_raw;
    int32_t deltat_ms = (int32_t)ms - (int32_t)last_ms;
    float rps = (delta_raw * 1000.0) / deltat_ms;

    // SAVE VALUES
    last_raw = raw;
    last_ms = ms;

}

hx711_t load_cell_1 = {
    .mux_pga = HX711_CH_A_GAIN_64,
    .dout_pin = LOADCELL_1_DOUT_PIN,
    .sck_pin = LOADCELL_1_SCK_PIN,
    .data_done_cb = data_done_1_cb,
    .rate_pin = -1,
};
