#pragma once

typedef enum
{
    // MSG FROM NEXTION RX TO MAIN TASK
    HOME_LOADED,
    HOME_TARA_1_ENABLED,
    HOME_TARA_1_DISABLED,
    HOME_TARA_2_ENABLED,
    HOME_TARA_2_DISABLED,
    HOME_TARA_3_ENABLED,
    HOME_TARA_3_DISABLED,
    HOME_TARA_4_ENABLED,
    HOME_TARA_4_DISABLED,
    SYSTEM_SETTINGS_LOADED,
    CALIBRATION_LOADED,
    CALIBRATION_SWITCH_1_ENABLED,
    CALIBRATION_SWITCH_1_DISABLED,
    CALIBRATION_SWITCH_2_ENABLED,
    CALIBRATION_SWITCH_2_DISABLED,
    CALIBRATION_SWITCH_3_ENABLED,
    CALIBRATION_SWITCH_3_DISABLED,
    CALIBRATION_SWITCH_4_ENABLED,
    CALIBRATION_SWITCH_4_DISABLED,

    //
    NEXTION_UPDATE,

} msg_type_t;

typedef enum
{
    HOME = 0,
    SYSTEM_SETTINGS,
    CALIBRATION,
} page_t;

typedef struct
{
    page_t page;
} page_status_t;

typedef struct
{
    msg_type_t type;
    union
    {
        uint32_t u32;
        float f32;
        int32_t i32;
        void *addr;
    } content;
    int size;
} msg_t;
