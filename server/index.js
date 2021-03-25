const envType = process.env.NODE_ENV || 'development';
const config = require('./config')[envType];
console.log('process.env.NODE_ENV', envType);

const WebSocketServer = require('./WebSocketServer');
const CommandLine = require('./WebSocketServer/CommandLine');

// const app = require('express')();
// const http = require('http').Server(app);

// app.get('/', function (req, res) {
//   res.sendFile(__dirname + '/web/index.html');
// });

// http.listen(PORT, function () {
//   console.log('listening on *:' + PORT);
// });


const types = { connectionData: "CONNECTION_DATA", command: "COMMAND", data: "DATA" };
const clientsStore = {};

// websockets client
const wss = new WebSocketServer({ port: config.wsWebserverPort });
wss.run();

new CommandLine((s)=>wss.sendCommand(s));

module.exports = {
  wss,
}
