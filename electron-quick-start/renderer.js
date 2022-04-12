// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

var worker = new Worker('./worker.js');
worker.onmessage = function(event) {   
   //print result on console and label tag
   console.log("worker : ", event.data);
   //document.querySelector('lblAnsU').innerHTML = "addonasw says: " + event.data;
   document.getElementById("lblAnsU").innerHTML = event.data;
   //terminate webworker
   
   const btnGetAU = document.getElementById("btnGAU")

    if (null != btnGetAU)
	    btnGetAU.onclick = getAnsU;
   
   worker.terminate();
   
   //set it to undefined
   worker = undefined;
}

worker.onerror = function (event) {
  console.log(event.message, event);
};

function getAnsU(){
    console.log('Called!');
	//const {echoNum} = app.require("./addonasw/addonasw.node");
	document.getElementById("lblAnsU").innerHTML = "40 + 2 = " + window.myApi.echoNumE(window.myApi.echoNumE(40)+2);
}
