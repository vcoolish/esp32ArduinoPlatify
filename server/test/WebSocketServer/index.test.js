const envType = process.env.NODE_ENV || 'development';
const config = require('./../../config')[envType];
const WebSocketServer = require('./../../WebSocketServer');

const WebSocket = require('ws');


describe('app', () => {
  it('connect and add client to the clients store', (done) => {
    const wss = new WebSocketServer({ port: config.wsWebserverPort });
    wss.run();

    expect.assertions(4);

    const testData = {
      type: "CONNECTION_DATA",
      uid: "myTestUUid",
    };

    const testMessage = JSON.stringify(testData);

    const ws = new WebSocket(`ws://localhost:${config.wsWebserverPort}`)
      .on('open', () => {
        ws.send(testMessage);
      })
      .on('message', (msg) => {
        expect(msg).toEqual(testMessage);
        
        const connectedClients = wss.clientsStore.clients;
        const client = wss.clientsStore.getClientByUUID(testData.uid);

        expect(connectedClients.length).toEqual(1);
        expect(client.uuid).toEqual(testData.uid);

        ws.close();
      })
      .on('close', () => {
        setTimeout(() => {
          const connectedClients = wss.clientsStore.clients;

          expect(connectedClients.length).toEqual(0);

          wss.close();

          done();
        }, 1000);
      });
  });
});
