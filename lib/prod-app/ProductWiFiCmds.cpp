/*
 * ProductDebug.cpp
 *
 *  Created on: 14.06.2016
 *      Author: nid
 */

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
#include <DbgCliNode.h>
#include <DbgCliTopic.h>
#include <DbgCliCommand.h>
#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include "ProductWiFiCmds.h"


//-----------------------------------------------------------------------------
// WiFi Commands
//-----------------------------------------------------------------------------
DbgCli_Cmd_WifiMac::DbgCli_Cmd_WifiMac(DbgCli_Topic* wifiTopic)
: DbgCli_Command(wifiTopic, "mac", "Print MAC Address.")
{ }

void DbgCli_Cmd_WifiMac::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  Serial.println();
  Serial.print("Wifi MAC: ");
  Serial.println(WiFi.macAddress().c_str());
  Serial.println();
}

DbgCli_Cmd_WifiNets::DbgCli_Cmd_WifiNets(DbgCli_Topic* wifiTopic)
: DbgCli_Command(wifiTopic, "nets", "Print nearby networks.")
{ }

void DbgCli_Cmd_WifiNets::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  bool bailOut = false;

  // scan for nearby networks:
  Serial.println();
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    Serial.println("Couldn't get a wifi connection");
    bailOut = true;
  }

  if (!bailOut)
  {
    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
      Serial.print(thisNet);
      Serial.print(") ");
      Serial.print(WiFi.SSID(thisNet));
      Serial.print(" - Signal: ");
      Serial.print(WiFi.RSSI(thisNet));
      Serial.print(" dBm");
      Serial.print(" - Encryption: ");
      printEncryptionType(WiFi.encryptionType(thisNet));
    }
  }
  Serial.println();
}

void DbgCli_Cmd_WifiNets::printEncryptionType(int thisType)
{
  // read the encryption type and print out the name:
  switch (thisType) 
  {
#if ! defined(ESP32)
// TODO: solve this for ESP32!
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
#endif
    default:
      Serial.println("Unknown");
      break;
  }
}

DbgCli_Cmd_WifiStat::DbgCli_Cmd_WifiStat(DbgCli_Topic* wifiTopic)
: DbgCli_Command(wifiTopic, "stat", "Show WiFi connection status.")
{ }

void DbgCli_Cmd_WifiStat::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  wl_status_t wlStatus = WiFi.status();
  Serial.println();
  Serial.println(wlStatus == WL_NO_SHIELD       ? "NO_SHIELD      " :
                  wlStatus == WL_IDLE_STATUS     ? "IDLE_STATUS    " :
                  wlStatus == WL_NO_SSID_AVAIL   ? "NO_SSID_AVAIL  " :
                  wlStatus == WL_SCAN_COMPLETED  ? "SCAN_COMPLETED " :
                  wlStatus == WL_CONNECTED       ? "CONNECTED      " :
                  wlStatus == WL_CONNECT_FAILED  ? "CONNECT_FAILED " :
                  wlStatus == WL_CONNECTION_LOST ? "CONNECTION_LOST" :
                  wlStatus == WL_DISCONNECTED    ? "DISCONNECTED   " : "UNKNOWN");
  Serial.println();
  WiFi.printDiag(Serial);
  Serial.println();
}

DbgCli_Cmd_WifiDis::DbgCli_Cmd_WifiDis(DbgCli_Topic* wifiTopic)
: DbgCli_Command(wifiTopic, "dis", "Disconnect WiFi.")
{ }

void DbgCli_Cmd_WifiDis::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  Serial.println();
  if (argc - idxToFirstArgToHandle > 0)
  {
    printUsage();
  }
  else
  {
    const bool DO_NOT_SET_wifioff = false;
    WiFi.disconnect(DO_NOT_SET_wifioff);
    Serial.println("WiFi is disconnected now.");
  }
  Serial.println();
}

void DbgCli_Cmd_WifiDis::printUsage()
{
  Serial.println(getHelpText());
  Serial.println("Usage: dbg wifi dis");
}

DbgCli_Cmd_WifiCon::DbgCli_Cmd_WifiCon(DbgCli_Topic* wifiTopic)
: DbgCli_Command(wifiTopic, "con", "Connect to WiFi.")
{ }

void DbgCli_Cmd_WifiCon::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  Serial.println();
  if (argc - idxToFirstArgToHandle != 2)
  {
    printUsage();
  }
  else
  {
    const char* ssid = args[idxToFirstArgToHandle];
    const char* pass = args[idxToFirstArgToHandle+1];
    Serial.print("SSID: ");
    Serial.print(ssid);
    Serial.print(", pass: ");
    Serial.println(pass);
    WiFi.begin(ssid, pass);
    Serial.println("WiFi is connecting now.");
  }
  Serial.println();
}

void DbgCli_Cmd_WifiCon::printUsage()
{
  Serial.println(getHelpText());
  Serial.println("Usage: dbg wifi con <SSID> <passwd>");
}
