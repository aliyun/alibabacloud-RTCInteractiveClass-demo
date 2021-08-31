import AliRtcEngine from 'aliyun-webrtc-electron-sdk'
import EventDispatcher from '../utils/eventdispatcher'
import EventType from "./eventtype"
import { appName, appKey, baseServer } from "../data/aim-config"
import requestPath from "./aim-request-path"
import AIMMessageType from "./aim-message-type"
import { 
  AliEngineClientRole, 
  AliEngineChannelProfile, 
  AliEngineVideoStreamType,
  AliEngineSubscribeState, 
  AliEnginePublishState,
  AliEngineVideoTrack,
  AliEngineFrameRate,
  AliEngineVideoEncoderOrientationMode,
  AliEngineVideoMirrorMode,
  AliEngineRotationMode,
  AliEngineScreenShareType
} from "../data/main"

const {
  IMSDK, // 核心 SDK
  DataSDK, // 数据 SDK
  ConnectionStatus,
  EventNameEnum,
} = AIM

class AliRTCElectronInterrativeEngine extends EventDispatcher {
  constructor() {
    super()
    this._rtcClient = new AliRtcEngine({
      h5CompatibleMode: true
    })
    this._bindRTCEvent()
    this._registerIMEvent()
    this._rtcClient.setChannelProfile(AliEngineChannelProfile.AliEngineInteractiveLive)
    this._rtcClient.setRemoteDefaultVideoStreamType(AliEngineVideoStreamType.AliEngineVideoStreamTypeLow)
    this._rtcClient.enableAudioVolumeIndication(300, 3, 1)
    this._init()
  }
  /**
   * 获取实例
   */
  static get instance() {
    if (!AliRTCElectronInterrativeEngine._instance) {
      AliRTCElectronInterrativeEngine._instance = new AliRTCElectronInterrativeEngine();
    }
    return AliRTCElectronInterrativeEngine._instance;
  }

  /**
   * 销毁实例
   */
  static destroy() {
    if(AliRTCElectronInterrativeEngine._instance) {
      this._rtcClient.destroy()
      this._init()
      AliRTCElectronInterrativeEngine._instance = null
    }
  }

  /**
   * 登录IM
   * @param {String} userid RTC鉴权信息中的userid
   */
  async loginIm(userid) {
    if(!appName || !appKey || !baseServer) {
      alert("请在src/renderer/core/data/aim-config.js中配置IM相关的appName、appKey、baseServer")
      return 
    }
    const deviceId = await IMSDK.getAuthService().getDeviceId();
    const Setting = {
      appKey, // 应用 key
      deviceId, // 设备唯一id
      appName, // app_name 应用名称
      debug: true,
      log: {
        error(...args) { console.error('报错信息', ...args) },
        info(...args) { console.info('info信息', ...args) }
      },
      async authTokenCallback() {
        return fetch(
          `${baseServer}${requestPath.login}?appKey=${appKey}&deviceId=${deviceId}&appUid=${userid}&appId=${appName}`
        )
          .then((res) => res.json())
          .then((res) => {
            if (res) {
              try {
                console.log(res)
                const authToken = res.data;
                return { ...authToken, uid: userid };
              } catch (err) {
                throw new Error(err);
              }
            }
            throw new Error('token is null');
          });
      },

    };
    IMSDK.getSettingService().set(Setting);
    return IMSDK.getAuthService().login();
  }
  /**
   * 登出IM
   */
  logoutIm() {
    return IMSDK.getAuthService().logout();
  }
  /**
   * 通过RTC信息创建IM房间
   * @param {String} userid RTC userid
   * @param {String} channel RTC channel
   */
  createRoom(userid, channel) {
    return fetch(
      `${baseServer}${requestPath.createGroup}?appId=${appName}&appUid=${userid}&room=${channel}`
    )
      .then((res) => res.json())
      .then((res) => {
        this._appCid = res.data
        return res.data
      });
  }
  /**
   * 进入房间
   * @param {Number} role 角色
   * @param {Object} authInfo 鉴权信息
   */
  enterRoom(role, authInfo) {
    return new Promise(async (resolve, reject) => {
      if (role !== AliEngineClientRole.AliEngineClientRoleInteractive && role !== AliEngineClientRole.AliEngineClientRoleLive) {
        reject("角色错误")
      }
      this._rtcClient.setClientRole(role)
      this._channel = authInfo.channel
      this._userid = authInfo.userid
      this._displayName = authInfo.displayName
      if (role === AliEngineClientRole.AliEngineClientRoleInteractive) {
        this.setVideoEncoderConfiguration(1280, 720)
        this._isTeacher = true
        this._teacherUserid = this._userid
        this._joinRoom().then(() => {
          let res = this._rtcClient.joinChannel(authInfo)
          if(res === 0) {
            resolve()
          }else {
            reject(`入会失败: ${res}`)
          }
        }).catch(err => {
          reject(err)
        })
      } else {
        // 进入房间是观众角色 学生身份
        this.setVideoEncoderConfiguration(640, 360)
        this._getRoom(authInfo.channel).then(() => {
          this._joinRoom().then(() => {
            let res = this._rtcClient.joinChannel(authInfo)
            if(res === 0) {
              resolve()
            }else {
              reject(`入会失败: ${res}`)
            }
          }).catch(err => {
            reject(err)
          })
        }).catch(err => {
          reject(err)
        })
      }
    })
  }

