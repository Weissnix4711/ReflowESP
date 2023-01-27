#pragma once

// @section info

#define MACHINE_NAME "ReflowESP"

// @section therm

/**
 * Thermocouple Interface
 *
 * Configure one of HAS_MAX6675 and HAS_MAX31855,
 * then configure pins below.
 */
// #define HAS_MAX31855
#define HAS_MAX6675

#define THERM_MISO 12
#define THERM_SCK 14

#define THERM_CS0 15
#define THERM_CS1 32

// Default PID values
#define PID_KP 0
#define PID_KI 0
#define PID_KD 0

// @section pins

// Buzzer pin
#define BUZZ 4

/**
 * SSR Outputs
 *
 * Define pins for SSR outputs here. Must define at least one.
 */
#define SSR1 25
#define SSR2 26

#define PWM_PERIOD 1000

// @section menu

// MAX DEPTH
// #define MAX_DEPTH 2
#define MAX_DEPTH 30

/**
 * LCD / OLED settings
 *
 * Must define all.
 */
#define FONT_WIDTH 6
#define FONT_HEIGHT 9
#define GFX_WIDTH 128
#define GFX_HEIGHT 128

/**
 * Rotary Encoder
 *
 * Must define all ENCA, ENCB, ENCBTN and ENCSTEPS.
 */
#define ENCA 34
#define ENCB 35
#define ENCBTN 13
#define ENCSTEPS 2

// Encoder decoder.
// :[ENC_NORMAL,ENC_FLAKY]
// #define ENC_DECODER ENC_FLAKY
#define ENC_DECODER ENC_NORMAL

// Additional options for ENC_FLAKY
#if ENC_DECODER == ENC_FLAKY
  #define ENC_HALFSTEP 1
#endif
