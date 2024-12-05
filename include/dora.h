#pragma once

// this is the only file that should be included

#include <Arduino.h>


#include <elapsedMillis.h>

#ifdef DORA_CAPTIVE_PORTAL
#include <DNSServer.h>
#endif
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "const.h"
#include "fcn_declare.h"


/*
===============================================================================
  Global variables
===============================================================================
*/
// both declared and defined in header (solution from http://www.keil.com/support/docs/1868.htm)
// this is to avoid multiple definition of global variables
//
//e.g. byte test = 2 becomes APP_GLOBAL byte test _INIT(2);
//     int arr[]{0,1,2} becomes APP_GLOBAL int arr[] _INIT_N(({0,1,2}));

#ifndef RMTC_DEFINE_GLOBAL_VARS
# define APP_GLOBAL extern
# define _INIT(x)
# define _INIT_N(x)
#else
# define APP_GLOBAL
# define _INIT(x) = x

//needed to ignore commas in array definitions
#define UNPACK( ... ) __VA_ARGS__
# define _INIT_N(x) UNPACK x
#endif

#define STRINGIFY(X) #X
#define TOSTRING(X) STRINGIFY(X)


///// wifi /////

APP_GLOBAL bool apActive _INIT(false);

#ifdef DORA_CAPTIVE_PORTAL
// dns server
APP_GLOBAL DNSServer dnsServer;
#endif


///// AsyncWebServer /////

APP_GLOBAL AsyncWebServer server _INIT_N(((80)));
APP_GLOBAL AsyncEventSource events _INIT_N((("/events")));


class DORA {
public:
  DORA();
  static DORA& instance()
  {
    static DORA instance;
    return instance;
  }

  void setup();

  void loop();
  void reset();

  void initAp();
};
