/*
 * TestLedMqttSubscriber.cpp
 *
 *  Created on: 05.02.2025
 *      Author: dniklaus
 */

#include "Indicator.h"
#include "SpinTimer.h"
#include "DbgTracePort.h"
#include "DbgTraceLevel.h"
#include "TestLedMqttSubscriber.h"

  TestLedMqttSubscriber::TestLedMqttSubscriber(Indicator* indicator)
  : MqttTopicSubscriber("test/led")
  , m_indicator(indicator)
  , m_trPort(new DbgTrace_Port("mqttled", DbgTrace_Level::debug))
  { }

  TestLedMqttSubscriber::~TestLedMqttSubscriber()
  {
    delete m_trPort;
    m_trPort = 0;
  }

  void TestLedMqttSubscriber::assignIndicator(Indicator* indicator)
  {
    m_indicator = indicator;
  }

  bool TestLedMqttSubscriber::processMessage(MqttRxMsg* rxMsg)
  {
    bool msgHasBeenHandled = false;

    if (0 != rxMsg)
    {
      bool state = atoi(rxMsg->getRxMsgString());
      TR_PRINTF(m_trPort, DbgTrace_Level::debug, "LED state: %s", (state > 0) ? "on" : "off");

      if (0 != m_indicator)
      {
        if (state)
        {
          m_indicator->set();
        }
        else
        {
          m_indicator->clear();
        }
      }

      msgHasBeenHandled = true;
    }
    else
    {
      TR_PRINTF(m_trPort, DbgTrace_Level::error, "rxMsg unavailable!");
    }
    return msgHasBeenHandled;
  }
