<template>
  <div class="hfooter">
    <div class="function" :class="{'teacher':$store.state.data.role==0}">
      <span class="vsersion">{{$store.state.data.version}}</span>
      <div class="mic" :class="[{'on':isMuteLocalMic}]" @click="muteLocalMic">
        <i :style="isMuteLocalMic ? 'background-image:url('+  micOff +')' : 'background-image:url('+  micOn +')'"></i>
        <span>{{isMuteLocalMic?'取消静音':'静音'}}</span>
      </div>
      <div class="camera" :class="[{'on':isMuteLocalCamera}]" @click="muteLocalCamera">
        <i :style="isMuteLocalCamera ? 'background-image:url('+  cameraOff +')' : 'background-image:url('+  cameraOn +')'"></i>
        <span>{{isMuteLocalCamera?'打开摄像头':'关闭摄像头'}}</span>
      </div>
      <div class="screen" @click="publishScreen" v-if="$store.state.data.supportInfo.browser!='Safari'">
        <i :style="'background-image:url(' + screenshare + ')'"></i>
        <span>{{$store.state.data.isPublishScreen?'取消屏幕共享':'屏幕共享'}}</span>
      </div>
      <div class="switchRole" :class="{'on':$store.state.data.isPublish}" v-if="$store.state.data.role==1" @click="switchRole">
        <i :style="$store.state.data.isPublish ? 'background-image:url('+ switchOff +')' : 'background-image:url('+  switchOn +')'"></i>
        <span>{{$store.state.data.isPublish?'取消连麦':'连麦'}}</span>
      </div>
      <div class="leaveclass" @click="exitRoom">
        <i :style="$store.state.data.role==0 ? 'background-image:url('+ leave +')' : 'background-image:url('+ end +');background-color: rgba(245,34,45,0.15)'"></i>
        <span>{{$store.state.data.role==0?'结束课程':'离开教室'}}</span>
      </div>
    </div>
  </div>
</template>

<script>
  import RTCClient from "../core/rtc-client";
  import Util from "../core/utils/utils";
  export default {
    data() {
      return {
        isMuteLocalMic: false,
        isMuteLocalCamera: false,
        micOn: require("../assets/img/mic-on.png"),
        micOff: require("../assets/img/mic-off.png"),
        cameraOn: require("../assets/img/camera-on.png"),
        cameraOff: require("../assets/img/camera-off.png"),
        start: require("../assets/img/start.png"),
        stop: require("../assets/img/stop.png"),
        switchOn: require("../assets/img/switch-on.png"),
        switchOff: require("../assets/img/switch-off.png"),
        screenshare: require("../assets/img/screen.png"),
        share: require("../assets/img/share.png"),
        leave: require("../assets/img/leave.png"),
        end: require("../assets/img/end.png")
      };
    },
    created() {},
    methods: {
      // 设置是否停止发布本地音频流
      muteLocalMic() {
        if (!this.$store.state.data.isPublish) {
          Util.toast("未推流");
          return false;
        }
        RTCClient.instance.muteLocalMic(!this.isMuteLocalMic);
        this.isMuteLocalMic = !this.isMuteLocalMic;
      },
      // 设置是否停止发布本地视频流
      muteLocalCamera() {
        if (!this.$store.state.data.isPublish) {
          Util.toast("未推流");
          return false;
        }
        RTCClient.instance
          .muteLocalCamera(document.getElementById("localVideo"))
          .then(re => {
            this.isMuteLocalCamera = !this.isMuteLocalCamera;
            hvuex({
              isPreview: RTCClient.instance.isPreview
            });
            if (RTCClient.instance.isPreview) {
              AppConfig.localStream = document.getElementById("localVideo").srcObject;
              document.getElementById(RTCClient.instance.userId).srcObject = document.getElementById("localVideo").srcObject;
            }
          })
          .catch(err => {});
      },
      /**
       * 推屏幕流
       */
      publishScreen() {
        if (!this.$store.state.data.isPublish) {
          Util.toast("未推流");
          return false;
        }
        if (this.$store.state.data.isPublishScreen) {
          RTCClient.instance
            .stopPublishScreen()
            .then(re => {
              RTCClient.instance.stopScreenSharePreview(document.getElementById("localVideo"));
              document.getElementById("localVideo").srcObject = AppConfig.localStream;
              if (document.getElementById(RTCClient.instance.userId).srcObject == AppConfig.localStream) {
                document.getElementById(RTCClient.instance.userId).srcObject = null;
              }
              hvuex({
                isPublishScreen: false
              });
            })
            .catch(err => {});
        } else {
          RTCClient.instance
            .startPublishScreen()
            .then(() => {
              hvuex({
                isPublishScreen: true
              });
              if (this.$store.state.data.isSwitchScreen) {
                RTCClient.instance.startScreenSharePreview(document.getElementById(RTCClient.instance.userId));
              } else {
                RTCClient.instance.startScreenSharePreview(document.getElementById("localVideo"));
                document.getElementById(RTCClient.instance.userId).srcObject = AppConfig.localStream;
              }
            })
            .catch(err => {});
        }
      },
      // 切换上下麦
      switchRole() {
        if(RTCClient.instance.currentRole == 1){
          RTCClient.instance.enterSeat();
        } else {
          RTCClient.instance.leavelSeat();
          this.isMuteLocalMic = false;
          this.isMuteLocalCamera = false;
        }
      },
      // 退出教室
      exitRoom() {
        if (this.$store.state.data.role == 1) {
          Util.exitRoom();
        } else if (this.$store.state.data.role == 0) {
          this.$confirm("结束课程后无法再次回到同一个教室，需要老师重新创建", "您确定要离开教室吗？").then(() => {
            Util.exitRoom();
          }).catch(err => {})
        }
      }
    }
  };
</script>

<style lang="scss">
  .hfooter {
    position: fixed;
    left: 0;
    bottom: 0;
    width: 100%;
    height: vh(104);
    width: vw(1024);
    background-color: #f8f8f8;
    box-sizing: border-box;
    padding: vh(17) vw(32);
    .visiable {
      visibility: hidden;
    }
    #share {
      position: fixed;
      bottom: vh(-1111);
    }
    .function {
      margin-left: vw(138);
      display: flex;
      .vsersion {
        position: absolute;
        left: vw(10);
      }
       :hover {
        i {
          background-color: #bfbfbf;
        }
      }
      .on {
        i {
          background-color: #333333;
        }
      }
      .initstate {
        i {
          background-color: #013ebe;
        }
        i:hover {
          background-color: #0036a6;
        }
      }
      div {
        text-align: center;
        margin-right: vw(24);
        cursor: pointer;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        i {
          width: vw(100);
          height: vh(48);
          border-radius: vh(24);
          border-radius: 24px;
          background-color: #e5e5e5;
          margin-bottom: 12px;
          cursor: pointer;
          background-repeat: no-repeat;
          background-position: center center;
          background-size: vh(40) vh(40);
        }
        span {
          font-size: vh(16);
          line-height: vh(22);
          background-color: #f8f8f8;
          color: #2f2f2f;
        }
      }
      .startclass p {
        background-color: #013ebe;
        &:hover {
          background-color: #0036a6;
        }
      }
      .leaveclass {
        i {
          width: vh(48);
          height: vh(48);
          border-radius: 50%;
        }
      }
      .footer-setting {
        position: absolute;
        right: 0;
      }
    }
    .teacher {
      margin-left: vw(178);
    }
  }
</style>