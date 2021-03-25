const readline = require('readline');

class CommandLine {
  constructor(sendFn) {
    this.rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
      prompt: ''
    });

    this.rl.prompt();

    this.rl.on('line', (line) => {
      const trimmed = line.trim();
      sendFn(trimmed);
      switch (trimmed) {
        case 'hello':
          console.log('world!');
          break;
        default:
          console.log(`Say what? I might have heard '${trimmed}'`);
          break;
      }
      this.rl.prompt();
    }).on('close', () => {
      console.log('Have a great day!');
      process.exit(0);
    });
  }

  close() {
    this.rl.close();
  }
}

module.exports = CommandLine;
