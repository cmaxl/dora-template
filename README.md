# DORA  
My template for an ESP32 hosting a webapp.

## Features
- responsive webapp
- automatic code generation from vue router
- Example implementations of:
  - ~~Websockets~~
  - Server-sent events
  - REST API
- [...more](#usage)

## Introduction
DORA is the Default Operational Reference Application  
All my knowledge and experience was packed with love in this template. 
New improvements are made and suggestions are welcome.  
I hope it helps you as much as it helps me whenever I need to start a new project on an ESP32.

## Installation
### Prerequisites
- [VS Code](https://code.visualstudio.com/) (preferred)
- [PlatformIO](https://platformio.org/)
- [npm](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm)
- [Volar](https://marketplace.visualstudio.com/items?itemName=Vue.volar) (extension for VS Code)

### 1. Clone the repository
```bash
git clone *insert repo here*
```

### 2. Install npm dependencies
```bash
cd webapp
npm install
```

## Quick start
### 1. Flash the ESP32
Build and upload the project using the platformio build command.

### 2. Connect to the ESP32
ESP will run in AP mode and create a wifi network called `DORA`.  
Connect to the network (standard password is `dora1234`).

### 3. Use the webapp
Open a browser and navigate to `http://10.1.2.3`  
You should see the webapp.  
*insert screenshot(s) here*  
  
from here you can:
- Do some REST API calls
- Connect to the event source and see the data
- Connect to the websocket and see the data
- view the API documentation

### 4. Run the webapp locally
from the `webapp` directory run:
```bash
npm run dev
```
This opens a webbrowser with the webapp.  
Every api, websocket or events call is redirected to the address specified as proxy_target in the `vite.config.js` file.  
Using the mdns address was not very fast for me in AP mode, so I prefer using the IP address of the ESP32.  

## Usage

*under construction*

### understanding the project structure

### how to use ...
#### the webapp

#### the REST API

#### the event source

#### the websocket

### how to test ...
#### the webapp

#### the REST API

#### the event source

#### the websocket

### how to add ...
#### new function to the Arduino code

#### new page/route to the webapp

#### new API endpoint

#### new event

#### new websocket

### how to change ...
#### the name of the project

#### the mdns name

#### the ~~(fallback)~~ AP credentials

#### the webapp proxy target



## Tech Stack
### Backend (uC)
- Arduino - Framework
  libraries:
  - [ArduinoJson](https://arduinojson.org/)
  - (ESPAsyncWebserver)[]
- [C/C++] - Language
- [PlatformIO](https://platformio.org/) - Build system

### Frontend (Webapp)
- [Vuejs]() - Framework
- [Typescript] - Language
- [PicoCSS]() - CSS

## Todo
- [ ] test other (smaller) js frameworks
- [ ] send some random values
- [ ] display some data from the ESP32
- [ ] do some stuff with api calls
- [ ] Write websocket example
- [ ] write the swagger.yml
- [ ] generate api code from swagger.yml
- [ ] generate an api documentation/try-it site from swagger.yml
- [ ] loggings
- [ ] Captive portal
- [ ] WiFiManager or similar
- [ ] renaming script for the project (DORA -> your project name)
- [ ] improvSerial and improvBLE
- [ ] ArduinoJson7 upgrade!?!
- [ ] (idea) generate an app that then uses bluetooth serial and the API
