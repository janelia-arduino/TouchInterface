// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

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
  MPR121::ADDRESS_5A,
  MPR121::ADDRESS_5B,
  MPR121::ADDRESS_5C,
  MPR121::ADDRESS_5D,
};

// Pins

// Units

// Properties
const bool polling_enabled_default[wire_interface::constants::WIRE_COUNT_MAX] =
{
  polling_enabled_element_default,
  polling_enabled_element_default,
};

const long polling_period_default[wire_interface::constants::WIRE_COUNT_MAX] =
{
  polling_period_element_default,
  polling_period_element_default,
};

const long physical_channel_count_default[TOUCH_DEVICE_COUNT_MAX] =
{
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
  physical_channel_count_element_default,
};

const long touch_threshold_default[TOUCH_DEVICE_COUNT_MAX] =
{
  touch_threshold_element_default,
  touch_threshold_element_default,
  touch_threshold_element_default,
  touch_threshold_element_default,
  touch_threshold_element_default,
  touch_threshold_element_default,
  touch_threshold_element_default,
  touch_threshold_element_default,
};

const long release_threshold_default[TOUCH_DEVICE_COUNT_MAX] =
{
  release_threshold_element_default,
  release_threshold_element_default,
  release_threshold_element_default,
  release_threshold_element_default,
  release_threshold_element_default,
  release_threshold_element_default,
  release_threshold_element_default,
  release_threshold_element_default,
};

const long touch_debounce_default[TOUCH_DEVICE_COUNT_MAX] =
{
  touch_debounce_element_default,
  touch_debounce_element_default,
  touch_debounce_element_default,
  touch_debounce_element_default,
  touch_debounce_element_default,
  touch_debounce_element_default,
  touch_debounce_element_default,
  touch_debounce_element_default,
};

const long release_debounce_default[TOUCH_DEVICE_COUNT_MAX] =
{
  release_debounce_element_default,
  release_debounce_element_default,
  release_debounce_element_default,
  release_debounce_element_default,
  release_debounce_element_default,
  release_debounce_element_default,
  release_debounce_element_default,
  release_debounce_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
