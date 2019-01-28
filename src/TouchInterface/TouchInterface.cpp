// ----------------------------------------------------------------------------
// TouchInterface.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../TouchInterface.h"


using namespace touch_interface;

TouchInterface::TouchInterface()
{
}

void TouchInterface::setup()
{
  // Parent Setup
  WireInterface::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & physical_channel_count_property = modular_server_.createProperty(constants::physical_channel_count_property_name,constants::physical_channel_count_default);
  physical_channel_count_property.setRange(constants::physical_channel_count_min,constants::physical_channel_count_max);
  physical_channel_count_property.setArrayLengthRange(constants::TOUCH_DEVICE_COUNT_MAX,constants::TOUCH_DEVICE_COUNT_MAX);
  physical_channel_count_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&TouchInterface::setPhysicalChannelCountHandler));

  // Parameters

  // Functions

  // Callbacks

  setupTouchDevices();
}

void TouchInterface::setupTouchDevices()
{
  for (size_t wire_index=0; wire_index<getWireCount(); ++wire_index)
  {
    MPR121 & touch_devices = touch_devices_array_[wire_index];
    touch_devices.setWire(*(wire_interface::constants::wire_ptrs[wire_index]),
      constants::fast_mode);
    for (size_t device_index=0; device_index<getDeviceCount(wire_index); ++device_index)
    {
      size_t touch_devices_index = (wire_index * MPR121::DEVICE_COUNT_MAX) + device_index;
      touch_devices.addDevice(constants::touch_device_addresses[touch_devices_index]);
    }
    touch_devices.setupAllDevices();
  }
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void TouchInterface::setWireCountHandler()
{
  WireInterface::setWireCountHandler();
  setupTouchDevices();
}

void TouchInterface::setDeviceCountHandler(size_t wire_index)
{
  WireInterface::setDeviceCountHandler(wire_index);
  setupTouchDevices();
}

void TouchInterface::pollingHandler(int wire_index)
{
}

void TouchInterface::setPhysicalChannelCountHandler(size_t touch_device_index)
{
}
