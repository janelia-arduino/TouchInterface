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
  modular_server::Pin & bnc_b_pin = modular_server_.pin(modular_device_base::constants::bnc_b_pin_name);
  bnc_b_pin.setModeDigitalOutput();
  bnc_b_pin.setValue(LOW);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & polling_enabled_property = modular_server_.property(wire_interface::constants::polling_enabled_property_name);
  polling_enabled_property.setDefaultValue(constants::polling_enabled_default);

  modular_server::Property & polling_period_property = modular_server_.property(wire_interface::constants::polling_period_property_name);
  polling_period_property.setDefaultValue(constants::polling_period_default);

  modular_server::Property & physical_channel_count_property = modular_server_.createProperty(constants::physical_channel_count_property_name,constants::physical_channel_count_default);
  physical_channel_count_property.setRange(constants::physical_channel_count_min,constants::physical_channel_count_max);
  physical_channel_count_property.setArrayLengthRange(constants::TOUCH_DEVICE_COUNT_MAX,constants::TOUCH_DEVICE_COUNT_MAX);
  physical_channel_count_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&TouchInterface::setPhysicalChannelCountHandler));

  modular_server::Property & touch_threshold_property = modular_server_.createProperty(constants::touch_threshold_property_name,constants::touch_threshold_default);
  touch_threshold_property.setRange(constants::touch_threshold_min,constants::touch_threshold_max);
  touch_threshold_property.setArrayLengthRange(constants::TOUCH_DEVICE_COUNT_MAX,constants::TOUCH_DEVICE_COUNT_MAX);
  touch_threshold_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&TouchInterface::setTouchThresholdHandler));

  modular_server::Property & release_threshold_property = modular_server_.createProperty(constants::release_threshold_property_name,constants::release_threshold_default);
  release_threshold_property.setRange(constants::release_threshold_min,constants::release_threshold_max);
  release_threshold_property.setArrayLengthRange(constants::TOUCH_DEVICE_COUNT_MAX,constants::TOUCH_DEVICE_COUNT_MAX);
  release_threshold_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&TouchInterface::setReleaseThresholdHandler));

  modular_server::Property & touch_debounce_property = modular_server_.createProperty(constants::touch_debounce_property_name,constants::touch_debounce_default);
  touch_debounce_property.setRange(constants::touch_debounce_min,constants::touch_debounce_max);
  touch_debounce_property.setArrayLengthRange(constants::TOUCH_DEVICE_COUNT_MAX,constants::TOUCH_DEVICE_COUNT_MAX);
  touch_debounce_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&TouchInterface::setTouchDebounceHandler));

  modular_server::Property & release_debounce_property = modular_server_.createProperty(constants::release_debounce_property_name,constants::release_debounce_default);
  release_debounce_property.setRange(constants::release_debounce_min,constants::release_debounce_max);
  release_debounce_property.setArrayLengthRange(constants::TOUCH_DEVICE_COUNT_MAX,constants::TOUCH_DEVICE_COUNT_MAX);
  release_debounce_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&TouchInterface::setReleaseDebounceHandler));

  // Parameters

  // Functions
  modular_server::Function & reinitialize_function = modular_server_.createFunction(constants::reinitialize_function_name);
  reinitialize_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&TouchInterface::reinitializeHandler));
  reinitialize_function.setResultTypeBool();

  modular_server::Function & communicating_function = modular_server_.createFunction(constants::communicating_function_name);
  communicating_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&TouchInterface::communicatingHandler));
  communicating_function.setResultTypeArray();
  communicating_function.setResultTypeBool();

  // Callbacks
  setupTouchDevices();
  updateProperties();
  reinitialize();
}

