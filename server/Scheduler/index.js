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
