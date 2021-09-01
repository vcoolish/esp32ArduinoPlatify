
### Messages format:

```json
{
  uid: "some id",
  type: "some type",
  payload: "object depends by type",
}
```

#### Messages types:
`CONNECTION_DATA` - send immediatelly when device has been connected

`COMMAND` - usually sends from the server to device

`SENSORS_DATA` - timeseries sensors data from the device

#### Message: `CONNECTION_DATA`
```json
{
  uid: "some id",
  type: "CONNECTION_DATA",
}
```

#### Message: `SENSORS_DATA`

**sensors tags:** 
- `AIR_HUMIDITY`
- `AIR_TEMPERATURE`
- `AIR_PRESSURE` 
- `SOIL_TEMPERATURE`
- `SOIL_MOISTURE`
- `AMBIENT_LIGHT`
- `SOIL_PH`
- `NUTRIENT_PH`

```json
{
  uid: "some id",
  type: "SENSORS_DATA",
  payload: [
    {
      tag: "some tag",
      value: 1313,
    }
  ]
}
```

### Scheduler
Server's cron collects tasks of current time (minute) and send them to ESP(s).

When ESP starts up it requests for current (started and active) tasks.

Advanced: 
Newly created task and assigned to ESP should be not only saved to DB, but push to ESP if needed.

#### Task
Example of a DB entity:
```json
{
  "id": 1,
  "name": "Morning light",
  "io": "LED_ON",
  "start": "4:10:00",
  "duration": 7200000
}
```
An example of a sent task to ESP:
```json
{
  "io": "LED_ON",
  "duration": 7200000
}
```
