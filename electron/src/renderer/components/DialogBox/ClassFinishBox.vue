<template>
  <el-dialog
    title=""
    :visible.sync="showLeaveBox"
    :append-to-body="true"
    :before-close="close"
    :modal="false"
    custom-class="myDialog"
    width="500px"
    center>
    <div class="class-title">
      <p class="info">课程已结束</p>
      <p class="describe">教师：{{teacherName}}</p>
    </div>
    <div class="class-info">
      <div>
        <div>
          <p class="info">{{formatStartTime}}</p>
          <p class="describe">开始时间</p>
        </div>
        <div>
          <p class="info">{{duration}}</p>
          <p class="describe">课程时长</p>
        </div>
      </div>
      <div>
        <div>
          <p class="info">{{maxOnlineList.size}}</p>
          <p class="describe">在线人数</p>
        </div>
        <div>
          <p class="info">{{interActiveStudentNum}}</p>
          <p class="describe">连麦人数</p>
        </div>
      </div>
    </div>
  </el-dialog>
</template>

<script>
import { mapState } from 'vuex'
export default {
  props: {
    showLeaveBox: {
      type: Boolean,
      default: true
    }
  },
  data() {
    return {
      classStartTime: this.$store.state.rtc.classStartTime,
      duration: 0,
    }
  },
  mounted() {
    this.getDuration()
  },
  computed: {
    ...mapState({
      teacherInfo: (state) => state.rtc.teacherInfo,
      isTeacher: (state) => state.rtc.isTeacher,
      displayName: (state) => state.rtc.displayName,
      maxOnlineList: (state) => state.rtc.maxOnlineList,
      maxMeetingList: (state) => state.rtc.maxMeetingList,
      isEverInterActive: (state) => state.rtc.isEverInterActive,
    }),
    interActiveStudentNum() {
      return !this.isTeacher && this.isEverInterActive ? this.maxMeetingList.size + 1 : this.maxMeetingList.size
    },
    formatStartTime() {
      let date = new Date(this.classStartTime)
      let month = (date.getMonth() + 1).toString().padStart(2,'0')
      let day = date.getDate().toString().padStart(2,'0')
      let hour = date.getHours().toString().padStart(2,'0')
      let mins = date.getMinutes().toString().padStart(2,'0')
      return `${month}-${day} ${hour}:${mins}`
    },
    teacherName() {
      if(!this.isTeacher) {
        return this.teacherInfo.displayName || ""
      }else {
        return this.displayName
      }
    }
  },
  methods: {
    getDuration() {
      let mss = Date.now() - this.classStartTime
      let hours = parseInt(mss / (1000 * 60 * 60)).toString().padStart(2,'0');
      let minutes = parseInt((mss % (1000 * 60 * 60)) / (1000 * 60)).toString().padStart(2,'0');
      let seconds = parseInt((mss % (1000 * 60)) / 1000).toString().padStart(2,'0');
      this.duration = hours + ":" + minutes + ":" + seconds
    },
    close() {
      this.$emit('close')
    }
  }
}
</script>

<style lang="scss" scoped>
  @import url("./theme-default/basic.scss");
  .info {
    color: #333333;
  }
  .describe {
    color: #666666;
  }
  .class-title{
    margin: vh(40) 0  vh(40);
    text-align: center;
    .info {
      font-size: vh(24);
      line-height: vh(34);
    }
    .describe {
      font-size: vh(20);
      line-height: vh(26);
    }
  }
  .class-info {
    padding-bottom: vh(50);
    >div {
      display: flex;
      margin-bottom: vh(24);
      >div {
        flex: 1;
        text-align: center;
        .info{
          font-size: vh(18);
          line-height: vh(26);
        }
        .describe {
          font-size: vh(16);
          line-height: vh(22);
        }
      }
    }
  }
</style>