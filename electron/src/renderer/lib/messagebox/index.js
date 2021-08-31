import Vue from 'vue';
import main from './src/main.vue';
let MyMessageConstructor = Vue.extend(main);
let instance, MyMessageBox = {};
let MyMessage = function (type, message, title, option) { //自定义传入的参数
  if (typeof option == "undefined") {
    option = {};
  }
  // 创建实例并且过滤参数
  if (!instance) {
    instance = new MyMessageConstructor({
      el: document.createElement('div'),
      data: {
        type: type,
        message: message,
        title: title,
        closeIcon: option && option.closeIcon ? option.closeIcon : false,
        confirmButtonText: option ? option.confirmButtonText ? option.confirmButtonText : "确认" : '',
        cancelButtonText: option ? option.cancelButtonText ? option.cancelButtonText : "取消" : ''
      }
    })
  }
  instance.callback = option.callback;
  document.body.appendChild(instance.$el);
  if (typeof Promise !== 'undefined' && !instance.callback) {
    return new Promise((resolve, reject) => {
      instance.$mount().$on("results", (data) => {
        if (data == "confirm") {
          instance = null
          resolve();
        } else if (data = "cancel") {
          instance = null
          reject();
        }
      });
    });
  } else {
    instance.$mount().$on("results", (data) => {
      if (typeof instance.callback === 'function') {
        instance.callback(data);
      }
    })
  }

  return instance;
}

MyMessageBox.alert = function (message, title, option) {
  if (option && option.callback) {
    MyMessage("alert", message, title, option);
  } else {
    return MyMessage("alert", message, title, option);
  }
}
MyMessageBox.confirm = function (message, title, option) {
  if (option && option.callback) {
    MyMessage("confirm", message, title, option);
  } else {
    return MyMessage("confirm", message, title, option);
  }
}
export default MyMessageBox;