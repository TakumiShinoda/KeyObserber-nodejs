const mod = require('./module/KeyObserber');


mod.setPasswd("12356");
mod.checkPasswd()
  .then(() => {
    console.log("suc");
    mod.keyListener((data) => {
      console.log(data.toString());
    }, (err) => {
      console.log(err.toString());
    });
  })
  .catch(() => {
    console.log("fail");
  });
