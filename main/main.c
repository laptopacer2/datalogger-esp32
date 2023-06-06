
#include "esp_log.h"
#include "project_defines.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "project_tasks.h"

#define TAG "MAIN"

void app_main(void)
{
    ESP_LOGI(TAG, "START");
    xTaskCreate(main_task, "main_task", 4 * 1024, NULL, 2, NULL);
}
