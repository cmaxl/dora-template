#include "dora.h"

jsonStatus_t serializeGET(String url, JsonObject root) {
  String nextRoute = extractNextRoute(&url);

  if(nextRoute == "/state") {
    serializeState(root);
  } else if(nextRoute == "/config") {
    serializeConfig(root);
  } else if(nextRoute == "/time") {
    serializeTime(root);
  } else {
    return JSON_NOT_FOUND;
  }

  return JSON_OK;
}

jsonStatus_t deserializePOST(String url, JsonObject root) {
  String nextRoute = extractNextRoute(&url);

  if(nextRoute == "/config") {
    deserializeConfig(root);
  } else {
    return JSON_NOT_FOUND;
  }

  return JSON_OK;
}

jsonStatus_t deserializePUT(String url, JsonObject root) {
  String nextRoute = extractNextRoute(&url);

  if(nextRoute == "/config") {
    deserializeConfig(root);
  } else if(nextRoute == "/time") {
    deserializeTime(root);
  } else {
    return JSON_NOT_FOUND;
  }

  return JSON_OK;
}

jsonStatus_t deserializeDELETE(String url, JsonObject root) {
  String nextRoute = extractNextRoute(&url);

  if(nextRoute == "/config") {
    deserializeConfig(root);
  } else {
    return JSON_NOT_FOUND;
  }

  return JSON_OK;
}
