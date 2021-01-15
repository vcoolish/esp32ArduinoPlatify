
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
