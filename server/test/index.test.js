const envType = process.env.NODE_ENV || 'development';
const config = require('./../config')[envType];


const app = require('./../index');

const WebSocket = require('ws');

describe('app', () => {
  it('connect websockets msg echo', (done) => {
    expect.assertions(1);

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
        
        ws.close();
      })
      .on('close', () => done());
  });

  afterAll(() => {
    app.wss.close();
  })
});
