/*
 * TestLedMqttSubscriber.h
 *
 *  Created on: 05.02.2025
 *      Author: dniklaus
 */

#ifndef TestLedMqttSubscriber_H_
#define TestLedMqttSubscriber_H_

#include "MqttTopic.h"

class Indicator;
class DbgTrace_Port;

class TestLedMqttSubscriber : public MqttTopicSubscriber
{
private:
  Indicator* m_indicator;
  DbgTrace_Port* m_trPort;

public:
  TestLedMqttSubscriber(Indicator* indicator = 0);
  virtual ~TestLedMqttSubscriber();

  void assignIndicator(Indicator* indicator);

  bool processMessage(MqttRxMsg* rxMsg);

private:
  // forbidden default functions
  TestLedMqttSubscriber& operator = (const TestLedMqttSubscriber& src); // assignment operator
  TestLedMqttSubscriber(const TestLedMqttSubscriber& src);              // copy constructor
};

#endif
