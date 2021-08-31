<template>
  <div class="teacher">
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
import MeetingHeader from "../../components/MeetingHeader/MeetingHeader.vue"
import RemoteViewList from "../../components/RemoteView/RemoteViewList.vue"
import CenterBigView from "../../components/CenterBigView/CenterBigView.vue"
import MeetingFooter from "../../components/MeetingFooter/MeetingFooter.vue"
import TeacherSmallView from "../../components/TeacherSmallView/TeacherSmallView.vue"
import IMessage from '../../components/IMessage/IMessage.vue'
import { AliEngineClientRole} from "../../core/data/main"
import EventType from "../../core/client/eventtype"
import AliRTCElectronInterrativeEngine from "../../core/client/alirtc-electron-interrative-engine"
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
    this.$electron.ipcRenderer.on("app-close", ()=> {
      AliRTCElectronInterrativeEngine.instance.exitRoom().finally(()=>{
        AliRTCElectronInterrativeEngine.instance.logoutIm()
        this.$store.commit("SET_RTC_DATA", {
          classFinished: true
        })
      })
    })
    this.registerEvent()
    this.createAndEnterRoom()
  },
  methods: {
    /**
     * 创建房间
     */
    createAndEnterRoom() {
      AliRTCElectronInterrativeEngine.instance.createRoom(this.userid, this.channel).then((res)=>{
        this.enterRoom()
      }).catch(err=> {
        this.$message({
          type: "error",
          iconClass: "el-icon-warning el-message__icon",
          customClass: "my-message-error",
          message: "创建房间失败",
          offset: 150
        })
        this.$electron.ipcRenderer.send("leaveClass")
        this.$router.back()
        console.log('createrooom fail',err)
      })
    },
    /**
     * 进入房间
     */
    enterRoom() {
      AliRTCElectronInterrativeEngine.instance.enterRoom(AliEngineClientRole.AliEngineClientRoleInteractive, this.$store.state.rtc.authInfo).then(()=>{
        AliRTCElectronInterrativeEngine.instance.startPreview()
        this.$store.commit("SET_RTC_DATA", {
          isPreview: true
        })
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

    /**
     * 注册回调
     */
    registerEvent() {
    
      AliRTCElectronInterrativeEngine.instance.on(EventType.PUBLISHED_SCREEN, ()=> {
        this.$store.commit("SET_RTC_DATA",{
          isPublishScreen: true,
          startScreenShareTime: Date.now()
        });
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.UNPUBLISHED_SCREEN, ()=> {
        this.$store.commit("SET_RTC_DATA",{
          isPublishScreen: false,
          startScreenShareTime: 0
        });
      })
      
      AliRTCElectronInterrativeEngine.instance.on(EventType.STUDENT_HAND_UP, (data)=> {
        if(data.handUp) {
          this.$message({
            type: "info",
            message: "学生" + data.displayName + "申请连麦",
            customClass: "my-message-info",
            offset: 150
          })
          this.$store.commit("ADD_LINK", data)
        }
      })
    },
  }
}
</script>

<style scoped lang="scss">
  .teacher{
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