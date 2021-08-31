import Vue from 'vue'
import axios from 'axios'

import App from './App'
import router from './router'
import store from './store'
import * as filters from './filters'

import './plugins/element.js'

import 'element-ui/lib/theme-chalk/index.css';

import './assets/js/hui-design.js'
import './core/utils/array.js'

if (!process.env.IS_WEB) Vue.use(require('vue-electron'))
Vue.http = Vue.prototype.$http = axios
Vue.config.productionTip = false

Object.keys(filters).forEach(key => {
  Vue.filter(key, filters[key])
})

router.afterEach((to, from) => {
  if((from.path === '/teacher' || from.path === '/student') && to.path === '/') {
    location.reload()
  }
})

/* eslint-disable no-new */
new Vue({
  components: { App },
  router,
  store,
  template: '<App/>'
}).$mount('#app')
