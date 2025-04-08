/*
 * MyBatteryAdapter.h
 *
 *  Created on: 15.03.2018
 *      Author: niklaudi
 */

#ifndef LIB_ADAPTERS_MYBATTERYADAPTER_H_
#define LIB_ADAPTERS_MYBATTERYADAPTER_H_

#include <Battery.h>

class Indicator;
class DbgTrace_Port;

class MyBatteryAdapter: public BatteryAdapter
{
public:
  MyBatteryAdapter(Indicator* battWarnLed, Indicator* servoPwrEn);
  virtual ~MyBatteryAdapter();

  float readBattVoltageSenseFactor();

  unsigned int readRawBattSenseValue();

  void notifyBattStateAnyChange();

  void notifyBattVoltageOk();
  void notifyBattVoltageBelowWarnThreshold();
  void notifyBattVoltageBelowStopThreshold();
  void notifyBattVoltageBelowShutdownThreshold();

private:
  Indicator* m_battWarnLed;
  Indicator* m_servoPwrEn;
  DbgTrace_Port* m_trPort;

private: // forbidden default functions
	MyBatteryAdapter& operator = (const MyBatteryAdapter& src); // assignment operator
	MyBatteryAdapter(const MyBatteryAdapter& src);              // copy constructor
};

#endif /* LIB_ADAPTERS_MYBATTERYADAPTER_H_ */
