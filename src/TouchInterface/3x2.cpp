// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace touch_interface
{
namespace constants
{
const MPR121::DeviceAddress touch_device_addresses[TOUCH_DEVICE_COUNT_MAX] =
{
  MPR121::ADDRESS_5A,
  MPR121::ADDRESS_5B,
  MPR121::ADDRESS_5C,
  MPR121::ADDRESS_5D,
};

// Pins

// Units

// Properties
const long physical_channel_count_default[TOUCH_DEVICE_COUNT_MAX] =
{
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
