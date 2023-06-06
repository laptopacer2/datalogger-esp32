#include "hx711_async.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_rom_sys.h"
#include "esp_intr_alloc.h"

#define TAG "HX711"

bool isr_service_installed = false;

#define NOP() __asm__ __volatile__("nop")
#define nNOP(x)                     \
    {                               \
        for (int i = 0; i < x; i++) \
        {                           \
            NOP();                  \
        }                           \
    }

#define PULSE(sck_pin)              \
    {                               \
        gpio_set_level(sck_pin, 1); \
        nNOP(10);                   \
        gpio_set_level(sck_pin, 0); \
        nNOP(10);                   \
    }

void IRAM_ATTR hx711_global_isr(void *arg)
{
    hx711_t *dev = (hx711_t *)arg;

    uint32_t count = 0;
    for (int i = 0; i < 24; i++)
    {
        PULSE(dev->sck_pin);

        count = count << 1;
        if (gpio_get_level(dev->dout_pin))
            count++;
    }

    if (dev->mux_pga == HX711_CH_A_GAIN_128)
    {
        PULSE(dev->sck_pin);
    }
    else if (dev->mux_pga == HX711_CH_A_GAIN_64)
    {
        PULSE(dev->sck_pin);
        PULSE(dev->sck_pin);
        PULSE(dev->sck_pin);
    }
    else
    { // HX711_CH_B_GAIN_32
        PULSE(dev->sck_pin);
        PULSE(dev->sck_pin);
    }

    count = count ^ 0x800000;

    // RUN DATA DONE CB
    if (dev->data_done_cb)
    {
        dev->data_done_cb(count);
    }
}

hx711_res_t hx711_init(hx711_t *dev)
{
    // CONFIG RATE PIN
    if (dev->rate_pin != -1)
    {
        gpio_config_t rate_conf = {};
        rate_conf.intr_type = GPIO_INTR_DISABLE;
        rate_conf.mode = GPIO_MODE_OUTPUT;
        rate_conf.pin_bit_mask = (1ULL << (dev->rate_pin));
        rate_conf.pull_down_en = 0;
        rate_conf.pull_up_en = 0;
        gpio_config(&rate_conf);

        if (dev->rate_hz == HX711_10HZ)
        {
            gpio_set_level(dev->rate_pin, 0);
        }
        else
        { // HX711_80HZ
            gpio_set_level(dev->rate_pin, 1);
        }
    }

    // CONFIG SCK PIN
    gpio_config_t sck_conf = {};
    sck_conf.intr_type = GPIO_INTR_DISABLE;
    sck_conf.mode = GPIO_MODE_OUTPUT;
    sck_conf.pin_bit_mask = (1ULL << (dev->sck_pin));
    sck_conf.pull_down_en = 0;
    sck_conf.pull_up_en = 0;
    gpio_config(&sck_conf);

    // CONFIG DOUT PIN
    gpio_config_t dout_conf = {};
    dout_conf.intr_type = GPIO_INTR_DISABLE;
    dout_conf.mode = GPIO_MODE_INPUT;
    dout_conf.pin_bit_mask = (1ULL << (dev->dout_pin));
    dout_conf.pull_down_en = 0;
    dout_conf.pull_up_en = 0;
    gpio_config(&dout_conf);

    if (!isr_service_installed)
    {
        isr_service_installed = true;

        // install gpio isr service
        gpio_install_isr_service(0);
    }

    // add handler for dout pin
    gpio_isr_handler_add(dev->dout_pin, hx711_global_isr, (void *)dev);
    gpio_intr_disable(dev->dout_pin);

    return HX711_OK;
}
hx711_res_t hx711_enable(hx711_t *dev)
{
    // power on
    gpio_set_level(dev->sck_pin, 0);

    // enable intr hw
    gpio_set_intr_type(dev->dout_pin, GPIO_INTR_LOW_LEVEL);
    gpio_intr_enable(dev->dout_pin);

    return HX711_OK;
}
hx711_res_t hx711_disable(hx711_t *dev)
{
    // disable intr hw
    gpio_intr_disable(dev->dout_pin);
    gpio_set_intr_type(dev->dout_pin, GPIO_INTR_DISABLE);

    // power off
    gpio_set_level(dev->sck_pin, 1);

    return HX711_OK;
}
