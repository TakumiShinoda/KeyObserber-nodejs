const mod = require('./module/KeyObserber');

mod.keyListener((data) => {
  console.log(data.toString());
}, (err) => {
  console.log(err.toString());
});