  /**
   * 设置角色 上下麦
   * @param {Number} role
   */
  setClientRole(role) {
    return this._rtcClient.setClientRole(role)
  }

  /**
   * 设置视频分辨率
   * @param {number} width 视频宽度
   * @param {number} height 视频高度
   * @returns 
   */
  setVideoEncoderConfiguration(width, height) {
    let videoEncoderConfiguration = {
      dimensions: {
        width: width,
        height: height
      },
      frameRate: AliEngineFrameRate.AliEngineFrameRateFps15,
      bitrate: 512,
      orientationMode: AliEngineVideoEncoderOrientationMode.AliEngineVideoEncoderOrientationModeAdaptive,
      mirrorMode: AliEngineVideoMirrorMode.AliEngineVideoMirrorModeDisabled,
      rotationMode: AliEngineRotationMode.AliEngineRotationMode_0
    }
    return this._rtcClient.setVideoEncoderConfiguration(videoEncoderConfiguration)
  }
  /**
   * 关闭/开启本地麦克风
   * @param {Boolean} mute 是否静音
   * @returns 0:成功, 其他:失败
   */
  muteLocalMic(mute) {
    this._isMuteLocalMic = mute
    return this._rtcClient.muteLocalMic(mute)
  }
  /**
   * 关闭/开启本地摄像头
   * @param {Boolean} mute 是否关闭摄像头
   * @returns 0:成功, 其他:失败
   */
  muteLocalCamera(mute) {
    let res = this._rtcClient.muteLocalCamera(mute, AliEngineVideoTrack.AliEngineVideoTrackCamera)
    if(res === 0) {
      this._isMuteLocalCamera = mute
      if(mute) {
        return this.stopPreview()
      }else {
        return this.startPreview()
      }
    }
    return res
  }

  /**
   * 开启预览
   * @returns 
   */
  startPreview() {
    let res = this._rtcClient.startPreview()
    if (0 === res) {
      this._isPreview = true
    }
    return res
  }

  /**
   * 停止预览
   * @returns 
   */
  stopPreview() {
    let res = this._rtcClient.stopPreview()
    if (0 === res) {
      this._isPreview = false
    }
    return res
  }

  /**
   * 设置本地视图窗口
   * @param {HTMLDivElement} container 
   */
  setLocalViewConfig(container) {
    this._rtcClient.setLocalViewConfig(container)
  }

