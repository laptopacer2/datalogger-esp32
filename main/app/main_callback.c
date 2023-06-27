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
    nextion_1_init();

    load_cell_1_init();
    load_cell_2_init();
    load_cell_3_init();
    load_cell_4_init();

    dial_big_1_init();
    dial_big_2_init();
    dial_big_3_init();
    dial_big_4_init();



    
}

/*
██╗  ██╗ ██████╗ ███╗   ███╗███████╗
██║  ██║██╔═══██╗████╗ ████║██╔════╝
███████║██║   ██║██╔████╔██║█████╗
██╔══██║██║   ██║██║╚██╔╝██║██╔══╝
██║  ██║╚██████╔╝██║ ╚═╝ ██║███████╗
╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝

*/

void home_loaded_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(HOME);
    nextion_1_start_timer();
}
void home_tara_1_enabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_1_set_tara();
}
void home_tara_1_disabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_1_clear_tara();
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
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_3_set_tara();
}
void home_tara_3_disabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_3_clear_tara();
}
void home_tara_4_enabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_4_set_tara();
}
void home_tara_4_disabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_4_clear_tara();
}

/*
███████╗███████╗████████╗████████╗██╗███╗   ██╗ ██████╗ ███████╗
██╔════╝██╔════╝╚══██╔══╝╚══██╔══╝██║████╗  ██║██╔════╝ ██╔════╝
███████╗█████╗     ██║      ██║   ██║██╔██╗ ██║██║  ███╗███████╗
╚════██║██╔══╝     ██║      ██║   ██║██║╚██╗██║██║   ██║╚════██║
███████║███████╗   ██║      ██║   ██║██║ ╚████║╚██████╔╝███████║
╚══════╝╚══════╝   ╚═╝      ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝

*/

void system_settings_loaded_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(SYSTEM_SETTINGS);
    nextion_1_stop_timer();
}

/*
 ██████╗ █████╗ ██╗     ██╗██████╗ ██████╗  █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
██╔════╝██╔══██╗██║     ██║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
██║     ███████║██║     ██║██████╔╝██████╔╝███████║   ██║   ██║██║   ██║██╔██╗ ██║
██║     ██╔══██║██║     ██║██╔══██╗██╔══██╗██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
╚██████╗██║  ██║███████╗██║██████╔╝██║  ██║██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
 ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

*/

void calibration_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(CALIBRATION);
    nextion_1_start_timer();
}

// SWITCH EVENTS

void calibration_switch_1_disabled_cb(msg_t *msg)
{
    load_cell_1_disable();
}
void calibration_switch_1_enabled_cb(msg_t *msg)
{
    load_cell_1_enable();
}
void calibration_switch_2_disabled_cb(msg_t *msg)
{
    load_cell_2_disable();
}
void calibration_switch_2_enabled_cb(msg_t *msg)
{
    load_cell_2_enable();
}
void calibration_switch_3_disabled_cb(msg_t *msg)
{
    load_cell_3_disable();
}
void calibration_switch_3_enabled_cb(msg_t *msg)
{
    load_cell_3_enable();
}
void calibration_switch_4_disabled_cb(msg_t *msg)
{
    load_cell_4_disable();
}
void calibration_switch_4_enabled_cb(msg_t *msg)
{
    load_cell_4_enable();
}
void calibration_switch_5_disabled_cb(msg_t *msg)
{
    dial_big_1_disable();
}
void calibration_switch_5_enabled_cb(msg_t *msg)
{
    dial_big_1_enable();
}
void calibration_switch_6_disabled_cb(msg_t *msg)
{
    dial_big_2_disable();
}
void calibration_switch_6_enabled_cb(msg_t *msg)
{
    dial_big_2_enable();
}
void calibration_switch_7_disabled_cb(msg_t *msg)
{
    dial_big_3_disable();
}
void calibration_switch_7_enabled_cb(msg_t *msg)
{
    dial_big_3_enable();
}
void calibration_switch_8_disabled_cb(msg_t *msg)
{
    dial_big_4_disable();
}
void calibration_switch_8_enabled_cb(msg_t *msg)
{
    dial_big_4_enable();
}

