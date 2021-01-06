<template>
  <div class="student">
    <hheader></hheader>
    <div class="student-box" id="student-box">
      <div class="video-div">
        <video autoplay :class="{'mirrorMode':mirrorModeState}" poster="../../assets/img/教师-学生的摄像头已关闭.png" id="localVideo"></video>
      </div>
      <div class="user-div on">
        <userlist></userlist>
      </div>
    </div>
    <hfooter></hfooter>
  </div>
</template>

<script>
  import RTCClient from "../../core/rtc-client";
  import Util from "../../core/utils/utils";
  export default {
    data() {
      return {};
    },
    created() {
      hvuex({
        isSwitchScreen: true,
        isPublishScreen:false
      });
      RTCClient.instance.setAutoPublishSubscribe(false,true);
      this.registerCallBack();
    },
    mounted() {
      this.$nextTick(() => {
        RTCClient.instance
          .login(this.$store.state.data.classNum,this.$store.state.data.userName)
          .then(userId => {
            hvuex({
              userId: userId,
            }).then(()=>{
               Util.startPreview(document.getElementById(userId));
            });
          })
          .catch(err => {});
      });
    },
    computed: {
      // 镜像状态
      mirrorModeState() {
        if (this.$store.state.data.isSwitchScreen) {
          return false;
        } else {
          if (!this.$store.state.data.isPreview) {
            return false;
          }
        }
        return true;
      }
    },
    methods: {
      // 注册回调
      registerCallBack() {
        RTCClient.instance.registerCallBack((eventName, data) => {
          switch (eventName) {
            case "onJoin":
            case "onPublisher":
            case "onUnPublisher":
            case "onNotify":
              hvuex({
                userList: RTCClient.instance.getRoomUserList()
              });
              break;
            case "onSubscribeResult":
              Util.showRemoteVideo(data);
              break;
            case "onEnterSeatResult":
              hvuex({
                isPublish: true
              });
              break;
            case "onLeaveSeatResult":
              hvuex({
                isPublish: false,
                isPublishScreen:false
              });
              break;
            case "onUserVideoMuted":
              break;
            case "onUserAudioMuted":
              break;
            case "onError":
              Util.showErrorMsg(data);
              break;
            case "onBye":
              Util.onByeMessage(data);
              break;
            case "onLeave":
              hvuex({
                userList: RTCClient.instance.getRoomUserList()
              });
              break;
          }
        });
      }
    }
  };
</script>

<style lang="scss">
  .student {
    .student-box {
      width: 100%;
      display: flex;
      height: vh(720-40-104);
      .video-div {
        flex: 1;
        height: vh(576);
        background-color: black;
        video {
          height: 100%;
          width: 100%;
        }
      }
      .on {
        width: 206px;
      }
    }
  }
</style>