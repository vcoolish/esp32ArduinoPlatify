const ClientsStore = require('./../../WebSocketServer/ClientsStore');

describe('app', () => {
  it('clientsStore.addClient', () => {
    const clientsStore = new ClientsStore();

    const testData = {
      ws: { some: "object value" },
      uuid: "myTestUUid",
    };

    clientsStore.addClient(testData);

    expect(clientsStore.clients[0]).toEqual(testData);
  });


  it('clientsStore.removeClientByUUID', () => {
    const clientsStore = new ClientsStore();

    const testData = {
      ws: { some: "object value" },
      uuid: "myTestUUid",
    };

    clientsStore.addClient(testData);
    clientsStore.removeClientByUUID("myTestUUid");

    expect(clientsStore.clients).toEqual([]);
  });

  it('clientsStore.removeClientByWS', () => {
    const clientsStore = new ClientsStore();

    const testData1 = {
      ws: { some: "object value" },
      uuid: "myTestUUid1",
    };

    const testData2 = {
      ws: { some: "object value2" },
      uuid: "myTestUUid2",
    };

    clientsStore.addClient(testData1);
    clientsStore.addClient(testData2);
    clientsStore.removeClientByWS(testData1.ws);

    expect(clientsStore.clients).toEqual([testData2]);
  });
});
