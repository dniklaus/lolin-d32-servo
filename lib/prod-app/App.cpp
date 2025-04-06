/*
 * App.cpp
 *
 *  Created on: 18.05.2023
 *      Author: didi
 */
#include <Arduino.h>
#include <SerialCommand.h>
#include <SpinTimer.h>
#include <Indicator.h>
#include <IndicatorFactory.h>
#include "MyBuiltinLedIndicatorAdapter.h"
#include <Button.h>
#include <ButtonEdgeDetector.h>
#include <MyButtonAdapter.h>
#include <ArduinoDigitalInPinSupervisor.h>
#include <ProductDebug.h>
#include <ECMqttClient.h>   // ERNI Community MQTT client wrapper library (depends on MQTT library)
#include "MqttTopic.h"
#include <DbgCliNode.h>
#include <DbgCliTopic.h>
#include <DbgCliCommand.h>
#include "ProductWiFiCmds.h"
#include "LedTestBlinkPublisher.h"
#include "TestLedMqttSubscriber.h"
#include "App.h"

#define MQTT_SERVER "test.mosquitto.org"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
// see https://github.com/espressif/arduino-esp32/issues/1960#issuecomment-429546528
#endif

//-----------------------------------------------------------------------------
// ESP8266 / ESP32 WiFi Client
//-----------------------------------------------------------------------------
#if defined(ESP8266) || defined(ESP32)
WiFiClient wifiClient;
#endif

const char App::s_termChar = '\n';

App::App()
: m_sCmd(new SerialCommand(s_termChar))
, m_led(0)
{ }

App::~App()
{ 
  if (0 != m_led)
  {
    delete m_led->adapter();
    m_led->assignAdapter(0);
  }

  delete m_led;
  m_led = 0;

  delete m_sCmd;
  m_sCmd = 0;
}

void App::setup()
{
  // setup basic debug environment (heap usage printer, trace ports & dbg cli)
  ProductDebug::setupProdDebugEnv(m_sCmd);

  // indicator LED
  m_led = IndicatorFactory::createIndicator("led", "Built in LED.");
  m_led->assignAdapter(new MyBuiltinLedIndicatorAdapter());

  #ifdef USER_BTN
    new Button(new ArduinoDigitalInPinSupervisor(USER_BTN), new ButtonEdgeDetector(), new MyButtonAdapter(m_led));
  #endif

  #if defined(ESP8266)
    enableWiFiAtBootTime();
  #endif

  #if defined(ESP8266) || defined(ESP32)
    WiFi.persistent(true);
    WiFi.mode(WIFI_STA);

    //-----------------------------------------------------------------------------
    // WiFi Commands
    //-----------------------------------------------------------------------------
    DbgCli_Topic* wifiTopic = new DbgCli_Topic(DbgCli_Node::RootNode(), "wifi", "WiFi debug commands");
    new DbgCli_Cmd_WifiMac(wifiTopic);
    new DbgCli_Cmd_WifiNets(wifiTopic);
    new DbgCli_Cmd_WifiStat(wifiTopic);
    new DbgCli_Cmd_WifiDis(wifiTopic);
    new DbgCli_Cmd_WifiCon(wifiTopic);

    //-----------------------------------------------------------------------------
    // MQTT Client
    //-----------------------------------------------------------------------------
    ECMqttClient.begin(MQTT_SERVER, ECMqttClientClass::defaultMqttPort, wifiClient, WiFi.macAddress().c_str());
    new TestLedMqttSubscriber(m_led);
    new DefaultMqttSubscriber("test/startup/#");
    new MqttTopicPublisher("test/startup", WiFi.macAddress().c_str(), MqttTopicPublisher::DO_AUTO_PUBLISH);
    // new LedTestBlinkPublisher();  // TODO: fix BUG, when this object gets created
  #endif
}

void App::loop()
{
  if (0 != m_sCmd)
  {
    m_sCmd->readSerial();     // process serial commands
  }
  ECMqttClient.loop();        // process MQTT Client
  scheduleTimers();           // process Timers
}
