<template>
  <div class="login">
    <header class="login-header">
      <i class="iconfont icon-rtcyinshipintongxin"></i> 音视频通信 
    </header>
    <div class="login-card">
      <div class="login-card-left">
        <img src="../../assets/img/interactive-class.png" alt srcset />
        <div class="version">rtc version: {{rtcVersion}}</div>
      </div>
      <div class="login-card-right">
        <p class="title">互动大班课</p>
        <div class="button-group">
          <button class="button" :class="studentBtnClass" @click="toTeacher">教师</button>
          <button class="button" :class="teacherBtnClass" @click="toStudent">学生</button>
        </div>
        <div class="form">
          <hui-name-input class="form-input-class" placeholder="您的姓名" v-model="displayName" title="姓名"></hui-name-input>
          <hui-code-input class="form-input-class" title="教室码" v-model="channel" :disable="role==0" placeholder="教室码（6位数字）"></hui-code-input>
        </div>
        <button class="submit-button" :class="(!channel||channel.length!=6||!displayName)?'disable':''" :disabled="!channel||channel.length!=6||!displayName" type="submit" @click="onSubmit">开始上课</button>
      </div>
    </div>
  </div>
</template>

<script>
import AliRTCElectronInterrativeEngine from "../../core/client/alirtc-electron-interrative-engine"
import EventType from "../../core/client/eventtype"
import Util from "../../core/utils/utils";
import { AliEngineClientRole, AliEngineErrorCode, AliEngineOnByeType } from "../../core/data/main"
export default {
  data() {
    return {
      role: AliEngineClientRole.AliEngineClientRoleInteractive,
      displayName: "",
      rtcVersion: "",
      channel: Math.random().toFixed(6).slice(-6)
    };
  },
  created() {
    window.rtc = AliRTCElectronInterrativeEngine.instance
  },
  mounted() {
    this.registerEvent()
    this.rtcVersion = AliRTCElectronInterrativeEngine.instance.getRTCVersion()
  },
  computed: {
    studentBtnClass() {
      return this.role === AliEngineClientRole.AliEngineClientRoleInteractive ? "on" : "off"
    },
    teacherBtnClass() {
      return this.role === AliEngineClientRole.AliEngineClientRoleLive ? "on" : "off"
    },
    loginDisplayName() {
      return this.role === AliEngineClientRole.AliEngineClientRoleInteractive ? this.displayName + "_老师" : this.displayName
    }
  },
  methods: {
    // 登陆
    onSubmit() {
      if (!this.displayName) {
        Util.toast("用户名不能为空");
        return;
      }
      if (!this.channel || this.channel.length != 6) {
        Util.toast("教室码不正确");
        return;
      }
      Util.getAuthInfo(this.channel, this.loginDisplayName).then(authInfo => {
        AliRTCElectronInterrativeEngine.instance.loginIm(authInfo.userid)
        this.$store.commit("SET_RTC_DATA", {
          role: this.role,
          channel: this.channel,
          displayName: this.loginDisplayName,
          userid: authInfo.userid,
          authInfo: authInfo
        });
        
      }).catch((err)=>{
        this.$message({
          type: "error",
          iconClass: "el-icon-warning el-message__icon",
          customClass: "my-message-error",
          message: `getAuthInfo Fail: ${err ? err : "no server"}`,
          offset: 150
        })
      })
    },
    // 切换为老师
    toTeacher() {
      this.role = AliEngineClientRole.AliEngineClientRoleInteractive;
      this.$store.commit("SET_RTC_DATA", {
        role: AliEngineClientRole.AliEngineClientRoleInteractive,
        isTeacher: true
      });
    },
    toStudent() {
      this.role = AliEngineClientRole.AliEngineClientRoleLive;
      this.$store.commit("SET_RTC_DATA", {
        role: AliEngineClientRole.AliEngineClientRoleLive,
        isTeacher: false
      });
    },
    registerEvent() {
      /**
       * 登录IM成功
       */
      AliRTCElectronInterrativeEngine.instance.on(EventType.LOGIN_IM_SUCCESS, ()=> {
        if (this.role == AliEngineClientRole.AliEngineClientRoleInteractive) {
          this.$router.push("/teacher");
        } else {
          this.$router.push("/student");
        }
      })
      AliRTCElectronInterrativeEngine.instance.on(EventType.JOIN_RESULT, (result)=> {
        console.warn(EventType.JOIN_RESULT, result)
        this.$store.commit("SET_RTC_DATA",{
          classStartTime: Date.now()
        })
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.LEAVE_RESULT, (result)=> {
        console.warn(EventType.LEAVE_RESULT, result)
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.STUDENT_ENTER, (userid)=> {
        let userInfo = AliRTCElectronInterrativeEngine.instance.getUserInfo(userid)
        this.$store.commit("ADD_USER", userInfo);
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.STUDENT_LEAVE, (userid)=> {
        this.$store.commit("REMOVE_USER", userid);
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.SUBSCRIBED_VIDEO, (userid)=> {
        let userInfo = AliRTCElectronInterrativeEngine.instance.getUserInfo(userid)
        if(userInfo.displayName.indexOf("_老师") >= 0) {
          this.$store.commit("SET_RTC_DATA", {
            teacherInfo : userInfo
          })
        }else {
          this.$store.commit("UPDATE_USER", userInfo)
        }
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.UNSUBSCRIBED_VIDEO, (userid)=> {
        let userInfo = AliRTCElectronInterrativeEngine.instance.getUserInfo(userid)
        if(userInfo.displayName.indexOf("_老师") >= 0) {
          this.$store.commit("SET_RTC_DATA", {
            teacherInfo : userInfo
          })
        }else {
          this.$store.commit("UPDATE_USER", userInfo)
        }
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.USER_AUDIO_MUTE, (userid, isMuted)=> {
        this.$store.commit("UPDATE_MUTE_STATE", {
          userid,
          label: "isMutedMic",
          isMuted: isMuted ? true : false
        })
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.USER_VIDEO_MUTE, (userid, isMuted)=> {
        this.$store.commit("UPDATE_MUTE_STATE", {
          userid,
          label: "isMutedCamera",
          isMuted: isMuted ? true : false
        })
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.AUDIO_VOLUME, (data)=> {
        let speakerList = []
        for(let i = 0; i < data.length; i++) {
          if(data[i].userid !== "0" && data[i].speechState === 1) {
            let teacherInfo = this.$store.state.rtc.teacherInfo
            if(teacherInfo.userid === data[i].userid) {
              speakerList.push(teacherInfo.displayName)
            }else {
              let info = this.$store.state.rtc.userList.getObjByProprety(data[i].userid, 'userid')
              if(info) {
                speakerList.push(info.displayName)
              }
            }
            if(speakerList.length >= 3) break
          }
        }
        const isArrEqual = (arr1, arr2) => {
          return arr1.length === arr2.length && arr1.every((ele) => arr2.includes(ele));
        };
        if(!isArrEqual(speakerList, this.$store.state.rtc.speakerList)) {
          this.$store.commit("SET_RTC_DATA", {
            speakerList: speakerList
          })
        }
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.ERROR, (code)=> {
        switch (code) {
          case AliEngineErrorCode.AliEngineErrorInvaildState:
          case AliEngineErrorCode.AliEngineErrorSessionRemoved:
          case AliEngineErrorCode.AliEngineErrorIceConnectionHeartbeatTimeout:
            this.$message({
              type: "error",
              iconClass: "el-icon-warning el-message__icon",
              customClass: "my-message-error",
              message: `房间状态错误: ${code}`,
              offset: 150
            })
            setTimeout(()=> {
              AliRTCElectronInterrativeEngine.instance.exitRoom().finally(()=> {
                AliRTCElectronInterrativeEngine.instance.logoutIm()
                this.$store.commit("SET_RTC_DATA", {
                  classFinished: true
                })
              })
            },3000)
            break;
        }
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.BYE, (code)=> {
        let message = code === AliEngineOnByeType.AliEngineOnByeChannelTerminated ? 
          "每节课体验时长最多10分钟，到时间后自动退出，如继续体验，请重新进入教室" : "被移出频道或账号在另一地点登录"
        AliRTCElectronInterrativeEngine.instance.exitRoom().finally(()=> {
          AliRTCElectronInterrativeEngine.instance.logoutIm()
          this.$myAlert(message, "", {
            confirmButtonText: "我知道了"
          }).then(()=>{
            this.$store.commit("SET_RTC_DATA", {
              classFinished: true
            })
          })
        })
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.MEMBER_LIST_UPDATE, ()=> {
        AliRTCElectronInterrativeEngine.instance.getMemberList().then(list => {
          this.$store.commit("UPDATE_MEMBER_LIST", list)
        })
      })

      AliRTCElectronInterrativeEngine.instance.on(EventType.TEXT_MESSAGE_ADD, (data)=> {
        this.$store.commit("ADD_MESSAGE", data)
      })
    }
  },
  watch: {
    role(newVal, oldVal) {
      this.channel = newVal == AliEngineClientRole.AliEngineClientRoleInteractive ? 
        Math.random().toFixed(6).slice(-6) : ""
    }
  }
}
</script>

<style lang="scss">
  .login {
    height: 100vh;
    overflow: hidden;
    position: relative;
    .login-header {
      margin: vh(32) vw(47) 0;
      font-size: vh(20);
      .icon-rtcyinshipintongxin {
        font-size: vh(40);
        vertical-align: middle;
        margin-right: vw(5);
      }
      .icon-shezhi {
        font-size: vh(31);
        cursor: pointer;
        float: right;
      }
    }
    .login-card {
      margin: vh(91) vw(110) 0;
      display: flex;
      .login-card-left {
        width: vw(402);
        img {
          width: 80%;
          height: auto;
          // top: vh(-80);
          position: relative;
        }
        .version {
          width: 80%;
          color: #888888;
          text-align: center;
        }
      }
      .login-card-right {
        flex: 1;
        .title {
          font-size: vh(45);
          line-height: vh(62);
          letter-spacing: vw(2);
        }
        .button-group {
          margin-top: vh(48);
          .button {
            width: vw(145);
            height: vh(48);
            background: #f6f9ff;
            border: vh(2) solid #c1c1c1;
            background-color: #ffffff;
            cursor: pointer;
            font-size: vh(18);
            color: #555555;
            outline: none;
            position: relative;
          }
          .button:nth-child(1) {
            border-radius: vh(24) 0 0 vh(24);
          }
          .button:nth-child(2) {
            border-radius: 0 vh(24) vh(24) 0;
            transform: translateX(vh(-6));
          }
          .on {
            border: vh(2) solid #013ebe;
            background-color: #f6f9ff;
            color: #013ebe;
            z-index: 1;
          }
        }
        .form {
          margin-top: vh(28);
          .form-input-class {
            margin-top: vh(25);
            width: vw(306);
          }
          .name-span {
            font-size: 12px;
            line-height: 2.36111vh;
            color: #888888;
          }
          .hui-select {
            margin-top: vh(15);
          }
        }
        .submit-button {
          margin-top: vh(30);
          display: block;
          width: vw(306);
          height: vh(48);
          text-align: center;
          line-height: vh(48);
          border-radius: vh(24);
          color: white;
          font-size: vh(23);
          background-color: rgb(10, 67, 187);
          letter-spacing: vh(1);
          outline: none;
          cursor: pointer;
          border: 0;
        }
        .disable {
          background-color: #013EBE;
          opacity: 0.3;
        }
      }
    }
  }
</style>