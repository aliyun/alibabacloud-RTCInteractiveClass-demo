<template>
  <div class="meeting-footer-wrap" 
    @mouseenter="showHandler"
    @mouseleave="showHandler"
  >
    <div class="meeting-footer" :class="{ 'showFooter': showFooter }">
      <div class="mic" @click="muteLocalMic">
        <i :style="micStyle | bgImageFilter"></i>
        <span>{{isMuteLocalMic ? "取消静音" : "静音"}}</span>
      </div>
      <div class="camera" @click="muteLocalCamera">
        <i :style="cameraStyle | bgImageFilter"></i>
        <span>{{isMuteLocalCamera ? "开启摄像头" : "关闭摄像头"}}</span>
      </div>
      <div class="screenshare" v-if="isTeacher && !isPublishScreen" @click="showScreenShare=true">
        <i :style="screenShareUrl | bgImageFilter"></i>
        <span>共享屏幕</span>
      </div>
      <div class="mute-all" v-if="isTeacher" @click="muteAllMic">
        <i :style="muteAllStyle | bgImageFilter"></i>
        <span>{{isMuteAll ? "取消静音" : "全员静音"}}</span>
      </div>
      <div class="online-list" @click="showOnlineList = true">
        <i :style="onLineListUrl | bgImageFilter"></i>
        <span>在线列表</span>
      </div>
      <div class="link-list" v-if="isTeacher" @click="showLinkMicMessage = true">
        <i :style="applyInfoStyle | bgImageFilter"></i>
        <span>连麦消息</span>
      </div>
      <div class="apply-join" v-if="!isTeacher" @click="applyHandUp">
        <i :style="handUpStyle | bgImageFilter"></i>
        <span>{{isInterActive ? "结束连麦" : "申请连麦"}}</span>
      </div>
      <span class="line"></span>
      <div class="leave" @click="exit" v-if="!isPublishScreen">
        <i :style="exitUrl | bgImageFilter"></i>
        <span>退出</span>
      </div>
      <screen-sharing
        v-else
      ></screen-sharing>
    </div>
    <!-- 在线列表 -->
    <online-list
      @close="showOnlineList = false"
      :showOnlineList="showOnlineList"
    ></online-list>
    <!-- 连麦列表 -->
    <link-mic-message
      @close="showLinkMicMessage = false"
      :showLinkMicMessage="showLinkMicMessage"
    ></link-mic-message>
    <!-- 屏幕共享 -->
    <screen-share-box
      v-if="showScreenShare"
      @close="showScreenShare = false"
    ></screen-share-box>
    <!-- 课程结束 -->
    <class-finish-box
      v-if="classFinished"
      @close="backToLogin"
    ></class-finish-box>
  </div>
</template>

