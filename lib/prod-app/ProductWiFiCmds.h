/*
 * ProductWiFiCmds.h
 *
 *  Created on: 05.02.2025
 *      Author: dniklaus
 */

#ifndef LIB_PROD_WIFICMDS_H_
#define LIB_PROD_WIFICMDS_H_

#include <DbgCliCommand.h>

class DbgCli_Topic;

//-----------------------------------------------------------------------------
// WiFi Commands
//-----------------------------------------------------------------------------
class DbgCli_Cmd_WifiMac : public DbgCli_Command
{
public:
  DbgCli_Cmd_WifiMac(DbgCli_Topic* wifiTopic);
  virtual ~DbgCli_Cmd_WifiMac() { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);
};

//-----------------------------------------------------------------------------

class DbgCli_Cmd_WifiNets : public DbgCli_Command
{
public:
  DbgCli_Cmd_WifiNets(DbgCli_Topic* wifiTopic);
  virtual ~DbgCli_Cmd_WifiNets() { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);

private:
  void printEncryptionType(int thisType);
};

//-----------------------------------------------------------------------------

class DbgCli_Cmd_WifiStat : public DbgCli_Command
{
public:
  DbgCli_Cmd_WifiStat(DbgCli_Topic* wifiTopic);
  virtual ~DbgCli_Cmd_WifiStat() { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);
};

//-----------------------------------------------------------------------------

class DbgCli_Cmd_WifiDis : public DbgCli_Command
{
public:
  DbgCli_Cmd_WifiDis(DbgCli_Topic* wifiTopic);
  virtual ~DbgCli_Cmd_WifiDis() { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);

private:
  void printUsage();
};

//-----------------------------------------------------------------------------

class DbgCli_Cmd_WifiCon : public DbgCli_Command
{
public:
  DbgCli_Cmd_WifiCon(DbgCli_Topic* wifiTopic);
  virtual ~DbgCli_Cmd_WifiCon() { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);

private:
  void printUsage();
};

#endif
