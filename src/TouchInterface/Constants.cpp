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

// Pins

// Units

// Properties
CONSTANT_STRING(physical_channel_count_property_name,"physicalChannelCount");
const long physical_channel_count_min = 1;
const long physical_channel_count_max = MPR121::PHYSICAL_CHANNELS_PER_DEVICE;
const long physical_channel_count_element_default = 1;

// Parameters

// Functions

// Callbacks

// Errors
}
}
