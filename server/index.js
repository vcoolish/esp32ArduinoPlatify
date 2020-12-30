// const app = require('express')();
// const http = require('http').Server(app);
// const io = require('socket.io')(http);
// const PORT = 3100;

// app.get('/', function(req, res){
//   res.sendFile(__dirname + '/web/index.html');
// });

// io.on('connection', function(socket){
//   socket.on('chat message', function(msg){
//     io.emit('chat message', msg);
//   });
// });

// http.listen(PORT, function(){
//   console.log('listening on *:' + PORT);
// });
const WebSocket = require('ws');

const ws = new WebSocket('ws://192.168.0.103/ws');

ws.on('open', function open() {
  // ws.send('something');
  let flag = false;
  setInterval(()=> {
    flag = !flag;
    const data = "toggle";
      ws.send(data);
  }, 1000)
});

ws.on('message', function incoming(data) {
  console.log(data);
});
