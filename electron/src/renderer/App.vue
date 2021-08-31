<template>
  <div id="app">
    <router-view></router-view>
  </div>
</template>

<script>
  export default {
    name: 'rtc-interactive-class',
  }
</script>

<style lang="scss">
@import './assets/scss/element.scss';
#app {
  font-family: "Avenir", Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;
  height: 100vh;
}
.mirrorMode{
  transform: rotateY(180deg);
}
</style>
