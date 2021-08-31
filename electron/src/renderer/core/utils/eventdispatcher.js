/***
 *  事件派发类
 */
export default class EventDispatcher {
  constructor() {
    this._eventListener = {}
  }

  /**
   * 判断是否监听了某个事件
   * @param type
   * @return {boolean}
   */
  has(type) {
    return this._eventListener[type] ? true : false
  }

  /**
   * 判断是否监听名字为type且响应函数为listener的事件
   * 
   * @param {String} type 
   * @param {Function} listener 
   */
  hasEventListener(type, listener, context) {
    if (this._checkFunction(listener)) {
      if (this._eventListener[type] !== undefined && this._eventListener[type].indexOf(listener) !== -1) {
        return true
      }
    }
    return false
  }

  /**
   * 监听名字为type的事件
   * @param type
   * @param listener
   * @param context
   * @param once
   * @return {boolean}
   */
  addEventListener(type, listener, context, once = false) {
    if (this._checkFunction(listener)) {
      if (this._eventListener[type] === undefined) {
        this._eventListener[type] = []
      }
      let arr = this._eventListener[type]
      for (let i = 0; i < arr.length; ++i) {
        if (arr[i].func === listener && arr[i].context === context) {
          return false
        }
      }
      this._eventListener[type].push({
        func: listener,
        context: context,
        once: once
      })
      return true
    }
    return false
  }

  /**
   * 监听名字为type的事件，并保持只有传入的listener会触发
   * @param type
   * @param listener
   * @param context
   * @param once
   */
  replaceEventListener(type, listener, context, once = false) {
    if (this._checkFunction(listener)) {
      if (this._eventListener[type] === undefined) {
        this._eventListener[type] = []
      } else {  // 清空数组
        this._eventListener[type].splice(0);
      }
      let arr = this._eventListener[type]
      for (let i = 0; i < arr.length; ++i) {
        if (arr[i].func === listener && arr[i].context === context) {
          return false
        }
      }
      this._eventListener[type].push({
        func: listener,
        context: context,
        once: once
      })
      return true
    }
    return false
  }

  /**
   * 移除名字为type且响应函数为listener的事件监听
   * 
   * @param {String} type 
   * @param {Function} listener 
   */
  removeEventListener(type, listener, context) {
    if (this._checkFunction(listener) && this._eventListener[type] !== undefined) {
      let arr = this._eventListener[type]
      for (let i = 0; i < arr.length; ++i) {
        if (arr[i].func === listener && context === arr[i].context) {
          arr.splice(i, 1)
          return
        }
      }
    }
  }

  /**
   * 触发type事件
   * 
   * @param {String} type 
   * @param {Array} params 
   */
  dispatchEvent() {
    let args = Array.prototype.slice.call(arguments)
    let type = args.shift()
    if (!type) {
      return
    }
    if (this._eventListener[type] !== undefined && this._eventListener[type].length) {
      let arr = this._eventListener[type]
      for (let i = arr.length - 1; i >= 0; --i) {
        let func = arr[i].func
        let context = arr[i].context
        if (arr[i].once) {
          arr.splice(i, 1)
        }
        func.apply(context, args)
      }
    }
  }

  /**
   * 检查是否是Function
   * @param {Function} listener 
   */
  _checkFunction(listener) {
    if (listener && typeof listener === 'function') {
      return true
    }
    return false
  }
}