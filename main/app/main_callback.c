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
#include "testing.h"

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
    vTaskDelay(pdMS_TO_TICKS(3000));

    // init sensors default
    for (int index = 0; index < NUM_SENSORS; index++)
        sensor_init(index);

    sensor_set_class(0, CLASS_D);
    sensor_set_class(1, CLASS_D);
    sensor_set_class(2, CLASS_D);
    sensor_set_class(3, CLASS_D);
    sensor_set_class(4, CLASS_I);
    sensor_set_class(5, CLASS_I);
    sensor_set_class(6, CLASS_I);
    sensor_set_class(7, CLASS_I);

    // init nvs storage
    inputCalib_init();

    // load all available calibs
    for (int index = 0; index < NUM_SENSORS; index++)
    {
        sensor_class_t class = sensor_get_class(index);
        if (class == CLASS_I)
        {
            ESP_LOGW(TAG, "inde[%i] is CLASS I", index);
            continue;
        }

        sensor_calib_t calib;
        sensor_config_t config;

        bool load_calib_success = (inputCalib_load(index, &calib) == ESP_OK);
        bool load_config_success = (config_sensor_load(index, &config) == ESP_OK);
        bool load_success = load_calib_success && load_config_success;

        if (!load_success)
        {
            ESP_LOGW(TAG, "file:%s, line:%d", __FILE__, __LINE__);
            continue;
        }

        // update ram
        sensor_set_calibration(index, &calib);
        sensor_set_configuration(index, &config);

        // update objects on screen
        nextion_1_home_write_name(index, sensor_get_name(index));
        nextion_1_home_write_unit(index, sensor_get_unit_str(index));
        nextion_1_home_write_unitps(index, sensor_get_unitps_str(index));
        nextion_1_calibration_write_name(index, sensor_get_name(index));
        nextion_1_calibration_write_range(index, sensor_get_range(index));
        nextion_1_calibration_write_units_path(index, sensor_get_units_path(index));
        nextion_1_calibration_write_units_val(index, sensor_get_units_val(index));
        nextion_1_calibration_write_unit(index, sensor_get_unit_str(index));
        nextion_1_calibration_write_limit(index, sensor_is_limit_enabled(index));
        bool is_enabled = sensor_is_enabled(index);
        nextion_1_calibration_write_switch(index, is_enabled);
        SEND_I32_MSG(sensor_queue, is_enabled ? SENSOR_ENABLED : SENSOR_DISABLED, index, portMAX_DELAY);
    }

    nextion_1_start_timer();
}

/*
██████╗  █████╗  ██████╗ ███████╗███████╗    ██╗      ██████╗  █████╗ ██████╗ ███████╗██████╗
██╔══██╗██╔══██╗██╔════╝ ██╔════╝██╔════╝    ██║     ██╔═══██╗██╔══██╗██╔══██╗██╔════╝██╔══██╗
██████╔╝███████║██║  ███╗█████╗  ███████╗    ██║     ██║   ██║███████║██║  ██║█████╗  ██║  ██║
██╔═══╝ ██╔══██║██║   ██║██╔══╝  ╚════██║    ██║     ██║   ██║██╔══██║██║  ██║██╔══╝  ██║  ██║
██║     ██║  ██║╚██████╔╝███████╗███████║    ███████╗╚██████╔╝██║  ██║██████╔╝███████╗██████╔╝
╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝    ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚═════╝

*/

void home_loaded_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(PAGE_HOME);
    nextion_1_start_timer();
}
void system_settings_loaded_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(PAGE_SYSTEM_SETTINGS);
    nextion_1_stop_timer();
}
void calibration_loaded_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(PAGE_CALIBRATION);
    nextion_1_start_timer();
}
void inputcalibp1_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(PAGE_INPUTCALIBP1);
    nextion_1_stop_timer();
}
void inputcalibp2_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(PAGE_INPUTCALIBP2);
    nextion_1_stop_timer();
}
void inputcalibp3_loaded_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(PAGE_INPUTCALIBP3);
    nextion_1_start_timer();
}
void inputcalibp4_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(PAGE_INPUTCALIBP4);
    nextion_1_stop_timer();
}
void numpad_popup_loaded_cb(msg_t *msg)
{
    nextion_1_set_page(PAGE_NUMPAD_POPUP);
    nextion_1_stop_timer();
}
void new_test_loaded_cb(msg_t *msg)
{
    ESP_LOGI(TAG, "%s", __func__);
    nextion_1_set_page(PAGE_NEW_TEST);
    nextion_1_stop_timer();
}

