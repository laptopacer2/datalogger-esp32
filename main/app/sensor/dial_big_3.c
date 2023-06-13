
#include "dial_big_async.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "project_tasks.h"
#include "project_typedefs.h"
#include "project_defines.h"
#include "esp_log.h"

#define TAG "DIAL_BIG_3"

static dialbig_unit_t last_unit = DIAL_BIG_UNIT_MAX;
static int last_decimals = DIALBIG_DECIMALS_MAX;
static float last_realps = 0.0;
static float last_real = 0.0;
static int32_t last_ms = 0;

static bool is_enabled = false;
static bool is_initialized = false;

void dial_big_data_done_3_cb(dialbig_data_t new_real)
{
    //ESP_LOGI(TAG, "new real 1: %.4f", new_real.val);
    bool dial_unit_changed = (last_unit != new_real.unit);

    // GET REAL PER SECOND
    uint32_t ms = xTaskGetTickCount();
    float delta_real = ((!dial_unit_changed) ? new_real.val - last_real : 0.0);
    int32_t deltat_ms = (int32_t)ms - last_ms;
    float realps = (delta_real * 1000.0) / deltat_ms;

    // SAVE VALUES
    last_real = new_real.val;
    last_unit = new_real.unit;
    last_ms = (int32_t)ms;
    last_realps = realps;
    last_decimals = new_real.decimals;

    //
    if (dial_unit_changed)
    {
        {
            char *unit = (char *)malloc(10 * sizeof(char));
            snprintf(unit, 10 * sizeof(char), "%s", last_unit == DIALBIG_MM ? "mm" : "inch");
            msg_t msg;
            msg.type = EXTERNAL_SENSOR_7_UNIT_CHANGED;
            msg.content.addr = (void *)unit;
            xQueueSend(main_queue, &msg, portMAX_DELAY);
        }

        {
            char *unitps = (char *)malloc(8 * sizeof(char));
            snprintf(unitps, 10 * sizeof(char), "%s", last_unit == DIALBIG_MM ? "mm/s" : "inch/s");
            msg_t msg;
            msg.type = EXTERNAL_SENSOR_7_UNITPS_CHANGED;
            msg.content.addr = (void *)unitps;
            xQueueSend(main_queue, &msg, portMAX_DELAY);
        }
    }
}

dialbig_t dial_big_3 = {
    .data_done_cb = dial_big_data_done_3_cb,
    .data_pin = DIALBIG_3_DATA_PIN,
    .clk_pin = DIALBIG_3_CLK_PIN,
    .req_pin = DIALBIG_3_REQ_PIN,
};

void dial_big_3_init()
{
    if (is_initialized)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    is_initialized = true;
    is_enabled = false;

    dialbig_init(&dial_big_3);
}

void dial_big_3_enable()
{
    if (is_enabled)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    is_enabled = true;
    dialbig_enable(&dial_big_3);
}

void dial_big_3_disable()
{
    if (!is_enabled)
    {
        ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    is_enabled = false;
    dialbig_disable(&dial_big_3);
}

bool dial_big_3_is_enabled()
{
    return is_enabled;
}

float dial_big_3_get_real()
{
    return last_real;
}

float dial_big_3_get_realps()
{
    return last_realps;
}
int dial_big_3_get_decimals(){
    return last_decimals;
}