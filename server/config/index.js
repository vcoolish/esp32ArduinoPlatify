require('dotenv').config(/*{ path: ".env" }*/);

module.exports = {
    production: {
        wsWebserverPort: process.env.WS_WEB_SERVER_PORT,
    },
    development: {
        wsWebserverPort: process.env.WS_WEB_SERVER_PORT,
    },
    test: {
        wsWebserverPort: process.env.TEST_WS_WEB_SERVER_PORT,
    }
};
