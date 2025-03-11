import path from 'path';

const systemMonitor = require(path.join(
  __dirname,
  'build/Release/system_monitor.node'
));

const memoryInfo = systemMonitor.getMemoryInfo();
console.log('System Memory Info:', memoryInfo);
