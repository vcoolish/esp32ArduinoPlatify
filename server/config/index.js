require('dotenv').config(/*{ path: ".env" }*/);

const env = process.env;
module.exports = {
    production: {
        wsWebserverPort: env.WS_WEB_SERVER_PORT,
        db: {
            host : env.PG_HOST,
            user : env.PG_USER,
            password : env.PG_PASSWORD,
            database : env.PG_DATABASE
        },
    },
    development: {
        wsWebserverPort: env.WS_WEB_SERVER_PORT,
        db: {
            host : env.PG_HOST,
            user : env.PG_USER,
            password : env.PG_PASSWORD,
            database : env.PG_DATABASE
        },
    },
    test: {
        wsWebserverPort: env.TEST_WS_WEB_SERVER_PORT,
    }
};
