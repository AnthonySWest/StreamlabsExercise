// All of the Node.js APIs are available in the preload process.
// It has the same sandbox as a Chrome extension.
window.addEventListener('DOMContentLoaded', () => {
  const replaceText = (selector, text) => {
    const element = document.getElementById(selector)
    if (element) element.innerText = text
  }

  for (const type of ['chrome', 'node', 'electron']) {
    replaceText(`${type}-version`, process.versions[type])
  }
})

// preload with contextIsolation enabled
console.log("getting context");
const { contextBridge } = require('electron')
console.log("getting echo func.");
const {echoNum} = require("./addonasw/addonasw.node");
//module.exports = require('bindings')('addon');

'use strict'

console.log("getting bindings");
//const {ObsTest} = require('./node_modules/bindings/bindings.js')("./addonasw/addonasw.node")
//const {ObsTest} = require('bindings')('addon');
const {ObsTest} = require('bindings')("../addonasw/addonasw.node");
//const {ObsTest} = require("./addonasw/addonasw.node")
//const addonasw = require("./addonasw/addonasw.node")

console.log("creating obsTest");
const obsTest = new ObsTest(false);
console.log("obs started (expecting false): " + obsTest.Started());
console.log("obs echo (expecting \"don't eat the cake\"): " + obsTest.EchoTestStr("don't eat the cake"));

contextBridge.exposeInMainWorld('myApi', {
  //echoNum: (value) => {}
  echoNumE: (value) => echoNum(value),
  obsTest: {
    Start: () => obsTest.Start(),
    Started: () => obsTest.Started(),
    Shutdown: () => obsTest.Shutdown(),
	EchoTestStr: (value) => obsTest.EchoTestStr(value),
  }
  //obsTestE: obsTest
  //obsTestObj = new ObsTest(false)
})