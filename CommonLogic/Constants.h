#pragma once

#define SCREEN_BUFFER_SIZE 20*4

#define HW_CHECKS_COUNT 10

#define SCREEN_ADDRESS 0x77
#define BAROMETER_ADDRESS 0x76

#define VOLTAGE_COEFFICIENT (double)2.8
#define LOW_VOLTAGE (double)9
#define ANALOG_COEFFICIENT (double)0.0048828125
#define PRESSURE_COEFFICIENT (double)1

#define I2C_SDA_PORT 20
#define I2C_SCL_PORT 21

#define LOADER_FWD_PORT 3
#define LOADER_REV_PORT 4
#define LOADER_ENABLE_PORT 5
#define LOADER_CURRENT_PORT 1

#define VOLTAGE_PORT 2

#define FAN_PORT 53
#define BREACH_OPEN_PORT 51
#define BREACH_CLOSE_PORT 49
#define INJECTOR_PORT 47

#define TEMP_HUM_SENSOR_PORT 3
#define AMMO_SENSOR_PORT 45
#define FSS_PORT 43
#define RSS_PORT 41
#define INJ_LED_PORT 50
#define IGNITION_PORT 48
#define BLAST_SENSOR_PORT 46
#define BLAST_TRIGGER_RESET_PORT 44
#define SS_TRIGGER_RESET_PORT 42
#define BLUETOOTH_RX_PORT 19
#define BLUETOOTH_TX_PORT 18
#define RECEIVER_PRESSURE_PORT 4

#define LOADER_CURRENT_MAX 1024
#define LOADER_CURRENT_WORKING 512

/*
 *		x2		x5
 *  x1		x4
 *		x3		x6
 */

#define BTN1_PORT 23
#define BTN2_PORT 25
#define BTN3_PORT 27
#define BTN4_PORT 29
#define BTN5_PORT 31
#define BTN6_PORT 33

enum Buttons { x1, x2, x3, x4, x5, x6, Combo, None };

#define TestAbortButton x1

enum OperationMode {FiringMode, AfrEditScreen, SettingsMode, TestMode};

enum ErrorCode { Unspecified};