/*
███████╗██╗  ██╗████████╗███████╗██████╗ ███╗   ██╗ █████╗ ██╗
██╔════╝╚██╗██╔╝╚══██╔══╝██╔════╝██╔══██╗████╗  ██║██╔══██╗██║
█████╗   ╚███╔╝    ██║   █████╗  ██████╔╝██╔██╗ ██║███████║██║
██╔══╝   ██╔██╗    ██║   ██╔══╝  ██╔══██╗██║╚██╗██║██╔══██║██║
███████╗██╔╝ ██╗   ██║   ███████╗██║  ██║██║ ╚████║██║  ██║███████╗
╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝

*/

// UNIT CHANGE EVENT

void external_sensor_5_unit_changed_cb(msg_t *msg)
{
    char *unit = (char *)(msg->content.addr);
    nextion_1_calibration_sensor_5_write_unit(unit);
    nextion_1_home_sensor_5_write_unit(unit);
    free(unit);
}
void external_sensor_6_unit_changed_cb(msg_t *msg)
{
    char *unit = (char *)(msg->content.addr);
    nextion_1_calibration_sensor_6_write_unit(unit);
    nextion_1_home_sensor_6_write_unit(unit);
    free(unit);
}
void external_sensor_7_unit_changed_cb(msg_t *msg)
{
    char *unit = (char *)(msg->content.addr);
    nextion_1_calibration_sensor_7_write_unit(unit);
    nextion_1_home_sensor_7_write_unit(unit);
    free(unit);
}
void external_sensor_8_unit_changed_cb(msg_t *msg)
{
    char *unit = (char *)(msg->content.addr);
    nextion_1_calibration_sensor_8_write_unit(unit);
    nextion_1_home_sensor_8_write_unit(unit);
    free(unit);
}

// UNITPS CHANGE EVENT

void external_sensor_5_unitps_changed_cb(msg_t *msg)
{
    char *unitps = (char *)(msg->content.addr);
    nextion_1_home_sensor_5_write_unitps(unitps);
    free(unitps);
}
void external_sensor_6_unitps_changed_cb(msg_t *msg)
{
    char *unitps = (char *)(msg->content.addr);
    nextion_1_home_sensor_6_write_unitps(unitps);
    free(unitps);
}
void external_sensor_7_unitps_changed_cb(msg_t *msg)
{
    char *unitps = (char *)(msg->content.addr);
    nextion_1_home_sensor_7_write_unitps(unitps);
    free(unitps);
}
void external_sensor_8_unitps_changed_cb(msg_t *msg)
{
    char *unitps = (char *)(msg->content.addr);
    nextion_1_home_sensor_8_write_unitps(unitps);
    free(unitps);
}

/*
███╗   ██╗███████╗██╗  ██╗████████╗██╗ ██████╗ ███╗   ██╗    ████████╗██╗███╗   ███╗███████╗██████╗
████╗  ██║██╔════╝╚██╗██╔╝╚══██╔══╝██║██╔═══██╗████╗  ██║    ╚══██╔══╝██║████╗ ████║██╔════╝██╔══██╗
██╔██╗ ██║█████╗   ╚███╔╝    ██║   ██║██║   ██║██╔██╗ ██║       ██║   ██║██╔████╔██║█████╗  ██████╔╝
██║╚██╗██║██╔══╝   ██╔██╗    ██║   ██║██║   ██║██║╚██╗██║       ██║   ██║██║╚██╔╝██║██╔══╝  ██╔══██╗
██║ ╚████║███████╗██╔╝ ██╗   ██║   ██║╚██████╔╝██║ ╚████║       ██║   ██║██║ ╚═╝ ██║███████╗██║  ██║
╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝       ╚═╝   ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═╝

*/

