#include "project_typedefs.h"
#include "stdbool.h"
#include "string.h"
#include "esp_log.h"
#include "calibration.h"

#define TAG "INPUT_CALIBRATION"

static sensor_type_t sensor_type = SENSOR_TYPE_MAX;
static double capacity = 0.0;
static sensor_data_unit_t data_unit;
static double sensibility = 0.0;
static sensor_sensibility_unit_t sensibility_unit = SENSIBILITY_UNIT_MAX;
static double calibration_limit = 0.0;
static bool limit_enabled = false;
static double table[11][2];
static calib_points_num_t num_points = NUM_POINTS_MAX; // 0 means custom number of points
static uint8_t row_to_fill = 0xAA;                     // 0xAA means "do not fill"
static char *name = NULL;
static int decimals_precision = 2; // number of decimals
static uint8_t sensor_index = 0;

void inputCalib_set_sensor_type(char *type_str)
{
    bool is_type_displacement = (strcmp(type_str, "DISPLACEMENT") == 0);
    if (is_type_displacement)
    {
        sensor_type = DISPLACEMENT;
        ESP_LOGI(TAG, "SENSOR TYPE: DISPLACEMENT");
        return;
    }

    bool is_type_load = (strcmp(type_str, "LOAD") == 0);
    if (is_type_load)
    {
        sensor_type = LOAD;
        ESP_LOGI(TAG, "SENSOR TYPE: LOAD");
        return;
    }

    bool is_type_pressure = (strcmp(type_str, "PRESSURE") == 0);
    if (is_type_pressure)
    {
        sensor_type = PRESSURE;
        ESP_LOGI(TAG, "SENSOR TYPE: PRESSURE");
        return;
    }

    bool is_type_volume = (strcmp(type_str, "VOLUME") == 0);
    if (is_type_volume)
    {
        sensor_type = VOLUME;
        ESP_LOGI(TAG, "SENSOR TYPE: VOLUME");
        return;
    }

    ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
}
void inputCalib_set_capacity(char *capacity_str)
{
    capacity = atof(capacity_str);
    ESP_LOGI(TAG, "capacity : %f", capacity);
}
void inputCalib_set_data_unit(char *unit_str)
{
    if (sensor_type == DISPLACEMENT)
    {
        bool unit_is_cm = (strcmp(unit_str, "cm") == 0);
        if (unit_is_cm)
        {
            data_unit.displacement_unit = DISPLACEMENT_UNIT_CM;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_CM");
            return;
        }

        bool unit_is_in = (strcmp(unit_str, "IN") == 0);
        if (unit_is_in)
        {
            data_unit.displacement_unit = DISPLACEMENT_UNIT_IN;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_IN");
            return;
        }

        bool unit_is_mm = (strcmp(unit_str, "MM") == 0);
        if (unit_is_mm)
        {
            data_unit.displacement_unit = DISPLACEMENT_UNIT_MM;
            ESP_LOGI(TAG, "SENSOR UNIT: DISPLACEMENT_UNIT_MM");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else if (sensor_type == LOAD)
    {
        bool unit_is_kN = (strcmp(unit_str, "kN") == 0);
        if (unit_is_kN)
        {
            data_unit.load_unit = LOAD_UNIT_KN;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_KN");
            return;
        }
        bool unit_is_lbf = (strcmp(unit_str, "lbf") == 0);
        if (unit_is_lbf)
        {
            data_unit.load_unit = LOAD_UNIT_LBF;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_LBF");
            return;
        }
        bool unit_is_N = (strcmp(unit_str, "N") == 0);
        if (unit_is_N)
        {
            data_unit.load_unit = LOAD_UNIT_N;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_N");
            return;
        }
        bool unit_is_kgf = (strcmp(unit_str, "kgf") == 0);
        if (unit_is_kgf)
        {
            data_unit.load_unit = LOAD_UNIT_KGF;
            ESP_LOGI(TAG, "SENSOR UNIT: LOAD_UNIT_KGF");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else if (sensor_type == PRESSURE)
    {
        bool unit_is_kPa = (strcmp(unit_str, "kPa") == 0);
        if (unit_is_kPa)
        {
            data_unit.pressure_unit = PRESSURE_UNIT_KPA;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KPA");
            return;
        }
        bool unit_is_psi = (strcmp(unit_str, "psi") == 0);
        if (unit_is_psi)
        {
            data_unit.pressure_unit = PRESSURE_UNIT_PSI;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_PSI");
            return;
        }
        bool unit_is_ksf = (strcmp(unit_str, "ksf") == 0);
        if (unit_is_ksf)
        {
            data_unit.pressure_unit = PRESSURE_UNIT_KSF;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KSF");
            return;
        }
        bool unit_is_MPa = (strcmp(unit_str, "MPa") == 0);
        if (unit_is_MPa)
        {
            data_unit.pressure_unit = PRESSURE_UNIT_MPA;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_MPA");
            return;
        }
        bool unit_is_kgf_cm2 = (strcmp(unit_str, "kgf/cm2") == 0);
        if (unit_is_kgf_cm2)
        {
            data_unit.pressure_unit = PRESSURE_UNIT_KGF_CM2;
            ESP_LOGI(TAG, "SENSOR UNIT: PRESSURE_UNIT_KGF_CM2");
            return;
        }

        ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
    }
    else if (sensor_type == VOLUME)
    {
        bool unit_is_cm3 = (strcmp(unit_str, "cm3") == 0);
        if (unit_is_cm3)
        {
            data_unit.volume_unit = VOLUME_UNIT_CM3;
            ESP_LOGI(TAG, "SENSOR UNIT: VOLUME_UNIT_CM3");
            return;
        }
        bool unit_is_in3 = (strcmp(unit_str, "in3") == 0);
        if (unit_is_in3)
        {
            data_unit.volume_unit = VOLUME_UNIT_IN3;
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
    sensibility = atof(sensibility_str);
    ESP_LOGI(TAG, "sensibility : %f", sensibility);
}
void inputCalib_set_sensibility_unit(char *unit_str)
{
    bool unit_is_mV_V = (strcmp(unit_str, "mV/V") == 0);
    if (unit_is_mV_V)
    {
        sensibility_unit = SENSIBILITY_UNIT_MV_V;
        ESP_LOGI(TAG, "SENSIBILITY UNIT: MV_V");
        return;
    }
    bool unit_is_V_V = (strcmp(unit_str, "V/V") == 0);
    if (unit_is_V_V)
    {
        sensibility_unit = SENSIBILITY_UNIT_V_V;
        ESP_LOGI(TAG, "SENSIBILITY UNIT: V_V");
        return;
    }

    ESP_LOGE(TAG, "%s: line %d", __FILE__, __LINE__);
}
void inputCalib_set_limit(char *limit_str)
{
    calibration_limit = atof(limit_str);
    ESP_LOGI(TAG, "calibration_limit : %f", calibration_limit);

    char *ptr = strtok(limit_str, ".");
    ptr = strtok(NULL, ".");
    decimals_precision = ptr ? strlen(ptr) : 0;
    ESP_LOGI(TAG, "decimals_precision : %i", decimals_precision);
}
void inputCalib_set_limit_enable(void *limit_enable)
{
    limit_enabled = (*(uint8_t *)limit_enable) == 1;
    ESP_LOGI(TAG, "limit_enabled : %s ", limit_enabled == true ? "true" : "false");
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
                table[i][j] = 0.0;
            else
                table[i][j] = atof(ptr);
        }
        ESP_LOGI(TAG, "%.*f  %.*f", decimals_precision, table[i][0], decimals_precision, table[i][1]);
    }
}
table_t inputCalib_set_num_points(char *num_points_str)
{

    if (strcmp(num_points_str, "1 Point") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 1");
        num_points = NUM_POINTS_1;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            if (i <= num_points)
                row[i][0] = 0.00 + i * (limit_enabled ? calibration_limit : capacity) / 1.0;
            else
                row[i][0] = 0.00;
        }
        return row;
    }
    else if (strcmp(num_points_str, "5 Points") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 5");
        num_points = NUM_POINTS_5;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            if (i <= num_points)
                row[i][0] = 0.00 + i * (limit_enabled ? calibration_limit : capacity) / 5.0;
            else
                row[i][0] = 0.00;
        }
        return row;
    }
    else if (strcmp(num_points_str, "10 Points") == 0)
    {
        ESP_LOGI(TAG, "NUM POINTS: 10");
        num_points = NUM_POINTS_10;
        row_t row = calloc(11, sizeof(*row));

        for (int i = 0; i < 11; i++)
        {
            if (i <= num_points)
                row[i][0] = 0.00 + i * (limit_enabled ? calibration_limit : capacity) / 10.0;
            else
                row[i][0] = 0.00;
        }
        return row;
    }
    else
    {
        ESP_LOGI(TAG, "NUM POINTS: Custom");
        num_points = NUM_POINTS_CUSTOM;
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
    row_to_fill = *(uint8_t *)_row_to_fill;
    ESP_LOGI(TAG, "row_to_fill : %x", row_to_fill);
}
void inputCalib_set_name(char *_name)
{
    if (name)
        free(name);

    name = _name;
    ESP_LOGI(TAG, "NAME:%s", name);
}
void inputCalib_save()
{
    ESP_LOGI(TAG, "INPUTCALIB SAVE");
}
int inputCalib_get_decimals_precision()
{
    return decimals_precision;
}
void inputCalib_set_sensor_index(void *index)
{
    sensor_index = *(uint8_t *)index;
    ESP_LOGI(TAG, "sensor_index:%u", sensor_index);
}
uint8_t inputCalib_get_sensor_index()
{
    return sensor_index;
}
uint8_t inputCalib_get_row_to_fill()
{
    return row_to_fill;
}