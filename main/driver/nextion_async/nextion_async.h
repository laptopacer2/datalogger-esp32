#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define NEXTION_MAX_TIMEOUT (0xffffffffUL)
#define NEXTION_PATTERN_CHR_NUM (3)
#define NEXTION_PATTERN_CHR ((char)0xff)
#define NEXTION_NUM_MAX 1

typedef enum
{
    NEXTION_OK,
    NEXTION_WAITING,
    NEXTION_ERROR,
    NEXTION_NO_AVAILABLE_TASK,
    NEXTION_TASK_NOT_CREATED,
} nextion_res_t;

typedef enum
{
    NEXTION_STARTUP_ID = 0x00,
    SERIAL_BUFFER_OVERFLOW_ID = 0x24,
    TOUCH_EVENT_ID = 0x65,
    CMD_ID_MAX = 0XFF,
} nextion_cmd_id_t;

typedef enum
{
    NEXTION_STARTUP_LEN = 6,
    SERIAL_BUFFER_OVERFLOW_LEN = 4,
    TOUCH_EVENT_LEN = 7,
    CMD_LEN_MAX = 0XFF,
} nextion_cmd_len_t;

typedef struct
{
    nextion_cmd_id_t id;
    nextion_cmd_len_t len;
    union
    {
        struct
        {
            uint8_t page;
            uint8_t component_id;
            uint8_t event;
        } touch_event;
    };

} nextion_cmd_t;

typedef void (*nextion_data_rcv_t)(uint8_t *buffer, int size);
typedef void (*nextion_code_rcv_t)(nextion_cmd_t *cmd);
typedef void (*nextion_task_t)(void *arg);

typedef struct
{
    // RUN TIME DEFINE
    QueueHandle_t rx_queue;
    // USER DEFINE
    int rx_queue_size; //  usually 10
    int uart_buffer_size; // usually 1024 bytes
    gpio_num_t uRX_nTX_pin;
    gpio_num_t uTX_nRX_pin;
    uart_port_t uart_num;
    int uart_baudrate;
    nextion_data_rcv_t data_rcv_cb;
    nextion_code_rcv_t code_rcv_cb;
} nextion_t;

nextion_res_t nextion_init(nextion_t *dev);
nextion_res_t nextion_write_text_global(nextion_t *dev,char* global, int text_index,  char* content);
