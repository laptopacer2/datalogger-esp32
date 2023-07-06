#include "nextion_async.h"
#include "stdbool.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "nextion_async.h"
#include "string.h"
#include "esp_log.h"

#define TAG "NEXTION_ASYNC"

void nextion_task_i0(void *arg);

int slot = 0;
nextion_task_t nextion_task[NEXTION_NUM_MAX] = {nextion_task_i0};

void nextion_task_i0(void *arg)
{
    // GET ATTRIBUTES
    nextion_t *dev = (nextion_t *)arg;
    int buf_size = dev->uart_buffer_size;
    uart_port_t uart_port = dev->uart_num;
    QueueHandle_t rx_queue = dev->rx_queue;
    nextion_data_rcv_t data_rcv_cb = dev->data_rcv_cb;
    nextion_code_rcv_t code_rcv_cb = dev->code_rcv_cb;

    // RAM ALLOC FOR RX BYTES
    uint8_t *dtmp = (uint8_t *)malloc(buf_size);

    while (1)
    {
        // WAIT FOR EVENT
        uart_event_t event;
        xQueueReceive(rx_queue, (void *)&event, portMAX_DELAY);
        bzero(dtmp, buf_size);

        // EXECUTE EVENT
        switch (event.type)
        {
        case UART_DATA:
            /*
            int n = uart_read_bytes(uart_port, dtmp, event.size, portMAX_DELAY);
            if (n != event.size)
            {
                uart_flush_input(uart_port);
                ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
                break;
            }
            // EXECUTE USER CALLBACK
            if (data_rcv_cb)
                data_rcv_cb(dtmp, n);
            */
            break;
        case UART_FIFO_OVF:
            uart_flush_input(uart_port);
            xQueueReset(rx_queue);
            ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
            break;
        case UART_BUFFER_FULL:
            uart_flush_input(uart_port);
            xQueueReset(rx_queue);
            ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
            break;
        case UART_BREAK:
            ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
            break;
        case UART_PARITY_ERR:
            ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
            break;
        case UART_FRAME_ERR:
            ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
            break;
        case UART_PATTERN_DET:

            ///// GET UART PATTERN
            int pos = uart_pattern_pop_pos(uart_port);
            if (pos == -1)
            {
                ESP_LOGW(TAG, "file:%s,line:%i", __FILE__, __LINE__);
                uart_flush_input(uart_port);
                break;
            }
            uart_read_bytes(uart_port, dtmp, pos, 100 / portTICK_PERIOD_MS);
            uart_read_bytes(uart_port, dtmp + pos, NEXTION_PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
            int pattern_len = pos + NEXTION_PATTERN_CHR_NUM;

            ///// GET NEXTION PATTERN
            bool is_touch_event = ((dtmp[0] == TOUCH_EVENT_ID) && (pattern_len == TOUCH_EVENT_LEN));
            bool is_custom_event = ((dtmp[0] == CUSTOM_EVENT_ID) && (pattern_len >= 6));
            nextion_cmd_t cmd;
            if (is_touch_event)
            {
                cmd.id = TOUCH_EVENT_ID;
                cmd.len = TOUCH_EVENT_LEN;
                cmd.touch_event.page = dtmp[1];
                cmd.touch_event.component_id = dtmp[2];
                cmd.touch_event.event = dtmp[3];
            }
            else if (is_custom_event)
            {
                cmd.id = CUSTOM_EVENT_ID;
                cmd.len = pattern_len;
                cmd.custom_event.page = dtmp[1];
                cmd.custom_event.component_id = dtmp[2];
                int data_len = pattern_len - 6; // 3 BYTE PREAMBLE + 3 BYTE ENDED(FF FF FF)
                cmd.custom_event.data_len = data_len;
                if (data_len > 0)
                {
                    void *data = calloc(data_len + 1, 1); // +1 for null terminated str
                    memcpy(data, dtmp + 3, data_len);
                    cmd.custom_event.data = data;
                }
            }
            else
            {
                break;
            }

            ///// EXECUTE USER CALLBACK
            if (code_rcv_cb)
                code_rcv_cb(&cmd);

            break;

        default:
            ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
            break;
        }
    }
}

nextion_res_t nextion_init(nextion_t *dev)
{
    // CHECK AVAILABLE SLOT
    if (slot >= NEXTION_NUM_MAX)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_NO_AVAILABLE_TASK;
    }

    // UART CONFIG
    uart_config_t uart_config = {
        .baud_rate = (dev->uart_baudrate),
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install((dev->uart_num),
                        (dev->uart_buffer_size) * 2, (dev->uart_buffer_size) * 2,
                        (dev->rx_queue_size), &(dev->rx_queue),
                        0);
    uart_param_config((dev->uart_num), &uart_config);
    uart_set_pin((dev->uart_num), (dev->uTX_nRX_pin), (dev->uRX_nTX_pin), UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_enable_pattern_det_baud_intr((dev->uart_num), NEXTION_PATTERN_CHR, NEXTION_PATTERN_CHR_NUM, 11, 0, 0); // 11
    uart_pattern_queue_reset((dev->uart_num), (dev->rx_queue_size));

    // CREATE TASK
    BaseType_t res = xTaskCreate(nextion_task[slot], "nextion task", 2 * 1024, (void *)dev, 4, NULL);
    if (res != pdPASS)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_TASK_NOT_CREATED;
    }

    slot++;
    return NEXTION_OK;
}

nextion_res_t nextion_write_text_global(nextion_t *dev, char *global, int text_index, char *content)
{

    char buff[100] = {0};
    int size = snprintf(buff, sizeof(buff), "%s.t%i.txt=\"%s\"\xff\xff\xff", global, text_index, content);

    if (size < 0 || size >= sizeof(buff))
    {
        ESP_LOGE(TAG, "file:%s,line:%i, size:%i", __FILE__, __LINE__, size);
        return NEXTION_ERROR;
    }

    int n = uart_write_bytes(dev->uart_num, buff, size);
    if (n != size)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    return NEXTION_OK;
}

nextion_res_t nextion_write_combobox_global(nextion_t *dev, char *global, int combobox_index, char *content)
{

    char buff[100] = {0};
    int size = snprintf(buff, sizeof(buff), "%s.cb%i.txt=\"%s\"\xff\xff\xff", global, combobox_index, content);

    if (size < 0 || size >= sizeof(buff))
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    int n = uart_write_bytes(dev->uart_num, buff, size);
    if (n != size)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    return NEXTION_OK;
}
nextion_res_t nextion_set_path_global(nextion_t *dev, char *global, char *obj, char *path)
{
    char buff[100] = {0};
    int size = snprintf(buff, sizeof(buff), "%s.%s.path=\"%s\"\xff\xff\xff", global, obj, path);

    if (size < 0 || size >= sizeof(buff))
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    int n = uart_write_bytes(dev->uart_num, buff, size);
    if (n != size)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    return NEXTION_OK;
}
nextion_res_t nextion_set_pco_global(nextion_t *dev, char *global, char *obj, uint32_t txt_color)
{
    char buff[100] = {0};
    int size = snprintf(buff, sizeof(buff), "%s.%s.pco=%lu\xff\xff\xff", global, obj, txt_color);

    if (size < 0 || size >= sizeof(buff))
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    int n = uart_write_bytes(dev->uart_num, buff, size);
    if (n != size)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    return NEXTION_OK;
}
nextion_res_t nextion_set_val_global(nextion_t *dev, char *global, char *obj, int32_t val)
{
    char buff[100] = {0};
    int size = snprintf(buff, sizeof(buff), "%s.%s.val=%li\xff\xff\xff", global, obj, val);

    if (size < 0 || size >= sizeof(buff))
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    int n = uart_write_bytes(dev->uart_num, buff, size);
    if (n != size)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    return NEXTION_OK;
}
nextion_res_t nextion_set_txt_global(nextion_t *dev, char *global, char *obj, char *txt)
{
    char buff[100] = {0};
    int size = snprintf(buff, sizeof(buff), "%s.%s.txt=\"%s\"\xff\xff\xff", global, obj, txt);

    if (size < 0 || size >= sizeof(buff))
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    int n = uart_write_bytes(dev->uart_num, buff, size);
    if (n != size)
    {
        ESP_LOGE(TAG, "file:%s,line:%i", __FILE__, __LINE__);
        return NEXTION_ERROR;
    }

    return NEXTION_OK;
}