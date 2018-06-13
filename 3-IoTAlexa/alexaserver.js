'use strict'  // to be compatible with older versions of JavaScript syntax

var express = require("express");
var alexa = require("alexa-app");
var request = require('request');

var PORT = process.env.port || 8003;
var app = express();
var alexaApp = new alexa.app("/");

//================================
var gatewayip = "127.0.0.1"
var gatewayport = "8000"
//================================

alexaApp.express({
  expressApp: app,
  checkCert: false,
  debug: false
});

alexaApp.launch(function(request, response) {
  response.say("Running");
});

//turn on ==============================
alexaApp.intent("turn_on_device", {
  },
  function(request, response) {
	console.log('turnon');
    
    var device = request.slot('device');

		request.post(
			{
			url:'http://' + gatewayip + ':' + gatewayport + '/Intentjson',
			body: '{"sensor":"' + device + '","onoff":"on"}'
		}
		,
			function(err,response,body){
				if(err) {
				}
				//console.log(response.statusCode);
		});

    response.say("Ok, turnon " + device);
  }
);
//==============================turn on

//turn off==============================
alexaApp.intent("turn_off_device", {
  },
  function(request, response) {
	console.log('turnoff');

    var device = request.slot('device');

		request.post(
			{
			url:'http://' + gatewayip + ':' + gatewayport + '/Intentjson',
			body: '{"sensor":"' + device + '","onoff":"off"}'
		}
		,
			function(err,response,body){
				if(err) {
				}
				//console.log(response.statusCode);
		});

    response.say("Ok, turnoff " + device);
  }
);
//==============================turn off

app.listen(PORT);
console.log("Alexa IoT Listening on port " + PORT + ", try http://localhost:" + PORT );