/*
 * ProductDebug.cpp
 *
 *  Created on: 14.06.2016
 *      Author: nid
 */

#include <Arduino.h>
#include <SerialCommand.h>
#include <AppDebug.h>
#include "ProductWiFiCmds.h"
#include "ProductDebug.h"

AppDebug* ProductDebug::s_appDebug = 0;

void ProductDebug::setupProdDebugEnv(SerialCommand* sCmd)
{
  s_appDebug = new AppDebug(sCmd);
  s_appDebug->setupDebugEnv();

  Serial.println();
  Serial.println("---------------------------------------------");
  Serial.println("Hello from Wiring (WiFi) Controller!");
  Serial.println("---------------------------------------------");
  Serial.println();
}
