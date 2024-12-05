#pragma once

/** all general functions (void) that are supposed to be used defined here.
 *  Each function can be written in a separate file, but the declaration should be here.
 *  Make sure you include dora.h in the created file
 */


/////// dora_server.cpp ///////

/**
 * @brief checks if the request is a captive portal request
 *        and forwards to http://10.1.2.3
 * 
 * @param request - the request to check from where function was called
 * @return true - request is a captive portal request
 * @return false - request is not a captive portal request
 */
bool captivePortal(AsyncWebServerRequest *request);

/**
 * @brief called once from setup and initializes:
 *         - the server with all files and endpoints
 *         - events (SSE - server sent events)
 *         - Websocket
 *         - captive portal (if enabled)
 */
void initServer();

void serveApi(AsyncWebServerRequest *request);

void serveApi(AsyncWebServerRequest *request, JsonObject root);


/////// api.cpp ///////

String extractNextRoute(String* url, bool shorten);
String extractNextRoute(String* url);
String keepNextRoute(String* url);

ApiResponse resolveApiRoute(String* url);

ApiResponse handleApiV1(uint8_t method, String* url, JsonObject requestJson, JsonObject responseJson);
ApiResponse handleApiV1(uint8_t method, String* url, JsonObject responseJson);

/////// json.cpp ///////

jsonStatus_t serializeGET(String url, JsonObject root);

jsonStatus_t deserializePOST(String url, JsonObject root);

jsonStatus_t deserializePUT(String url, JsonObject root);

jsonStatus_t deserializeDELETE(String url, JsonObject root);

void serializeState(JsonObject root);
void serializeConfig(JsonObject root);
void serializeTime(JsonObject root);

void deserializeConfig(JsonObject root);
void deserializeTime(JsonObject root);

/////// events.cpp ///////

/**
 * @brief sends events and its data to the client at different intervals
 *        is called in the main loop
 *        mainly used for live data
 */
void sendEvents();


/////// vue_app.cpp ///////
/**
 * @brief initializes all vue endpoints
 *        (serves content of vue_app.h)
 *        endpoints are generated from nodejs deploy script
 *        called once from setup
 */
void initVueApp();