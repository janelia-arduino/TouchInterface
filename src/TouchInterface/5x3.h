// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef TOUCH_INTERFACE_5X3_CONSTANTS_H
#define TOUCH_INTERFACE_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace touch_interface
{
namespace constants
{
enum {MPR121_COUNT_MAX=wire_interface::constants::WIRE_COUNT_MAX*MPR121::DEVICE_COUNT_MAX};

extern const MPR121::DeviceAddress mpr121_addresses[MPR121_COUNT_MAX];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
