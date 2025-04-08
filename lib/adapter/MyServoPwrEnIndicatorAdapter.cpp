/*
 * MyServoPwrEnIndicatorAdapter.cpp
 *
 *  Created on: 06.04.2025
 *      Author: dniklaus
 */

#include "MyServoPwrEnIndicatorAdapter.h"

#include <Arduino.h>

const int MyServoPwrEnIndicatorAdapter::s_servoPwrEnPin = 15;

MyServoPwrEnIndicatorAdapter::MyServoPwrEnIndicatorAdapter()
{
  // initialize Servo Power Enable pin as output
  pinMode(s_servoPwrEnPin, OUTPUT);

  // disable Servo Power
  setPwrEn(false);
}

MyServoPwrEnIndicatorAdapter::~MyServoPwrEnIndicatorAdapter()
{ }

void MyServoPwrEnIndicatorAdapter::notifyStatusChange(bool status)
{
  setPwrEn(status);
}

void MyServoPwrEnIndicatorAdapter::setPwrEn(bool isOn)
{
  digitalWrite(s_servoPwrEnPin, isOn);
}