  /**
   * 设置远端视图窗口
   * @param {String} userid 用户id
   * @param {HTMLDivElement} container 视图容器 div
   * @param {Number} type 1: 摄像头  2:共享
   * @returns 
   */
  setRemoteViewConfig(userid, container, type) {
    return this._rtcClient.setRemoteViewConfig(userid, container, type)
  }

  /**
   * 设置远端大小流
   * @param {String} userid 用户id
   * @param {Number} streamType 1: 大流 2: 小流
   * @returns 
   */
  setRemoteVideoStreamType(userid, streamType) {
    return this._rtcClient.setRemoteVideoStreamType(userid, streamType)
  }

  /**
   * 获取屏幕分享信息
   * @param {Number} sourceType 0 屏幕 1 应用窗口
   */
  getScreenShareSourceInfo(sourceType) {
    return this._rtcClient.getScreenShareSourceInfo(sourceType)
  }

  /**
   * 开启屏幕共享
   * @param {*} type 共享类型
   * @param {*} sourceId 共享Id
   */
  startScreenShare(type, sourceId) {
    if (type === AliEngineScreenShareType.AliEngineScreenShareDesktop) {
      return this._rtcClient.startScreenShareByDesktopId(sourceId)
    } else if (type === AliEngineScreenShareType.AliEngineScreenShareWindow) {
      return this._rtcClient.startScreenShareByWindowId(sourceId)
    }
  }

  /**
   * 停止屏幕共享
   */
  stopScreenShare() {
    return this._rtcClient.stopScreenShare()
  }

  /**
   * 获取用户RTC信息 仅上麦用户
   * @param {string} userid 用户id
   * @returns 
   */
  getUserInfo(userid) {
    return this._rtcClient.getUserInfo(userid)
  }

  /**
   * 获取成员列表
   * @returns {Promise<Array>}
   */
  getMemberList() {
    return new Promise((resolve, reject) => {
      if (!this._appCid) {
        reject()
      } else {
        IMSDK.getConvService().groupConversationListAllMembers(this._appCid).then((memberList) => {
          let _memberList = []
          for (let i = 0; i < memberList.length; i++) {
            let _rtcUid = memberList[i].uid.split("@")[0]
            _memberList.push({
              userid: _rtcUid,
              isSelf: this._userid === _rtcUid,
              isTeacher: this._teacherUserid === _rtcUid,
              displayName: memberList[i].groupNick
            })
          }
          resolve(_memberList.reverse())
        }).catch(err => {
          reject(err)
        })
      }
    })
  }
  /**
   * 退出教室
   * 老师 解散群组 离开教室
   * 学生 退出群组 离开教室
   */
  exitRoom() {
    return new Promise((resolve, reject)=> {
      if(!this._isTeacher) {
        // IMSDK.getConvService().groupConversationLeave(this._appCid).finally(()=>{
          this._init()
          let res = this._rtcClient.leaveChannel()
          if(res === 0) {
            resolve()
          }else {
            reject(res)
          }
        // })
      }else {
        fetch(
          `${baseServer}${requestPath.destoryChannel}?appUid=${this._userid}&room=${this._channel}`
        )
          .then((res) => res.json())
          .then((res) => {
            let _res = this._rtcClient.leaveChannel()
            if(_res === 0) {
              resolve()
            }else {
              reject(_res)
            }
          }).catch((err)=>{
            reject(err)
          }).finally(()=>{
            this._init()
          })
      }
    })
  }

