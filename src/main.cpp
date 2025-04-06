/*
 * wiring-skeleton.cpp
 *
 *  Created on: 05.02.2025
 *      Author: niklausd
 */

#include <Arduino.h>
#include <App.h>

static App* s_app;

void setup()
{
  s_app = new App();
  if (0 != s_app)
  {
    s_app->setup();
  }
}

void loop()
{
  if (0 != s_app)
  {
    s_app->loop();
  }
}
