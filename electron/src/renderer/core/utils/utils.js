import { Message } from 'element-ui';
import Http from "../http/http"
export default class Util {
  /**
   * 显示信息
   * @param {*} v 
   */
  static toast(v) {
    Message(v);
  }
  /**
   * 复制
   * @param {*} id 
   */
  static hCopy(id) {
    if (id) {
      try {
        var range = document.createRange();
        var tar = document.getElementById(id);
        range.selectNodeContents(tar);
        var selection = window.getSelection();
        selection.removeAllRanges();
        selection.addRange(range);
        document.execCommand('copy');
        selection.removeAllRanges();
      } catch (error) {
        console.log(error);
        return false;
      }
      return true;
    } else {
      return true;
    }
  }
  /**
   * 
   * @param {*} id 
   */
  static inputCopy(id) {
    try {
      var Url2 = document.getElementById(id);
      Url2.select(); // 选择对象
      document.execCommand("Copy");
      return true;
    } catch (error) {
      console.error(error);
      return false;
    }
  }
  /**
* 获取浏览器地址栏参数
* @param {*} url 
* @param {*} name 
*/
  static getUrlParam(name) {
    let url = window.location.href;
    var reg = new RegExp('(^|&)' + name + '=([^&]*)(&|$)');
    let urlArr = url.split("?");
    if (urlArr.length > 1) {
      url = "?" + urlArr[1];
      var r = url.substr(1).match(reg);
      if (r != null) return decodeURIComponent(r[2]); return null;
    } else {
      return null;
    }
  }
  /**
   * 获取鉴权信息
   * @param {*} channel 
   * @param {*} displayName 
   * @returns 
   */
  static getAuthInfo(channel, displayName) {
    return new Promise((resolve, reject) => {
      Http.getAuthInfo(channel, displayName).then(authInfo => {
        resolve(authInfo);
      }).catch(err => {
        reject(err)
      })
    })
  }
}