bool TouchInterface::reinitialize()
{
  bool reinitialized = true;

  size_t touch_device_index;

  modular_server::Property & physical_channel_count_property = modular_server_.property(constants::physical_channel_count_property_name);
  long physical_channel_count;

  modular_server::Property & touch_threshold_property = modular_server_.property(constants::touch_threshold_property_name);
  long touch_threshold;

  modular_server::Property & release_threshold_property = modular_server_.property(constants::release_threshold_property_name);
  long release_threshold;

  modular_server::Property & touch_debounce_property = modular_server_.property(constants::touch_debounce_property_name);
  long touch_debounce;

  modular_server::Property & release_debounce_property = modular_server_.property(constants::release_debounce_property_name);
  long release_debounce;

  for (size_t wire_index=0; wire_index<getWireCount(); ++wire_index)
  {
    MPR121 & touch_devices = touch_devices_array_[wire_index];
    for (size_t device_index=0; device_index<getDeviceCount(wire_index); ++device_index)
    {
      resetWatchdog();

      MPR121::DeviceAddress device_address = getDeviceAddress(wire_index,device_index);
      bool device_setup = touch_devices.setupDevice(device_address);
      reinitialized = (reinitialized && device_setup);

      touch_device_index = getTouchDeviceIndex(wire_index,device_index);

      touch_threshold_property.getElementValue(touch_device_index,
        touch_threshold);
      release_threshold_property.getElementValue(touch_device_index,
        release_threshold);
      touch_devices.setAllDeviceChannelsThresholds(device_address,
        touch_threshold,
        release_threshold);
      touch_debounce_property.getElementValue(touch_device_index,
        touch_debounce);
      release_debounce_property.getElementValue(touch_device_index,
        release_debounce);
      touch_devices.setDebounce(device_address,
        touch_debounce,
        release_debounce);
      touch_devices.setBaselineTracking(device_address,
        constants::baseline_tracking);
      touch_devices.setChargeDischargeCurrent(device_address,
        constants::charge_discharge_current);
      touch_devices.setChargeDischargeTime(device_address,
        constants::charge_discharge_time);
      touch_devices.setFirstFilterIterations(device_address,
        constants::first_filter_iterations);
      touch_devices.setSecondFilterIterations(device_address,
        constants::second_filter_iterations);
      touch_devices.setSamplePeriod(device_address,
        constants::sample_period);
      physical_channel_count_property.getElementValue(touch_device_index,
        physical_channel_count);
      touch_devices.startChannels(device_address,
        physical_channel_count,
        constants::proximity_mode);
    }
  }
  if (reinitialized)
  {
    setupPolling();
  }
  return reinitialized;
}

bool TouchInterface::communicating(size_t touch_device_index)
{
  if ((touch_device_index >= constants::TOUCH_DEVICE_COUNT_MAX) ||
    (!touch_device_exists_[touch_device_index]))
  {
    return false;
  }
  MPR121 & touch_devices = getTouchDevices(touch_device_index);
  return touch_devices.communicating(constants::touch_device_addresses[touch_device_index]);
}

size_t TouchInterface::getTouchDeviceCountLimit()
{
  size_t wire_count = getWireCount();
  size_t last_wire_device_count = getDeviceCount(wire_count - 1);
  size_t touch_device_count_limit = (wire_count - 1) * MPR121::DEVICE_COUNT_MAX;
  touch_device_count_limit += last_wire_device_count;
  return touch_device_count_limit;
}

void TouchInterface::updateTouchStatus(size_t wire_index)
{
  for (size_t device_index=0; device_index<getDeviceCount(wire_index); ++device_index)
  {
    size_t touch_device_index = getTouchDeviceIndex(wire_index,device_index);
    if (touch_device_exists_[touch_device_index])
    {
      MPR121 & touch_devices = touch_devices_array_[wire_index];
      MPR121::DeviceAddress device_address = getDeviceAddress(wire_index,device_index);
      uint16_t touch_status = touch_devices.getTouchStatus(device_address);
      touch_status_prev_[touch_device_index] = touch_status_[touch_device_index];
      touch_status_[touch_device_index] = touch_status;
    }
  }
}

