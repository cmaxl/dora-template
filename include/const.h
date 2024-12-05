#pragma once

#define JSON_BUFFER_SIZE 4032

const char TEXT_PLAIN[] PROGMEM = "text/plain";
const char TEXT_HTML[] PROGMEM = "text/html";
const char TEXT_CSS[] PROGMEM = "text/css";
const char APPLICATION_JAVASCRIPT[] PROGMEM = "application/javascript";

// Enum for API response status
enum ApiResponse {
  API_SUCCESS,
  API_ERROR,
  API_V1_VALID,
  API_V1_DOC,
  API_DOC,
  API_NONE
};

const char END_OF_ROUTE[] PROGMEM = "/";

enum jsonStatus_t
{
   JSON_OK,
   JSON_NULL,
   JSON_NOT_FOUND,
   JSON_ERR
};