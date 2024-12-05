#include "dora.h"

void initServer()
{
  //CORS compatiblity
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), "*");
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Methods"), "*");
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), "*");

  initVueApp();

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Resetting...");
    DORA::instance().reset();
  });

  
  //called when the url is not defined here, ajax-in; get-settings
  server.onNotFound([](AsyncWebServerRequest *request){
    Serial.println("Not-Found HTTP call:");
    Serial.println("URI: " + request->url());
    if (captivePortal(request)) return;

    //make API CORS compatible
    if (request->method() == HTTP_OPTIONS)
    {
      AsyncWebServerResponse *response = request->beginResponse(200);
      response->addHeader(F("Access-Control-Max-Age"), F("7200"));
      request->send(response);
      return;
    }

    AsyncWebServerResponse *response = request->beginResponse_P(404, "text/plain", "Not found");
    request->send(response);
  });

  /* 
    ██  █████  ██████  ██ 
   ██  ██   ██ ██   ██ ██ 
  ██   ███████ ██████  ██ 
 ██    ██   ██ ██      ██ 
██     ██   ██ ██      ██ 
  */

  server.on("/api", HTTP_GET, [](AsyncWebServerRequest *request){
    serveApi(request);
  });

  AsyncCallbackJsonWebHandler* apiHandler = new AsyncCallbackJsonWebHandler("/api", 
      [](AsyncWebServerRequest *request, JsonVariant &json) {
    serveApi(request, json.as<JsonObject>());
  });
  server.addHandler(apiHandler);

  /*
    ██ ███████ ██    ██ ███████ ███    ██ ████████ ███████ 
   ██  ██      ██    ██ ██      ████   ██    ██    ██      
  ██   █████   ██    ██ █████   ██ ██  ██    ██    ███████ 
 ██    ██       ██  ██  ██      ██  ██ ██    ██         ██ 
██     ███████   ████   ███████ ██   ████    ██    ███████ 
  */

  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    //send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!",NULL,millis(),1000);
  });
  //HTTP Basic authentication
  // events.setAuthentication("user", "pass");
  server.addHandler(&events);
}

void serveApi(AsyncWebServerRequest *request) {
  String url = request->url();
  ApiResponse route = resolveApiRoute(&url);
  jsonStatus_t status = JSON_ERR;

  if(route == API_V1_VALID) {
    // create new response with a large enough buffer
    AsyncJsonResponse *response = new AsyncJsonResponse(false, JSON_BUFFER_SIZE); 
    JsonObject responseJson = response->getRoot().as<JsonObject>();

    route = handleApiV1(request->method(), &url, responseJson);

    if(route == API_SUCCESS) {
      response->setLength();
      request->send(response);
      // request->send(200, TEXT_PLAIN, "API v1 valid");
      return;
    }
  } else if (route == API_DOC) {
    request->send(200, TEXT_PLAIN, "Documentation for each of the API versions lives here");
    return;
  } else if (route == API_V1_DOC) {
    request->send(200, TEXT_PLAIN, "API v1 documentation");
    return;
  }

  request->send(403, TEXT_PLAIN, "Method not allowed");
}

void serveApi(AsyncWebServerRequest *request, JsonObject root) {
  String url = request->url();
  ApiResponse route = resolveApiRoute(&url);
  jsonStatus_t status = JSON_ERR;

  if(route == API_V1_VALID) {
    // create new response with a large enough buffer
    AsyncJsonResponse *response = new AsyncJsonResponse(false, 10240);
    JsonObject responseJson = response->getRoot().as<JsonObject>();

    route = handleApiV1(request->method(), &url, root, responseJson);
    
    if(route == API_SUCCESS) {
      // response->setLength();
      // request->send(response);
      request->send(200, TEXT_PLAIN, "API v1 valid");
      return;
    }
  }

  request->send(403, TEXT_PLAIN, "Method not allowed");
}

//Is this an IP?
bool isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

// from https://github.com/Aircoookie/WLED/blob/2f6f0d2f3e3ca7c016d7f507a9a5433564484de0/wled00/wled_server.cpp#L94
bool captivePortal(AsyncWebServerRequest *request)
{
#ifdef DORA_CAPTIVE_PORTAL
  if (ON_STA_FILTER(request)) return false; //only serve captive in AP mode
  String hostH;
  if (!request->hasHeader(F("Host"))) return false;
  hostH = request->getHeader(F("Host"))->value();

  if (!isIp(hostH)) {
    Serial.println(F("Captive portal"));
    AsyncWebServerResponse *response = request->beginResponse(302);
    response->addHeader(F("Location"), F("http://10.1.2.3"));
    request->send(response);
    return true;
  }
#endif
  return false;
}
