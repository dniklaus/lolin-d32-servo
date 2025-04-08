/*
 * MyBatteryAdapter.cpp
 *
 *  Created on: 15.03.2018
 *      Author: niklaudi
 */

#include <Arduino.h>
#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include "Indicator.h"
#include "MyBatteryAdapter.h"

MyBatteryAdapter::MyBatteryAdapter(Indicator* battWarnLed, Indicator* servoPwrEn)
: BatteryAdapter()
, m_battWarnLed(battWarnLed)
, m_servoPwrEn(servoPwrEn)
, m_trPort(new DbgTrace_Port("batt", DbgTrace_Level::notice))
{ }

MyBatteryAdapter::~MyBatteryAdapter()
{
  delete m_trPort;
  m_trPort = 0;
}

float MyBatteryAdapter::readBattVoltageSenseFactor()
{
  return 2.2801;
}

unsigned int MyBatteryAdapter::readRawBattSenseValue()
{
  TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Batt: %d.%02dV, %s", 
    static_cast<int>(battery()->getBatteryVoltage()),
    static_cast<int>(battery()->getBatteryVoltage() * 100.0) -
    static_cast<int>(battery()->getBatteryVoltage()) * 100,
    battery()->isBattVoltageOk() ? "ok" : "/!\\");

  const uint8_t cVbatPin = A7;
  unsigned int rawBattSenseValue = analogRead(cVbatPin);
  return rawBattSenseValue;
}

void MyBatteryAdapter::notifyBattStateAnyChange()
{
  if ((0 != m_trPort) && (0 != battery()))
  {
    TR_PRINTF(m_trPort, DbgTrace_Level::notice,
        "MyBatteryAdapter::notifyBattStateAnyChange(), %d.%02dV, %s",
        static_cast<int>(battery()->getBatteryVoltage()),
        static_cast<int>(battery()->getBatteryVoltage() * 100.0)
            - static_cast<int>(battery()->getBatteryVoltage()) * 100,
        battery()->isBattVoltageOk() ? "ok" : "/!\\");
  }
}

void MyBatteryAdapter::notifyBattVoltageOk()
{
  // switch warn LED off
  if (0 != m_battWarnLed)
  {
    m_battWarnLed->clear();
  }

  // enable Servo PWR
  if (0 != m_servoPwrEn)
  {
    m_servoPwrEn->set();
  }
}

void MyBatteryAdapter::notifyBattVoltageBelowWarnThreshold()
{
  // switch warn LED on (blink)
  if (0 != m_battWarnLed)
  {
    m_battWarnLed->blink();
  }

  // enable Servo PWR
  if (0 != m_servoPwrEn)
  {
    m_servoPwrEn->set();
  }
}

void MyBatteryAdapter::notifyBattVoltageBelowStopThreshold()
{
  // switch warn LED on (blink)
  if (0 != m_battWarnLed)
  {
    m_battWarnLed->blink();
  }

  // disable Servo PWR
  if (0 != m_servoPwrEn)
  {
    m_servoPwrEn->clear();
  }
}

void MyBatteryAdapter::notifyBattVoltageBelowShutdownThreshold()
{
  // switch warn LED off
  if (0 != m_battWarnLed)
  {
    m_battWarnLed->clear();
  }

  // disable Servo PWR
  if (0 != m_servoPwrEn)
  {
    m_servoPwrEn->clear();
  }

  // go to Low Power sleep
  //esp_deep_sleep_start();
}