/*
████████╗ █████╗ ██████╗  █████╗
╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗
   ██║   ███████║██████╔╝███████║
   ██║   ██╔══██║██╔══██╗██╔══██║
   ██║   ██║  ██║██║  ██║██║  ██║
   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝

*/
void tara_enabled_cb(msg_t *msg)
{
    int index = msg->content.i32;
    sensor_set_tara(index);
}
void tara_disabled_cb(msg_t *msg)
{
    int index = msg->content.i32;
    sensor_clear_tara(index);
}

/*
███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗     ███████╗███╗   ██╗ █████╗ ██████╗ ██╗     ███████╗
██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗    ██╔════╝████╗  ██║██╔══██╗██╔══██╗██║     ██╔════╝
███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝    █████╗  ██╔██╗ ██║███████║██████╔╝██║     █████╗
╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗    ██╔══╝  ██║╚██╗██║██╔══██║██╔══██╗██║     ██╔══╝
███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║    ███████╗██║ ╚████║██║  ██║██████╔╝███████╗███████╗
╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝    ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝

*/

void sensor_disabled_cb(msg_t *msg)
{
    // get index
    int index = msg->content.i32;

    // disable physically
    SEND_I32_MSG(sensor_queue, SENSOR_DISABLED, index, portMAX_DELAY);

    // status disabled in ram
    sensor_disable(index);

    // status disabled in nvs
    config_sensor_save(index, sensor_get_configuration(index));
}
void sensor_enabled_cb(msg_t *msg)
{
    // ESP_LOGI(TAG, "file:%s,line:%i", __FILE__, __LINE__);

    int index = msg->content.i32;

    // enable physically
    SEND_I32_MSG(sensor_queue, SENSOR_ENABLED, index, portMAX_DELAY);

    // status disabled in ram
    sensor_enable(index);

    // status disabled in nvs
    config_sensor_save(index, sensor_get_configuration(index));
}

/*
██╗███╗   ██╗██████╗ ██╗   ██╗████████╗     ██████╗ █████╗ ██╗     ██╗██████╗     ██████╗  ██╗
██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔════╝██╔══██╗██║     ██║██╔══██╗    ██╔══██╗███║
██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║     ███████║██║     ██║██████╔╝    ██████╔╝╚██║
██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║     ██╔══██║██║     ██║██╔══██╗    ██╔═══╝  ██║
██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╗██║  ██║███████╗██║██████╔╝    ██║      ██║
╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝     ╚═╝      ╚═╝

*/

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
    inputCalib_set_index(addr);
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

