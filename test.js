var addon = require('./bin/Debug/simple-addon');

addon.hello();

addon.createWorkers();

var i = setInterval(() => {
    console.log(' ---- 10 sec passed ---- //' + new Date().toISOString());
}, 10000);

setTimeout(()=>{
    clearInterval(i);
}, 25000);
