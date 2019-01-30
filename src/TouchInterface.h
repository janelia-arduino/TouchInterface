// ----------------------------------------------------------------------------
// TouchInterface.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef TOUCH_INTERFACE_H
#define TOUCH_INTERFACE_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <MPR121.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <WireInterface.h>

#include "TouchInterface/Constants.h"


class TouchInterface : public WireInterface
{
public:
  TouchInterface();
  virtual void setup();

  virtual bool reinitialize();

  bool communicating(size_t touch_device_index);

  size_t getTouchDeviceCountLimit();

protected:
  // Handlers
  virtual void setWireCountHandler();
  virtual void setDeviceCountHandler(size_t wire_index);
  virtual void pollingHandler(int wire_index);

private:
  modular_server::Property properties_[touch_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[touch_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[touch_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[touch_interface::constants::CALLBACK_COUNT_MAX];

  MPR121 touch_devices_array_[wire_interface::constants::WIRE_COUNT_MAX];
  MPR121 dummy_touch_devices_;
  bool touch_device_exists_[touch_interface::constants::TOUCH_DEVICE_COUNT_MAX];

  void getWireAndDeviceIndex(size_t touch_device_index,
    size_t & wire_index,
    size_t & device_index);
  size_t getTouchDeviceIndex(size_t wire_index,
    size_t device_index);
  MPR121::DeviceAddress getDeviceAddress(size_t wire_index,
    size_t device_index);
  MPR121 & getTouchDevices(size_t touch_device_index);
  void setupTouchDevices();
  void updateProperties();

  // Handlers
  void setPhysicalChannelCountHandler(size_t touch_device_index);
  void reinitializeHandler();
  void communicatingHandler();

};

#endif
