#include "configuration.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "project_defines.h"
#include "esp_log.h"
#include "string.h"

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

esp_err_t config_sensor_save(int index, sensor_config_t *config)
{
    char key[15] = {0};
    snprintf(key, sizeof(key), "%s%2i", NVS_KEY_CONFIG_BASE_STR, index);

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
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
esp_err_t config_sensor_load(int index, sensor_config_t *config)
{
    char key[15] = {0};
    snprintf(key, sizeof(key), "%s%2i", NVS_KEY_CONFIG_BASE_STR, index);

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
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
esp_err_t config_sensor_delete(int index)
{
    return ESP_OK;
}
esp_err_t config_get_unit_from_str(char *unit_str, sensor_unit_t *unit)
{

    bool unit_is_cm = (strcmp(unit_str, "cm") == 0);
    if (unit_is_cm)
    {
        *unit = DISPLACEMENT_UNIT_CM;
        return ESP_OK;
    }

    bool unit_is_in = (strcmp(unit_str, "in") == 0);
    if (unit_is_in)
    {
        *unit = DISPLACEMENT_UNIT_IN;
        return ESP_OK;
    }

    bool unit_is_mm = (strcmp(unit_str, "mm") == 0);
    if (unit_is_mm)
    {
        *unit = DISPLACEMENT_UNIT_MM;
        return ESP_OK;
    }

    bool unit_is_kN = (strcmp(unit_str, "kN") == 0);
    if (unit_is_kN)
    {
        *unit = LOAD_UNIT_KN;
        return ESP_OK;
    }
    bool unit_is_lbf = (strcmp(unit_str, "lbf") == 0);
    if (unit_is_lbf)
    {
        *unit = LOAD_UNIT_LBF;
        return ESP_OK;
    }
    bool unit_is_N = (strcmp(unit_str, "N") == 0);
    if (unit_is_N)
    {
        *unit = LOAD_UNIT_N;
        return ESP_OK;
    }
    bool unit_is_kgf = (strcmp(unit_str, "kgf") == 0);
    if (unit_is_kgf)
    {
        *unit = LOAD_UNIT_KGF;
        return ESP_OK;
    }

    bool unit_is_kPa = (strcmp(unit_str, "kPa") == 0);
    if (unit_is_kPa)
    {
        *unit = PRESSURE_UNIT_KPA;
        return ESP_OK;
    }
    bool unit_is_psi = (strcmp(unit_str, "psi") == 0);
    if (unit_is_psi)
    {
        *unit = PRESSURE_UNIT_PSI;
        return ESP_OK;
    }
    bool unit_is_ksf = (strcmp(unit_str, "ksf") == 0);
    if (unit_is_ksf)
    {
        *unit = PRESSURE_UNIT_KSF;
        return ESP_OK;
    }
    bool unit_is_MPa = (strcmp(unit_str, "MPa") == 0);
    if (unit_is_MPa)
    {
        *unit = PRESSURE_UNIT_MPA;
        return ESP_OK;
    }
    bool unit_is_kgf_cm2 = (strcmp(unit_str, "kgf/cm2") == 0);
    if (unit_is_kgf_cm2)
    {
        *unit = PRESSURE_UNIT_KGF_CM2;
        return ESP_OK;
    }

    bool unit_is_cm3 = (strcmp(unit_str, "cm3") == 0);
    if (unit_is_cm3)
    {
        *unit = VOLUME_UNIT_CM3;
        return ESP_OK;
    }
    bool unit_is_in3 = (strcmp(unit_str, "in3") == 0);
    if (unit_is_in3)
    {
        *unit = VOLUME_UNIT_IN3;
        return ESP_OK;
    }

    ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    return ESP_ERR_NOT_FOUND;
}
bool config_is_unit_ok(sensor_unit_t unit, sensor_type_t type)
{
    ESP_LOGI(TAG, "type:%d, unit:%d", type, unit);
    if (type == DISPLACEMENT)
    {
        uint8_t u = (uint8_t)(unit);
        uint8_t u_min = (uint8_t)(DISPLACEMENT_UNIT_CM);
        uint8_t u_max = (uint8_t)(DISPLACEMENT_UNIT_MM);
        return ((u >= u_min && u <= u_max) ? true : false);
    }
    else if (type == LOAD)
    {
        uint8_t u = (uint8_t)(unit);
        uint8_t u_min = (uint8_t)(LOAD_UNIT_KN);
        uint8_t u_max = (uint8_t)(LOAD_UNIT_KGF);
        return ((u >= u_min && u <= u_max) ? true : false);
    }
    else if (type == PRESSURE)
    {
        uint8_t u = (uint8_t)(unit);
        uint8_t u_min = (uint8_t)(PRESSURE_UNIT_KPA);
        uint8_t u_max = (uint8_t)(PRESSURE_UNIT_KGF_CM2);
        return ((u >= u_min && u <= u_max) ? true : false);
    }
    else if (type == VOLUME)
    {
        uint8_t u = (uint8_t)(unit);
        uint8_t u_min = (uint8_t)(VOLUME_UNIT_CM3);
        uint8_t u_max = (uint8_t)(VOLUME_UNIT_IN3);
        return ((u >= u_min && u <= u_max) ? true : false);
    }
    else
    {
        return false;
    }
}

//***************************************** TO:
//******************[to][from]    cm        in         mm
double displacement_fc[3][3] = {{1.000000, 2.5399986, 0.10000}, // cm
                                {0.393701, 1.0000000, 0.03937}, // in   FROM:
                                {10.00000, 25.400000, 1.0000}}; // mm

//******************************************* TO:
//**********[to][from]      kN          lbf         N          kgf
double load_fc[4][4] = {{1.0000000, 0.0044482, 0.0010000, 0.0098066}, // kN
                        {224.80900, 1.0000000, 0.2248089, 2.2046244}, // lbf   FROM:
                        {1000.0000, 4.4482216, 1.0000000, 9.8066520}, // N
                        {101.97162, 0.4535920, 0.1019716, 1.000000}}; // kgf

//*********************************************** TO:
//***************[to][from]     kPa         psi         ksf          MPa      kgf/cm2
double pressure_fc[5][5] = {{1.0000000, 6.8947448, 47.8803374, 1000.000000, 98.0392156}, // kPa
                            {0.1450380, 1.0000000, 6.94443960, 145.0389429, 14.2233348}, // psi   FROM:
                            {0.0208854, 0.1440001, 1.00000000, 20.88541630, 2.04812680}, // ksf
                            {0.0010000, 0.0068947, 0.04788030, 1.000000000, 0.09806800}, // MPa
                            {0.0102000, 0.0703070, 0.48825100, 10.19700000, 1.0000000}}; // kgf/cm2

//******************************** TO:
//************[to][from]     cm3           in3
double volume_fc[2][2] = {{1.00000000, 16.387064}, // cm3
                          {0.06102374, 1.000000}}; // in3   FROM:

double config_get_fc(sensor_unit_t old_unit, sensor_unit_t new_unit, sensor_type_t type)
{
    if (type == DISPLACEMENT)
    {
        return displacement_fc[new_unit][old_unit];
    }
    if (type == LOAD)
    {
        return load_fc[new_unit - LOAD_UNIT_KN][old_unit - LOAD_UNIT_KN];
    }
    if (type == PRESSURE)
    {
        return pressure_fc[new_unit - PRESSURE_UNIT_KPA][old_unit - PRESSURE_UNIT_KPA];
    }
    if (type == VOLUME)
    {
        return volume_fc[new_unit - VOLUME_UNIT_CM3][old_unit - VOLUME_UNIT_CM3];
    }

    return 1.0;
}