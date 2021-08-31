<template>
  <el-dialog
    title="在线列表"
    :visible.sync="showOnlineList"
    :append-to-body="true"
    :before-close="close"
    :modal="false"
    custom-class="myDialog"
    width="40%"
    center>
    <div class="list-info">
      <span>
        当前在线人数：{{memberList.length}} 人
      </span>
      <span>
        连麦学生：{{ interActiveStudentNum }} 人
      </span>
    </div>
    <div class="online-list">
      <div class="online-info"
        v-for="member in memberList"
        :key="member.userid"
      >
        <div class="online-name">{{computedMemberName(member)}}</div>
        <div class="online-label" 
          :class="{ 'label-self': member.isSelf, 'label-teacher': member.isTeacher }"
        >{{member.isSelf ? "自己" : member.isTeacher ? "老师" : ""}}</div>
      </div>
    </div>
  </el-dialog>
</template>

<script>
import {mapState} from "vuex"
export default {
  props: {
    showOnlineList: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      userid: this.$store.state.rtc.userid,
    }
  },
  computed: {
    ...mapState({
      memberList: (state) => state.rtc.memberList,
      userList: (state) => state.rtc.userList,
      isTeacher: (state) => state.rtc.isTeacher,
      isInterActive: (state) => state.rtc.isInterActive,
      teacherInfo: (state) => state.rtc.teacherInfo
    }),
    interActiveStudentNum() {
      return !this.isTeacher && this.isInterActive ? this.userList.length + 1 : this.userList.length
    },
    computedMemberName() {
      return (member)=> {
        if(member.isTeacher) {
          if(this.isTeacher) {
            return this.$store.state.rtc.displayName
          }else {
            return this.teacherInfo.displayName
          }
        }
        return member.displayName
      }
    }
  },
  methods: {
    close() {
      this.$emit('close')
    }
  },
}
</script>

<style lang="scss" scoped>
  @import url("./theme-default/basic.scss");
  .list-info {
    display: flex;
    padding: 0 vw(20) vh(20);
    >span{
      flex: 1;
      color: #333333;
      font-size: vh(12);
    }
  }
  .online-list {
    height: vh(396);
    overflow: auto;
    .online-info {
      &:hover {
        background: #FAFAFA;
      }
      cursor: pointer;
      height: vh(44);
      display: flex;
      align-items: center;
      line-height: vh(44);
      padding: 0 vw(24);
      .online-name {
        font-size: vh(12);
        color: #333333;
        margin-right: vw(8);
      }
      .online-label {
        height: vh(20);
        line-height: vh(20);
        padding: 0 vw(4);
        font-size: vh(12);
        border-radius: 4px;
      }
      .online-label.label-teacher {
        background: rgba(232,3,32,0.1);
        color: rgba(232,3,32,1);
      }
      .online-label.label-self {
        background: #EAEEFF;
        color: #365AFF;
      }
      .online-label:empty {
        display: none;
      }
    }
  }
</style>