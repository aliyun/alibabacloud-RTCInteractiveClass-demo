<template>
  <div class="center-big-view">
    <div class="teacher-info">{{isTeacher ? displayName : teacherInfo.displayName}}(教师)</div>
    <div class="speaker" v-show="speakerList.length">{{speakerList.join(', ')}}正在发言</div>
    <div class="center-big-video" ref="centerVideo" :class="{'hideVideo': isHideVide, 'transform': isTeacher}"></div>
  </div>
</template>

<script>
import {mapState} from 'vuex'
import AliRTCElectronInterrativeEngine from '../../core/client/alirtc-electron-interrative-engine';
export default {
  computed: {
    ...mapState({
      isTeacher: (state) => state.rtc.isTeacher,
      teacherInfo: (state) => state.rtc.teacherInfo,
      speakerList: (state) => state.rtc.speakerList,
      displayName: (state) => state.rtc.displayName,
    }),
    /**
     * 学生看老师 是否关闭了摄像头
     */
    isMutedCamera() {
      let muteList = this.$store.state.rtc.muteList
      if(this.teacherInfo) {
        if(muteList[this.teacherInfo.userid] && muteList[this.teacherInfo.userid].isMutedCamera) {
          return true
        }
      }
      return false
    },
    isHideVide() {
      if(!this.isTeacher && this.teacherInfo) {
        if(!this.teacherInfo.subScribedScreenSharing && this.teacherInfo.subScribedCameraMaster && this.isMutedCamera) {
          return true
        }
      }
      return false
    },
  },
  mounted() {
    if(this.isTeacher) {
      this.$nextTick(()=> {
        AliRTCElectronInterrativeEngine.instance.setLocalViewConfig(this.$refs.centerVideo)
      })
    }
  },
  watch: {
    teacherInfo(newState, oldState) {
      if(newState.subScribedScreenSharing && !oldState.subScribedScreenSharing) {
        AliRTCElectronInterrativeEngine.instance.setRemoteViewConfig(newState.userid, this.$refs.centerVideo, 2)
        return
      }
      if(!newState.subScribedScreenSharing && oldState.subScribedScreenSharing) {
        if(newState.subScribedCameraMaster) {
          AliRTCElectronInterrativeEngine.instance.setRemoteViewConfig(newState.userid, this.$refs.centerVideo, 1)
        }
        return
      }
      if(newState.subScribedCameraMaster && !oldState.subScribedCameraMaster) {
        AliRTCElectronInterrativeEngine.instance.setRemoteViewConfig(newState.userid, this.$refs.centerVideo, 1)
      }
    }
  }
}
</script>

<style lang="scss" scoped>
.center-big-view {
  width: vw(710);
  flex: 1;
  background: #ffffff;
  position: relative;
  .teacher-info {
    position: absolute;
    left: vw(16);
    top: vh(18);
    color: #333333;
    font-size: vh(12);
  }
  .speaker {
    position: absolute;
    left: vw(16);
    top: vh(40);
    font-size: vh(12);
    line-height: vh(20);
    padding: 0 vw(5);
    background: #EAEEFF;
    color: #365aff;
    border-radius: vh(4);
  }
  .center-big-video {
    height: 100%;
  }
  .hideVideo{
    opacity: 0;
  }
}
</style>