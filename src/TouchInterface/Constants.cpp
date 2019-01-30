// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace touch_interface
{
namespace constants
{
CONSTANT_STRING(device_name,"touch_interface");

CONSTANT_STRING(firmware_name,"TouchInterface");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

const bool fast_mode = true;

const long null_long = 0;

const MPR121::ProximityMode proximity_mode = MPR121::DISABLED;

const uint8_t touch_threshold = 40;
const uint8_t release_threshold = 20;
const uint8_t touch_debounce = 1;
const uint8_t release_debounce = 1;

const MPR121::BaselineTracking baseline_tracking = MPR121::BASELINE_TRACKING_INIT_10BIT;
const uint8_t charge_discharge_current = 63;
const MPR121::ChargeDischargeTime charge_discharge_time = MPR121::CHARGE_DISCHARGE_TIME_HALF_US;
const MPR121::FirstFilterIterations first_filter_iterations = MPR121::FIRST_FILTER_ITERATIONS_34;
const MPR121::SecondFilterIterations second_filter_iterations = MPR121::SECOND_FILTER_ITERATIONS_10;
const MPR121::SamplePeriod sample_period = MPR121::SAMPLE_PERIOD_1MS;

// Pins

// Units

// Properties
CONSTANT_STRING(physical_channel_count_property_name,"physicalChannelCount");
const long physical_channel_count_min = 0;
const long physical_channel_count_max = MPR121::PHYSICAL_CHANNELS_PER_DEVICE;
const long physical_channel_count_element_default = 1;

// Parameters

// Functions
CONSTANT_STRING(reinitialize_function_name,"reinitialize");
CONSTANT_STRING(communicating_function_name,"communicating");

// Callbacks

// Errors
}
}
