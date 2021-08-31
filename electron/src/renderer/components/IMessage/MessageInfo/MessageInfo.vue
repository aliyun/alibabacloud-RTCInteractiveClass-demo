<template>
  <div class="message-info" ref="info">
    <div class="message-info-inner">
      <div 
        v-for="(info, index) in messageList"
        :key="index"
      >
        <message-sender
          :isSelf="info.isSelf"
          :isTeacher="info.isTeacher"
          :displayName="info.displayName"
        ></message-sender>
        <message-bubble
          :isSelf="info.isSelf"
          :message="info.message"
        ></message-bubble>
      </div>
    </div>
  </div>
</template>

<script>
import MessageSender from './MessageSender.vue'
import MessageBubble from './MessageBubble.vue'
import {mapState} from 'vuex'
export default {
  components: {
    MessageSender,
    MessageBubble
  },
  computed: {
    ...mapState({
      messageList: (state)=> state.rtc.messageList
    })
  },
  watch: {
    messageList() {
      this.$nextTick(()=> {
        this.$refs.info.scrollTo({
          top: this.$refs.info.scrollHeight,
          behavior:"smooth"
        })
      })
    }
  }
}
</script>

<style lang="scss" scoped>
  .message-info {
    height: vh(393);
    overflow-y: auto;
    &::-webkit-scrollbar{
      display: none;
    }
  }
</style>