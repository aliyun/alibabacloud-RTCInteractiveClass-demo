<template>
  <div class="teacher-small-view" :style="teacherSamllUrl | bgImageFilter">
    <div id="teacher-small-view" ref="localView" :class="{'hideVideo': isHideVide, 'transform': isTeacher}"></div>
    <div class="teacher-info">
      <div class="teacher-label">教师</div>
      <div class="teacher-other">
        <div class="teacher-name">{{teacherName}}</div>
        <div class="teacher-media">
          <div :style="meetingMicStyle | bgImageFilter" @click="muteMic"></div>
          <div :style="meetingCameraStyle | bgImageFilter" @click="muteCamera"></div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { mapState } from "vuex"
import AliRTCElectronInterrativeEngine from '../../core/client/alirtc-electron-interrative-engine';
export default {
  data() {
    return {
      teacherSamllUrl: require("../../assets/img/teacher.png"),
      meetingMicOnUrl: require("../../assets/img/meeting-mic-on.png"),
      meetingMicOffUrl: require("../../assets/img/meeting-mic-off.png"),
      meetingCameraOnUrl: require("../../assets/img/meeting-camera-on.png"),
      meetingCameraOffUrl: require("../../assets/img/meeting-camera-off.png"),
      videoInfo: null
    }
  },
  computed: {
    meetingMicStyle() {
      // 静音图标 显示
      if(this.isTeacher) {
        return this.isMuteLocalMic ? this.meetingMicOffUrl : this.meetingMicOnUrl
      }else {
        return this.isMutedMic ? this.meetingMicOffUrl : this.meetingMicOnUrl
      }
    },
    meetingCameraStyle() {
      // 摄像头图标 显示
      if(this.isTeacher) {
        return this.isMuteLocalCamera ? this.meetingCameraOffUrl : this.meetingCameraOnUrl
      }else {
        return this.isMutedCamera  ? this.meetingCameraOffUrl : this.meetingCameraOnUrl
      }
    },
    isMutedMic() {
      // 学生获取老师是否静音
      let muteList = this.$store.state.rtc.muteList
      if(this.teacherInfo) {
        if(muteList[this.teacherInfo.userid] && muteList[this.teacherInfo.userid].isMutedMic) {
          return true
        }
      }
      return false
    },
    isMutedCamera() {
      // 学生获取老师是否关闭摄像头
      let muteList = this.$store.state.rtc.muteList
      if(this.teacherInfo) {
        if(muteList[this.teacherInfo.userid] && muteList[this.teacherInfo.userid].isMutedCamera) {
          return true
        }
      }
      return false
    },
    isHideVide() {
      // 是否应该隐藏摄像头
      if(!this.isTeacher && this.teacherInfo) {
        if(this.teacherInfo.subScribedScreenSharing && this.teacherInfo.subScribedScreenSharing && this.isMutedCamera) {
          return true
        }
      }
      return false
    },
    ...mapState({
      isTeacher: (state) => state.rtc.isTeacher,
      isMuteLocalMic: (state) => state.rtc.isMuteLocalMic,
      isMuteLocalCamera: (state) => state.rtc.isMuteLocalCamera,
      teacherInfo: (state) => state.rtc.teacherInfo,
      teacherName: function(state) {
        if(state.rtc.isTeacher) {
          return state.rtc.displayName
        }else {
          if(state.rtc.teacherInfo) {
            return state.rtc.teacherInfo.displayName
          }else {
            return ""
          }
        }
      },
    })
  },
  methods: {
    muteMic() {
      // 只有老师可以控制自己的麦克风
      if(this.isTeacher) {
        if(0 == AliRTCElectronInterrativeEngine.instance.muteLocalMic(!this.isMuteLocalMic)) {
          this.$store.commit("SET_RTC_DATA",{
            isMuteLocalMic: !this.isMuteLocalMic
          })
        }
      }
    },
    muteCamera() {
      // 只有老师可以控制自己的摄像头
      if(this.isTeacher) {
        if(0 == AliRTCElectronInterrativeEngine.instance.muteLocalCamera(!this.isMuteLocalCamera)) {
          this.$store.commit("SET_RTC_DATA",{
            isMuteLocalCamera: !this.isMuteLocalCamera,
            isPreview: this.isMuteLocalCamera
          })
        }
      }
    }
  },
  watch: {
    /**
     * 学生根据老师信息处理视图显示
     * 如果新增屏幕流，且有摄像头流，则在小窗显示摄像头流
     */
    teacherInfo(newState, oldState) {
      if(newState.subScribedScreenSharing && !oldState.subScribedScreenSharing) {
        if(newState.subScribedCameraMaster) {
          AliRTCElectronInterrativeEngine.instance.setRemoteViewConfig(newState.userid, this.$refs.localView, 1)
        }
      }
    }
  }
}
</script>

<style lang="scss" scoped>
  .teacher-small-view {
    width: vh(158);
    height: vh(89);
    margin: vh(16) auto vh(8);
    border-radius: 4px;
    position: relative;
    background-color: #f7f7f7;
    background-repeat: no-repeat;
    background-size: vh(45) vh(45);
    background-position: center center;
    #teacher-small-view {
      width: 100%;
      height: 100%;
      border-radius: 4px;
      >div {
        border-radius: 4px;
      }
    }
    .hideVideo {
      opacity: 0;
    }
    .teacher-info {
      position: absolute;
      left: 0;
      top: 0;
      width: 100%;
      height: vh(89);
      .teacher-label {
        padding: 0 vw(4);
        display: inline-block;
        height: vh(20);
        background: #EAEEFF;
        color: #365aff;
        font-size: vh(12);
        text-align: center;
        line-height: vh(22);
        border-radius: vh(4);
        margin: vh(8) 0 0 vh(8);
      }
      .teacher-other {
        position: absolute;
        left: 0;
        bottom: 0;
        display: flex;
        width: 100%;
        justify-content: space-between;
        margin-bottom: vh(8);
        padding: 0 vw(8);
        .teacher-name {
          padding: 0 vw(4);
          height: vh(22);
          border-radius: vh(4);
          background: rgba(255, 255, 255, 0.6);
          color: #333333;
          font-size: vh(10);
          text-align: center;
          line-height: vh(22);
        }
        .teacher-media {
          display: flex;
          justify-content: space-between;
          >div {
            cursor: pointer;
            height: vh(20);
            width: vh(20);
            background-repeat: no-repeat;
            background-size: vh(20) vh(20);
            background-position: center center;
            margin-left: vw(8);
          }
        }
      }
    }
  }
</style>