  /**
   * 发送普通文本
   * @param {String} message 普通文本信息
   */
  sendTextMessage(message) {
    return this._sendMessage({
      type: AIMMessageType.Common_Message,
      isTeacher: this._isTeacher,
      message
    })
  }
  /**
   * 关闭学生麦克风
   * @param {String} userid 用户id
   * @param {Boolean} muteMic 是否关闭学生麦克风
   */
  muteStudentMic(userid, muteMic) {
    return this._sendMessage({
      type: AIMMessageType.Signalling_Message,
      isTeacher: this._isTeacher,
      uid: userid,
      muteMic
    })
  }
  /**
   * 关闭学生摄像头
   * @param {String} userid 用户id
   * @param {Boolean} muteCamera 是否关闭学生摄像头
   */
  muteStudentCamera(userid, muteCamera) {
    return this._sendMessage({
      type: AIMMessageType.Signalling_Message,
      isTeacher: this._isTeacher,
      uid: userid,
      muteCamera
    })
  }
  /**
   * 关闭所有学生麦克风
   * @param {Boolean} muteAllMic 是否关闭所有学生麦克风
   */
  muteAllStudentMic(muteAllMic) {
    return this._sendMessage({
      type: AIMMessageType.Signalling_Message,
      isTeacher: this._isTeacher,
      muteAllMic,
    })
  }
  /**
   * 返回是否允许学生上麦
   * @param {String} userid 用户id
   * @param {Boolean} backHandUp 是否允许学生上麦
   */
  backHandUp(userid, backHandUp) {
    return this._sendMessage({
      type: AIMMessageType.Signalling_Message,
      isTeacher: this._isTeacher,
      uid: userid,
      backHandUp
    })
  }
  /**
   * 学生举手请求上麦
   * @param {Boolean} handUp 是否举手
   */
  handUp(handUp) {
    return this._sendMessage({
      type: AIMMessageType.Signalling_Message,
      isTeacher: this._isTeacher,
      handUp,
    })
  }

  /**
   * 获取RTC版本号
   * @returns {String} electron RTC版本号
   */
  getRTCVersion() {
    return this._rtcClient.getSDKVersion()
  }

  /**
   * 订阅事件
   *
   * @param {string} name - 事件名字
   * @param {string} handler - 处理事件的方法
   */
   on (name, handler, context) {  // 此处需要加日志
    this.replaceEventListener(name, handler, context)
  }

  /**
   * 取消订阅事件
   *
   * @param {string} name - 事件名字
   * @param {string} handler - 处理事件的方法
   */
  off (name, handler, context) { // 此处需要加日志
    this.removeEventListener(name, handler, context)
  }

  _init() {
    this._isTeacher = false
    this._channel = "" // 当前频道
    this._userid = "" // 用户userid
    this._displayName = "" // 用户昵称
    this._appCid = "" // AIM 群聊appCid
  }

  /**
   * 获取IM appCid
   * @param {String} channel 
   */
  _getRoom(channel) {
    return new Promise((resolve, reject) => {
      fetch(
        `${baseServer}${requestPath.getGroup}?appId=${appName}&room=${channel}`
      )
        .then((res) => res.json())
        .then((res) => {
          if (res) {
            if (res.code == 200) {
              this._appCid = res.data
              resolve(res.data)
            } else {
              reject(`no room: ${res.data}`)
            }
          } else {
            reject('no room')
          }
        })
    })
  }

  _joinRoom() {
    return new Promise((resolve, reject) => {
      fetch(
        `${baseServer}${requestPath.joinChannel}?appId=${appName}&appCid=${this._appCid}&appUid=${this._userid}&role=3&nickName=${this._displayName}&room=${this._channel}`
      )
        .then((res) => res.json())
        .then((res) => {
          if (res && res.code == 200) {
            this._dataSDKSubscribe()
            resolve()
          } else {
            reject(`请确认老师是否已经创建教室`)
          }
        });
    })
  }

  _joinRTCChannel(authInfo) {
    return this._rtcClient.joinChannel(authInfo)
  }

  /**
   * 发送IM消息
   * @param {*} content 要发送的消息
   */
  _sendMessage(content) {
    content.displayName = this._displayName
    content = encodeURIComponent(JSON.stringify(content))
    return fetch(
      `${baseServer}${requestPath.sendMsg}?appId=${appName}&appCid=${this._appCid}&sendUid=${this._userid}&content=${content}`
    )
  }

  _dataSDKSubscribe() {
    DataSDK.subscribe((newStore) => {
      console.log('store 更新', newStore)
    });
    DataSDK.activeConv(this._appCid)
  }

