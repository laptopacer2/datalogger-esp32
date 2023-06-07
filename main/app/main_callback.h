#pragma once

#include "project_defines.h"
#include "project_typedefs.h"

void main_task_init();

// NEXTION CALLBACK
void home_loaded_cb(msg_t *msg);
void home_tara_1_enabled_cb(msg_t *msg);
void home_tara_1_disabled_cb(msg_t *msg);
void home_tara_2_enabled_cb(msg_t *msg);
void home_tara_2_disabled_cb(msg_t *msg);
void home_tara_3_enabled_cb(msg_t *msg);
void home_tara_3_disabled_cb(msg_t *msg);
void home_tara_4_enabled_cb(msg_t *msg);
void home_tara_4_disabled_cb(msg_t *msg);
void system_settings_loaded_cb(msg_t *msg);
void calibration_loaded_cb(msg_t *msg);
void calibration_switch_1_disabled_cb(msg_t *msg);
void calibration_switch_1_enabled_cb(msg_t *msg);
void calibration_switch_2_disabled_cb(msg_t *msg);
void calibration_switch_2_enabled_cb(msg_t *msg);
void calibration_switch_3_disabled_cb(msg_t *msg);
void calibration_switch_3_enabled_cb(msg_t *msg);
void calibration_switch_4_disabled_cb(msg_t *msg);
void calibration_switch_4_enabled_cb(msg_t *msg);


void nextion_update_cb(msg_t *msg);

