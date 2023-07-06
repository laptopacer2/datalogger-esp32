#include "configuration.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "project_defines.h"
#include "esp_log.h"

#define TAG "SENSOR_CONFIG"

static bool is_initialized = false;

void config_init()
{
    if (is_initialized)
        return;

    // set local variables

    // init nvs
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_LOGW(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_flash_erase();
        err = nvs_flash_init();
    }

    is_initialized = ((err == ESP_OK) ? true : false);
}

static esp_err_t config_sensor_save(sensor_config_t *config, char *namespace, char *key)
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return err;
    }
    err = nvs_set_blob(handle, key, config, sizeof(sensor_config_t));
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return err;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return err;
    }
    nvs_close(handle);
    return err;
}
static esp_err_t config_sensor_load(sensor_config_t *config, char *namespace, char *key)
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return err;
    }
    size_t size = sizeof(sensor_config_t);
    err = nvs_get_blob(handle, key, config, &size);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return err;
    }

    nvs_close(handle);
    return err;
}
void config_sensor_1_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_1_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_2_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_2_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_3_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_3_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_4_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_4_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_5_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_5_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_6_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_6_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_7_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_7_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void config_sensor_8_save(sensor_config_t *config)
{
    esp_err_t err = config_sensor_save(config, NVS_NAMESPACE, NVS_KEY_SENSOR_8_CONFIG);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
esp_err_t config_sensor_1_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_1_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_2_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_2_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_3_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_3_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_4_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_4_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_5_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_5_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_6_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_6_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_7_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_7_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
esp_err_t config_sensor_8_load(sensor_config_t *config)
{
    esp_err_t err = config_sensor_load(config, NVS_NAMESPACE, NVS_KEY_SENSOR_8_CONFIG);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);

    return err;
}
