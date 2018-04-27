#pragma once

//#define PIN_A1   (55)
//#define PIN_A2   (56)
//#define PIN_A3   (57)
//#define PIN_A4   (58)
//#define PIN_A5   (59)

#define Debug

#define SCREEN_ROWS_ACTUAL 4
#define SCREEN_BUFFER_SIZE 20*SCREEN_ROWS_ACTUAL

#define HW_CHECKS_COUNT 10

#define SCREEN_ADDRESS 0x77
#define BAROMETER_ADDRESS 0x76

#define VOLTAGE_COEFFICIENT 2.8f
#define LOW_VOLTAGE 9.0f
#define ANALOG_COEFFICIENT 0.0048828125l
#define PRESSURE_COEFFICIENT 344.737865//0.29391897l //1378951.46pa max with 4.5v output
#define CURRENT_MIDDLE_POINT 2.53f
#define CURRENT_COEFFICIENT 0.07f
#define PRESSURE_CONSTANT 0.5f

#define SPEED_CONSTANT 0.7f

#define LOADER_CURRENT_MAX 150.0f
#define LOADER_CURRENT_WORKING 0.4f

#define RECEIVER_PRESSURE_MAX 607.950f //kpa //6.0f 
#define RECEIVER_PRESSURE_MIN 202.650f //kpa //2.0f

#define LOADER_FORWARD_TIME 5000
#define LOADER_REVERSE_TIME 5000
#define MAX_INJECTION_TIME 2000
#define BREACH_ENGAGING_TIME 2000
#define FIRING_TIMEOUT 60000

#define I2C_SDA_PORT 20
#define I2C_SCL_PORT 21

#define LOADER_FWD_PORT 34
#define LOADER_REV_PORT 36
#define LOADER_ENABLE_PORT 30
#define LOADER_CURRENT_PORT 55//A1

#define VOLTAGE_PORT 56//A2

#define IGNITION_PORT 22
#define FAN_PORT 24
#define BREACH_OPEN_PORT 28
#define BREACH_CLOSE_PORT 26
#define INJECTOR_PORT 42
#define RESERVED_PORT1 40
#define AMMO_SENSOR_PORT 38

#define SS_TRIGGER_RESET_PORT 53
#define BLAST_SENSOR_PORT 51
#define FSS_PORT 49
#define RSS_PORT 47
#define BLAST_TRIGGER_RESET_PORT 45
#define TEMP_HUM_SENSOR_PORT 43
#define INJ_LED_PORT 41

#define RECEIVER_PRESSURE_PORT 58//A4

#define BLUETOOTH_RX_PORT 19
#define BLUETOOTH_TX_PORT 18

#define RESERVED_RELAY_PORT 32

#define LDR_FW_CHECK_PORT 10
#define LDR_REV_CHECK_PORT 11

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

//A continue
//B stop
enum Buttons { x1A, x2B, x3C, x4D, x5E, x6F, Combo, None };

#define TestAbortButton x1A

enum FiringSequenceMode {Auto, SemiAuto};

enum OperationMode {MainMenu, FiringMode, FiringModeForcedMixing, ConfigEditScreen, TestMode, InjectorTestMode};

enum SystemState {SystemIdle, SystemRunning, SystemError};

enum FiringState {Undefined, Front, FrontRev, Reversed, Firing, RevFront, Reloading};