  _bindRTCEvent() {
    /**
      * 加入频道结果的回调
      */
    this._rtcClient.on("onJoinChannelResult", (result, channel) => {
      this.dispatchEvent(EventType.JOIN_RESULT, result);
    })

    /**
     * 离开频道结果的回调
     */
    this._rtcClient.on("onLeaveChannelResult", (result) => {
      this.dispatchEvent(EventType.LEAVE_RESULT, result);
    })

    /**
     * 远端用户上线的回调
     */
    this._rtcClient.on("onRemoteUserOnLineNotify", (userid) => {
      let userInfo = this.getUserInfo(userid)
      if (userInfo && userInfo.displayName && userInfo.displayName.indexOf('_老师') > -1) {
        this._teacherUserid = userid
        this.dispatchEvent(EventType.TEACHER_ENTER, userid)
      } else {
        this.dispatchEvent(EventType.STUDENT_ENTER, userid);
      }
    })

    /**
     * 远端用户下线的回调
     */
    this._rtcClient.on("onRemoteUserOffLineNotify", (userid) => {
      console.log("onRemoteUserOffLineNotify")
      if (this._teacherUserid === userid) {
        this._teacherUserid = ""
        this.dispatchEvent(EventType.TEACHER_LEAVE, userid)
      } else {
        this.dispatchEvent(EventType.STUDENT_LEAVE, userid);
      }
    })

    /**
     * 角色切换回调
     */
    this._rtcClient.on("onUpdateRoleNotify", (oldRole, newRole) => {
      if (newRole === AliEngineClientRole.AliEngineClientRoleInteractive) {
        this.dispatchEvent(EventType.TO_INTERACTIVE);
      } else if (newRole === AliEngineClientRole.AliEngineClientRoleLive) {
        this.dispatchEvent(EventType.TO_LIVE);
      }
    })

    /**
     * 音频订阅情况变更的回调
     */
    this._rtcClient.on("onAudioSubscribeStateChanged", (userid, oldState, newState) => {
      if (newState === AliEngineSubscribeState.AliEngineStatsSubscribed) {
        this.dispatchEvent(EventType.SUBSCRIBED_AUDIO, userid);
      } else if (newState === AliEngineSubscribeState.AliEngineStatsNoSubscribe) {
        this.dispatchEvent(EventType.UNSUBSCRIBED_AUDIO, userid);
      }
    })

    /**
     * 视频订阅情况变更的回调
     */
    this._rtcClient.on("onVideoSubscribeStateChanged", (userid, oldState, newState) => {
      if (newState === AliEngineSubscribeState.AliEngineStatsSubscribed) {
        this.dispatchEvent(EventType.SUBSCRIBED_VIDEO, userid);
      } else if (newState === AliEngineSubscribeState.AliEngineStatsNoSubscribe) {
        this.dispatchEvent(EventType.UNSUBSCRIBED_VIDEO, userid);
      }
    })

    /**
     * 屏幕分享流订阅情况变更的回调
     */
    this._rtcClient.on("onScreenShareSubscribeStateChanged", (userid, oldState, newState) => {
      if (newState === AliEngineSubscribeState.AliEngineStatsSubscribed) {
        this.dispatchEvent(EventType.SUBSCRIBED_SCREEN, userid);
      } else if (newState === AliEngineSubscribeState.AliEngineStatsNoSubscribe) {
        this.dispatchEvent(EventType.UNSUBSCRIBED_SCREEN, userid);
      }
    })

    /**
     * 屏幕共享推流结果通知
     */
    this._rtcClient.on("onScreenSharePublishStateChangedWithInfo", (oldState, newState) => {
      if (newState === AliEnginePublishState.AliEngineStatsPublished) {
        this.dispatchEvent(EventType.PUBLISHED_SCREEN);
      } else if (newState === AliEnginePublishState.AliEngineStatsNoPublish) {
        this.dispatchEvent(EventType.UNPUBLISHED_SCREEN);
      }
    })

    this._rtcClient.on("onAudioVolumeCallback", (data) => {
      this.dispatchEvent(EventType.AUDIO_VOLUME, data);
    })

    /**
     * 对端用户停止音频数据发送的通知
     */
    this._rtcClient.on("onUserAudioMuted", (userid, isMuted) => {
      this.dispatchEvent(EventType.USER_AUDIO_MUTE, userid, isMuted);
    })

    /**
     * 对端用户发送视频黑帧数据发送的通知
     */
    this._rtcClient.on("onUserVideoMuted", (userid, isMuted) => {
      this.dispatchEvent(EventType.USER_VIDEO_MUTE, userid, isMuted);
    })

    /**
     * 错误回调
     */
    this._rtcClient.on("onOccurError", (errorCode, msg) => {
      console.warn("onOccurError", errorCode, msg);
      this.dispatchEvent(EventType.ERROR, errorCode, msg);
    })

    /**
     * 被服务器踢出或者频道关闭时回调	
     */
    this._rtcClient.on("onBye", (code) => {
      console.warn("onBye", code);
      this.dispatchEvent(EventType.BYE, code);
    })
  }

