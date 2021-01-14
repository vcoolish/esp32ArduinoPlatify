const envType = process.env.NODE_ENV || 'development';
const config = require('./config')[envType];
console.log('process.env.NODE_ENV', envType);

const WebSocket = require('ws');

// const app = require('express')();
// const http = require('http').Server(app);
// const io = require('socket.io')(http);
// const PORT = 3100;

// app.get('/', function (req, res) {
//   res.sendFile(__dirname + '/web/index.html');
// });

// io.on('connection', function (socket) {
//   socket.on('chat message', function (msg) {
//     io.emit('chat message', msg);
//   });
// });

// http.listen(PORT, function () {
//   console.log('listening on *:' + PORT);
// });

const types = { connectionData: "CONNECTION_DATA", command: "COMMAND", data: "DATA" };

// {
//   uid, type, payload
// }

const clientsStore = {};

// websockets client
const wss = new WebSocket.Server({ port: config.wsWebserverPort });

wss.on('connection', function connection(ws, req) {
  console.log("connected ", req.socket.remoteAddress);

  ws.on('message', function incoming(message) {
    console.log('received: %s', message);

    parseMessage(ws, message);
    wss.clients.forEach(function each(client) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(message);
      } else {
        client.send(message);
      }
    });

  });

});

function parseMessage(client, message) {
  switch (message.type) {
    case types.connectionData:
      const uid = message.uid;
      clientsStore[uid] = client;
      break;
    case types.command:
    case types.data:
    default:
      break;
  }
}

// const ws = new WebSocket('ws://192.168.0.109/ws');

// ws.on('open', function open() {
//   console.log('The socket is open.');
//   let flag = false;
//   setInterval(() => {
//     flag = !flag;
//     const data = "toggle";
//     ws.send(data);
//   }, 1000)
// });

// ws.on('message', function incoming(data) {
//   console.log(data);
// });

module.exports = {
  wss,
}