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
#include "configuration.h"
#include "esp_err.h"

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
    // init gui
    nextion_1_init();

    // init sensors
    load_cell_1_init();
    load_cell_2_init();
    load_cell_3_init();
    load_cell_4_init();

    dial_big_1_init();
    dial_big_2_init();
    dial_big_3_init();
    dial_big_4_init();

    // init nvs storage
    inputCalib_init();

    // load all available calibs
    calib_params_t calib;
    size_t calib_len = sizeof(calib_params_t);
    sensor_config_t config;

    bool load_params_1_success = (inputCalib_load(SENSOR_1_TO_LOAD, &calib, &calib_len) == LOAD_CALIB_SUCCESS);
    bool load_config_1_success = (config_sensor_1_load(&config) == ESP_OK);

    if (load_params_1_success && load_config_1_success)
    {
        // calib in mcu
        load_cell_1_set_calib(&calib);
        load_cell_1_set_config(&config);
        // home page
        nextion_1_home_sensor_1_write_name(calib.name);
        nextion_1_home_sensor_1_write_unit(config.unit_str);
        nextion_1_home_sensor_1_write_unitps(config.unitps_str);
        // calibration page
        nextion_1_calibration_sensor_1_write_name(calib.name);
        nextion_1_calibration_sensor_1_write_limit(config.unit_str, calib.capacity * config.unit_fc, config.decimals_precision);
        nextion_1_calibration_sensor_1_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_1_combobox_set_val(255);
        nextion_1_calibration_sensor_1_combobox_set_txt(config.unit_str);
        nextion_1_calibration_sensor_1_checkbox_set_val(config.is_limit_enabled);
        nextion_1_calibration_sensor_1_switch_set_val(config.is_sensor_enabled);
    }

    bool load_params_2_success = (inputCalib_load(SENSOR_2_TO_LOAD, &calib, &calib_len) == LOAD_CALIB_SUCCESS);
    if (load_params_2_success)
    {
        // calib in mcu
        load_cell_2_set_calib(&calib);
        // home page
        nextion_1_home_sensor_2_write_name(calib.name);
        nextion_1_home_sensor_2_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_2_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_2_write_name(calib.name);
        nextion_1_calibration_sensor_2_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_2_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_2_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_2_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
    }

    bool load_params_3_success = (inputCalib_load(SENSOR_3_TO_LOAD, &calib, &calib_len) == LOAD_CALIB_SUCCESS);
    if (load_params_3_success)
    {
        // calib in mcu
        load_cell_3_set_calib(&calib);
        // home page
        nextion_1_home_sensor_3_write_name(calib.name);
        nextion_1_home_sensor_3_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_3_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_3_write_name(calib.name);
        nextion_1_calibration_sensor_3_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_3_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_3_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_3_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
    }

    bool load_params_4_success = (inputCalib_load(SENSOR_4_TO_LOAD, &calib, &calib_len) == LOAD_CALIB_SUCCESS);
    if (load_params_4_success)
    {
        // calib in mcu
        load_cell_4_set_calib(&calib);
        // home page
        nextion_1_home_sensor_4_write_name(calib.name);
        nextion_1_home_sensor_4_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_4_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_4_write_name(calib.name);
        nextion_1_calibration_sensor_4_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_4_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_4_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_4_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
    }
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

    config_sensor_1_save(load_cell_1_get_config());
}
void home_tara_1_disabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    load_cell_1_clear_tara();

    config_sensor_1_save(load_cell_1_get_config());
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
    // ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(CALIBRATION);
    nextion_1_start_timer();
}

// SWITCH EVENTS

