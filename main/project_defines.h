#pragma once

// RX CMD
#define uTX_nRX_PIN (16)
#define uRX_nTX_PIN (17)
#define NEXTION_UART_NUM (UART_NUM_1)
#define NEXTION_BAUDRATE (921600)

#define BUF_SIZE (1024)

#define INITIAL_PAGE (HOME)

#define SAMPLE_RATE_MAX_HZ (50)
#define POINTS_PER_TEST_MAX (3000)
#define MULTITEST_STORAGE_MAX (1000)

#define LOADCELL_1_DOUT_PIN (12)
#define LOADCELL_1_SCK_PIN (13)
#define LOADCELL_2_DOUT_PIN (14)
#define LOADCELL_2_SCK_PIN (15)
#define LOADCELL_3_DOUT_PIN (18)
#define LOADCELL_3_SCK_PIN (21)
#define LOADCELL_4_DOUT_PIN (33)
#define LOADCELL_4_SCK_PIN (34)

#define DIALBIG_1_DATA_PIN (6)
#define DIALBIG_1_CLK_PIN (7)
#define DIALBIG_1_REQ_PIN (8)
#define DIALBIG_2_DATA_PIN (9)
#define DIALBIG_2_CLK_PIN (10)
#define DIALBIG_2_REQ_PIN (11)
#define DIALBIG_3_DATA_PIN (35)
#define DIALBIG_3_CLK_PIN (36)
#define DIALBIG_3_REQ_PIN (37)
#define DIALBIG_4_DATA_PIN (38)
#define DIALBIG_4_CLK_PIN (39)
#define DIALBIG_4_REQ_PIN (40)

#define CALIB_NAME_LEN_MAX (30) // without null end

#define NVS_NAMESPACE "storage"
#define NVS_KEY_SENSOR_1_CALIB "s1calib"
#define NVS_KEY_SENSOR_2_CALIB "s2calib"
#define NVS_KEY_SENSOR_3_CALIB "s3calib"
#define NVS_KEY_SENSOR_4_CALIB "s4calib"
#define NVS_KEY_SENSOR_5_CALIB "s5calib"
#define NVS_KEY_SENSOR_6_CALIB "s6calib"
#define NVS_KEY_SENSOR_7_CALIB "s7calib"
#define NVS_KEY_SENSOR_8_CALIB "s8calib"

#define NVS_KEY_SENSOR_1_CONFIG "s1cfg"
#define NVS_KEY_SENSOR_2_CONFIG "s2cfg"
#define NVS_KEY_SENSOR_3_CONFIG "s3cfg"
#define NVS_KEY_SENSOR_4_CONFIG "s4cfg"
#define NVS_KEY_SENSOR_5_CONFIG "s5cfg"
#define NVS_KEY_SENSOR_6_CONFIG "s6cfg"
#define NVS_KEY_SENSOR_7_CONFIG "s7cfg"
#define NVS_KEY_SENSOR_8_CONFIG "s8cfg"

