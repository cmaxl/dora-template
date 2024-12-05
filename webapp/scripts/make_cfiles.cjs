/**
 * This script generates a header file containing the contents of all .gz files
 * and (if present) favicon.ico in the specified directory.
 */

const fs = require('fs');
const path = require('path');

const { createChunk, vue_app_h, vue_static_cpp, createRouter, favicon, getFilesOfExt, createHandler } = require('./utils.cjs');

// Get command line arguments
const [,, sourceDir, outputHFile, outputCppFile, routerTs] = process.argv;

// Create the header file and add the initial content
let headerBuffer = vue_app_h;
// Create the cpp file and add the initial content
let cppBuffer = vue_static_cpp;

// Process favicon.ico if it exists
const faviconPath = path.join(sourceDir, 'favicon.ico');
if (fs.existsSync(faviconPath)) {
  headerBuffer += createChunk(sourceDir, 'favicon.ico');
  cppBuffer += favicon;
}

// Process the router file
if(routerTs) {
  let routerContent = fs.readFileSync(routerTs, 'utf8');

  // Remove comments and whitespace
  routerContent = routerContent.replace(/\/\/.*/g, '').replace(/\s/g, '');
  
  // Extract all path values
  const pathMatches = routerContent.match(/path:'(.*?)'/g);
  const paths = pathMatches ? pathMatches.map(match => match.replace(/path:'(.*?)'/, '$1')) : [];

  console.log('Extracted paths:', paths);

  paths.forEach(path => {
    if (path !== '/') {
      cppBuffer += createRouter(path);
    }
  });
}

// Process all .gz files in the source directory
const gzFiles = getFilesOfExt(sourceDir, '.gz');
gzFiles.forEach(file => {
  headerBuffer += createChunk(sourceDir, file);
  cppBuffer += createHandler(sourceDir, file);
});

fs.writeFileSync(outputHFile, headerBuffer);
console.log(`Header file ${outputHFile} created successfully.`);

fs.writeFileSync(outputCppFile, cppBuffer + '}\n');
console.log(`Cpp file ${outputCppFile} created successfully.`);