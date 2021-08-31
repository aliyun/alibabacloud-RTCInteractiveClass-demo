<template>
  <div class="i-message">
    <div class="i-message-title">实时互动</div>
    <message-info />
    <send-message />
  </div>
</template>

<script>
import MessageInfo from "./MessageInfo/MessageInfo.vue"
import SendMessage from "./SendMessage/SendMessage.vue"
export default {
  components: {
    MessageInfo,
    SendMessage
  },
  data() {
    return {}
  }
}
</script>

<style lang="scss" scoped>
  .i-message{
    position: relative;
    height: vh(553);
    .i-message-title {
      font-size: vh(14);
      height: vh(35);
      text-align: center;
      line-height: vh(36);
      border-bottom: 1px solid #EDEDED;
    }
  }
</style>