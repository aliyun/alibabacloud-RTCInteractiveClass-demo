<template>
  <p class="screen-sharing">
    <span class="share-icon" :style="shareIcon | bgImageFilter"></span>
    <span class="share-time">{{screenShareTime}}</span>
    <hui-button size="small" type="danger" @click="stopScreenShare">结束共享</hui-button>
  </p>
</template>

<script>
import {mapState} from 'vuex'
import AliRTCElectronInterrativeEngine from '../../core/client/alirtc-electron-interrative-engine'
export default {
  data() {
    return {
      shareTimer: null,
      screenShareTime: "00:00:00",
      shareIcon: require("../../assets/img/screen-audio.png")
    }
  },
  mounted() {
    this.shareTimer = setInterval(()=>{
      let mss = Date.now() - this.startScreenShareTime
      let hours = parseInt(mss / (1000 * 60 * 60)).toString().padStart(2,'0');
      let minutes = parseInt((mss % (1000 * 60 * 60)) / (1000 * 60)).toString().padStart(2,'0');
      let seconds = parseInt((mss % (1000 * 60)) / 1000).toString().padStart(2,'0');
      this.screenShareTime = hours + ":" + minutes + ":" + seconds
    },500)
  },
  beforeDestroy() {
    clearInterval(this.shareTimer)
    this.shareTimer= null
    this.screenShareTime = "00:00:00"
  },
  computed: {
    ...mapState({
      startScreenShareTime: (state) => state.rtc.startScreenShareTime
    })
  },
  methods: {
    stopScreenShare() {
      AliRTCElectronInterrativeEngine.instance.stopScreenShare()
    }
  }
}
</script>

<style lang="scss" scoped>
.screen-sharing {
  display: flex;
  align-items: center;
  justify-content: space-between;
  width: vw(196);
  padding: 0 vw(15);
  .share-icon {
    width: vw(24);
    height: vh(24);
    background-size: vw(24) vh(24);
    background-repeat: no-repeat;
  }
  .share-time {
    font-size: vh(12);
    color: #ffffff;
  }
}
</style>