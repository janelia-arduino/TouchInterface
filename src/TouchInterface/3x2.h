// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef TOUCH_INTERFACE_3X2_CONSTANTS_H
#define TOUCH_INTERFACE_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace touch_interface
{
namespace constants
{
enum {TOUCH_DEVICE_COUNT_MAX=wire_interface::constants::WIRE_COUNT_MAX * MPR121::DEVICE_COUNT_MAX};

extern const MPR121::DeviceAddress touch_device_addresses[TOUCH_DEVICE_COUNT_MAX];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long physical_channel_count_default[TOUCH_DEVICE_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
