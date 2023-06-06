#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "project_defines.h"
#include "project_typedefs.h"
#include "project_tasks.h"
#include "sensor.h"
#include "gui.h"

#define TAG "MAIN_CALLBACK"

/*
██╗███╗   ██╗██╗████████╗
██║████╗  ██║██║╚══██╔══╝
██║██╔██╗ ██║██║   ██║
██║██║╚██╗██║██║   ██║
██║██║ ╚████║██║   ██║
╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝

*/

void main_task_init()
{
    load_cell_2_init();

    nextion_1_init();
}

/*
███╗   ██╗███████╗██╗  ██╗████████╗██╗ ██████╗ ███╗   ██╗     ██████╗ █████╗ ██╗     ██╗     ██████╗  █████╗  ██████╗██╗  ██╗
████╗  ██║██╔════╝╚██╗██╔╝╚══██╔══╝██║██╔═══██╗████╗  ██║    ██╔════╝██╔══██╗██║     ██║     ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝
██╔██╗ ██║█████╗   ╚███╔╝    ██║   ██║██║   ██║██╔██╗ ██║    ██║     ███████║██║     ██║     ██████╔╝███████║██║     █████╔╝
██║╚██╗██║██╔══╝   ██╔██╗    ██║   ██║██║   ██║██║╚██╗██║    ██║     ██╔══██║██║     ██║     ██╔══██╗██╔══██║██║     ██╔═██╗
██║ ╚████║███████╗██╔╝ ██╗   ██║   ██║╚██████╔╝██║ ╚████║    ╚██████╗██║  ██║███████╗███████╗██████╔╝██║  ██║╚██████╗██║  ██╗
╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝     ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝

*/

void home_loaded_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(HOME);
    nextion_1_start_timer();
}
void home_tara_1_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_1_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_2_enabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_2_set_tara();
}
void home_tara_2_disabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_2_clear_tara();
}
void home_tara_3_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_3_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_4_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_4_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_5_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_5_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_6_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_6_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_7_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_7_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_8_enabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void home_tara_8_disabled_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
}
void system_settings_loaded_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(SYSTEM_SETTINGS);
    nextion_1_stop_timer();
}
void calibration_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(CALIBRATION);
    nextion_1_start_timer();
}

void calibration_switch_2_disabled_cb(msg_t *msg)
{
    load_cell_2_disable();
}
void calibration_switch_2_enabled_cb(msg_t *msg)
{
    load_cell_2_enable();
}

void nextion_update_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    page_t page = nextion_1_get_page();
    if (page == HOME)
    {
        if (load_cell_2_is_enabled())
        {
            float data = load_cell_2_get_real();
            nextion_1_home_sensor_2_write_data(data);

            float dataps = load_cell_2_get_realps();
            nextion_1_home_sensor_2_write_dataps(dataps);
        }
    }
    else if (page == CALIBRATION)
    {
        if (load_cell_2_is_enabled())
        {
            float data = load_cell_2_get_real();
            nextion_1_calibration_sensor_2_write_data(data);
        }
    }
    else
    {
        ESP_LOGW(TAG, "%s", __func__);
    }
}