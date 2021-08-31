<template>
  <div class="send-message">
    <div-editable
      v-model="message"
      @sendMsg="sendMsg"
    ></div-editable>
    <div class="send" 
      @click="sendMsg"
    >发送</div>
  </div>
</template>

<script>
import DivEditable from "./DivEditable.vue"
import AliRTCElectronInterrativeEngine from '../../../core/client/alirtc-electron-interrative-engine'
export default {
  components: {
    DivEditable
  },
  data() {
    return {
      message: ""
    }
  },
  methods: {
    async sendMsg() {
      if(!this.message) return
      AliRTCElectronInterrativeEngine.instance.sendTextMessage(this.message)
      this.message = ""
    }
  }
}
</script>

<style lang="scss" scoped>
  .send-message {
    position: absolute;
    width: 100%;
    height: vh(124);
    bottom: 0;
    padding: vh(16) vw(12);
    .div-editable:empty+.send{
      opacity: 0.2;
      cursor: not-allowed;
    }
    .send {
      position: absolute;
      border-radius: 5px;
      right: vw(12);
      bottom: vh(16);
      background: #365AFF;
      color: #ffffff;
      width: vw(44);
      height: vh(24);
      font-size: vh(12);
      text-align: center;
      line-height: vh(24);
      cursor: pointer;
    }
  }
</style>
