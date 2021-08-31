<template>
  <div class="meeting-header">
    {{classInfo}}教室码：<span id="channel">{{$store.state.rtc.channel}}</span>
    <i class="iconfont icon-fuzhi" @click="copy"></i>
    <span class="classState">上课中</span>
  </div>
</template>

<script>
import Util from "../../core/utils/utils";
import {mapState} from 'vuex'
export default {
  data() {
    return {};
  },
  computed: {
    ...mapState({
      classInfo: function(state) {
        if(state.rtc.isTeacher) {
          return state.rtc.displayName + "的课堂 | "
        }else {
          if(state.rtc.teacherInfo) {
            return state.rtc.teacherInfo.displayName + "的课堂 | "
          }else {
            return ""
          }
        }
      }
    })
    
  },
  methods: {
    /**
     * 拷贝房间号
     */
    copy() {
      if (Util.hCopy("channel")) {
        this.$message({
          type: "info",
          customClass: "my-message-info",
          message: "复制成功",
          offset: 150
        });
      } else {
        this.$message({
          type: "error",
          iconClass: "el-icon-warning el-message__icon",
          customClass: "my-message-error",
          message: "复制失败",
          offset: 150
        });
      }
    }
  }
};
</script>

<style lang="scss">
.meeting-header {
  position: relative;
  height: vh(40);
  line-height: vh(40);
  width: vw(900);
  background-color: #ffffff;
  text-align: center;
  color: #333333;
  font-size: vh(16);
  box-shadow: 0 2px 4px 0 rgba(0,0,0,0.1);
  .icon-fuzhi {
    font-size: vh(17);
    color: #979797;
    cursor: pointer;
    margin-left: vw(5);
  }
  .classState {
    margin-left: vw(20);
    height: vh(28);
    padding:0 vw(10);
    border-radius: vh(4);
    background-color: #EAEEFF;
    font-size: vh(14);
    color: #365aff;
    vertical-align: bottom;
  }
}
</style>