<script>
import AliRTCElectronInterrativeEngine from '../../core/client/alirtc-electron-interrative-engine'
import OnlineList from "../DialogBox/OnlineList.vue"
import LinkMicMessage from "../DialogBox/LinkMicMessage.vue"
import ScreenSharing from "./ScreenSharing.vue"
import ScreenShareBox from "../DialogBox/ScreenShareBox.vue"
import classFinishBox from "../DialogBox/ClassFinishBox.vue"
import { AliEngineClientRole } from '../../core/data/main'
import { mapState } from 'vuex'
export default {
  components: {
    LinkMicMessage,
    ScreenSharing,
    OnlineList,
    ScreenShareBox,
    classFinishBox
  },
  data() {
    return {
      micOnUrl: require("../../assets/img/mic-on.png"),
      micOffUrl: require("../../assets/img/mic-off.png"),
      cameraOnUrl: require("../../assets/img/camera-on.png"),
      cameraOffUrl: require("../../assets/img/camera-off.png"),
      screenShareUrl: require("../../assets/img/screen-share.png"),
      muteAllOnUrl: require("../../assets/img/mute-all-on.png"),
      muteAllOffUrl: require("../../assets/img/mute-all-off.png"),
      onLineListUrl: require("../../assets/img/online-list.png"),
      applyInfoUrl: require("../../assets/img/apply-info.png"),
      applyNoInfoUrl: require("../../assets/img/apply-no-info.png"),
      handUp: require("../../assets/img/apply-for-join.png"),
      cancelHandUp: require("../../assets/img/apply-for-leave.png"),
      exitUrl: require("../../assets/img/exit.png"),
      showOnlineList: false,
      showLinkMicMessage: false,
      showScreenShare: false,
      showFooter: true,
      showFooterTimer: null,
      isMuteAll: false
    }
  },
  computed: {
    micStyle() {
      return this.isMuteLocalMic ? this.micOffUrl : this.micOnUrl
    },
    cameraStyle() {
      return this.isMuteLocalCamera ? this.cameraOffUrl : this.cameraOnUrl
    },
    muteAllStyle() {
      return this.isMuteAll ? this.muteAllOnUrl : this.muteAllOffUrl
    },
    applyInfoStyle() {
      return this.linkList.length ?  this.applyInfoUrl : this.applyNoInfoUrl
    },
    handUpStyle() {
      return this.isInterActive ? this.cancelHandUp : this.handUp
    },
    ...mapState({
      isHandUp: (state) => state.rtc.isHandUp,
      isTeacher: (state) => state.rtc.isTeacher,
      isInterActive: (state) => state.rtc.isInterActive,
      isPublishScreen: (state) => state.rtc.isPublishScreen,
      isMuteLocalMic: (state) => state.rtc.isMuteLocalMic,
      isMuteLocalCamera: (state) => state.rtc.isMuteLocalCamera,
      linkList: (state) => state.rtc.linkList,
      classFinished: (state) => state.rtc.classFinished,
    })
  },
  methods: {
    /**
     * 底部功能栏动态显示
     */
    showHandler(e) {
      if(e.type === "mouseenter") {
        if(this.showFooterTimer) {
          clearTimeout(this.showFooterTimer)
          this.showFooterTimer = null
        }
        this.showFooter = true
      }else if(e.type === "mouseleave"){
        this.showFooterTimer = setTimeout(()=> {
          this.showFooter = false
          clearTimeout(this.showFooterTimer)
          this.showFooterTimer = null
        }, 1000)
      }
    },
    /**
     * 本地静音
     */
    muteLocalMic() {
      if(0 == AliRTCElectronInterrativeEngine.instance.muteLocalMic(!this.isMuteLocalMic)) {
        this.$store.commit("SET_RTC_DATA",{
          isMuteLocalMic: !this.isMuteLocalMic
        })
      }
    },
    /**
     * 本地关闭摄像头
     */
    muteLocalCamera() {
      if(0 == AliRTCElectronInterrativeEngine.instance.muteLocalCamera(!this.isMuteLocalCamera)) {
        this.$store.commit("SET_RTC_DATA",{
          isMuteLocalCamera: !this.isMuteLocalCamera,
          isPreview: this.isMuteLocalCamera
        })
      }
    },
    /**
     * 全员静音
     */
    muteAllMic() {
      AliRTCElectronInterrativeEngine.instance.muteAllStudentMic(!this.isMuteAll)
      this.isMuteAll = !this.isMuteAll
    },
    /**
     * 学生举手
     */
    applyHandUp() {
      if(this.$store.state.rtc.isWaitingBackHandUp) return
      if(this.isInterActive) {
        this.$myConfirm("连麦关闭后，无法语音和视频沟通内容", "您确定要结束与老师连麦吗？").then(()=>{
          AliRTCElectronInterrativeEngine.instance.setClientRole(AliEngineClientRole.AliEngineClientRoleLive)
        }).catch((err)=>{})
      }else {
        this.$myConfirm("连麦成功后，方可语音和视频沟通内容", "您确定要向老师申请连麦吗？").then(()=>{
          AliRTCElectronInterrativeEngine.instance.handUp(true)
          this.$store.commit("SET_RTC_DATA", {
            isWaitingBackHandUp: true
          })
        }).catch((err)=>{})
      }
    },
    /**
     * 结束课堂
     */
    exit() {
      this.$myConfirm("退出课堂后无法再次进入", "您确定要退出课堂吗？").then(async () => {
        AliRTCElectronInterrativeEngine.instance.exitRoom().finally(()=>{
          AliRTCElectronInterrativeEngine.instance.logoutIm().then((e)=>{
            console.log('logout success',e)
          }).catch(err=>{
            console.log('logout fail',err)
          })
          this.$store.commit("SET_RTC_DATA", {
            classFinished: true
          })
        })
      }).catch(err => {})
    },
    backToLogin() {
      this.$store.commit("SET_RTC_DATA", {
        classFinished: false
      })
      this.$electron.ipcRenderer.send("leaveClass")
      this.$router.back()
    }
  }
}
</script>

<style scoped lang="scss">
  .meeting-footer-wrap{
    display: flex;
    position: fixed;
    left: 0;
    bottom: 0;
    height: vh(553);
    width: vw(710);
    .meeting-footer {
      position: relative;
      bottom: vh(-560);
      display: flex;
      border-radius: 8px;
      background: rgba(0,0,0,0.5);
      height: vh(62);
      margin: 0 auto;
      transition: .3s bottom;
      >div {
        width: vw(76);
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        cursor: pointer;
        &:hover{
          background: rgba(0,0,0,0.4);
        }
        i{
          width: vh(20);
          height: vh(20);
          display: inline-block;
          margin-bottom: 6px;
          cursor: pointer;
          background-repeat: no-repeat;
          background-position: center center;
          background-size: vh(20) vh(20);
        }
        span {
          font-size: vh(12);
          color: #ffffff;
        }
      }
      >div:first-child {
        border-radius: 8px 0 0 8px;
      }
      >div:last-child {
        border-radius: 0 8px 8px 0;
      }
      .line {
        margin: auto 0;
        border: 1px solid #969696;
        width: 0px;
        height: vh(38);
        background: #000;
      }
    }
    .showFooter {
      bottom: vh(-471);
    }
  }
</style>