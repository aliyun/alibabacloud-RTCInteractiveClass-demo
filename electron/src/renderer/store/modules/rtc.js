export default {
  state: {
    channel: "",// 教室号
    displayName: "", // 用户名
    userid: "",
    authInfo: null, // 鉴权信息
    isTeacher: true, // 是否是老师
    isEverInterActive: false, // 自己是否上过麦（用于统计结束课程时连麦人数）
    isInterActive: false, // 学生是否上麦
    isPreview: false, // 是否开启预览
    isPublishScreen: false, //屏幕分享
    isWaitingBackHandUp: false, // 学生是否等待举手返回
    isMuteLocalMic: false, // 是否本地mute麦克风
    isMuteLocalCamera: false, // 是否本地mute摄像头
    muteList: {}, // mute列表
    userList: [], // 用户列表（不包含老师）
    messageList: [], // 普通消息列表
    linkList: [], // 连麦请求列表
    memberList: [], // 成员列表
    teacherInfo: {}, // 老师信息
    classStartTime: 0, // 课程开始时间
    startScreenShareTime: 0, // 屏幕共享时间
    classFinished: false, // 课程结束
    speakerList: [], // 当前说话人列表
    maxOnlineList: new Set(), // 累计在线列表 
    maxMeetingList: new Set() // 累计连麦列表（只统计上麦 不含自己和老师）
  },
  mutations: {
    /**
     * 更新state值
     * @param {*} state 
     * @param {*} data 
     */
    SET_RTC_DATA: (state, data) => {
      Object.keys(data).forEach(function (key) {
        state[key] = data[key]
      })
    },
    /**
     * 增加用户
     */
    ADD_USER: (state, userInfo) => {
      console.log('增加用户')
      state.maxMeetingList.add(userInfo.userid)
      let userList = JSON.parse(JSON.stringify(state.userList));
      if(userList.getIndexByProprety(userInfo.userid, "userid") == -1){
        userList.push(userInfo)
        state.userList = userList
      }
    },
    /**
     * 更新用户
     */
    UPDATE_USER: (state, userInfo) => {
      console.log('更新用户')
      let userList = JSON.parse(JSON.stringify(state.userList));
      if(userInfo){
        userList.distinctPush(userInfo, "userid")
        state.userList = userList
      }
    },
    /**
     * 移除用户
     */
    REMOVE_USER: (state, userid) => {
      console.log('移除用户')
      let userList = JSON.parse(JSON.stringify(state.userList));
      let index = userList.getIndexByProprety(userid,"userid")
      if(index !== -1){
        userList.splice(index, 1)
        state.userList = userList
      }
    },
    /**
     * 更新静音列表
     * @param {*} state 
     * @param {*} payload 
     */
    UPDATE_MUTE_STATE: (state, payload) => {
      let { userid, label, isMuted } = payload
      let muteList = JSON.parse(JSON.stringify(state.muteList));
      if(muteList[userid]) {
        muteList[userid][label] = isMuted
      }else {
        muteList[userid] = {
          [label]: isMuted
        }
      }
      state.muteList = muteList
    },
    /**
     * 增加普通文本信息
     * @param {*} state 
     * @param {*} payload 
     */
    ADD_MESSAGE: (state, messageInfo) => {
      let messageList = JSON.parse(JSON.stringify(state.messageList));
      messageList.push(messageInfo)
      state.messageList = messageList
    },
    /**
     * 增加申请连麦列表信息
     * @param {*} state 
     * @param {*} payload 
     */
    ADD_LINK: (state, linkInfo) => {
      let linkList = JSON.parse(JSON.stringify(state.linkList));
      linkList.distinctPush(linkInfo, "userid")
      state.linkList = linkList
    },
    /**
     * 删除申请连麦列表信息
     * @param {*} state 
     * @param {*} userid 
     */
    DELETE_LINK: (state, userid) => {
      let linkList = JSON.parse(JSON.stringify(state.linkList));
      let index = linkList.getIndexByProprety(userid, "userid")
      if(index !== -1){
        linkList.splice(index, 1)
        state.linkList = linkList
      }
    },
    /**
     * 更新成员列表
     * @param {*} state 
     * @param {*} list 
     */
    UPDATE_MEMBER_LIST: (state, list) => {
      for(let i = 0; i < list.length; i++) {
        state.maxOnlineList.add(list[i].userid)
      }
      state.memberList = list
    }
  }
}