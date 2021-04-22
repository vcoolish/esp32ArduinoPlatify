const envType = process.env.NODE_ENV || 'development';
const config = require('./config')[envType];
console.log('Environment:', envType);

const WebSocketServer = require('./WebSocketServer');
const CommandLine = require('./WebSocketServer/CommandLine');
const Scheduler = require('./Scheduler');

// const app = require('express')();
// const http = require('http').Server(app);

// app.get('/', function (req, res) {
//   res.sendFile(__dirname + '/web/index.html');
// });

// http.listen(PORT, function () {
//   console.log('listening on *:' + PORT);
// });


const types = { connectionData: "CONNECTION_DATA", command: "COMMAND", data: "DATA" };
const pg = require('knex')({
  client: 'postgres',
  connection: config.db,
});

// websockets client
const wss = new WebSocketServer({ port: config.wsWebserverPort });
wss.run();

const cli = new CommandLine((s)=>wss.sendCommand(s));

const sch = new Scheduler({send: wss.sendCommand});

module.exports = {
  wss, cli, sch
}
