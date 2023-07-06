#include "project_typedefs.h"
#include "stdbool.h"
#include "string.h"
#include "esp_log.h"
#include "calibration.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_err.h"

#define TAG "INPUT_CALIBRATION"

static calib_params_t calibration;
static sensor_under_calibration_t sensor_under_calibration;
static row_to_fill_t row_to_fill;
static bool is_initialized = false;

void inputCalib_init()
{
    if (is_initialized)
        return;

    // set local variables
    calibration = CALIB_PARAMS_DEFAULT;
    sensor_under_calibration = NO_SENSOR_UNDER_CALIBRATION;
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
            calibration.unit.displacement_unit = DISPLACEMENT_UNIT_CM;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_CM");
            return;
        }

        bool unit_is_in = (strcmp(unit_str, "IN") == 0);
        if (unit_is_in)
        {
            calibration.unit.displacement_unit = DISPLACEMENT_UNIT_IN;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_IN");
            return;
        }

        bool unit_is_mm = (strcmp(unit_str, "MM") == 0);
        if (unit_is_mm)
        {
            calibration.unit.displacement_unit = DISPLACEMENT_UNIT_MM;
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
            calibration.unit.load_unit = LOAD_UNIT_KN;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_KN");
            return;
        }
        bool unit_is_lbf = (strcmp(unit_str, "lbf") == 0);
        if (unit_is_lbf)
        {
            calibration.unit.load_unit = LOAD_UNIT_LBF;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_LBF");
            return;
        }
        bool unit_is_N = (strcmp(unit_str, "N") == 0);
        if (unit_is_N)
        {
            calibration.unit.load_unit = LOAD_UNIT_N;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_N");
            return;
        }
        bool unit_is_kgf = (strcmp(unit_str, "kgf") == 0);
        if (unit_is_kgf)
        {
            calibration.unit.load_unit = LOAD_UNIT_KGF;
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
            calibration.unit.pressure_unit = PRESSURE_UNIT_KPA;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KPA");
            return;
        }
        bool unit_is_psi = (strcmp(unit_str, "psi") == 0);
        if (unit_is_psi)
        {
            calibration.unit.pressure_unit = PRESSURE_UNIT_PSI;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_PSI");
            return;
        }
        bool unit_is_ksf = (strcmp(unit_str, "ksf") == 0);
        if (unit_is_ksf)
        {
            calibration.unit.pressure_unit = PRESSURE_UNIT_KSF;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KSF");
            return;
        }
        bool unit_is_MPa = (strcmp(unit_str, "MPa") == 0);
        if (unit_is_MPa)
        {
            calibration.unit.pressure_unit = PRESSURE_UNIT_MPA;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_MPA");
            return;
        }
        bool unit_is_kgf_cm2 = (strcmp(unit_str, "kgf/cm2") == 0);
        if (unit_is_kgf_cm2)
        {
            calibration.unit.pressure_unit = PRESSURE_UNIT_KGF_CM2;
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
            calibration.unit.volume_unit = VOLUME_UNIT_CM3;
            ESP_LOGI(TAG, "SENSOR UNIT: VOLUME_UNIT_CM3");
            return;
        }
        bool unit_is_in3 = (strcmp(unit_str, "in3") == 0);
        if (unit_is_in3)
        {
            calibration.unit.volume_unit = VOLUME_UNIT_IN3;
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
    calibration.decimals_precision = ptr ? strlen(ptr) : 0;
    ESP_LOGI(TAG, "decimals_precision : %i", calibration.decimals_precision);
}
void inputCalib_set_limit_enable(void *limit_enable)
{
    calibration.limit_enabled = (*(uint8_t *)limit_enable) == 1;
    ESP_LOGI(TAG, "limit_enabled : %s ", (calibration.limit_enabled == true) ? "true" : "false");
}
void inputCalib_set_table(char *table_str)
{
    char *ptr;

    ESP_LOGI(TAG, "TABLE:");
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
                 calibration.decimals_precision, calibration.table[i][0],
                 calibration.decimals_precision, calibration.table[i][1]);
    }
}
table_t inputCalib_set_num_points(char *num_points_str)
{

    if (strcmp(num_points_str, "1 Point") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 1");
        calibration.num_points = NUM_POINTS_1;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            if (i <= calibration.num_points)
                row[i][0] = 0.00 + i * ((calibration.limit_enabled) ? calibration.limit_val : calibration.capacity) / 1.0;
            else
                row[i][0] = 0.00;
        }
        return row;
    }
    else if (strcmp(num_points_str, "5 Points") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 5");
        calibration.num_points = NUM_POINTS_5;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            if (i <= calibration.num_points)
                row[i][0] = 0.00 + i * ((calibration.limit_enabled) ? calibration.limit_val : calibration.capacity) / 5.0;
            else
                row[i][0] = 0.00;
        }
        return row;
    }
    else if (strcmp(num_points_str, "10 Points") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 10");
        calibration.num_points = NUM_POINTS_10;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            if (i <= calibration.num_points)
                row[i][0] = 0.00 + i * ((calibration.limit_enabled) ? calibration.limit_val : calibration.capacity) / 10.0;
            else
                row[i][0] = 0.00;
        }
        return row;
    }
    else
    {
        ESP_LOGI(TAG, "NUM POINTS: Custom");
        calibration.num_points = NUM_POINTS_CUSTOM;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            row[i][0] = 0.00;
        }
        return row;
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

    row_to_fill = *(uint8_t *)_row_to_fill;
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
static save_res_t nvs_save_calibration_parameters(char *namespace, char *key, char **info)
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        *info = "Error: can't open nvs storage";
        return SAVE_CALIB_FAILED;
    }
    err = nvs_set_blob(handle, key, &calibration, sizeof(calib_params_t));
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        *info = "Error: can't set calibration parameters";
        return SAVE_CALIB_FAILED;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        *info = "Error: can't commit calibration parameters";
        return SAVE_CALIB_FAILED;
    }
    nvs_close(handle);
    *info = "Success: calibration parameters saved";
    return SAVE_CALIB_SUCCESS;
}
static load_res_t nvs_load_calibration_parameters(char *namespace, char *key, calib_params_t *out, size_t *len)
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return LOAD_CALIB_FAILED;
    }
    err = nvs_get_blob(handle, key, out, len);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return LOAD_CALIB_FAILED;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        nvs_close(handle);
        return LOAD_CALIB_FAILED;
    }
    nvs_close(handle);
    return LOAD_CALIB_SUCCESS;
}
save_res_t inputCalib_save(char **info)
{
    ESP_LOGI(TAG, "INPUTCALIB SAVE");

    switch (sensor_under_calibration)
    {
    case SENSOR_1_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_1_CALIB, info);
    case SENSOR_2_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_2_CALIB, info);
    case SENSOR_3_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_3_CALIB, info);
    case SENSOR_4_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_4_CALIB, info);
    case SENSOR_5_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_5_CALIB, info);
    case SENSOR_6_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_6_CALIB, info);
    case SENSOR_7_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_7_CALIB, info);
    case SENSOR_8_UNDER_CALIBRATION:
        return nvs_save_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_8_CALIB, info);
    default:
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        *info = "Error: invalid sensor";
        return SAVE_CALIB_FAILED;
    }
}
load_res_t inputCalib_load(sensor_to_load_t sensor, calib_params_t *out, size_t *len)
{
    switch (sensor)
    {
    case SENSOR_1_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_1_CALIB, out, len);
    case SENSOR_2_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_2_CALIB, out, len);
    case SENSOR_3_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_3_CALIB, out, len);
    case SENSOR_4_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_4_CALIB, out, len);
    case SENSOR_5_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_5_CALIB, out, len);
    case SENSOR_6_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_6_CALIB, out, len);
    case SENSOR_7_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_7_CALIB, out, len);
    case SENSOR_8_TO_LOAD:
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_8_CALIB, out, len);
    default:
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return LOAD_CALIB_FAILED;
    }
}
load_res_t inputCalib_load_last_saved(sensor_to_load_t *sensor, calib_params_t *out, size_t *len)
{
    switch (sensor_under_calibration)
    {
    case SENSOR_1_UNDER_CALIBRATION:
        *sensor = SENSOR_1_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_1_CALIB, out, len);
    case SENSOR_2_UNDER_CALIBRATION:
        *sensor = SENSOR_2_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_2_CALIB, out, len);
    case SENSOR_3_UNDER_CALIBRATION:
        *sensor = SENSOR_3_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_3_CALIB, out, len);
    case SENSOR_4_UNDER_CALIBRATION:
        *sensor = SENSOR_4_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_4_CALIB, out, len);
    case SENSOR_5_UNDER_CALIBRATION:
        *sensor = SENSOR_5_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_5_CALIB, out, len);
    case SENSOR_6_UNDER_CALIBRATION:
        *sensor = SENSOR_6_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_6_CALIB, out, len);
    case SENSOR_7_UNDER_CALIBRATION:
        *sensor = SENSOR_7_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_7_CALIB, out, len);
    case SENSOR_8_UNDER_CALIBRATION:
        *sensor = SENSOR_8_TO_LOAD;
        return nvs_load_calibration_parameters(NVS_NAMESPACE, NVS_KEY_SENSOR_8_CALIB, out, len);
    default:
        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
        return LOAD_CALIB_FAILED;
    }
}
int inputCalib_get_decimals_precision()
{
    return calibration.decimals_precision;
}
void inputCalib_set_sensor_under_calibration(void *index)
{

    switch (*(uint8_t *)index)
    {
    case 1:
        sensor_under_calibration = SENSOR_1_UNDER_CALIBRATION;
        break;
    case 2:
        sensor_under_calibration = SENSOR_2_UNDER_CALIBRATION;
        break;
    case 3:
        sensor_under_calibration = SENSOR_3_UNDER_CALIBRATION;
        break;
    case 4:
        sensor_under_calibration = SENSOR_4_UNDER_CALIBRATION;
        break;
    case 5:
        sensor_under_calibration = SENSOR_5_UNDER_CALIBRATION;
        break;
    case 6:
        sensor_under_calibration = SENSOR_6_UNDER_CALIBRATION;
        break;
    case 7:
        sensor_under_calibration = SENSOR_7_UNDER_CALIBRATION;
        break;
    case 8:
        sensor_under_calibration = SENSOR_8_UNDER_CALIBRATION;
        break;
    default:
        sensor_under_calibration = NO_SENSOR_UNDER_CALIBRATION;
        break;
    }

    ESP_LOGI(TAG, "sensor_under_calibration:%u", sensor_under_calibration);
}
sensor_under_calibration_t inputCalib_get_sensor_under_calibration()
{
    return sensor_under_calibration;
}
row_to_fill_t inputCalib_get_row_to_fill()
{
    return row_to_fill;
}
char *inputCalib_unit_to_str(sensor_unit_t unit, sensor_type_t type)
{
    if (type == DISPLACEMENT)
    {
        switch (unit.displacement_unit)
        {
        case DISPLACEMENT_UNIT_CM:
            return "cm";
        case DISPLACEMENT_UNIT_IN:
            return "in";
        case DISPLACEMENT_UNIT_MM:
            return "mm";
        default:
            break;
        }
    }
    else if (type == LOAD)
    {
        switch (unit.load_unit)
        {
        case LOAD_UNIT_KN:
            return "kN";
        case LOAD_UNIT_LBF:
            return "lbf";
        case LOAD_UNIT_N:
            return "N";
        case LOAD_UNIT_KGF:
            return "kgf";
        default:
            break;
        }
    }
    else if (type == PRESSURE)
    {
        switch (unit.pressure_unit)
        {
        case PRESSURE_UNIT_KPA:
            return "kPa";
        case PRESSURE_UNIT_PSI:
            return "psi";
        case PRESSURE_UNIT_KSF:
            return "ksf";
        case PRESSURE_UNIT_MPA:
            return "MPa";
        case PRESSURE_UNIT_KGF_CM2:
            return "kgf/cm2";
        default:
            break;
        }
    }
    else if (type == VOLUME)
    {
        switch (unit.volume_unit)
        {
        case VOLUME_UNIT_CM3:
            return "cm3";
        case VOLUME_UNIT_IN3:
            return "in3";
        default:
            break;
        }
    }

    return "N.A.";
}
char *inputCalib_unitps_to_str(sensor_unit_t unit, sensor_type_t type)
{
    if (type == DISPLACEMENT)
    {
        switch (unit.displacement_unit)
        {
        case DISPLACEMENT_UNIT_CM:
            return "cm/s";
        case DISPLACEMENT_UNIT_IN:
            return "in/s";
        case DISPLACEMENT_UNIT_MM:
            return "mm/s";
        default:
            break;
        }
    }
    else if (type == LOAD)
    {
        switch (unit.load_unit)
        {
        case LOAD_UNIT_KN:
            return "kN/s";
        case LOAD_UNIT_LBF:
            return "lbf/s";
        case LOAD_UNIT_N:
            return "N/s";
        case LOAD_UNIT_KGF:
            return "kgf/s";
        default:
            break;
        }
    }
    else if (type == PRESSURE)
    {
        switch (unit.pressure_unit)
        {
        case PRESSURE_UNIT_KPA:
            return "kPa/s";
        case PRESSURE_UNIT_PSI:
            return "psi/s";
        case PRESSURE_UNIT_KSF:
            return "ksf/s";
        case PRESSURE_UNIT_MPA:
            return "MPa/s";
        case PRESSURE_UNIT_KGF_CM2:
            return "(kgf/cm2)/s";
        default:
            break;
        }
    }
    else if (type == VOLUME)
    {
        switch (unit.volume_unit)
        {
        case VOLUME_UNIT_CM3:
            return "cm3/s";
        case VOLUME_UNIT_IN3:
            return "in3/s";
        default:
            break;
        }
    }

    return "N.A.";
}
char *inputCalib_path_from_type(sensor_type_t type)
{
    switch (type)
    {
    case DISPLACEMENT:
        return "cm\r\nin\r\nmm";
    case LOAD:
        return "kN\r\nlbf\r\nN\r\nkgf";
    case PRESSURE:
        return "kPa\r\npsi\r\nksf\r\nMPa\r\nkgf/cm2";
    case VOLUME:
        return "cm3\r\nin3";
    default:
        return "N.A.";
    }
}
int inputCalib_val_from_type_and_unit(sensor_type_t type, sensor_unit_t unit)
{
    switch (type)
    {
    case DISPLACEMENT:
        switch (unit.displacement_unit)
        {
        case DISPLACEMENT_UNIT_CM:
            return 0;
        case DISPLACEMENT_UNIT_IN:
            return 1;
        case DISPLACEMENT_UNIT_MM:
            return 2;
        default:
            return 0;
        }
    case LOAD:
        switch (unit.load_unit)
        {
        case LOAD_UNIT_KN:
            return 0;
        case LOAD_UNIT_LBF:
            return 1;
        case LOAD_UNIT_N:
            return 2;
        case LOAD_UNIT_KGF:
            return 3;
        default:
            return 0;
        }
    case PRESSURE:
        switch (unit.pressure_unit)
        {
        case PRESSURE_UNIT_KPA:
            return 0;
        case PRESSURE_UNIT_PSI:
            return 1;
        case PRESSURE_UNIT_KSF:
            return 2;
        case PRESSURE_UNIT_MPA:
            return 3;
        case PRESSURE_UNIT_KGF_CM2:
            return 4;
        default:
            return 0;
        }
    case VOLUME:
        switch (unit.volume_unit)
        {
        case VOLUME_UNIT_CM3:
            return 0;
        case VOLUME_UNIT_IN3:
            return 1;
        default:
            return 0;
        }
    default:
        return 0;
    }
}
esp_err_t inputCalib_get_sensor_unit_from_str(char *unit_str, sensor_unit_t *unit, sensor_type_t *type)
{

    bool unit_is_cm = (strcmp(unit_str, "cm") == 0);
    if (unit_is_cm)
    {
        *type = DISPLACEMENT;
        unit->displacement_unit = DISPLACEMENT_UNIT_CM;
        return ESP_OK;
    }

    bool unit_is_in = (strcmp(unit_str, "IN") == 0);
    if (unit_is_in)
    {
        *type = DISPLACEMENT;
        unit->displacement_unit = DISPLACEMENT_UNIT_IN;
        return ESP_OK;
    }

    bool unit_is_mm = (strcmp(unit_str, "MM") == 0);
    if (unit_is_mm)
    {
        *type = DISPLACEMENT;
        unit->displacement_unit = DISPLACEMENT_UNIT_MM;
        return ESP_OK;
    }

    bool unit_is_kN = (strcmp(unit_str, "kN") == 0);
    if (unit_is_kN)
    {
        *type = LOAD;
        unit->displacement_unit = LOAD_UNIT_KN;
        return ESP_OK;
    }
    bool unit_is_lbf = (strcmp(unit_str, "lbf") == 0);
    if (unit_is_lbf)
    {
        *type = LOAD;
        unit->displacement_unit = LOAD_UNIT_LBF;
        return ESP_OK;
    }
    bool unit_is_N = (strcmp(unit_str, "N") == 0);
    if (unit_is_N)
    {
        *type = LOAD;
        unit->displacement_unit = LOAD_UNIT_N;
        return ESP_OK;
    }
    bool unit_is_kgf = (strcmp(unit_str, "kgf") == 0);
    if (unit_is_kgf)
    {
        *type = LOAD;
        unit->displacement_unit = LOAD_UNIT_KGF;
        return ESP_OK;
    }

    bool unit_is_kPa = (strcmp(unit_str, "kPa") == 0);
    if (unit_is_kPa)
    {
        *type = PRESSURE;
        unit->displacement_unit = PRESSURE_UNIT_KPA;
        return ESP_OK;
    }
    bool unit_is_psi = (strcmp(unit_str, "psi") == 0);
    if (unit_is_psi)
    {
        *type = PRESSURE;
        unit->displacement_unit = PRESSURE_UNIT_PSI;
        return ESP_OK;
    }
    bool unit_is_ksf = (strcmp(unit_str, "ksf") == 0);
    if (unit_is_ksf)
    {
        *type = PRESSURE;
        unit->displacement_unit = PRESSURE_UNIT_KSF;
        return ESP_OK;
    }
    bool unit_is_MPa = (strcmp(unit_str, "MPa") == 0);
    if (unit_is_MPa)
    {
        *type = PRESSURE;
        unit->displacement_unit = PRESSURE_UNIT_MPA;
        return ESP_OK;
    }
    bool unit_is_kgf_cm2 = (strcmp(unit_str, "kgf/cm2") == 0);
    if (unit_is_kgf_cm2)
    {
        *type = PRESSURE;
        unit->displacement_unit = PRESSURE_UNIT_KGF_CM2;
        return ESP_OK;
    }

    bool unit_is_cm3 = (strcmp(unit_str, "cm3") == 0);
    if (unit_is_cm3)
    {
        *type = PRESSURE;
        unit->displacement_unit = VOLUME_UNIT_CM3;
        return ESP_OK;
    }
    bool unit_is_in3 = (strcmp(unit_str, "in3") == 0);
    if (unit_is_in3)
    {
        *type = PRESSURE;
        unit->displacement_unit = VOLUME_UNIT_IN3;
        return ESP_OK;
    }

    ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    return ESP_ERR_NOT_FOUND;
}                           
                                    // FROM:
                   //from to   //cm        in         mm 
