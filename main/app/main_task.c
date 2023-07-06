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
        else if(type ==CALIBRATION_SENSOR_1_UNIT_CHANGED)
            calibration_sensor_1_unit_changed_cb(&msg);
        else if(type ==CALIBRATION_SENSOR_2_UNIT_CHANGED)
            calibration_sensor_2_unit_changed_cb(&msg);
        else if(type ==CALIBRATION_SENSOR_3_UNIT_CHANGED)
            calibration_sensor_3_unit_changed_cb(&msg);
        else if(type ==CALIBRATION_SENSOR_4_UNIT_CHANGED)
            calibration_sensor_4_unit_changed_cb(&msg);
        // INPUT CALIB P1
        else if (type == INPUTCALIBP1_LOADED)
            inputcalibp1_loaded_cb(&msg);
        else if (type == INPUTCALIBP1_TYPE_RECEIVED)
            inputcalibp1_type_received_cb(&msg);
        else if (type == INPUTCALIBP1_CAPACITY_RECEIVED)
            inputcalibp1_capacity_received_cb(&msg);
        else if (type == INPUTCALIBP1_CAPACITY_UNIT_RECEIVED)
            inputcalibp1_capacity_unit_received_cb(&msg);
        else if (type == INPUTCALIBP1_SENSIBILITY_RECEIVED)
            inputcalibp1_sensibility_received_cb(&msg);
        else if (type == INPUTCALIBP1_SENSIBILITY_UNIT_RECEIVED)
            inputcalibp1_sensibility_unit_received_cb(&msg);
        else if (type == INPUTCALIBP1_SENSOR_INDEX_RECEIVED)
            inputcalibp1_sensor_index_received(&msg);
        // INPUT CALIB P2
        else if (type == INPUTCALIBP2_LOADED)
            inputcalibp2_loaded_cb(&msg);
        else if (type == INPUTCALIBP2_CALIBRATION_LIMIT_RECEIVED)
            inputcalibp2_calibration_limit_received_cb(&msg);
        else if (type == INPUTCALIBP2_CALIBRATION_LIMIT_UNIT_RECEIVED)
            inputcalibp2_calibration_limit_unit_received_cb(&msg);
        else if (type == INPUTCALIBP2_LIMIT_ENABLE_RECEIVED)
            inputcalibp2_limit_enable_receive_cb(&msg);
        // INPUT CALIB P3
        else if (type == INPUTCALIBP3_LOADED)
            inputcalibp3_loaded_cb(&msg);
        else if (type == INPUTCALIBP3_TABLE_RECEIVED)
            inputcalibp3_table_received(&msg);
        else if (type == INPUTCALIBP3_NUM_POINTS_RECEIVED)
            inputcalibp3_num_points_received(&msg);
        else if (type == INPUTCALIBP3_ROW_TO_FILL_RECEIVED)
            inputcalibp3_row_to_fill_received(&msg);
        // INPUT CALIB P4
        else if (type == INPUTCALIBP4_LOADED)
            inputcalibp4_loaded_cb(&msg);
        else if (type == INPUTCALIBP4_NAME_RECEIVED)
            inputcalibp4_name_received_cb(&msg);
        else if (type == INPUTCALIBP4_SAVE_PRESSED)
            inputcalibp4_save_pressed_cb(&msg);
        // NUMPAD POPUP 
        else if(type == NUMPAD_POPUP_LOADED)
            numpad_popup_loaded_cb(&msg);

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