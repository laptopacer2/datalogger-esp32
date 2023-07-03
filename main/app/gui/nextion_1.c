
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "project_defines.h"
#include "nextion_async.h"
#include "project_tasks.h"
#include "project_typedefs.h"
#include "esp_log.h"

#define TAG "NEXTION_1"

page_t page = INITIAL_PAGE;

/*
███╗   ██╗███████╗██╗  ██╗████████╗██╗ ██████╗ ███╗   ██╗     ██████╗ ██████╗ ██████╗ ███████╗
████╗  ██║██╔════╝╚██╗██╔╝╚══██╔══╝██║██╔═══██╗████╗  ██║    ██╔════╝██╔═══██╗██╔══██╗██╔════╝
██╔██╗ ██║█████╗   ╚███╔╝    ██║   ██║██║   ██║██╔██╗ ██║    ██║     ██║   ██║██████╔╝█████╗
██║╚██╗██║██╔══╝   ██╔██╗    ██║   ██║██║   ██║██║╚██╗██║    ██║     ██║   ██║██╔══██╗██╔══╝
██║ ╚████║███████╗██╔╝ ██╗   ██║   ██║╚██████╔╝██║ ╚████║    ╚██████╗╚██████╔╝██║  ██║███████╗
╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝

*/

void data_rcv_1_cb(uint8_t *buffer, int size)
{
    ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
    ESP_LOGI(TAG, "%*s", size, (char *)buffer);
}
void code_rcv_1_cb(nextion_cmd_t *cmd)
{
    nextion_cmd_id_t cmd_id = cmd->id;
    if (cmd_id == TOUCH_EVENT_ID)
    {
        uint8_t page = cmd->touch_event.page;
        uint8_t component_id = cmd->touch_event.component_id;
        uint8_t event = cmd->touch_event.event;

        // HOME
        if (page == 0 && component_id == 0x00)
            SEND2FRONT_EMPTY_MSG(main_queue, HOME_LOADED, portMAX_DELAY)
        // HOME - TARA 1 BUTTON
        else if (page == 0 && component_id == 0x04 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_1_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x04 && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_1_ENABLED, portMAX_DELAY)
        // HOME - TARA 2 BUTTON
        else if (page == 0 && component_id == 0x0B && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_2_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x0B && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_2_ENABLED, portMAX_DELAY)
        // HOME - TARA 3 BUTTON
        else if (page == 0 && component_id == 0x12 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_3_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x12 && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_3_ENABLED, portMAX_DELAY)
        // HOME - TARA 4 BUTTON
        else if (page == 0 && component_id == 0x19 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_4_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x19 && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_4_ENABLED, portMAX_DELAY)
        // SYSTEM SETTINGS LOADED
        else if (page == 1 && component_id == 0x00)
            SEND2FRONT_EMPTY_MSG(main_queue, SYSTEM_SETTINGS_LOADED, portMAX_DELAY)
        // CALIBRATION LOADED
        else if (page == 2 && component_id == 0x00)
            SEND2FRONT_EMPTY_MSG(main_queue, CALIBRATION_LOADED, portMAX_DELAY)
        // CALIBRATION - SWITCH 1
        else if (page == 2 && component_id == 0x04 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_1_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x04 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_1_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 2
        else if (page == 2 && component_id == 0x10 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_2_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x10 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_2_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 3
        else if (page == 2 && component_id == 0x16 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_3_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x16 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_3_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 4
        else if (page == 2 && component_id == 0x1C && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_4_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x1C && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_4_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 5
        else if (page == 2 && component_id == 0x22 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_5_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x22 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_5_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 6
        else if (page == 2 && component_id == 0x28 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_6_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x28 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_6_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 7
        else if (page == 2 && component_id == 0x2E && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_7_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x2E && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_7_ENABLED, portMAX_DELAY)
        // CALIBRATION - SWITCH 8
        else if (page == 2 && component_id == 0x34 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_8_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x34 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_8_ENABLED, portMAX_DELAY)
        // INPUTCALIBP1 LOADED
        else if (page == 8 && component_id == 0x00)
            SEND_EMPTY_MSG(main_queue, INPUTCALIBP1_LOADED, portMAX_DELAY)
        // INPUTCALIBP2 LOADED
        else if (page == 9 && component_id == 0x00)
            SEND_EMPTY_MSG(main_queue, INPUTCALIBP2_LOADED, portMAX_DELAY)
        // INPUTCALIBP3 LOADED
        else if (page == 10 && component_id == 0x00)
            SEND_EMPTY_MSG(main_queue, INPUTCALIBP3_LOADED, portMAX_DELAY)
        // INPUTCALIBP4 LOADED
        else if (page == 11 && component_id == 0x00)
            SEND_EMPTY_MSG(main_queue, INPUTCALIBP4_LOADED, portMAX_DELAY)
        // INPUTCALIBP4 SAVE
        else if (page == 0x0B && component_id == 0x0A)
            SEND_EMPTY_MSG(main_queue, INPUTCALIBP4_SAVE_PRESSED, portMAX_DELAY)
        // UNKNOWN BUTTON
        else
        {
            ESP_LOGW(TAG, "file:%s,line:%u", __FILE__, __LINE__);
            ESP_LOGW(TAG, "page:0x%02x || component_id:0x%02x || event:0x%02x", page, component_id, event);
        }
    }
    else if (cmd_id == CUSTOM_EVENT_ID)
    {
        uint8_t page = cmd->custom_event.page;
        uint8_t component_id = cmd->custom_event.component_id;
        void *data = cmd->custom_event.data;
        int data_len = cmd->custom_event.data_len;

        // INPUTCALIBP1  TYPE RECEIVED
        if (page == 8 && component_id == 0x10)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP1_TYPE_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP1  CAPACITY RECEIVED
        else if (page == 8 && component_id == 0x09)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP1_CAPACITY_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP1  CAPACITY UNIT RECEIVED
        else if (page == 8 && component_id == 0x0F)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP1_CAPACITY_UNIT_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP1  SENSIBILITY RECEIVED
        else if (page == 8 && component_id == 0x0A)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP1_SENSIBILITY_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP1  SENSIBILITY UNIT RECEIVED
        else if (page == 8 && component_id == 0x0B)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP1_SENSIBILITY_UNIT_RECEIVED, data, data_len, portMAX_DELAY)

        // INPUTCALIBP1 SENSOR INDEX RECEIVED
        else if (page == 8 && component_id == 0x13)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP1_SENSOR_INDEX_RECEIVED, data, data_len, portMAX_DELAY)

        // INPUTCALIBP2 CALIBRATION LIMIT RECEIVED
        else if (page == 9 && component_id == 0x08)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP2_CALIBRATION_LIMIT_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP2  CALIBRATION LIMIT UNIT RECEIVED
        else if (page == 9 && component_id == 0x14)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP2_CALIBRATION_LIMIT_UNIT_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP2  LIMIT ENABLE RECEIVED
        else if (page == 9 && component_id == 0x0D)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP2_LIMIT_ENABLE_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP3 TABLE RECEIVED
        else if (page == 0x0A && component_id == 0x1C)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP3_TABLE_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP3 NUM POINTS RECEIVED
        else if (page == 0x0A && component_id == 0x32)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP3_NUM_POINTS_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP3 ROW TO FILL RECEIVED
        else if (page == 0x0A && component_id == 0x0C)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP3_ROW_TO_FILL_RECEIVED, data, data_len, portMAX_DELAY)
        // INPUTCALIBP4 NAME RECEIVED
        else if (page == 0x0B && component_id == 0x08)
            SEND_ADDR_MSG(main_queue, INPUTCALIBP4_NAME_RECEIVED, data, data_len, portMAX_DELAY)
    }
    else
    {
        ESP_LOGW(TAG, "file:%s,line:%u", __FILE__, __LINE__);
        ESP_LOGW(TAG, "cmd_id: 0x%02x ", cmd_id);
    }
}

void nextion_1_timer(TimerHandle_t xTimer)
{
    SEND_EMPTY_MSG(main_queue, NEXTION_UPDATE, portMAX_DELAY);
}

nextion_t nextion_1 = {
    .rx_queue_size = 10,
    .uart_buffer_size = 1024,
    .uRX_nTX_pin = uRX_nTX_PIN,
    .uTX_nRX_pin = uTX_nRX_PIN,
    .uart_num = NEXTION_UART_NUM,
    .uart_baudrate = NEXTION_BAUDRATE,
    .data_rcv_cb = data_rcv_1_cb,
    .code_rcv_cb = code_rcv_1_cb,
};

TimerHandle_t timer_handle = NULL;

void nextion_1_init()
{
    nextion_init(&nextion_1);
    timer_handle = xTimerCreate("nextion_timer", pdMS_TO_TICKS(200), pdTRUE, NULL, nextion_1_timer);
}

void nextion_1_start_timer()
{
    xTimerStart(timer_handle, portMAX_DELAY);
}

void nextion_1_stop_timer()
{
    xTimerStop(timer_handle, portMAX_DELAY);
}

void nextion_1_set_page(page_t new_page)
{
    page = new_page;
}

page_t nextion_1_get_page()
{
    return page;
}

/*
██╗  ██╗ ██████╗ ███╗   ███╗███████╗
██║  ██║██╔═══██╗████╗ ████║██╔════╝
███████║██║   ██║██╔████╔██║█████╗
██╔══██║██║   ██║██║╚██╔╝██║██╔══╝
██║  ██║╚██████╔╝██║ ╚═╝ ██║███████╗
╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝

*/

void nextion_1_home_sensor_1_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "home", 10, buff);
}
void nextion_1_home_sensor_2_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "home", 16, buff);
}
void nextion_1_home_sensor_3_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "home", 20, buff);
}
void nextion_1_home_sensor_4_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "home", 25, buff);
}
void nextion_1_home_sensor_5_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    nextion_write_text_global(&nextion_1, "home", 30, buff);
}
void nextion_1_home_sensor_6_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    nextion_write_text_global(&nextion_1, "home", 35, buff);
}
void nextion_1_home_sensor_7_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    nextion_write_text_global(&nextion_1, "home", 40, buff);
}
void nextion_1_home_sensor_8_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }

    nextion_write_text_global(&nextion_1, "home", 45, buff);
}