void nextion_update_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    page_t page = nextion_1_get_page();
    if (page == HOME)
    {
        if (load_cell_1_is_enabled())
        {
            float data = load_cell_1_get_real();
            nextion_1_home_sensor_1_write_data(data);

            float dataps = load_cell_1_get_realps();
            nextion_1_home_sensor_1_write_dataps(dataps);
        }
        if (load_cell_2_is_enabled())
        {
            float data = load_cell_2_get_real();
            nextion_1_home_sensor_2_write_data(data);

            float dataps = load_cell_2_get_realps();
            nextion_1_home_sensor_2_write_dataps(dataps);
        }
        if (load_cell_3_is_enabled())
        {
            float data = load_cell_3_get_real();
            nextion_1_home_sensor_3_write_data(data);

            float dataps = load_cell_3_get_realps();
            nextion_1_home_sensor_3_write_dataps(dataps);
        }
        if (load_cell_4_is_enabled())
        {
            float data = load_cell_4_get_real();
            nextion_1_home_sensor_4_write_data(data);

            float dataps = load_cell_4_get_realps();
            nextion_1_home_sensor_4_write_dataps(dataps);
        }
        if (dial_big_1_is_enabled())
        {
            float real = dial_big_1_get_real();
            int decimals = dial_big_1_get_decimals();
            nextion_1_home_sensor_5_write_data(real, decimals);

            float realps = dial_big_1_get_realps();
            nextion_1_home_sensor_5_write_dataps(realps, decimals);
        }
        if (dial_big_2_is_enabled())
        {
            float real = dial_big_2_get_real();
            int decimals = dial_big_2_get_decimals();
            nextion_1_home_sensor_6_write_data(real, decimals);

            float realps = dial_big_2_get_realps();
            nextion_1_home_sensor_6_write_dataps(realps, decimals);
        }
        if (dial_big_3_is_enabled())
        {
            float real = dial_big_3_get_real();
            int decimals = dial_big_3_get_decimals();
            nextion_1_home_sensor_7_write_data(real, decimals);

            float realps = dial_big_3_get_realps();
            nextion_1_home_sensor_7_write_dataps(realps, decimals);
        }
        if (dial_big_4_is_enabled())
        {
            float real = dial_big_4_get_real();
            int decimals = dial_big_4_get_decimals();
            nextion_1_home_sensor_8_write_data(real, decimals);

            float realps = dial_big_4_get_realps();
            nextion_1_home_sensor_8_write_dataps(realps, decimals);
        }
    }
    else if (page == CALIBRATION)
    {
        if (load_cell_1_is_enabled())
        {
            float data = load_cell_1_get_real();
            nextion_1_calibration_sensor_1_write_data(data);
        }
        if (load_cell_2_is_enabled())
        {
            float data = load_cell_2_get_real();
            nextion_1_calibration_sensor_2_write_data(data);
        }
        if (load_cell_3_is_enabled())
        {
            float data = load_cell_3_get_real();
            nextion_1_calibration_sensor_3_write_data(data);
        }
        if (load_cell_4_is_enabled())
        {
            float data = load_cell_4_get_real();
            nextion_1_calibration_sensor_4_write_data(data);
        }
        if (dial_big_1_is_enabled())
        {
            float data = dial_big_1_get_real();
            int decimals = dial_big_1_get_decimals();
            nextion_1_calibration_sensor_5_write_data(data, decimals);
        }
        if (dial_big_2_is_enabled())
        {
            float data = dial_big_2_get_real();
            int decimals = dial_big_2_get_decimals();
            nextion_1_calibration_sensor_6_write_data(data, decimals);
        }
        if (dial_big_3_is_enabled())
        {
            float data = dial_big_3_get_real();
            int decimals = dial_big_3_get_decimals();
            nextion_1_calibration_sensor_7_write_data(data, decimals);
        }
        if (dial_big_4_is_enabled())
        {
            float data = dial_big_4_get_real();
            int decimals = dial_big_4_get_decimals();
            nextion_1_calibration_sensor_8_write_data(data, decimals);
        }
    }
    else
    {
        ESP_LOGW(TAG, "%s", __func__);
    }
}