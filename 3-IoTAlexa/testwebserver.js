var http = require('http');
var request = require('request');

var gatewayip = "127.0.0.1"
var gatewayport = "8000"

http.createServer(function (req, res) {
	
		request.post(
			{
			url:'http://' + gatewayip + ':' + gatewayport + '/Intentjson',
			body: '{"controller":"nodemcu","sensor":"led","onoff":"on"}'
		}
		,
			function(err,response,body){
				if(err) {
				}
				console.log(response.body);
		});
		//res.writeHead(200, {'Content-Type': 'text/plain'});
		res.end();	
}).listen(8080);


