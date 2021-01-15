const ClientsStore = require('./ClientsStore');
const MessagesHandler = require('./MessagesHandler');
const WebSocket = require('ws');

// const timeSeriesDataServise = require('');
const timeSeriesDataServise = {};
const devicesServise = {};
const usersServise = {};


class WebSocketServer {
  constructor({ port=3001, services }) {
    this.clientsStore = new ClientsStore();
    this.wss = new WebSocket.Server({ port });

    if (services) {
      this.services = services;
    } else {
      this.services = {
        timeSeriesDataServise,
        devicesServise,
        usersServise,
      };
    }

    this.messagesHandler = new MessagesHandler(this.clientsStore, this.services);
  }

  run() {
    this.wss.on('connection', (ws, req) => {
      this._connectionHandler(ws, req);
    });

    /* fixing broken sockets if there some exists */
    const polingInterval = 20000;
    const interval = setInterval(() => {
      this.wss.clients.forEach((ws) => {
        if (ws.isAlive === false) {
          this.clientsStore.removeClientByWS(ws);

          ws.terminate();
        } else {
          ws.isAlive = false;
          ws.ping(noop);
        }
      });
    }, polingInterval);

    this.wss.on('close', (ws) => {
      clearInterval(interval);
    });
  }

  _connectionHandler(ws, req) {
    // console.log("connected ", req.socket.remoteAddress);

    ws.on('message', (message) => {
      this._incomingMessagesHandler(ws, message);
    });

    ws.on('close', () => {
      this.clientsStore.removeClientByWS(ws);
      console.log("ws.on('close')", /*ws*/);
    });
  }

  _incomingMessagesHandler(ws, message) {
    console.log('received: %s', message);

    ws.send(message); /* test echo */

    const callback = () => {};

    try {
      const objectMessage = JSON.parse(message);
      this.messagesHandler.handleMessage(ws, objectMessage, callback);
    } catch(e) {
      console.error(e);
    }
  }

  close() {
    this.wss.close();
  }
}


module.exports = WebSocketServer;