void inputcalibp2_calibration_limit_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_limit(addr);
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

    ESP_LOGI(TAG, "NEW TABLE:");
    for (int i = 0; i < 11; i++)
        ESP_LOGI(TAG, "%s - %s", table[i][0], table[i][1]);

    nextion_1_inputcalibp3_write_real0(table[0][0]);
    nextion_1_inputcalibp3_write_real1(table[1][0]);
    nextion_1_inputcalibp3_write_real2(table[2][0]);
    nextion_1_inputcalibp3_write_real3(table[3][0]);
    nextion_1_inputcalibp3_write_real4(table[4][0]);
    nextion_1_inputcalibp3_write_real5(table[5][0]);
    nextion_1_inputcalibp3_write_real6(table[6][0]);
    nextion_1_inputcalibp3_write_real7(table[7][0]);
    nextion_1_inputcalibp3_write_real8(table[8][0]);
    nextion_1_inputcalibp3_write_real9(table[9][0]);
    nextion_1_inputcalibp3_write_real10(table[10][0]);

    nextion_1_inputcalibp3_write_raw0(table[0][1]);
    nextion_1_inputcalibp3_write_raw1(table[1][1]);
    nextion_1_inputcalibp3_write_raw2(table[2][1]);
    nextion_1_inputcalibp3_write_raw3(table[3][1]);
    nextion_1_inputcalibp3_write_raw4(table[4][1]);
    nextion_1_inputcalibp3_write_raw5(table[5][1]);
    nextion_1_inputcalibp3_write_raw6(table[6][1]);
    nextion_1_inputcalibp3_write_raw7(table[7][1]);
    nextion_1_inputcalibp3_write_raw8(table[8][1]);
    nextion_1_inputcalibp3_write_raw9(table[9][1]);
    nextion_1_inputcalibp3_write_raw10(table[10][1]);

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

