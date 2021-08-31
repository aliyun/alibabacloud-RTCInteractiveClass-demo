import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: "/",
      component: resolve => require(["../views/login/login.vue"], resolve)
    },
    {
      path: "/teacher",
      component: resolve => require(["../views/teacher/teacher.vue"], resolve)
    },
    {
      path: "/student",
      component: resolve => require(["../views/student/student.vue"], resolve)
    },
  ]
})