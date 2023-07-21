#include "project_typedefs.h"
#include "stdbool.h"
#include "string.h"
#include "esp_log.h"
#include "calibration.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_err.h"

#define TAG "INPUT_CALIBRATION"

static sensor_calib_t calibration;
static int _index;
static row_to_fill_t row_to_fill;
static bool is_initialized = false;

void inputCalib_init()
{
    if (is_initialized)
        return;

    // set local variables
    calibration = SENSOR_CALIB_DEFAULT;
    _index = 0;
    row_to_fill = ROW_NOT_TO_FILL;

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
void inputCalib_set_sensor_type(char *type_str)
{
    bool is_type_displacement = (strcmp(type_str, "DISPLACEMENT") == 0);
    if (is_type_displacement)
    {
        calibration.sensor_type = DISPLACEMENT;
        ESP_LOGI(TAG, "SENSOR TYPE: DISPLACEMENT");
        return;
    }

    bool is_type_load = (strcmp(type_str, "LOAD") == 0);
    if (is_type_load)
    {
        calibration.sensor_type = LOAD;
        ESP_LOGI(TAG, "SENSOR TYPE: LOAD");
        return;
    }

    bool is_type_pressure = (strcmp(type_str, "PRESSURE") == 0);
    if (is_type_pressure)
    {
        calibration.sensor_type = PRESSURE;
        ESP_LOGI(TAG, "SENSOR TYPE: PRESSURE");
        return;
    }

    bool is_type_volume = (strcmp(type_str, "VOLUME") == 0);
    if (is_type_volume)
    {
        calibration.sensor_type = VOLUME;
        ESP_LOGI(TAG, "SENSOR TYPE: VOLUME");
        return;
    }

    ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
}
void inputCalib_set_capacity(char *capacity_str)
{
    calibration.capacity = atof(capacity_str);
    ESP_LOGI(TAG, "capacity : %f", calibration.capacity);
}
void inputCalib_set_unit(char *unit_str)
{
    if (calibration.sensor_type == DISPLACEMENT)
    {
        bool unit_is_cm = (strcmp(unit_str, "cm") == 0);
        if (unit_is_cm)
        {
            calibration.unit = DISPLACEMENT_UNIT_CM;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_CM");
            return;
        }

        bool unit_is_in = (strcmp(unit_str, "in") == 0);
        if (unit_is_in)
        {
            calibration.unit = DISPLACEMENT_UNIT_IN;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_IN");
            return;
        }

        bool unit_is_mm = (strcmp(unit_str, "mm") == 0);
        if (unit_is_mm)
        {
            calibration.unit = DISPLACEMENT_UNIT_MM;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_MM");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else if (calibration.sensor_type == LOAD)
    {
        bool unit_is_kN = (strcmp(unit_str, "kN") == 0);
        if (unit_is_kN)
        {
            calibration.unit = LOAD_UNIT_KN;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_KN");
            return;
        }
        bool unit_is_lbf = (strcmp(unit_str, "lbf") == 0);
        if (unit_is_lbf)
        {
            calibration.unit = LOAD_UNIT_LBF;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_LBF");
            return;
        }
        bool unit_is_N = (strcmp(unit_str, "N") == 0);
        if (unit_is_N)
        {
            calibration.unit = LOAD_UNIT_N;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_N");
            return;
        }
        bool unit_is_kgf = (strcmp(unit_str, "kgf") == 0);
        if (unit_is_kgf)
        {
            calibration.unit = LOAD_UNIT_KGF;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_KGF");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else if (calibration.sensor_type == PRESSURE)
    {
        bool unit_is_kPa = (strcmp(unit_str, "kPa") == 0);
        if (unit_is_kPa)
        {
            calibration.unit = PRESSURE_UNIT_KPA;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KPA");
            return;
        }
        bool unit_is_psi = (strcmp(unit_str, "psi") == 0);
        if (unit_is_psi)
        {
            calibration.unit = PRESSURE_UNIT_PSI;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_PSI");
            return;
        }
        bool unit_is_ksf = (strcmp(unit_str, "ksf") == 0);
        if (unit_is_ksf)
        {
            calibration.unit = PRESSURE_UNIT_KSF;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KSF");
            return;
        }
        bool unit_is_MPa = (strcmp(unit_str, "MPa") == 0);
        if (unit_is_MPa)
        {
            calibration.unit = PRESSURE_UNIT_MPA;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_MPA");
            return;
        }
        bool unit_is_kgf_cm2 = (strcmp(unit_str, "kgf/cm2") == 0);
        if (unit_is_kgf_cm2)
        {
            calibration.unit = PRESSURE_UNIT_KGF_CM2;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KGF_CM2");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else if (calibration.sensor_type == VOLUME)
    {
        bool unit_is_cm3 = (strcmp(unit_str, "cm3") == 0);
        if (unit_is_cm3)
        {
            calibration.unit = VOLUME_UNIT_CM3;
            ESP_LOGI(TAG, "SENSOR UNIT: VOLUME_UNIT_CM3");
            return;
        }
        bool unit_is_in3 = (strcmp(unit_str, "in3") == 0);
        if (unit_is_in3)
        {
            calibration.unit = VOLUME_UNIT_IN3;
            ESP_LOGI(TAG, "SENSOR UNIT: VOLUME_UNIT_IN3");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
void inputCalib_set_sensibility(char *sensibility_str)
{
    calibration.sensibility_val = atof(sensibility_str);
    ESP_LOGI(TAG, "sensibility : %lf", calibration.sensibility_val);
}
void inputCalib_set_sensibility_unit(char *unit_str)
{
    bool unit_is_mV_V = (strcmp(unit_str, "mV/V") == 0);
    if (unit_is_mV_V)
    {
        calibration.sensibility_unit = SENSIBILITY_UNIT_MV_V;
        ESP_LOGI(TAG, "SENSIBILITY UNIT: MV_V");
        return;
    }
    bool unit_is_V_V = (strcmp(unit_str, "V/V") == 0);
    if (unit_is_V_V)
    {
        calibration.sensibility_unit = SENSIBILITY_UNIT_V_V;
        ESP_LOGI(TAG, "SENSIBILITY UNIT: V_V");
        return;
    }

    ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
}
void inputCalib_set_limit(char *limit_str)
{
    calibration.limit_val = atof(limit_str);
    ESP_LOGI(TAG, "calibration_limit : %f", calibration.limit_val);

    char *ptr = strtok(limit_str, ".");
    ptr = strtok(NULL, ".");
    calibration.num_decimals = ptr ? strlen(ptr) : 0;
    ESP_LOGI(TAG, "decimals_precision : %i", calibration.num_decimals);
}
void inputCalib_set_limit_enable(void *limit_enable)
{
    calibration.limit_enabled = (*(uint8_t *)limit_enable) == 1;
    ESP_LOGI(TAG, "limit_enabled : %s ", (calibration.limit_enabled == true) ? "true" : "false");
}
void inputCalib_set_table(char *table_str)
{
    char *ptr;

    ESP_LOGI(TAG, "TABLE RECEIVED FROM NEXTION:");
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i == 0 && j == 0)
                ptr = strtok(table_str, "-");
            else
                ptr = strtok(NULL, "-");

            if (ptr == NULL)
                calibration.table[i][j] = 0.0;
            else
                calibration.table[i][j] = atof(ptr);
        }
        ESP_LOGI(TAG, "%.*f  %.*f",
                 calibration.num_decimals, calibration.table[i][0],
                 calibration.num_decimals, calibration.table[i][1]);
    }
}
table_t inputCalib_set_num_points(char *num_points_str)
{
    int num_decimals = inputCalib_get_num_decimals();

    if (strcmp(num_points_str, "1 Point") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 1");
        calibration.num_points = NUM_POINTS_1;
        table_t table = calloc(TABLE_NUM_ROWS, sizeof(row_t));

        for (int i = 0; i < TABLE_NUM_ROWS; i++)
        {
            double value;
            if (i <= calibration.num_points)
                value = 0.00 + i * ((calibration.limit_enabled) ? calibration.limit_val : calibration.capacity) / 1.0;
            else
                value = 0.00;

            snprintf(table[i][0], sizeof(table[i][0]), "%.*lf", num_decimals, value);
            snprintf(table[i][1], sizeof(table[i][1]), "%.*lf", num_decimals, 0.0);
        }
        return table;
    }
    else if (strcmp(num_points_str, "5 Points") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 5");
        calibration.num_points = NUM_POINTS_5;
        table_t table = calloc(TABLE_NUM_ROWS, sizeof(row_t));

        for (int i = 0; i < TABLE_NUM_ROWS; i++)
        {
            double value;
            if (i <= calibration.num_points)
                value = 0.00 + i * ((calibration.limit_enabled) ? calibration.limit_val : calibration.capacity) / 5.0;
            else
                value = 0.00;

            snprintf(table[i][0], sizeof(table[i][0]), "%.*lf", num_decimals, value);
            snprintf(table[i][1], sizeof(table[i][1]), "%.*lf", num_decimals, 0.0);
        }
        return table;
    }
    else if (strcmp(num_points_str, "10 Points") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 10");
        calibration.num_points = NUM_POINTS_10;
        table_t table = calloc(TABLE_NUM_ROWS, sizeof(row_t));

        for (int i = 0; i < TABLE_NUM_ROWS; i++)
        {
            double value;
            if (i <= calibration.num_points)
                value = 0.00 + i * ((calibration.limit_enabled) ? calibration.limit_val : calibration.capacity) / 10.0;
            else
                value = 0.00;

            snprintf(table[i][0], sizeof(table[i][0]), "%.*lf", num_decimals, value);
            snprintf(table[i][1], sizeof(table[i][1]), "%.*lf", num_decimals, 0.0);
        }
        return table;
    }
    else
    {
        ESP_LOGI(TAG, "NUM POINTS: Custom");
        calibration.num_points = NUM_POINTS_CUSTOM;
        table_t table = calloc(TABLE_NUM_ROWS, sizeof(row_t));

        for (int i = 0; i < TABLE_NUM_ROWS; i++)
        {
            snprintf(table[i][0], sizeof(table[i][0]), "%.*lf", num_decimals, 0.0);
            snprintf(table[i][1], sizeof(table[i][1]), "%.*lf", num_decimals, 0.0);
        }
        return table;
    }
}
void inputCalib_set_row_to_fill(void *_row_to_fill)
{
    switch (*(uint8_t *)_row_to_fill)
    {
    case 0:
        row_to_fill = ROW_0_TO_FILL;
        break;
    case 1:
        row_to_fill = ROW_1_TO_FILL;
        break;
    case 2:
        row_to_fill = ROW_2_TO_FILL;
        break;
    case 3:
        row_to_fill = ROW_3_TO_FILL;
        break;
    case 4:
        row_to_fill = ROW_4_TO_FILL;
        break;
    case 5:
        row_to_fill = ROW_5_TO_FILL;
        break;
    case 6:
        row_to_fill = ROW_6_TO_FILL;
        break;
    case 7:
        row_to_fill = ROW_7_TO_FILL;
        break;
    case 8:
        row_to_fill = ROW_8_TO_FILL;
        break;
    case 9:
        row_to_fill = ROW_9_TO_FILL;
        break;
    case 10:
        row_to_fill = ROW_10_TO_FILL;
        break;
    default:
        row_to_fill = ROW_NOT_TO_FILL;
        break;
    }

    ESP_LOGI(TAG, "row_to_fill : %x", row_to_fill);
}
void inputCalib_set_name(char *name_str)
{
    int name_len = strlen(name_str);
    if (name_len <= CALIB_NAME_LEN_MAX)
    {
        memset(calibration.name, 0, sizeof(calibration.name));
        memcpy(calibration.name, name_str, name_len);
        calibration.name_len = name_len;

        ESP_LOGI(TAG, "NAME:%*s", calibration.name_len, calibration.name);
    }
    else
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
static esp_err_t nvs_save_calibration_parameters(int index, char *namespace, char **info)
{
    char key[15];
    snprintf(key, sizeof(key), "%s%2i", NVS_KEY_CALIB_BASE_STR, index);

    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        *info = "Error: can't open nvs storage";
        return ESP_FAIL;
    }
    err = nvs_set_blob(handle, key, &calibration, sizeof(sensor_calib_t));
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        *info = "Error: can't set calibration parameters";
        return ESP_FAIL;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        *info = "Error: can't commit calibration parameters";
        return ESP_FAIL;
    }
    nvs_close(handle);
    *info = "Success: calibration parameters saved";
    return ESP_OK;
}
static esp_err_t nvs_load_calibration_parameters(int index, char *namespace, sensor_calib_t *out, size_t *len)
{
    char key[15];
    snprintf(key, sizeof(key), "%s%2i", NVS_KEY_CALIB_BASE_STR, index);

    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return ESP_FAIL;
    }
    err = nvs_get_blob(handle, key, out, len);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return ESP_FAIL;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return ESP_FAIL;
    }
    nvs_close(handle);
    return ESP_OK;
}
static esp_err_t nvs_delete_calibration_parameters(int index, char *namespace)
{
    char key[15];
    snprintf(key, sizeof(key), "%s%2i", NVS_KEY_CALIB_BASE_STR, index);

    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return ESP_FAIL;
    }
    err = nvs_erase_key(handle, key);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return ESP_FAIL;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return ESP_FAIL;
    }
    nvs_close(handle);
    return ESP_OK;
}
esp_err_t inputCalib_save(char **info)
{
    ESP_LOGI(TAG, "INPUTCALIB SAVE");

    if (_index >= 0 && _index < NUM_SENSORS)
    {
        return nvs_save_calibration_parameters(_index, NVS_NAMESPACE, info);
    }
    else
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        *info = "Error: invalid sensor";
        return ESP_FAIL;
    }
}
esp_err_t inputCalib_load(int i, sensor_calib_t *out)
{
    ESP_LOGI(TAG, "INPUTCALIB LOAD");

    if (i >= 0 && i < NUM_SENSORS)
    {
        size_t len = sizeof(sensor_calib_t);
        return nvs_load_calibration_parameters(i, NVS_NAMESPACE, out, &len);
    }
    else
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return ESP_FAIL;
    }
}
void inputCalib_delete(int i)
{
    ESP_LOGI(TAG, "INPUTCALIB DELETE");

    if (i >= 0 && i < NUM_SENSORS)
    {
        nvs_delete_calibration_parameters(i, NVS_NAMESPACE);
    }
    else
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
}
esp_err_t inputCalib_load_last_saved(int *i, sensor_calib_t *out)
{
    ESP_LOGI(TAG, "INPUTCALIB LOAD LAST SAVED");

    if (_index >= 0 && _index < NUM_SENSORS)
    {
        size_t len = sizeof(sensor_calib_t);
        *i = _index;
        return nvs_load_calibration_parameters(_index, NVS_NAMESPACE, out, &len);
    }
    else
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return ESP_FAIL;
    }
}
int inputCalib_get_num_decimals()
{
    return calibration.num_decimals;
}
void inputCalib_set_index(void *i)
{
    int n = *(uint8_t *)i;
    if (n >= 0 && n < NUM_SENSORS)
        _index = n;

    ESP_LOGI(TAG, "index:%i", _index);
}
int inputCalib_get_index()
{
    return _index;
}
row_to_fill_t inputCalib_get_row_to_fill()
{
    return row_to_fill;
}