void inputcalibp4_name_received_cb(msg_t *msg)
{
    char *addr = (char *)(msg->content.addr);
    inputCalib_set_name(addr);
    free(addr);
}
void inputcalibp4_save_pressed_cb(msg_t *msg)
{
    // save current sensor calibration on inpucalib engine
    char *info;
    bool save_calib_success = (inputCalib_save(&info) == ESP_OK);

    if (!save_calib_success)
    {
        // infor text (red)
        nextion_1_inputcalibp4_write_result_color(63488);
        nextion_1_inputcalibp4_write_result("Save calibration error");
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    // info text (green)
    nextion_1_inputcalibp4_write_result_color(3457);
    nextion_1_inputcalibp4_write_result(info);

    // load last saved calib
    sensor_calib_t calib;
    int index;
    bool load_success = (inputCalib_load_last_saved(&index, &calib) == ESP_OK);

    // load success
    if (!load_success)
    {
        // infor text (red)
        nextion_1_inputcalibp4_write_result_color(63488);
        nextion_1_inputcalibp4_write_result("Verify calibration error");
        inputCalib_delete(index);
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    // generate configuration from last calibration saved
    sensor_config_t config;
    config.num_decimals = calib.num_decimals;
    config.unit_fc = 1.0;
    config.unit = calib.unit;
    config.is_tara_enabled = false;
    config.tara_val = 0.0;
    config.is_sensor_enabled = sensor_is_enabled(index);
    config.is_limit_enabled = false;

    // save configuration in nvs
    bool save_configuration_success = (config_sensor_save(index, &config) == ESP_OK);
    if (!save_configuration_success)
    {
        // infor text (red)
        nextion_1_inputcalibp4_write_result_color(63488);
        nextion_1_inputcalibp4_write_result("Save configuration error");
        inputCalib_delete(index);
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    // set configuration in ram
    sensor_set_configuration(index, &config);

    // set calibration in ram
    sensor_set_calibration(index, &calib);

    // update objects in screen
    nextion_1_home_write_name(index, sensor_get_name(index));
    nextion_1_home_write_unit(index, sensor_get_unit_str(index));
    nextion_1_home_write_unitps(index, sensor_get_unitps_str(index));
    nextion_1_calibration_write_switch(index, sensor_is_enabled(index));
    nextion_1_calibration_write_name(index, sensor_get_name(index));
    nextion_1_calibration_write_range(index, sensor_get_range(index));
    nextion_1_calibration_write_unit(index, sensor_get_unit_str(index));
    nextion_1_calibration_write_units_path(index, sensor_get_units_path(index));
    nextion_1_calibration_write_units_val(index, sensor_get_units_val(index));
}

/*
    ███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗     ██╗   ██╗███╗   ██╗██╗████████╗     ██████╗██╗  ██╗ █████╗ ███╗   ██╗ ██████╗ ███████╗██████╗
    ██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗    ██║   ██║████╗  ██║██║╚══██╔══╝    ██╔════╝██║  ██║██╔══██╗████╗  ██║██╔════╝ ██╔════╝██╔══██╗
    ███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝    ██║   ██║██╔██╗ ██║██║   ██║       ██║     ███████║███████║██╔██╗ ██║██║  ███╗█████╗  ██║  ██║
    ╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗    ██║   ██║██║╚██╗██║██║   ██║       ██║     ██╔══██║██╔══██║██║╚██╗██║██║   ██║██╔══╝  ██║  ██║
    ███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║    ╚██████╔╝██║ ╚████║██║   ██║       ╚██████╗██║  ██║██║  ██║██║ ╚████║╚██████╔╝███████╗██████╔╝
    ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝     ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝        ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝╚═════╝

*/

void sensor_unit_changed(msg_t *msg)
{
    content_str_t content = (msg->content.cs);
    int index = content.index;

    // VERIFY SENSOR CLASS
    sensor_class_t class = sensor_get_class(index);
    if (class == CLASS_I)
    {
        goto update_screen;
    }
    // RETURN_IF_TRUE(class != CLASS_D);

    // UNIT STR TO SENSOR_UNIT_T
    esp_err_t err;
    sensor_unit_t new_unit;
    err = config_get_unit_from_str(content.str, &new_unit);
    free(content.str);
    RETURN_IF_TRUE(err != ESP_OK);

    // VERIFY NEW UNIT IS IN VALID RANGE
    sensor_type_t type = sensor_get_type(index);
    bool res = config_is_unit_ok(new_unit, type);
    RETURN_IF_TRUE(res != true);

    // CREATE NEW SENSOR CONFIGURATION
    sensor_type_t old_unit = sensor_get_src_unit(index);
    double new_fc = config_get_fc(old_unit, new_unit, type);
    sensor_config_t *config = sensor_get_configuration(index);
    config->unit_fc = new_fc;
    config->unit = new_unit;

    // SAVE NEW CONFIGURATION ON NVS
    err = config_sensor_save(index, config);
    RETURN_IF_TRUE(err != ESP_OK);

    // SET NEW CONFIGURATION ON RAM
    sensor_set_configuration(index, config);

update_screen:
    // UPDATE SCREEN
    nextion_1_home_write_unit(index, sensor_get_unit_str(index));
    nextion_1_home_write_unitps(index, sensor_get_unitps_str(index));
    nextion_1_calibration_write_range(index, sensor_get_range(index));
    nextion_1_calibration_write_unit(index, sensor_get_unit_str(index));
}

/*
    ██╗     ██╗███╗   ███╗██╗████████╗███████╗    ███████╗███╗   ██╗ █████╗ ██████╗ ██╗     ███████╗██████╗
    ██║     ██║████╗ ████║██║╚══██╔══╝██╔════╝    ██╔════╝████╗  ██║██╔══██╗██╔══██╗██║     ██╔════╝██╔══██╗
    ██║     ██║██╔████╔██║██║   ██║   ███████╗    █████╗  ██╔██╗ ██║███████║██████╔╝██║     █████╗  ██║  ██║
    ██║     ██║██║╚██╔╝██║██║   ██║   ╚════██║    ██╔══╝  ██║╚██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ██║  ██║
    ███████╗██║██║ ╚═╝ ██║██║   ██║   ███████║    ███████╗██║ ╚████║██║  ██║██████╔╝███████╗███████╗██████╔╝
    ╚══════╝╚═╝╚═╝     ╚═╝╚═╝   ╚═╝   ╚══════╝    ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚═════╝

*/
void sensor_limits_enabled(msg_t *msg)
{
    int index = msg->content.i32;
    sensor_set_limits(index, true);
    config_sensor_save(index, sensor_get_configuration(index));
}

/*
██╗     ██╗███╗   ███╗██╗████████╗███████╗    ██████╗ ██╗███████╗ █████╗ ██████╗ ██╗     ███████╗██████╗
██║     ██║████╗ ████║██║╚══██╔══╝██╔════╝    ██╔══██╗██║██╔════╝██╔══██╗██╔══██╗██║     ██╔════╝██╔══██╗
██║     ██║██╔████╔██║██║   ██║   ███████╗    ██║  ██║██║███████╗███████║██████╔╝██║     █████╗  ██║  ██║
██║     ██║██║╚██╔╝██║██║   ██║   ╚════██║    ██║  ██║██║╚════██║██╔══██║██╔══██╗██║     ██╔══╝  ██║  ██║
███████╗██║██║ ╚═╝ ██║██║   ██║   ███████║    ██████╔╝██║███████║██║  ██║██████╔╝███████╗███████╗██████╔╝
╚══════╝╚═╝╚═╝     ╚═╝╚═╝   ╚═╝   ╚══════╝    ╚═════╝ ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚═════╝

*/
void sensor_limits_disabled(msg_t *msg)
{
    int index = msg->content.i32;
    sensor_set_limits(index, false);
    config_sensor_save(index, sensor_get_configuration(index));
}

/*
    ███╗   ███╗███████╗ ██████╗     ███████╗██████╗  ██████╗ ███╗   ███╗    ███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗     ████████╗ █████╗ ███████╗██╗  ██╗
    ████╗ ████║██╔════╝██╔════╝     ██╔════╝██╔══██╗██╔═══██╗████╗ ████║    ██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗    ╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝
    ██╔████╔██║███████╗██║  ███╗    █████╗  ██████╔╝██║   ██║██╔████╔██║    ███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝       ██║   ███████║███████╗█████╔╝
    ██║╚██╔╝██║╚════██║██║   ██║    ██╔══╝  ██╔══██╗██║   ██║██║╚██╔╝██║    ╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗       ██║   ██╔══██║╚════██║██╔═██╗
    ██║ ╚═╝ ██║███████║╚██████╔╝    ██║     ██║  ██║╚██████╔╝██║ ╚═╝ ██║    ███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║       ██║   ██║  ██║███████║██║  ██╗
    ╚═╝     ╚═╝╚══════╝ ╚═════╝     ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝    ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝       ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝

*/

void sensor_reading_received_cb(msg_t *msg)
{
    content_reading_t cr = msg->content.cr;
    int index = cr.index;
    reading_t reading = cr.reading;
    sensor_set_data(index, &reading);
}
void sensor_class_received_cb(msg_t *msg)
{
    sensor_set_class(msg->content.cc.index, msg->content.cc.class);
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
    if (page == PAGE_HOME)
    {
        for (int index = 0; index < NUM_SENSORS; index++)
        {
            bool is_ready = sensor_is_ready(index);

            if (is_ready)
            {
                nextion_1_home_write_data(index, sensor_get_real_str(index));
                nextion_1_home_write_dataps(index, sensor_get_realps_str(index));
            }
        }
    }
    else if (page == PAGE_CALIBRATION)
    {
        for (int index = 0; index < NUM_SENSORS; index++)
        {
            bool is_ready = sensor_is_ready(index);
            bool is_enabled = sensor_is_enabled(index);

            if (is_ready)
            {
                nextion_1_calibration_write_value(index, sensor_get_real_str(index));
            }
            if (is_enabled)
            {
                nextion_1_calibration_write_counts(index, sensor_get_raw_str(index));
            }
        }
    }
    else if (page == PAGE_INPUTCALIBP3)
    {
        int index = inputCalib_get_index();

        // VERIFY SENSOR IS ENABLED
        bool is_enabled = sensor_is_enabled(index);
        RETURN_IF_TRUE(!is_enabled);

        // PRINT RAW IN ROW
        switch (inputCalib_get_row_to_fill())
        {
        case ROW_0_TO_FILL:
            nextion_1_inputcalibp3_write_raw0(sensor_get_raw_str(index));
            break;
        case ROW_1_TO_FILL:
            nextion_1_inputcalibp3_write_raw1(sensor_get_raw_str(index));
            break;
        case ROW_2_TO_FILL:
            nextion_1_inputcalibp3_write_raw2(sensor_get_raw_str(index));
            break;
        case ROW_3_TO_FILL:
            nextion_1_inputcalibp3_write_raw3(sensor_get_raw_str(index));
            break;
        case ROW_4_TO_FILL:
            nextion_1_inputcalibp3_write_raw4(sensor_get_raw_str(index));
            break;
        case ROW_5_TO_FILL:
            nextion_1_inputcalibp3_write_raw5(sensor_get_raw_str(index));
            break;
        case ROW_6_TO_FILL:
            nextion_1_inputcalibp3_write_raw6(sensor_get_raw_str(index));
            break;
        case ROW_7_TO_FILL:
            nextion_1_inputcalibp3_write_raw7(sensor_get_raw_str(index));
            break;
        case ROW_8_TO_FILL:
            nextion_1_inputcalibp3_write_raw8(sensor_get_raw_str(index));
            break;
        case ROW_9_TO_FILL:
            nextion_1_inputcalibp3_write_raw9(sensor_get_raw_str(index));
            break;
        case ROW_10_TO_FILL:
            nextion_1_inputcalibp3_write_raw10(sensor_get_raw_str(index));
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

/*
    ███╗   ██╗███████╗██╗    ██╗    ████████╗███████╗███████╗████████╗
    ████╗  ██║██╔════╝██║    ██║    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝
    ██╔██╗ ██║█████╗  ██║ █╗ ██║       ██║   █████╗  ███████╗   ██║
    ██║╚██╗██║██╔══╝  ██║███╗██║       ██║   ██╔══╝  ╚════██║   ██║
    ██║ ╚████║███████╗╚███╔███╔╝       ██║   ███████╗███████║   ██║
    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝        ╚═╝   ╚══════╝╚══════╝   ╚═╝

*/

void test_execute_cb(msg_t *msg)
{
    // ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    bool is_runnig = test_is_running();
    RETURN_IF_TRUE(!is_runnig);

    int index1 = test_get_index1();
    int index2 = test_get_index2();
    uint8_t row = test_get_row();
    bool res = test_execute(sensor_get_real(index1), sensor_get_real(index2));
    if (res == true)
    {
        switch (row)
        {
        case 0:
            nextion_1_newtest_write_table01(sensor_get_real_str(index2));
            break;
        case 1:
            nextion_1_newtest_write_table11(sensor_get_real_str(index2));
            break;
        case 2:
            nextion_1_newtest_write_table21(sensor_get_real_str(index2));
            break;
        case 3:
            nextion_1_newtest_write_table31(sensor_get_real_str(index2));
            break;
        case 4:
            nextion_1_newtest_write_table41(sensor_get_real_str(index2));
            break;
        case 5:
            nextion_1_newtest_write_table51(sensor_get_real_str(index2));
            break;
        case 6:
            nextion_1_newtest_write_table61(sensor_get_real_str(index2));
            break;
        case 7:
            nextion_1_newtest_write_table71(sensor_get_real_str(index2));
            break;
        case 8:
            nextion_1_newtest_write_table81(sensor_get_real_str(index2));
            break;
        case 9:
            nextion_1_newtest_write_table91(sensor_get_real_str(index2));
            test_stop();
            break;
        default:
            break;
        }
    }
}
void new_test_set_index_1_cb(msg_t *msg)
{
    // ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    int index = *(uint8_t *)(msg->content.addr);
    test_set_index1(index);
    free(msg->content.addr);
}
void new_test_set_index2_cb(msg_t *msg)
{
    // ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    int index = *(uint8_t *)(msg->content.addr);
    test_set_index2(index);
    free(msg->content.addr);
}
void new_test_start_cb(msg_t *msg)
{
    // ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    test_start();
}
void new_test_stop_cb(msg_t *msg)
{
    // ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    test_stop();
}
void new_test_download_cb(msg_t *msg)
{
    // ESP_LOGW(TAG, "%s:line %d", __FILE__, __LINE__);
    
}