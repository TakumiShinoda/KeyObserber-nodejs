const {spawn} = require('child_process');
var kill  = require('tree-kill');

let Passwd = "";

module.exports = {
  setPasswd: (passwd) => {
    Passwd = passwd;
  },
  getPasswd: () => {
    return Passwd;
  },
  checkPasswd: () =>{
    return new Promise((res, rej) => {
      var exec = spawn('echo', [Passwd, '|', 'sudo', '-S', 'ls'], {shell: true});
      var forceReject = setTimeout(() => {
        rej();
        removeSpawnEvents();
      },3000);

      function removeSpawnEvents(){
        exec.stderr.removeAllListeners();
        exec.stdout.removeAllListeners();
      }

      exec.stderr.on('data', (data) => {
        let err = data.toString();

        if(err.indexOf("try again") >= 0 || err.indexOf("incorrect password") >= 0){
          rej()
          clearTimeout(forceReject);
          removeSpawnEvents();
        }
      });

      exec.stdout.on('data', (data) => {
        res();
        clearTimeout(forceReject);
        removeSpawnEvents();
      });
    });
  },
  keyListener: (callback, errCallback) => {
    var exec = spawn('echo', [Passwd, '|', 'sudo', '-S', './module/darwin/keyEvents'], {shell: true});

    exec.stderr.on('data', (data) => {
      if(data.toString().indexOf("Password:") == -1){
        errCallback(data);
      }
    });

    exec.stdout.on('data', callback);
  },
}
