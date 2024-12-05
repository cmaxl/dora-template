#include "dora.h"

String extractNextRoute(String* url, bool shorten) {
  // abort if url has no leading '/'
  if(!url->startsWith("/")) {
    return END_OF_ROUTE;
  }
  // add a slash at the end if it is missing
  if(!url->endsWith("/")) {
    *url += "/";
  }
  int beginIndex = url->indexOf('/', 1);
  if(beginIndex != -1) {
    int endIndex = url->indexOf('/', beginIndex + 1);
    if(endIndex != -1) {
      String nextRoute = url->substring(beginIndex, endIndex);
      // shorten the delivered String
      if(shorten) *url = url->substring(beginIndex);
      return nextRoute;
    }
  }
  // no next route found and return empty string
  return END_OF_ROUTE;
}

String extractNextRoute(String* url) {
  return extractNextRoute(url, true);
}

String keepNextRoute(String* url) {
  return extractNextRoute(url, false);
}

ApiResponse resolveApiRoute(String* url) {
  Serial.println("Resolving API route: ");
  String nextRoute = extractNextRoute(url);
  Serial.println("Next route: " + nextRoute);
  if (nextRoute == "/v1") {
    nextRoute = keepNextRoute(url);
    if(nextRoute != END_OF_ROUTE) {
      return API_V1_VALID;
    }
    else {
      return API_V1_DOC;
    }
  } else if (nextRoute == END_OF_ROUTE) {
    return API_DOC;
  } else {
    return API_NONE;
  }
}

// Function prototypes for handling different HTTP methods
ApiResponse handleV1Get(String* url, JsonObject responseJson);
ApiResponse handleV1Put(String* url, JsonObject requestJson, JsonObject responseJson);
ApiResponse handleV1Post(String* url, JsonObject requestJson, JsonObject responseJson);
ApiResponse handleV1Delete(String* url, JsonObject responseJson);

ApiResponse handleApiV1(uint8_t method, String* url, JsonObject requestJson, JsonObject responseJson) {
  String nextRoute = extractNextRoute(url);
    if(nextRoute != END_OF_ROUTE) {
      switch (method) {
        case HTTP_GET:
          return handleV1Get(url, responseJson);
        case HTTP_PUT:
          return handleV1Put(url, requestJson, responseJson);
        case HTTP_POST:
          return handleV1Post(url, requestJson, responseJson);
        case HTTP_DELETE:
          return handleV1Delete(url, responseJson);
        default:
          return API_ERROR;
      }
    }
}

ApiResponse handleApiV1(uint8_t method, String* url, JsonObject responseJson) {
  JsonObject requestJson;
  return handleApiV1(method, url, requestJson, responseJson);
}

// Implementations for handling different HTTP methods
ApiResponse handleV1Get(String* url, JsonObject responseJson) {
  // Implement your GET request handling logic here
  responseJson["message"] = "GET request on " + *url + " received";
  return API_SUCCESS;
}

ApiResponse handleV1Put(String* url, JsonObject requestJson, JsonObject responseJson) {
  // Implement your PUT request handling logic here
  return API_SUCCESS;
}

ApiResponse handleV1Post(String* url, JsonObject requestJson, JsonObject responseJson) {
  // Implement your POST request handling logic here
  return API_SUCCESS;
}

ApiResponse handleV1Delete(String* url, JsonObject responseJson) {
  // Implement your DELETE request handling logic here
  return API_SUCCESS;
}