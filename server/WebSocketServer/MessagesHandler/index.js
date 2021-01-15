const messagesTypes = {
  connectionData: 'CONNECTION_DATA',
}

class MessagesHandler {
  constructor(clientsStore, services) {
    if (!services) {
      throw Error("services is undefined");
    }
    this.services = services;

    if (!clientsStore) {
      throw Error("clientsStore is undefined");
    }
    this.clientsStore = clientsStore;
  }

  handleMessage(ws, message, callback) {
    if (message.type === messagesTypes.connectionData) {
      this.clientsStore.addClient({
        uuid: message.uid,
        ws,
      });

      callback();
    }
    // parseMessage(ws, message);
    // this.wss.clients.forEach((client) => {
    //   console.log("client.readyState", client.readyState);
    //   if (client === ws && client.readyState === WebSocket.OPEN) {
    //     client.send(message);
    //   } else {
    //   }
    // });
  }
}

module.exports = MessagesHandler;