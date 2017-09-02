#pragma once

//#define PIN_A1   (55)
//#define PIN_A2   (56)
//#define PIN_A3   (57)
//#define PIN_A4   (58)
//#define PIN_A5   (59)

#define Debug

#define SCREEN_BUFFER_SIZE 20*4

#define HW_CHECKS_COUNT 10

#define SCREEN_ADDRESS 0x77
#define BAROMETER_ADDRESS 0x76

#define VOLTAGE_COEFFICIENT (double)2.8
#define LOW_VOLTAGE (double)9
#define ANALOG_COEFFICIENT (double)0.0048828125
#define PRESSURE_COEFFICIENT (double)1
#define CURRENT_MIDDLE_POINT (double)2.53
#define CURRENT_COEFFICIENT (double)0.07

#define LOADER_CURRENT_MAX 150.0f
#define LOADER_CURRENT_WORKING 0.4f

#define I2C_SDA_PORT 20
#define I2C_SCL_PORT 21

#define LOADER_FWD_PORT 34
#define LOADER_REV_PORT 36
#define LOADER_ENABLE_PORT 30
#define LOADER_CURRENT_PORT 55//A1

#define VOLTAGE_PORT 56//A2

#define FAN_PORT 24
#define BREACH_OPEN_PORT 26
#define BREACH_CLOSE_PORT 28
#define INJECTOR_PORT 47

#define RESERVED_PORT1 40
#define TEMP_HUM_SENSOR_PORT 17
#define AMMO_SENSOR_PORT 38
#define FSS_PORT 43
#define RSS_PORT 41
#define INJ_LED_PORT 50
#define IGNITION_PORT 22
#define BLAST_SENSOR_PORT 46
#define BLAST_TRIGGER_RESET_PORT 44
#define SS_TRIGGER_RESET_PORT 42
#define BLUETOOTH_RX_PORT 19
#define BLUETOOTH_TX_PORT 18
#define RECEIVER_PRESSURE_PORT 58//A4

#define RESERVED_RELAY_PORT 32

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