void nextion_1_home_sensor_1_write_dataps(float dataps)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", dataps);
    nextion_write_text_global(&nextion_1, "home", 12, buff);
}
void nextion_1_home_sensor_2_write_dataps(float dataps)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", dataps);
    nextion_write_text_global(&nextion_1, "home", 18, buff);
}
void nextion_1_home_sensor_3_write_dataps(float dataps)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", dataps);
    nextion_write_text_global(&nextion_1, "home", 22, buff);
}
void nextion_1_home_sensor_4_write_dataps(float dataps)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", dataps);
    nextion_write_text_global(&nextion_1, "home", 27, buff);
}
void nextion_1_home_sensor_5_write_dataps(float dataps, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", dataps);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", dataps);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "home", 32, buff);
}
void nextion_1_home_sensor_6_write_dataps(float dataps, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", dataps);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", dataps);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "home", 37, buff);
}
void nextion_1_home_sensor_7_write_dataps(float dataps, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", dataps);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", dataps);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "home", 42, buff);
}
void nextion_1_home_sensor_8_write_dataps(float dataps, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", dataps);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", dataps);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "home", 47, buff);
}

void nextion_1_home_sensor_5_write_unit(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 31, unit);
}
void nextion_1_home_sensor_6_write_unit(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 36, unit);
}
void nextion_1_home_sensor_7_write_unit(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 41, unit);
}
void nextion_1_home_sensor_8_write_unit(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 46, unit);
}

