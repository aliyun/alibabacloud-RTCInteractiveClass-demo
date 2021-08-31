<template>
  <div class="student">
    <meeting-header></meeting-header>
    <div class="meeting-main">
      <div class="meeting-main-left">
        <remote-view-list></remote-view-list>
        <center-big-view></center-big-view>
      </div>
      <div class="meeting-main-right">
        <teacher-small-view></teacher-small-view>
        <i-message></i-message>
      </div>
    </div>
    <meeting-footer></meeting-footer>
  </div>
</template>

<script>
import AliRTCElectronInterrativeEngine from "../../core/client/alirtc-electron-interrative-engine"
import EventType from "../../core/client/eventtype"
import MeetingHeader from "../../components/MeetingHeader/MeetingHeader.vue"
import RemoteViewList from "../../components/RemoteView/RemoteViewList.vue"
import CenterBigView from "../../components/CenterBigView/CenterBigView.vue"
import MeetingFooter from "../../components/MeetingFooter/MeetingFooter.vue"
import TeacherSmallView from "../../components/TeacherSmallView/TeacherSmallView.vue"
import IMessage from '../../components/IMessage/IMessage.vue'
import { 
  AliEngineClientRole,
  AliEngineVideoStreamType
} from '../../core/data/main';
export default {
  components: {
    MeetingHeader,
    MeetingFooter,
    RemoteViewList,
    CenterBigView,
    TeacherSmallView,
    IMessage
  },
  data() {
    return {
      userid: this.$store.state.rtc.userid,
      displayName: this.$store.state.rtc.displayName,
      channel: this.$store.state.rtc.channel,
    }
  },
  mounted() {
    this.$electron.ipcRenderer.send("enterClass")
    console.log('enterClass')
    this.$electron.ipcRenderer.on("app-close", ()=> {
      AliRTCElectronInterrativeEngine.instance.exitRoom().finally(()=>{
        AliRTCElectronInterrativeEngine.instance.logoutIm()
        this.$store.commit("SET_RTC_DATA", {
          classFinished: true
        })
      })
    })
    this.registerEvent()
    this.enterRoom()
  },
  methods: {
    /**
     * 进入房间
     */
    enterRoom() {
      AliRTCElectronInterrativeEngine.instance.enterRoom(AliEngineClientRole.AliEngineClientRoleLive, this.$store.state.rtc.authInfo).then(()=>{
        // AliRTCElectronInterrativeEngine.instance.startPreview()
        // this.$store.commit("SET_RTC_DATA", {
        //   isPreview: true
        // })
      }).catch((err)=>{
        this.$message({
          type: "error",
          iconClass: "el-icon-warning el-message__icon",
          customClass: "my-message-error",
          message: err,
          offset: 150
        });
        setTimeout(()=> {
          this.$electron.ipcRenderer.send("leaveClass")
          this.$router.back()
        }, 3000)
      })
    },
    registerEvent() {
      /**
       * 老师进入
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.TEACHER_ENTER, (userid)=> {
        AliRTCElectronInterrativeEngine.instance.setRemoteVideoStreamType(userid, AliEngineVideoStreamType.AliEngineVideoStreamTypeHigh)
        let userInfo = AliRTCElectronInterrativeEngine.instance.getUserInfo(userid)
        this.$store.commit("SET_RTC_DATA", {
          teacherInfo: userInfo
        })
      })
      /**
       * 老师离开
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.TEACHER_LEAVE, ()=> {
        AliRTCElectronInterrativeEngine.instance.exitRoom().finally(()=>{
          AliRTCElectronInterrativeEngine.instance.logoutIm()
          this.$store.commit("SET_RTC_DATA", {
            classFinished: true
          })
        })
      })
      /**
       * 上麦成功
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.TO_INTERACTIVE, ()=> {
        if(!this.$store.state.rtc.isPreview && !this.$store.state.rtc.isMuteLocalCamera) {
          AliRTCElectronInterrativeEngine.instance.startPreview()
          this.$store.commit("SET_RTC_DATA", {
            isPreview: true
          })
        }
        this.$store.commit("SET_RTC_DATA", {
          isEverInterActive: true,
          isInterActive: true
        })
      })
      /**
       * 下麦成功
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.TO_LIVE, ()=> {
        if(this.$store.state.rtc.isPreview) {
          AliRTCElectronInterrativeEngine.instance.stopPreview()
          this.$store.commit("SET_RTC_DATA", {
            isPreview: false
          })
        }
        this.$store.commit("SET_RTC_DATA", {
          isInterActive: false
        })
      })

      /**
       * 订阅了老师屏幕流
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.SUBSCRIBED_SCREEN, (userid)=> {
        let userInfo = AliRTCElectronInterrativeEngine.instance.getUserInfo(userid)
        this.$store.commit("SET_RTC_DATA", {
          teacherInfo : userInfo
        })
      })

      /**
       * 停止订阅了老师屏幕流
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.UNSUBSCRIBED_SCREEN, (userid)=> {
        let userInfo = AliRTCElectronInterrativeEngine.instance.getUserInfo(userid)
        this.$store.commit("SET_RTC_DATA", {
          teacherInfo : userInfo
        })
      })

      /**
       * 麦克风被老师控制
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.TEACHER_CONTROL_MIC, (mute)=> {
        let res = AliRTCElectronInterrativeEngine.instance.muteLocalMic(mute)
        if(0 == res) {
          this.$store.commit("SET_RTC_DATA",{
            isMuteLocalMic: mute
          })
        }
      })

      /**
       * 摄像头被老师控制
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.TEACHER_CONTROL_CAMERA, (mute)=> {
        let res = AliRTCElectronInterrativeEngine.instance.muteLocalCamera(mute)
        if(0 == res) {
          this.$store.commit("SET_RTC_DATA",{
            isMuteLocalCamera: mute,
            isPreview: !mute
          })
        }
      })
      /**
       * 收到老师反馈是否允许上麦通知
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.HAND_UP_RESULT, (backHandUp)=> {
        this.$store.commit("SET_RTC_DATA", {
          isWaitingBackHandUp: false,
        })
        if(backHandUp) {
          AliRTCElectronInterrativeEngine.instance.setClientRole(AliEngineClientRole.AliEngineClientRoleInteractive)
          this.$message({
            type: "info",
            customClass: "my-message-info",
            message: "老师同意了连麦",
            offset: 150
          });
        }else {
          this.$message({
            type: "error",
            iconClass: "el-icon-warning el-message__icon",
            customClass: "my-message-error",
            message: "老师拒绝了连麦",
            offset: 150
          });
        }
      })

    },
  }
}
</script>

<style scoped lang="scss">
  .student{
    background: #FAFAFA;
    height: 100%;
    .meeting-main{
      width: 100%;
      height: vh(666);
      display: flex;
      .meeting-main-left{
        display: flex;
        flex-direction: column;
        height: 100%;
        width: vw(710);
        margin-right: vw(8);
      }
      .meeting-main-right{
        background: #ffffff;
        height: 100%;
        flex: 1;
      }
    }
  }
</style>