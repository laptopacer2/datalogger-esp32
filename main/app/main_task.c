#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "project_defines.h"
#include "project_typedefs.h"
#include "main_callback.h"
#include "sensor.h"
#include "project_tasks.h"
#include "project_defines.h"
#include "sensor.h"
#include "driver/gpio.h"

#define TAG "MAIN_TASK"

QueueHandle_t main_queue = NULL;
static msg_t msg;

void main_task(void *arg)
{
    ESP_LOGI(TAG, TAG);
    main_queue = xQueueCreate(20, sizeof(msg_t));

    main_task_init();

    while (1)
    {
        xQueueReceive(main_queue, &msg, portMAX_DELAY);
        msg_type_t type = msg.type;

        // NEXTION MESSAGES
        if (type == HOME_LOADED)
            home_loaded_cb(&msg);
        else if (type == HOME_TARA_1_ENABLED)
            home_tara_1_enabled_cb(&msg);
        else if (type == HOME_TARA_1_DISABLED)
            home_tara_1_disabled_cb(&msg);
        else if (type == HOME_TARA_2_ENABLED)
            home_tara_2_enabled_cb(&msg);
        else if (type == HOME_TARA_2_DISABLED)
            home_tara_2_disabled_cb(&msg);
        else if (type == HOME_TARA_3_ENABLED)
            home_tara_3_enabled_cb(&msg);
        else if (type == HOME_TARA_3_DISABLED)
            home_tara_3_disabled_cb(&msg);
        else if (type == HOME_TARA_4_ENABLED)
            home_tara_4_enabled_cb(&msg);
        else if (type == HOME_TARA_4_DISABLED)
            home_tara_4_disabled_cb(&msg);
        else if (type == SYSTEM_SETTINGS_LOADED)
            system_settings_loaded_cb(&msg);
        else if (type == CALIBRATION_LOADED)
            calibration_loaded_cb(&msg);
        else if (type == CALIBRATION_SWITCH_1_DISABLED)
            calibration_switch_1_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_1_ENABLED)
            calibration_switch_1_enabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_2_DISABLED)
            calibration_switch_2_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_2_ENABLED)
            calibration_switch_2_enabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_3_DISABLED)
            calibration_switch_3_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_3_ENABLED)
            calibration_switch_3_enabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_4_DISABLED)
            calibration_switch_4_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_4_ENABLED)
            calibration_switch_4_enabled_cb(&msg);
        else if (type == NEXTION_UPDATE)
            nextion_update_cb(&msg);
        else
        {
            ESP_LOGE(TAG, "file:%s,line:%u", __FILE__, __LINE__);
        }
    }
}
/*
1 2 3 4
5 6 7 8
*/