double displacement_fc[3][3] = {{1.0,      2.5399986, 0.1    }, // cm
                                {0.393701, 1.0,       0.03937}, // in   TO:
                                {10.0,     25.4,      1.0    }};// mm

                                    // FROM:
           //from to   //kN          lbf         N          kgf 
double load_fc[4][4] = {{1.0,        0.0044466, 0.001,      0.0098066}, // kN
                        {224.89,     1.0,       0.2248089,  2.2046244}, // lbf   TO:
                        {1000.0,     4.4482216, 1.0,        9.8066520}, // N
                        {101.97162,  0.453592,  0.1019716,      1.0  }};// kgf


                                    // FROM:
               //from to   //kPa         psi         ksf          MPa         kgf/cm2 
double pressure_fc[5][5] = {{1.0,        6.8947448, 47.8803374, 1000.0000,    98.0392156}, // kPa
                            {0.145038,   1.0,       6.9444396,  145.0389429,  14.2233348}, // psi   TO:
                            {0.0208854,  0.1440001, 1.0,        20.8854163,   2.0481268 }, // ksf
                            {0.001,      0.0068947, 0.0478803,  1.0,          0.0980680 }, // MPa
                            {0.0102000,  0.0703070, 0.4882510,  10.1970000,   1.0       }};// kgf/cm2

                                    // FROM:
             //from to   //cm3           in3        
double volume_fc[2][2] = {{1.0,        16.387064 }, // cm3
                          {0.06102374, 1.0       }};// in3   TO:
                                

double inputCalib_get_fc(sensor_unit_t unit_from, sensor_unit_t unit_to, sensor_type_t type)
{
    if(type == DISPLACEMENT){
       return displacement_fc[unit_from.displacement_unit][unit_to.displacement_unit];
    }
    if(type == LOAD){
        return load_fc[unit_from.load_unit][unit_to.load_unit];
    }
    if(type == PRESSURE){
        return pressure_fc[unit_from.pressure_unit][unit_to.pressure_unit];
    }
    if(type == VOLUME){
        return volume_fc[unit_from.volume_unit][unit_to.volume_unit];
    }

    return 1.0;
}