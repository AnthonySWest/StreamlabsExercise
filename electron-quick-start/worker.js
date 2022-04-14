//address of native addon 
const {echoNum} = require("./addonasw/addonasw.node");
var result = echoNum(42);
postMessage(result);