#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define SEND_EMPTY_MSG(queue_dest, msg_type, timeout_ticks) \
    {                                                       \
        msg_t msg;                                          \
        msg.type = msg_type;                                \
        xQueueSend(queue_dest, &msg, timeout_ticks);        \
    }
#define SEND2FRONT_EMPTY_MSG(queue_dest, msg_type, timeout_ticks) \
    {                                                             \
        msg_t msg;                                                \
        msg.type = msg_type;                                      \
        xQueueSendToFront(queue_dest, &msg, timeout_ticks);       \
    }
#define SEND_ADDR_MSG(_queue_dest, _msg_type, _content, _size, _timeout_ticks) \
    {                                                                          \
        msg_t msg;                                                             \
        msg.type = _msg_type;                                                  \
        msg.content.addr = _content;                                           \
        msg.size = _size;                                                      \
        xQueueSend(_queue_dest, &msg, _timeout_ticks);                         \
    }
extern QueueHandle_t main_queue;
extern QueueHandle_t tx_queue;
void main_task(void *arg);
void nextion_rx_task(void *arg);
void nextion_tx_task(void *arg);
