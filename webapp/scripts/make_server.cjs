/**
 * Generates all server.on handlers from the provided directory for ESPAsyncWebServer
 * Imports all routes from the provided index.ts file
 */

const fs = require('fs');
const path = require('path');

// Get command line arguments
const [,, sourceDir, outputFile] = process.argv;

