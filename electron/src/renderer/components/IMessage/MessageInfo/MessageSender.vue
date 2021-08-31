<template>
  <div class="sender-wrapper clearfix">
    <div class="sender" :class="{'right': isSelf}">
      <div class="sender-username">{{displayName}}</div>
      <div class="sender-label" :class="senderClass" v-if="senderLabel">{{senderLabel}}</div>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    isSelf: {
      type: Boolean,
      default: true
    },
    isTeacher: {
      type: Boolean,
      default: true
    },
    displayName: {
      type: String
    }
  },
  computed: {
    senderClass() {
      return this.isSelf ? "self" : (this.isTeacher ? "teacher" : "")
    },
    senderLabel() {
      return this.isSelf ? "自己" : (this.isTeacher ? "教师" : "")
    }
  }
}
</script>

<style lang="scss" scoped>
  .sender-wrapper {
    width: vw(182);
    padding: 0 vw(12);
    margin-top: vh(10);
    .sender {
      max-width: vw(158);
      display: flex;
      .sender-username {
        font-size: vh(10);
        line-height: vh(20);
        margin-right: vw(4);
      }
      .sender-label {
        height: vh(18);
        font-size: vh(10);
        text-align: center;
        line-height: vh(20);
        padding: 0 vw(4);
        border-radius: 3px;
      }
      .sender-label.self {
        background: #EAEEFF;
        color: #365AFF;
      }
      .sender-label.teacher {
        background: #FFEDF0;
        color: #E80320;
      }
    }
    .sender.right {
      float: right;
    }
  }
  .clearfix:after {
    content: '\20';
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
    overflow: hidden;
  }
</style>