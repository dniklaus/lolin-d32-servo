/*
 * ProductDebug.h
 *
 *  Created on: 14.06.2016
 *      Author: nid
 */

#ifndef LIB_PROD_DBG_PRODUCTDEBUG_H_
#define LIB_PROD_DBG_PRODUCTDEBUG_H_

class AppDebug;
class SerialCommand;

class ProductDebug
{
public:
  static void setupProdDebugEnv(SerialCommand* sCmd);

private:
  static AppDebug* s_appDebug;
};

#endif /* LIB_PROD_DBG_PRODUCTDEBUG_H_ */
