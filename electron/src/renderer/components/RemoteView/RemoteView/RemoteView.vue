<template>
  <div class="remote-view-item" :style="studentUrl | bgImageFilter">
    <div class="remote-view-video" ref="video" :class="{'hideVideo': isMutedCamera, 'transform': isSelf}"></div>
    <div class="remote-view-info">
      <div class="remote-info-top">
        <div class="remote-label">{{isSelf ? "自己" : ""}}</div>
      </div>
      <div class="remote-info-bottom">
        <div class="remote-user-name">{{displayName}}</div>
        <div class="remote-media">
          <div :style="meetingMicStyle | bgImageFilter" @click="setMic"></div>
          <div :style="meetingCameraStyle | bgImageFilter" @click="setCamera"></div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { mapState } from 'vuex'
import AliRTCElectronInterrativeEngine from '../../../core/client/alirtc-electron-interrative-engine'
export default {
  props: {
    userid: {
      type: String,
      default: ""
    },
    displayName: {
      type: String,
      default: ""
    },
    subScribedCameraMaster: {
      type: Boolean,
      default: false
    },
    isSelf: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      meetingMicOnUrl: require("../../../assets/img/meeting-mic-on.png"),
      meetingMicOffUrl: require("../../../assets/img/meeting-mic-off.png"),
      meetingCameraOnUrl: require("../../../assets/img/meeting-camera-on.png"),
      meetingCameraOffUrl: require("../../../assets/img/meeting-camera-off.png"),
      studentUrl: require("../../../assets/img/student.png"),
    }
  },
  mounted() {

  },
  methods: {
    setMic() {
      if(this.isSelf) {
        AliRTCElectronInterrativeEngine.instance.muteLocalMic(!this.isMutedMic)
        this.$store.commit("SET_RTC_DATA", {
          isMuteLocalMic: !this.isMutedMic
        })
      }else {
        if(this.isTeacher) {
          AliRTCElectronInterrativeEngine.instance.muteStudentMic(this.userid, !this.isMutedMic)
        }
      }
    },
    setCamera() {
      if(this.isSelf) {
        if(0 == AliRTCElectronInterrativeEngine.instance.muteLocalCamera(!this.isMutedCamera)) {
          this.$store.commit("SET_RTC_DATA",{
            isMuteLocalCamera: !this.isMutedCamera,
            isPreview: this.isMutedCamera
          })
        }
      }else {
        if(this.isTeacher) {
          AliRTCElectronInterrativeEngine.instance.muteStudentCamera(this.userid, !this.isMutedCamera)
        }
      }
    }
  },
  computed: {
    meetingMicStyle() {
      return this.isMutedMic ? this.meetingMicOffUrl : this.meetingMicOnUrl
    },
    meetingCameraStyle() {
      return this.isMutedCamera ? this.meetingCameraOffUrl : this.meetingCameraOnUrl
    },
    isMutedMic() {
      if(this.isSelf) {
        return this.$store.state.rtc.isMuteLocalMic
      }else {
        let muteList = this.$store.state.rtc.muteList
        if(muteList[this.userid] && muteList[this.userid].isMutedMic) {
          return true
        }
        return false
      }
    },
    isMutedCamera() {
      if(this.isSelf) {
        return this.$store.state.rtc.isMuteLocalCamera
      }else {
        let muteList = this.$store.state.rtc.muteList
        if(muteList[this.userid] && muteList[this.userid].isMutedCamera) {
          return true
        }
        return false
      }
    },
    ...mapState({
      isPreview: (state) => state.rtc.isPreview,
      isTeacher: (state) => state.rtc.isTeacher
    })
  },
  watch: {
    subScribedCameraMaster(newState) {
      if(newState) {
        AliRTCElectronInterrativeEngine.instance.setRemoteViewConfig(this.userid, this.$refs.video, 1)
      }
    },
    isPreview(newState) {
      if(newState) {
        if(this.isSelf) {
          AliRTCElectronInterrativeEngine.instance.setLocalViewConfig(this.$refs.video)
        }
      }
    }
  }
}
</script>

<style lang="scss" scoped>
  .remote-view-item {
    margin: vh(16) vw(8) vh(16) 0;
    width: vh(144);
    height: vh(81);
    border-radius: 5px;
    box-shadow: 0 0 11px 0 rgb(217,217,217);
    background-color: #F7F7F7;
    background-repeat: no-repeat;
    background-size: vh(40) vh(40);
    background-position: center center;
    display: inline-block;
    position: relative;
    &:nth-of-type(1) {
      margin-left: vw(8);
    }
    .remote-view-video {
      width: 100%;
      height: vh(81);
      overflow: hidden;
      border-radius: 4px;
    }
    .hideVideo {
      opacity: 0;
    }
    .remote-view-info {
      position: absolute;
      left: 0;
      top: 0;
      width: 100%;
      height: vh(81);
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      padding: vh(8) vw(8);
      .remote-info-top {
        display: flex;
        justify-content: space-between;
        .remote-label {
          font-size: vh(12);
          line-height: vh(20);
          padding: 0 vw(3);
          background: #EAEEFF;
          color: #365aff;
          border-radius: vh(4);
        }
      }
      .remote-info-bottom {
        display: flex;
        justify-content: space-between;
        .remote-user-name {
          font-size: vh(12);
          line-height: vh(20);
          text-shadow: 1px 1px 1px #ccc;
        }
        .remote-media {
          display: flex;
          >div {
            height: vh(20);
            width: vh(20);
            background-repeat: no-repeat;
            background-size: vh(20) vh(20);
            background-position: center center;
            margin-left: vw(5);
            cursor: pointer;
          }
        }
      }
    }
    &:hover .remote-bye{
      opacity: 1 !important; 
    }
  }
</style>