  _registerIMEvent() {
    IMSDK.getEventService().register((eventName, eventData) => {
      console.log('== event ==', { eventName, eventData });
      switch (eventName) {
        case EventNameEnum.PaaSConnectionChanged:
          if (eventData === ConnectionStatus.CONN_AUTHED) {
            this.dispatchEvent(EventType.LOGIN_IM_SUCCESS)
          }
          break;
        case EventNameEnum.PaaSMessageAdd:
          this._parseMessage(eventData.message)
          break;
        case EventNameEnum.PaaSConversationGroupChatPeerJoined:
        case EventNameEnum.PaaSConversationGroupChatJoined:
        case EventNameEnum.PaaSConversationGroupChatPeerLeft:
        case EventNameEnum.PaaSConversationGroupChatPeerKicked:
          this.dispatchEvent(EventType.MEMBER_LIST_UPDATE)
          break;
      }
    });
  }

  _parseMessage(message) {
    let {sender, content} = message
    let msg = JSON.parse(content.text.content)
    if(msg && msg.type === AIMMessageType.Common_Message) {
      this.dispatchEvent(EventType.TEXT_MESSAGE_ADD, {
        userid: sender,
        isSelf: sender === this._userid,
        isTeacher: msg.isTeacher,
        displayName: msg.displayName,
        message: msg.message
      })
    }else if(msg && msg.type === AIMMessageType.Signalling_Message) {
      if("handUp" in msg) {
        // 学生举手消息给老师
        if(this._isTeacher && !msg.isTeacher) {
          this.dispatchEvent(EventType.STUDENT_HAND_UP, {
            userid: sender,
            displayName: msg.displayName,
            handUp: msg.handUp
          })
        }
      }else if ("muteMic" in msg) {
        // 教师要求某学生静音
        if(msg.uid === this._userid && msg.isTeacher) {
          this.dispatchEvent(EventType.TEACHER_CONTROL_MIC, msg.muteMic)
        }
      }else if ("muteCamera" in msg) {
        // 教师要求学生关闭摄像头
        if(msg.uid === this._userid && msg.isTeacher) {
          this.dispatchEvent(EventType.TEACHER_CONTROL_CAMERA, msg.muteCamera)
        }
      }else if ("muteAllMic" in msg) {
        // 教师要求所有学生静音
        this.dispatchEvent(EventType.TEACHER_CONTROL_MIC, msg.muteAllMic)
      }else if ("backHandUp" in msg) {
        // 教师反馈是否同意学生上麦
        if(msg.uid === this._userid && msg.isTeacher) {
          this.dispatchEvent(EventType.HAND_UP_RESULT, msg.backHandUp)
        } 
      }
    }
  }
}

export default AliRTCElectronInterrativeEngine