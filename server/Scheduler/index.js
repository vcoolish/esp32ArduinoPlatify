class Scheduler {
  constructor({intervalValue = 1000, taskStorage, send}) {
    this.intervalId = setInterval(() => {
      if (taskStorage) {
        send("LED_ON");
      }
    }, intervalValue);
  }

  stop() {
    clearInterval(this.intervalId);
  }
}

module.exports = Scheduler;

// Task
// id, name, io, start, duration
/* {
  "id": 1,
  "name": "Morning light",
  "io": "LED_ON",
  "start": "4:10:00",
  "duration": 7200000
} */
