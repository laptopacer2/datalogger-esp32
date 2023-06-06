
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

void data_rcv_1_cb(uint8_t *buffer, int size)
{
    ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
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
        // HOME - TARA 5 BUTTON
        else if (page == 0 && component_id == 0x20 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_5_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x20 && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_5_ENABLED, portMAX_DELAY)
        // HOME - TARA 6 BUTTON
        else if (page == 0 && component_id == 0x27 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_6_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x27 && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_6_ENABLED, portMAX_DELAY)
        // HOME - TARA 7 BUTTON
        else if (page == 0 && component_id == 0x2E && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_7_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x2E && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_7_ENABLED, portMAX_DELAY)
        // HOME - TARA 8 BUTTON
        else if (page == 0 && component_id == 0x35 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_8_DISABLED, portMAX_DELAY)
        else if (page == 0 && component_id == 0x35 && event == 0x04)
            SEND_EMPTY_MSG(main_queue, HOME_TARA_8_ENABLED, portMAX_DELAY)
        // SYSTEM SETTINGS
        else if (page == 1 && component_id == 0x00)
            SEND2FRONT_EMPTY_MSG(main_queue, SYSTEM_SETTINGS_LOADED, portMAX_DELAY)
        // CALIBRATION
        else if (page == 2 && component_id == 0x00)
            SEND2FRONT_EMPTY_MSG(main_queue, CALIBRATION_LOADED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x10 && event == 0x02)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_2_DISABLED, portMAX_DELAY)
        else if (page == 2 && component_id == 0x10 && event == 0x03)
            SEND_EMPTY_MSG(main_queue, CALIBRATION_SWITCH_2_ENABLED, portMAX_DELAY)
        // UNKNOWN BUTTON
        else
        {
            ESP_LOGW(TAG, "file:%s,line:%u", __FILE__, __LINE__);
            ESP_LOGW(TAG, "page:0x%02x || component_id:0x%02x || event:0x%02x", page, component_id, event);
        }
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

void nextion_1_home_sensor_2_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "home", 16, buff);
}

void nextion_1_home_sensor_2_write_dataps(float dataps)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", dataps);
    nextion_write_text_global(&nextion_1, "home", 18, buff);
}

void nextion_1_calibration_sensor_2_write_data(float data)
{
    char buff[15] = {0};
    snprintf(buff, 15, "%.02f", data);
    nextion_write_text_global(&nextion_1, "calibration", 12, buff);
}