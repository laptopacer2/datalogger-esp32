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

        // HOME
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
        // SETTINGS
        else if (type == SYSTEM_SETTINGS_LOADED)
            system_settings_loaded_cb(&msg);
        // CALIBRATION
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
        else if (type == CALIBRATION_SWITCH_5_DISABLED)
            calibration_switch_5_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_5_ENABLED)
            calibration_switch_5_enabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_6_DISABLED)
            calibration_switch_6_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_6_ENABLED)
            calibration_switch_6_enabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_7_DISABLED)
            calibration_switch_7_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_7_ENABLED)
            calibration_switch_7_enabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_8_DISABLED)
            calibration_switch_8_disabled_cb(&msg);
        else if (type == CALIBRATION_SWITCH_8_ENABLED)
            calibration_switch_8_enabled_cb(&msg);

        // EXTERNAL ( SENSORS, ...)
        else if (type == EXTERNAL_SENSOR_5_UNIT_CHANGED)
            external_sensor_5_unit_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_6_UNIT_CHANGED)
            external_sensor_6_unit_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_7_UNIT_CHANGED)
            external_sensor_7_unit_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_8_UNIT_CHANGED)
            external_sensor_8_unit_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_5_UNITPS_CHANGED)
            external_sensor_5_unitps_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_6_UNITPS_CHANGED)
            external_sensor_6_unitps_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_7_UNITPS_CHANGED)
            external_sensor_7_unitps_changed_cb(&msg);
        else if (type == EXTERNAL_SENSOR_8_UNITPS_CHANGED)
            external_sensor_8_unitps_changed_cb(&msg);
            
        // NEXTION-TIMER
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