void nextion_1_home_sensor_5_write_unitps(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 33, unit);
}
void nextion_1_home_sensor_6_write_unitps(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 38, unit);
}
void nextion_1_home_sensor_7_write_unitps(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 43, unit);
}
void nextion_1_home_sensor_8_write_unitps(char *unit)
{
    nextion_write_text_global(&nextion_1, "home", 48, unit);
}

/*
 ██████╗ █████╗ ██╗     ██╗██████╗ ██████╗  █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
██╔════╝██╔══██╗██║     ██║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
██║     ███████║██║     ██║██████╔╝██████╔╝███████║   ██║   ██║██║   ██║██╔██╗ ██║
██║     ██╔══██║██║     ██║██╔══██╗██╔══██╗██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
╚██████╗██║  ██║███████╗██║██████╔╝██║  ██║██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
 ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

*/

void nextion_1_calibration_sensor_1_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "calibration", 7, buff);
}

void nextion_1_calibration_sensor_2_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "calibration", 12, buff);
}

void nextion_1_calibration_sensor_3_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "calibration", 16, buff);
}

void nextion_1_calibration_sensor_4_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "calibration", 20, buff);
}

void nextion_1_calibration_sensor_5_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "calibration", 24, buff);
}
void nextion_1_calibration_sensor_6_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "calibration", 28, buff);
}
void nextion_1_calibration_sensor_7_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "calibration", 32, buff);
}
void nextion_1_calibration_sensor_8_write_data(float data, int decimals)
{
    char buff[15] = {0};
    if (decimals == 2)
    {
        snprintf(buff, 15, "%.02f", data);
    }
    else if (decimals == 4)
    {
        snprintf(buff, 15, "%.04f", data);
    }
    else
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return;
    }
    nextion_write_text_global(&nextion_1, "calibration", 36, buff);
}

