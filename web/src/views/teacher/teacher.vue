<template>
  <div class="teacher">
    <hheader></hheader>
    <div class="teacher-box">
      <div class="video-div">
        <img class="video-div-img" v-show="showImg()" src="../../assets/img/教师-学生的摄像头已关闭.png" alt="" srcset="">
        <video autoplay :class="{'mirrorMode':mirrorModeState}" id="localVideo"></video>
      </div>
      <div class="user-div">
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
        isSwitchScreen: false
      });
      RTCClient.instance.setAutoPublishSubscribe(false,true);
      this.registerCallBack();
    },
    mounted() {
      this.$nextTick(() => {
        RTCClient.instance
          .login(this.$store.state.data.classNum,this.$store.state.data.userName+"_老师")
          .then(userId => {
            Util.startPreview(document.getElementById("localVideo")).then(()=>{
              document.getElementById(userId).srcObject = AppConfig.localStream;
            })
            RTCClient.instance.enterSeat();
            hvuex({
              userId: userId
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
          if (this.$store.state.data.isPublishScreen) {
            return false;
          }
        }
        return true;
      }
    },
    methods: {
      showImg() {
        if (document.getElementById("localVideo") && !document.getElementById("localVideo").srcObject) {
          return true;
        }
        return false;
      },
      /**
       * 注册回调
       */
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
                isPublish: false
              });
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
  .teacher {
    .teacher-box {
      width: 100%;
      display: flex;
      .video-div {
        flex: 1;
        height: vh(576);
        position: relative;
        .video-div-img {
          position: absolute;
          top: 0;
          left: 0;
          bottom: 0;
          right: 0;
          height: 100%;
          width: auto;
          margin: auto;
        }
        video {
          height: 100%;
          width: 100%;
          background-color: black;
        }
      }
    }
  }
</style>