/*
 * MyServoPwrEnIndicatorAdapter.h
 *
 *  Created on: 06.04.2025
 *      Author: dniklaus
 */

#ifndef LIB_ADAPTER_MyServoPwrEnIndicatorAdapter_H_
#define LIB_ADAPTER_MyServoPwrEnIndicatorAdapter_H_

#include <Indicator.h>

class MyServoPwrEnIndicatorAdapter: public AIndicatorAdapter
{
public:
  MyServoPwrEnIndicatorAdapter();
  virtual ~MyServoPwrEnIndicatorAdapter();
  void notifyStatusChange(bool status);

private:
  const static int s_servoPwrEnPin;
  
private:
  void setPwrEn(bool isOn);

private:  // forbidden default functions
  MyServoPwrEnIndicatorAdapter(const MyServoPwrEnIndicatorAdapter &other) = delete;
  MyServoPwrEnIndicatorAdapter(MyServoPwrEnIndicatorAdapter &&other) = delete;
};

#endif /* LIB_ADAPTER_MyServoPwrEnIndicatorAdapter_H_ */