void TouchInterface::getWireAndDeviceIndex(size_t touch_device_index,
  size_t & wire_index,
  size_t & device_index)
{
  wire_index = touch_device_index / MPR121::DEVICE_COUNT_MAX;
  device_index = touch_device_index % MPR121::DEVICE_COUNT_MAX;
}

size_t TouchInterface::getTouchDeviceIndex(size_t wire_index,
  size_t device_index)
{
  return (wire_index * MPR121::DEVICE_COUNT_MAX) + device_index;
}

MPR121::DeviceAddress TouchInterface::getDeviceAddress(size_t wire_index,
  size_t device_index)
{
  size_t touch_device_index = getTouchDeviceIndex(wire_index,device_index);
  return constants::touch_device_addresses[touch_device_index];
}

MPR121 & TouchInterface::getTouchDevices(size_t touch_device_index)
{
  if (touch_device_index >= constants::TOUCH_DEVICE_COUNT_MAX)
  {
    return dummy_touch_devices_;
  }
  size_t wire_index;
  size_t device_index;
  getWireAndDeviceIndex(touch_device_index,
    wire_index,
    device_index);
  return touch_devices_array_[wire_index];
}

void TouchInterface::setupTouchDevices()
{
  size_t touch_device_index;
  for (size_t wire_index=0; wire_index<wire_interface::constants::WIRE_COUNT_MAX; ++wire_index)
  {
    for (size_t device_index=0; device_index<MPR121::DEVICE_COUNT_MAX; ++device_index)
    {
      touch_device_index = getTouchDeviceIndex(wire_index,device_index);
      touch_device_exists_[touch_device_index] = false;
      touch_status_prev_[touch_device_index] = 0;
      touch_status_[touch_device_index] = 0;
    }
  }
  for (size_t wire_index=0; wire_index<getWireCount(); ++wire_index)
  {
    MPR121 & touch_devices = touch_devices_array_[wire_index];
    touch_devices.setWire(*(wire_interface::constants::wire_ptrs[wire_index]),
      constants::fast_mode);
    for (size_t device_index=0; device_index<getDeviceCount(wire_index); ++device_index)
    {
      MPR121::DeviceAddress device_address = getDeviceAddress(wire_index,device_index);
      touch_devices.addDevice(device_address);
      touch_device_index = getTouchDeviceIndex(wire_index,device_index);
      touch_device_exists_[touch_device_index] = true;
    }
  }
}

