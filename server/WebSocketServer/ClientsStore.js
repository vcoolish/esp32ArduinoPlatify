
class ClientsStore {
  constructor() {
    this.clients = [];
  }

  _validateClient({ uuid, ws }) {
    if (!uuid) {
      throw Error("uuid is undefined");
    }

    if (!ws) {
      throw Error("ws is undefined");
    }

    return true;
  }

  addClient({ uuid, ws }) {
    this._validateClient({ uuid, ws });

    const existingClient = this.getClientByUUID(uuid);
    
    if (existingClient) {
      existingClient.ws = ws;
    } else {
      this.clients.push({ uuid, ws });
    }
  }

  getClientByUUID(uuid) {
    return this.clients.find(item => item.uuid === uuid);
  }

  getClientByWS(ws) {
    return this.clients.find(item => item.ws === ws);
  }

  removeClient(client) {
    const index = this.clients.indexOf(client);
    if (index != -1) { // .indexOf return -1 if element doesn't exist in array
      this.clients.splice(index, 1);
    }
  }

  removeClientByUUID(uuid) {
    const client = this.getClientByUUID(uuid);
    if (client) {
      this.removeClient(client);
    }
  }

  removeClientByWS(ws) {
    const client = this.getClientByWS(ws);
    if (client) {
      this.removeClient(client);
    }
  }
}


module.exports = ClientsStore;
