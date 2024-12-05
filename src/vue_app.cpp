/**
*  Autogenerated during build by make_header.cjs
*  Do not edit this file directly
*  Changes to the source files should be made in the nodejs project
*/
#include "dora.h"

#include "vue_app.h" // generated from nodejs deploy script

// every page of the webapp is forwarded to index page
void serveIndex(AsyncWebServerRequest *request)
{
    AsyncWebServerResponse *response;
    response = request->beginResponse_P(200, "text/html", index_html_gz, index_html_gz_len);
    
    response->addHeader("Content-Encoding","gzip");
    request->send(response);
}

void initVueApp() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { 
    if (captivePortal(request)) return;
    serveIndex(request); 
    });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) { 
    serveIndex(request); 
    });


  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response;
    response = request->beginResponse_P(200, "image/x-icon", favicon_ico, favicon_ico_len);
    request->send(response);
  });

  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request) { 
    serveIndex(request); 
  });

  server.on("/sse", HTTP_GET, [](AsyncWebServerRequest *request) { 
    serveIndex(request); 
  });

  server.on("/websocket", HTTP_GET, [](AsyncWebServerRequest *request) { 
    serveIndex(request); 
  });

  server.on("/assets/AboutView.js", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, APPLICATION_JAVASCRIPT, assets_AboutView_js_gz, 253);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });

  server.on("/assets/EventsView.js", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, APPLICATION_JAVASCRIPT, assets_EventsView_js_gz, 416);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });

  server.on("/assets/WebsocketView.js", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, APPLICATION_JAVASCRIPT, assets_WebsocketView_js_gz, 381);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });

  server.on("/assets/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, TEXT_CSS, assets_index_css_gz, 11953);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });

  server.on("/assets/index.js", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, APPLICATION_JAVASCRIPT, assets_index_js_gz, 40585);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, TEXT_HTML, index_html_gz, 267);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });
}