void TouchInterface::updateProperties()
{
  size_t touch_device_count_limit = getTouchDeviceCountLimit();

  modular_server::Property & physical_channel_count_property = modular_server_.property(constants::physical_channel_count_property_name);
  physical_channel_count_property.setArrayLengthRange(touch_device_count_limit,touch_device_count_limit);

  modular_server::Property & touch_threshold_property = modular_server_.property(constants::touch_threshold_property_name);
  touch_threshold_property.setArrayLengthRange(touch_device_count_limit,touch_device_count_limit);

  modular_server::Property & release_threshold_property = modular_server_.property(constants::release_threshold_property_name);
  release_threshold_property.setArrayLengthRange(touch_device_count_limit,touch_device_count_limit);

  modular_server::Property & touch_debounce_property = modular_server_.property(constants::touch_debounce_property_name);
  touch_debounce_property.setArrayLengthRange(touch_device_count_limit,touch_device_count_limit);

  modular_server::Property & release_debounce_property = modular_server_.property(constants::release_debounce_property_name);
  release_debounce_property.setArrayLengthRange(touch_device_count_limit,touch_device_count_limit);

  size_t touch_device_index;
  for (size_t wire_index=0; wire_index<wire_interface::constants::WIRE_COUNT_MAX; ++wire_index)
  {
    for (size_t device_index=0; device_index<MPR121::DEVICE_COUNT_MAX; ++device_index)
    {
      touch_device_index = getTouchDeviceIndex(wire_index,device_index);
      setPhysicalChannelCountHandler(touch_device_index);
      setTouchThresholdHandler(touch_device_index);
      setReleaseThresholdHandler(touch_device_index);
      setTouchDebounceHandler(touch_device_index);
      setReleaseDebounceHandler(touch_device_index);
    }
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
  updateProperties();
}

void TouchInterface::setDeviceCountHandler(size_t wire_index)
{
  WireInterface::setDeviceCountHandler(wire_index);
  setupTouchDevices();
  updateProperties();
}

void TouchInterface::pollingHandler(int wire_index)
{
  updateTouchStatus(wire_index);

  MPR121 & touch_devices = touch_devices_array_[wire_index];

  size_t device_index = 0;
  size_t touch_device_index = getTouchDeviceIndex(wire_index,device_index);
  uint8_t device_channel = 0;

  modular_server::Pin & led_yellow_pin = modular_server_.pin(modular_device_base::constants::led_yellow_pin_name);
  modular_server::Pin & bnc_b_pin = modular_server_.pin(modular_device_base::constants::bnc_b_pin_name);
  if (touch_devices.deviceChannelTouched(touch_status_[touch_device_index],device_channel))
  {
    led_yellow_pin.setValue(HIGH);
    bnc_b_pin.setValue(HIGH);
  }
  else
  {
    led_yellow_pin.setValue(LOW);
    bnc_b_pin.setValue(LOW);
  }
}

void TouchInterface::setPhysicalChannelCountHandler(size_t touch_device_index)
{
  if (!touch_device_exists_[touch_device_index])
  {
    modular_server::Property & physical_channel_count_property = modular_server_.property(constants::physical_channel_count_property_name);
    physical_channel_count_property.disableFunctors();
    physical_channel_count_property.setElementValue(touch_device_index,
      constants::null_long);
    physical_channel_count_property.reenableFunctors();
  }
}

void TouchInterface::setTouchThresholdHandler(size_t touch_device_index)
{
  if (!touch_device_exists_[touch_device_index])
  {
    modular_server::Property & touch_threshold_property = modular_server_.property(constants::touch_threshold_property_name);
    touch_threshold_property.disableFunctors();
    touch_threshold_property.setElementValue(touch_device_index,
      constants::null_long);
    touch_threshold_property.reenableFunctors();
  }
}

void TouchInterface::setReleaseThresholdHandler(size_t touch_device_index)
{
  if (!touch_device_exists_[touch_device_index])
  {
    modular_server::Property & release_threshold_property = modular_server_.property(constants::release_threshold_property_name);
    release_threshold_property.disableFunctors();
    release_threshold_property.setElementValue(touch_device_index,
      constants::null_long);
    release_threshold_property.reenableFunctors();
  }
}

void TouchInterface::setTouchDebounceHandler(size_t touch_device_index)
{
  if (!touch_device_exists_[touch_device_index])
  {
    modular_server::Property & touch_debounce_property = modular_server_.property(constants::touch_debounce_property_name);
    touch_debounce_property.disableFunctors();
    touch_debounce_property.setElementValue(touch_device_index,
      constants::null_long);
    touch_debounce_property.reenableFunctors();
  }
}

void TouchInterface::setReleaseDebounceHandler(size_t touch_device_index)
{
  if (!touch_device_exists_[touch_device_index])
  {
    modular_server::Property & release_debounce_property = modular_server_.property(constants::release_debounce_property_name);
    release_debounce_property.disableFunctors();
    release_debounce_property.setElementValue(touch_device_index,
      constants::null_long);
    release_debounce_property.reenableFunctors();
  }
}

void TouchInterface::reinitializeHandler()
{
  bool reinitialized = reinitialize();
  modular_server_.response().returnResult(reinitialized);
}

void TouchInterface::communicatingHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t touch_device_index=0; touch_device_index<getTouchDeviceCountLimit(); ++touch_device_index)
  {
    modular_server_.response().write(communicating(touch_device_index));
  }
  modular_server_.response().endArray();
}
