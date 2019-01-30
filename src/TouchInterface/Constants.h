// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef TOUCH_INTERFACE_CONSTANTS_H
#define TOUCH_INTERFACE_CONSTANTS_H
#include <ConstantVariable.h>
#include <WireInterface.h>
#include <MPR121.h>


namespace touch_interface
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=2};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const bool fast_mode;

extern const long null_long;

extern const MPR121::ProximityMode proximity_mode;

extern const uint8_t touch_threshold;
extern const uint8_t release_threshold;
extern const uint8_t touch_debounce;
extern const uint8_t release_debounce;

extern const MPR121::BaselineTracking baseline_tracking;
extern const uint8_t charge_discharge_current;
extern const MPR121::ChargeDischargeTime charge_discharge_time;
extern const MPR121::FirstFilterIterations first_filter_iterations;
extern const MPR121::SecondFilterIterations second_filter_iterations;
extern const MPR121::SamplePeriod sample_period;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString physical_channel_count_property_name;
extern const long physical_channel_count_min;
extern const long physical_channel_count_max;
extern const long physical_channel_count_element_default;

// Parameters

// Functions
extern ConstantString reinitialize_function_name;
extern ConstantString communicating_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
