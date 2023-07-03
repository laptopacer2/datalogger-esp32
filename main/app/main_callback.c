#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "project_defines.h"
#include "project_typedefs.h"
#include "project_tasks.h"
#include "sensor.h"
#include "gui.h"
#include "calibration.h"


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
    // ESP_LOGI(TAG, "%s", __func__);
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
    // ESP_LOGI(TAG, "%s", __func__);
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
    //ESP_LOGI(TAG, "%s", __func__);
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
██╗███╗   ██╗██████╗ ██╗   ██╗████████╗     ██████╗ █████╗ ██╗     ██╗██████╗     ██████╗  ██╗
██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔════╝██╔══██╗██║     ██║██╔══██╗    ██╔══██╗███║
██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║     ███████║██║     ██║██████╔╝    ██████╔╝╚██║
██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║     ██╔══██║██║     ██║██╔══██╗    ██╔═══╝  ██║
██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╗██║  ██║███████╗██║██████╔╝    ██║      ██║
╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝     ╚═╝      ╚═╝

*/
void inputcalibp1_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(INPUTCALIBP1);
    nextion_1_stop_timer();
}
void inputcalibp1_type_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_sensor_type(addr);
    free(addr);
}
void inputcalibp1_capacity_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_capacity(addr);
    free(addr);
}
void inputcalibp1_capacity_unit_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_data_unit(addr);
    free(addr);
}
void inputcalibp1_sensibility_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_sensibility(addr);
    free(addr);
}
void inputcalibp1_sensibility_unit_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_sensibility_unit(addr);
    free(addr);
}
void inputcalibp1_sensor_index_received(msg_t *msg)
{
    void *addr = (msg->content.addr);
    inputCalib_set_sensor_index(addr);
    free(addr);
}
/*
██╗███╗   ██╗██████╗ ██╗   ██╗████████╗     ██████╗ █████╗ ██╗     ██╗██████╗     ██████╗ ██████╗
██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔════╝██╔══██╗██║     ██║██╔══██╗    ██╔══██╗╚════██╗
██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║     ███████║██║     ██║██████╔╝    ██████╔╝ █████╔╝
██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║     ██╔══██║██║     ██║██╔══██╗    ██╔═══╝ ██╔═══╝
██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╗██║  ██║███████╗██║██████╔╝    ██║     ███████╗
╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝     ╚═╝     ╚══════╝

*/
void inputcalibp2_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(INPUTCALIBP2);
    nextion_1_stop_timer();
}
void inputcalibp2_calibration_limit_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_limit(addr);
    free(addr);
}
void inputcalibp2_calibration_limit_unit_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    free(addr);
}
void inputcalibp2_limit_enable_receive_cb(msg_t *msg)
{
    void *addr = (msg->content.addr);
    inputCalib_set_limit_enable(addr);
    free(addr);
}
/*
██╗███╗   ██╗██████╗ ██╗   ██╗████████╗     ██████╗ █████╗ ██╗     ██╗██████╗     ██████╗ ██████╗
██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔════╝██╔══██╗██║     ██║██╔══██╗    ██╔══██╗╚════██╗
██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║     ███████║██║     ██║██████╔╝    ██████╔╝ █████╔╝
██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║     ██╔══██║██║     ██║██╔══██╗    ██╔═══╝  ╚═══██╗
██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╗██║  ██║███████╗██║██████╔╝    ██║     ██████╔╝
╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝     ╚═╝     ╚═════╝

*/
void inputcalibp3_loaded_cb(msg_t *msg)
{
   // ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(INPUTCALIBP3);
    nextion_1_start_timer();
}
void inputcalibp3_table_received(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_table(addr);
    free(addr);
}
void inputcalibp3_num_points_received(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    table_t table = inputCalib_set_num_points(addr);
    int decimals_precision = inputCalib_get_decimals_precision();

    ESP_LOGI(TAG, "NEW TABLE:");
    for (int i = 0; i < 11; i++)
    {
        ESP_LOGI(TAG, "%.*f", decimals_precision, table[i][0]);
    }
    nextion_1_inputcalibp3_applied0_write(table[0][0], decimals_precision);
    nextion_1_inputcalibp3_applied1_write(table[1][0], decimals_precision);
    nextion_1_inputcalibp3_applied2_write(table[2][0], decimals_precision);
    nextion_1_inputcalibp3_applied3_write(table[3][0], decimals_precision);
    nextion_1_inputcalibp3_applied4_write(table[4][0], decimals_precision);
    nextion_1_inputcalibp3_applied5_write(table[5][0], decimals_precision);
    nextion_1_inputcalibp3_applied6_write(table[6][0], decimals_precision);
    nextion_1_inputcalibp3_applied7_write(table[7][0], decimals_precision);
    nextion_1_inputcalibp3_applied8_write(table[8][0], decimals_precision);
    nextion_1_inputcalibp3_applied9_write(table[9][0], decimals_precision);
    nextion_1_inputcalibp3_applied10_write(table[10][0], decimals_precision);

    free(table);
    free(addr);
}
void inputcalibp3_row_to_fill_received(msg_t *msg)
{
    void *addr = (msg->content.addr);
    inputCalib_set_row_to_fill(addr);
    free(addr);
}
/*
██╗███╗   ██╗██████╗ ██╗   ██╗████████╗     ██████╗ █████╗ ██╗     ██╗██████╗     ██████╗ ██╗  ██╗
██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔════╝██╔══██╗██║     ██║██╔══██╗    ██╔══██╗██║  ██║
██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║     ███████║██║     ██║██████╔╝    ██████╔╝███████║
██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║     ██╔══██║██║     ██║██╔══██╗    ██╔═══╝ ╚════██║
██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╗██║  ██║███████╗██║██████╔╝    ██║          ██║
╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝     ╚═╝          ╚═╝

*/
void inputcalibp4_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(INPUTCALIBP4);
    nextion_1_stop_timer();
}
void inputcalibp4_name_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_name(addr);
}
void inputcalibp4_save_pressed_cb(msg_t *msg)
{

    inputCalib_save();
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
        if (load_cell_1_is_enabled() && load_cell_1_is_calibrated())
        {
            float data = load_cell_1_get_real();
            nextion_1_home_sensor_1_write_data(data);

            float dataps = load_cell_1_get_realps();
            nextion_1_home_sensor_1_write_dataps(dataps);
        }
        if (load_cell_2_is_enabled() && load_cell_2_is_calibrated())
        {
            float data = load_cell_2_get_real();
            nextion_1_home_sensor_2_write_data(data);

            float dataps = load_cell_2_get_realps();
            nextion_1_home_sensor_2_write_dataps(dataps);
        }
        if (load_cell_3_is_enabled() && load_cell_3_is_calibrated())
        {
            float data = load_cell_3_get_real();
            nextion_1_home_sensor_3_write_data(data);

            float dataps = load_cell_3_get_realps();
            nextion_1_home_sensor_3_write_dataps(dataps);
        }
        if (load_cell_4_is_enabled() && load_cell_4_is_calibrated())
        {
            float data = load_cell_4_get_real();
            nextion_1_home_sensor_4_write_data(data);

            float dataps = load_cell_4_get_realps();
            nextion_1_home_sensor_4_write_dataps(dataps);
        }
        if (dial_big_1_is_enabled() && dial_big_1_is_calibrated())
        {
            float real = dial_big_1_get_real();
            int decimals = dial_big_1_get_decimals();
            nextion_1_home_sensor_5_write_data(real, decimals);

            float realps = dial_big_1_get_realps();
            nextion_1_home_sensor_5_write_dataps(realps, decimals);
        }
        if (dial_big_2_is_enabled() && dial_big_2_is_calibrated())
        {
            float real = dial_big_2_get_real();
            int decimals = dial_big_2_get_decimals();
            nextion_1_home_sensor_6_write_data(real, decimals);

            float realps = dial_big_2_get_realps();
            nextion_1_home_sensor_6_write_dataps(realps, decimals);
        }
        if (dial_big_3_is_enabled() && dial_big_3_is_calibrated())
        {
            float real = dial_big_3_get_real();
            int decimals = dial_big_3_get_decimals();
            nextion_1_home_sensor_7_write_data(real, decimals);

            float realps = dial_big_3_get_realps();
            nextion_1_home_sensor_7_write_dataps(realps, decimals);
        }
        if (dial_big_4_is_enabled() && dial_big_4_is_calibrated())
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
    else if (page == INPUTCALIBP3)
    {
       // ESP_LOGI(TAG, "%s", __func__);
        uint8_t sensor_index = inputCalib_get_sensor_index();
        uint8_t row_to_fill = inputCalib_get_row_to_fill();

        double raw;
        if (sensor_index == 1)
        {
            raw = load_cell_1_get_raw();
        }
        else if (sensor_index == 2)
        {
            raw = load_cell_2_get_raw();
        }
        else if (sensor_index == 3)
        {
            raw = load_cell_3_get_raw();
        }
        else if (sensor_index == 4)
        {
            raw = load_cell_4_get_raw();
        }
        else
        {
            return;
        }

        if (row_to_fill == 0xAA)
        {
            return;
        }
        else if (row_to_fill == 0)
        {
            nextion_1_inputcalibp3_adc0_write(raw);
        }
        else if (row_to_fill == 1)
        {
            nextion_1_inputcalibp3_adc1_write(raw);
        }
        else if (row_to_fill == 2)
        {
            nextion_1_inputcalibp3_adc2_write(raw);
        }
        else if (row_to_fill == 3)
        {
            nextion_1_inputcalibp3_adc3_write(raw);
        }
        else if (row_to_fill == 4)
        {
            nextion_1_inputcalibp3_adc4_write(raw);
        }
        else if (row_to_fill == 5)
        {
            nextion_1_inputcalibp3_adc5_write(raw);
        }
        else if (row_to_fill == 6)
        {
            nextion_1_inputcalibp3_adc6_write(raw);
        }
        else if (row_to_fill == 7)
        {
            nextion_1_inputcalibp3_adc7_write(raw);
        }
        else if (row_to_fill == 8)
        {
            nextion_1_inputcalibp3_adc8_write(raw);
        }
        else if (row_to_fill == 9)
        {
            nextion_1_inputcalibp3_adc9_write(raw);
        }
        else if (row_to_fill == 10)
        {
            nextion_1_inputcalibp3_adc10_write(raw);
        }
    }
    else
    {
        ESP_LOGW(TAG, "%s", __func__);
    }
}