void calibration_switch_1_disabled_cb(msg_t *msg)
{
    load_cell_1_disable();
    config_sensor_1_save(load_cell_1_get_config());
}
void calibration_switch_1_enabled_cb(msg_t *msg)
{
    load_cell_1_enable();
    config_sensor_1_save(load_cell_1_get_config());
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
void calibration_sensor_1_unit_changed_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    // verify unit str
    sensor_unit_t unit_to;
    sensor_type_t type;
    esp_err_t res = inputCalib_get_sensor_unit_from_str(addr, &unit_to, &type);
    if (res != ESP_OK)
        return;

    // update ram
    sensor_unit_t unit_from = load_cell_1_get_unit_from_calib();  

    sensor_config_t *config = load_cell_1_get_config();
    config->unit_fc = inputCalib_get_fc(unit_from, unit_to, type);
    config->unit_str = inputCalib_unit_to_str(unit_to, type);
    config->unitps_str = inputCalib_unitps_to_str(unit_to, type);

    // update screen
    nextion_1_home_sensor_1_write_unit(config->unit_str);
    nextion_1_home_sensor_1_write_unitps(config->unitps_str);
    nextion_1_calibration_sensor_1_write_limit(config->unit_str, load_cell_1_get_capacity(), load_cell_1_get_calib_decimals());

    // update flash
    config_sensor_1_save(load_cell_1_get_config());
    free(addr);
}
void calibration_sensor_2_unit_changed_cb(msg_t *msg)
{
}
void calibration_sensor_3_unit_changed_cb(msg_t *msg)
{
}
void calibration_sensor_4_unit_changed_cb(msg_t *msg)
{
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
    inputCalib_set_unit(addr);
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
    inputCalib_set_sensor_under_calibration(addr);
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
    free(addr);
}
void inputcalibp4_save_pressed_cb(msg_t *msg)
{
    // save current sensor config on inpucalib engine
    char *info;
    bool save_params_success = (inputCalib_save(&info) == SAVE_CALIB_SUCCESS);

    if (!save_params_success)
    {
        // infor text (red)
        nextion_1_inputcalibp4_result_set_txt_color(63488);
        nextion_1_inputcalibp4_result_write(info);
        return;
    }

    // info text (green)
    nextion_1_inputcalibp4_result_set_txt_color(3457);
    nextion_1_inputcalibp4_result_write(info);

    // load last saved calib
    calib_params_t calib;
    size_t len = sizeof(calib_params_t);
    sensor_to_load_t sensor;
    bool load_params_success = (inputCalib_load_last_saved(&sensor, &calib, &len) == LOAD_CALIB_SUCCESS);

    // load success
    if (!load_params_success)
        return;

    // set config
    sensor_config_t config = SENSOR_CONFIG_DEFAULT;
    config.decimals_precision = calib.decimals_precision;
    config.unit_fc = 1.0;
    config.unit_str = inputCalib_unit_to_str(calib.unit, calib.sensor_type);
    config.unitps_str = inputCalib_unitps_to_str(calib.unit, calib.sensor_type);
    config.is_tara_enabled = false;
    config.tara_val = 0.0;
    config.is_limit_enabled = true;
    if (sensor == SENSOR_1_TO_LOAD)
    {
        config.is_sensor_enabled = load_cell_1_is_enabled();
        config_sensor_1_save(&config);
        load_cell_1_set_config(&config);
    }
    else if (sensor == SENSOR_2_TO_LOAD)
    {
        config.is_sensor_enabled = load_cell_2_is_enabled();
        config_sensor_2_save(&config);
        load_cell_2_set_config(&config);
    }
    else if (sensor == SENSOR_3_TO_LOAD)
    {
        config.is_sensor_enabled = load_cell_3_is_enabled();
        config_sensor_3_save(&config);
        load_cell_3_set_config(&config);
    }
    else if (sensor == SENSOR_4_TO_LOAD)
    {
        config.is_sensor_enabled = load_cell_4_is_enabled();
        config_sensor_4_save(&config);
        load_cell_4_set_config(&config);
    }
    else
    {
        config.is_sensor_enabled = false;
        return;
    }

    // update system
    switch (sensor)
    {
    case SENSOR_1_TO_LOAD:
        // calib in mcu
        load_cell_1_set_calib(&calib);
        // home page
        nextion_1_home_sensor_1_write_name(calib.name);
        nextion_1_home_sensor_1_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_1_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_1_write_name(calib.name);
        nextion_1_calibration_sensor_1_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_1_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_1_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_1_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));

        break;
    case SENSOR_2_TO_LOAD:
        // calib in mcu
        load_cell_2_set_calib(&calib);
        // home page
        nextion_1_home_sensor_2_write_name(calib.name);
        nextion_1_home_sensor_2_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_2_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_2_write_name(calib.name);
        nextion_1_calibration_sensor_2_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_2_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_2_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_2_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        break;
    case SENSOR_3_TO_LOAD:
        // calib in mcu
        load_cell_3_set_calib(&calib);
        // home page
        nextion_1_home_sensor_3_write_name(calib.name);
        nextion_1_home_sensor_3_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_3_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_3_write_name(calib.name);
        nextion_1_calibration_sensor_3_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_3_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_3_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_3_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        break;
    case SENSOR_4_TO_LOAD:
        // calib in mcu
        load_cell_4_set_calib(&calib);
        // home page
        nextion_1_home_sensor_4_write_name(calib.name);
        nextion_1_home_sensor_4_write_unit(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        nextion_1_home_sensor_4_write_unitps(inputCalib_unitps_to_str(calib.unit, calib.sensor_type));
        // calibration page
        nextion_1_calibration_sensor_4_write_name(calib.name);
        nextion_1_calibration_sensor_4_write_limit(inputCalib_unit_to_str(calib.unit, calib.sensor_type), calib.limit_val, calib.decimals_precision);
        nextion_1_calibration_sensor_4_combobox_set_path(inputCalib_path_from_type(calib.sensor_type));
        nextion_1_calibration_sensor_4_combobox_set_val(inputCalib_val_from_type_and_unit(calib.sensor_type, calib.unit));
        nextion_1_calibration_sensor_4_combobox_set_txt(inputCalib_unit_to_str(calib.unit, calib.sensor_type));
        break;
    default:
        break;
    }
}
/*
███╗   ██╗██╗   ██╗███╗   ███╗██████╗  █████╗ ██████╗     ██████╗  ██████╗ ██████╗ ██╗   ██╗██████╗
████╗  ██║██║   ██║████╗ ████║██╔══██╗██╔══██╗██╔══██╗    ██╔══██╗██╔═══██╗██╔══██╗██║   ██║██╔══██╗
██╔██╗ ██║██║   ██║██╔████╔██║██████╔╝███████║██║  ██║    ██████╔╝██║   ██║██████╔╝██║   ██║██████╔╝
██║╚██╗██║██║   ██║██║╚██╔╝██║██╔═══╝ ██╔══██║██║  ██║    ██╔═══╝ ██║   ██║██╔═══╝ ██║   ██║██╔═══╝
██║ ╚████║╚██████╔╝██║ ╚═╝ ██║██║     ██║  ██║██████╔╝    ██║     ╚██████╔╝██║     ╚██████╔╝██║
╚═╝  ╚═══╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝╚═════╝     ╚═╝      ╚═════╝ ╚═╝      ╚═════╝ ╚═╝

*/
void numpad_popup_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(NUMPAD_POPUP);
    nextion_1_stop_timer();
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
        if (load_cell_1_is_enabled() && load_cell_1_is_calibrated())
        {
            float data = load_cell_1_get_real();
            nextion_1_calibration_sensor_1_write_data(data);
        }
        if (load_cell_2_is_enabled() && load_cell_2_is_calibrated())
        {
            float data = load_cell_2_get_real();
            nextion_1_calibration_sensor_2_write_data(data);
        }
        if (load_cell_3_is_enabled() && load_cell_3_is_calibrated())
        {
            float data = load_cell_3_get_real();
            nextion_1_calibration_sensor_3_write_data(data);
        }
        if (load_cell_4_is_enabled() && load_cell_4_is_calibrated())
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
        double raw;

        switch (inputCalib_get_sensor_under_calibration())
        {
        case SENSOR_1_UNDER_CALIBRATION:
            if (load_cell_1_is_enabled())
            {
                raw = load_cell_1_get_raw();
                break;
            }
            else
            {
                return;
            }
        case SENSOR_2_UNDER_CALIBRATION:
            if (load_cell_2_is_enabled())
            {
                raw = load_cell_2_get_raw();
                break;
            }
            else
            {
                return;
            }
        case SENSOR_3_UNDER_CALIBRATION:
            if (load_cell_3_is_enabled())
            {
                raw = load_cell_3_get_raw();
                break;
            }
            else
            {
                return;
            }
        case SENSOR_4_UNDER_CALIBRATION:
            if (load_cell_4_is_enabled())
            {
                raw = load_cell_4_get_raw();
                break;
            }
            else
            {
                return;
            }
        default:
            return;
        }

        switch (inputCalib_get_row_to_fill())
        {
        case ROW_0_TO_FILL:
            nextion_1_inputcalibp3_adc0_write(raw);
            break;
        case ROW_1_TO_FILL:
            nextion_1_inputcalibp3_adc1_write(raw);
            break;
        case ROW_2_TO_FILL:
            nextion_1_inputcalibp3_adc2_write(raw);
            break;
        case ROW_3_TO_FILL:
            nextion_1_inputcalibp3_adc3_write(raw);
            break;
        case ROW_4_TO_FILL:
            nextion_1_inputcalibp3_adc4_write(raw);
            break;
        case ROW_5_TO_FILL:
            nextion_1_inputcalibp3_adc5_write(raw);
            break;
        case ROW_6_TO_FILL:
            nextion_1_inputcalibp3_adc6_write(raw);
            break;
        case ROW_7_TO_FILL:
            nextion_1_inputcalibp3_adc7_write(raw);
            break;
        case ROW_8_TO_FILL:
            nextion_1_inputcalibp3_adc8_write(raw);
            break;
        case ROW_9_TO_FILL:
            nextion_1_inputcalibp3_adc9_write(raw);
            break;
        case ROW_10_TO_FILL:
            nextion_1_inputcalibp3_adc10_write(raw);
            break;
        default:
            break;
        }
    }
    else
    {
        ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    }
}