void nextion_1_calibration_sensor_5_write_unit(char *unit)
{
    nextion_write_combobox_global(&nextion_1, "calibration", 4, unit);
}
void nextion_1_calibration_sensor_6_write_unit(char *unit)
{
    nextion_write_combobox_global(&nextion_1, "calibration", 5, unit);
}
void nextion_1_calibration_sensor_7_write_unit(char *unit)
{
    nextion_write_combobox_global(&nextion_1, "calibration", 6, unit);
}
void nextion_1_calibration_sensor_8_write_unit(char *unit)
{
    nextion_write_combobox_global(&nextion_1, "calibration", 7, unit);
}

/*
██╗███╗   ██╗██████╗ ██╗   ██╗████████╗     ██████╗ █████╗ ██╗     ██╗██████╗     ██████╗ ██████╗
██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██╔════╝██╔══██╗██║     ██║██╔══██╗    ██╔══██╗╚════██╗
██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║     ███████║██║     ██║██████╔╝    ██████╔╝ █████╔╝
██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║     ██╔══██║██║     ██║██╔══██╗    ██╔═══╝  ╚═══██╗
██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╗██║  ██║███████╗██║██████╔╝    ██║     ██████╔╝
╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═════╝     ╚═╝     ╚═════╝

*/

void nextion_1_inputcalibp3_applied0_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 21, buffer);
}
void nextion_1_inputcalibp3_applied1_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 22, buffer);
}
void nextion_1_inputcalibp3_applied2_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 23, buffer);
}
void nextion_1_inputcalibp3_applied3_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 24, buffer);
}
void nextion_1_inputcalibp3_applied4_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 25, buffer);
}
void nextion_1_inputcalibp3_applied5_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 26, buffer);
}
void nextion_1_inputcalibp3_applied6_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 27, buffer);
}
void nextion_1_inputcalibp3_applied7_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 28, buffer);
}
void nextion_1_inputcalibp3_applied8_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 29, buffer);
}
void nextion_1_inputcalibp3_applied9_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 30, buffer);
}
void nextion_1_inputcalibp3_applied10_write(double val, int precision)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.*lf", precision, val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 31, buffer);
}


void nextion_1_inputcalibp3_adc0_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 32, buffer);
}
void nextion_1_inputcalibp3_adc1_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 33, buffer);
}
void nextion_1_inputcalibp3_adc2_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 34, buffer);
}
void nextion_1_inputcalibp3_adc3_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 35, buffer);
}
void nextion_1_inputcalibp3_adc4_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 36, buffer);
}
void nextion_1_inputcalibp3_adc5_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 37, buffer);
}
void nextion_1_inputcalibp3_adc6_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 38, buffer);
}
void nextion_1_inputcalibp3_adc7_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 39, buffer);
}
void nextion_1_inputcalibp3_adc8_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 40, buffer);
}
void nextion_1_inputcalibp3_adc9_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 41, buffer);
}
void nextion_1_inputcalibp3_adc10_write(double val)
{
    char buffer[15 + 1];
    snprintf(buffer, sizeof(buffer), "%.0f", val);
    nextion_write_text_global(&nextion_1, "inputcalibp3", 42, buffer);
}