#pragma once

#include "project_defines.h"
#include "project_typedefs.h"

void main_task_init();

// HOME
void home_loaded_cb(msg_t *msg);
void home_tara_1_enabled_cb(msg_t *msg);
void home_tara_1_disabled_cb(msg_t *msg);
void home_tara_2_enabled_cb(msg_t *msg);
void home_tara_2_disabled_cb(msg_t *msg);
void home_tara_3_enabled_cb(msg_t *msg);
void home_tara_3_disabled_cb(msg_t *msg);
void home_tara_4_enabled_cb(msg_t *msg);
void home_tara_4_disabled_cb(msg_t *msg);
// SYSTEM SETTINGS
void system_settings_loaded_cb(msg_t *msg);
// CALIBRATION
void calibration_loaded_cb(msg_t *msg);
void calibration_switch_1_disabled_cb(msg_t *msg);
void calibration_switch_1_enabled_cb(msg_t *msg);
void calibration_switch_2_disabled_cb(msg_t *msg);
void calibration_switch_2_enabled_cb(msg_t *msg);
void calibration_switch_3_disabled_cb(msg_t *msg);
void calibration_switch_3_enabled_cb(msg_t *msg);
void calibration_switch_4_disabled_cb(msg_t *msg);
void calibration_switch_4_enabled_cb(msg_t *msg);
void calibration_switch_5_disabled_cb(msg_t *msg);
void calibration_switch_5_enabled_cb(msg_t *msg);
void calibration_switch_6_disabled_cb(msg_t *msg);
void calibration_switch_6_enabled_cb(msg_t *msg);
void calibration_switch_7_disabled_cb(msg_t *msg);
void calibration_switch_7_enabled_cb(msg_t *msg);
void calibration_switch_8_disabled_cb(msg_t *msg);
void calibration_switch_8_enabled_cb(msg_t *msg);
// INPUT CALIB P1
void inputcalibp1_loaded_cb(msg_t *msg);
void inputcalibp1_type_received_cb(msg_t *msg);
void inputcalibp1_capacity_received_cb(msg_t *msg);
void inputcalibp1_capacity_unit_received_cb(msg_t *msg);
void inputcalibp1_sensibility_received_cb(msg_t *msg);
void inputcalibp1_sensibility_unit_received_cb(msg_t *msg);
void inputcalibp1_sensor_index_received(msg_t *msg);
// INPUT CALIB P2
void inputcalibp2_loaded_cb(msg_t *msg);
void inputcalibp2_calibration_limit_received_cb(msg_t *msg);
void inputcalibp2_calibration_limit_unit_received_cb(msg_t *msg);
void inputcalibp2_limit_enable_receive_cb(msg_t *msg);
// INPUT CALIB P3
void inputcalibp3_loaded_cb(msg_t *msg);
void inputcalibp3_table_received(msg_t *msg);
void inputcalibp3_num_points_received(msg_t *msg);
void inputcalibp3_row_to_fill_received(msg_t *msg);
// INPUT CALIB P4
void inputcalibp4_loaded_cb(msg_t *msg);
void inputcalibp4_name_received_cb(msg_t *msg);
void inputcalibp4_save_pressed_cb(msg_t *msg);
// EXTERNAL
void external_sensor_5_unit_changed_cb(msg_t *msg);
void external_sensor_6_unit_changed_cb(msg_t *msg);
void external_sensor_7_unit_changed_cb(msg_t *msg);
void external_sensor_8_unit_changed_cb(msg_t *msg);
void external_sensor_5_unitps_changed_cb(msg_t *msg);
void external_sensor_6_unitps_changed_cb(msg_t *msg);
void external_sensor_7_unitps_changed_cb(msg_t *msg);
void external_sensor_8_unitps_changed_cb(msg_t *msg);

void nextion_update_cb(msg_t *msg);
