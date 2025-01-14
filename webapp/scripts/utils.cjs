const { get } = require('http');

fs = require('fs');
path = require('path');

// from Aircookie/WLED
function hexdump(buffer, isHex=false) {
  let lines = [];

  for (let i = 0; i < buffer.length; i +=(isHex?32:16)) {
    let block;
    let hexArray = [];
    if (isHex) {
      block = buffer.slice(i, i + 32)
      for (let j = 0; j < block.length; j +=2 ) {
        hexArray.push("0x" + block.slice(j,j+2))
      }
    } else {
      block = buffer.slice(i, i + 16); // cut buffer into blocks of 16
      for (let value of block) {
        hexArray.push("0x" + value.toString(16).padStart(2, "0"));
      }
    }

    let hexString = hexArray.join(", ");
    let line = `  ${hexString}`;
    lines.push(line);
  }

  return lines.join(",\n");
}

function createFileProps(sourceDir, file) {
  const filePath = path.join(sourceDir, file);
  const fileSize = fs.statSync(filePath).size;
  const varName = filePath.replace(sourceDir + '/', '').replace(/[\.\-\/]/g, '_');

  return [varName, fileSize];
}

// Create a chunk for each file
function createChunk(sourceDir, file) {
  [varName, fileSize] = createFileProps(sourceDir, file);
  const filePath = path.join(sourceDir, file);
  console.log(`Processing ${filePath} (${fileSize} bytes)`);
  const arrayContent = hexdump(fs.readFileSync(filePath));

  // create the chunk for the header file
  let headerChunk = `const size_t ${varName}_len = ${fileSize};\n`;
  headerChunk += `const uint8_t ${varName}[] PROGMEM = {\n`;
  headerChunk += arrayContent;
  headerChunk += '\n};\n\n';

  return headerChunk;
}

// all files with given extension in the directory and subdirectories
function getFilesOfExt(dir, ext) {
  let results = [];
  const list = fs.readdirSync(dir);
  list.forEach((file) => {
    const filePath = path.join(dir, file);
    const stat = fs.statSync(filePath);
    if (stat && stat.isDirectory()) {
      results = results.concat(getFilesOfExt(filePath, ext));
    } else if (file.endsWith(ext)) {
      results.push(filePath);
    }
  });
  return results;
}

const vue_app_h =
`#pragma once

/* vue-app header file 
*  Autogenerated during build by make_header.cjs
*  Do not edit this file directly
*  Changes to the source files should be made in the nodejs project
*/

`;

const vue_static_cpp =
`/**
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
`;

const favicon =
`

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response;
    response = request->beginResponse_P(200, "image/x-icon", favicon_ico, favicon_ico_len);
    request->send(response);
  });
`;

const routerTemplate = 
`
  server.on("%ENDPOINT%", HTTP_GET, [](AsyncWebServerRequest *request) { 
    serveIndex(request); 
  });
`;
function createRouter(endpoint) {
  return routerTemplate.replace("%ENDPOINT%", endpoint);
}

const handlerTemplate = 
`
  server.on("%ENDPOINT%", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncWebServerResponse *response = request->beginResponse_P(200, %TYPE, %CONTENT%, %LENGTH%);
      response->addHeader("Content-Encoding","gzip");
      request->send(response);
  });
`;
function createHandler(sourceDir, file) {
  const filePath = path.join(sourceDir, file);
  const endpoint = file.replace(sourceDir, '').replace(/\.gz$/, '');
  let type = "TEXT_PLAIN";
  if(filePath.endsWith('.html.gz')) {
    type = "TEXT_HTML";
  } else if(filePath.endsWith('.js.gz')) {
    type = "APPLICATION_JAVASCRIPT";
  } else if(filePath.endsWith('.css.gz')) {
    type = "TEXT_CSS";
  }

  const [content, length] = createFileProps(sourceDir, file);

  // create the handler for the cpp file
  let handler = handlerTemplate.replace("%ENDPOINT%", endpoint);
  handler = handler.replace("%TYPE", type);
  handler = handler.replace("%CONTENT%", content);
  handler = handler.replace("%LENGTH%", length);

  return handler;
}

module.exports = {

  favicon,
  vue_app_h,
  vue_static_cpp,
  getFilesOfExt,
  createChunk,
  createRouter,
  createHandler

};