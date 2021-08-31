<template>
  <div class="remote-view-list" v-show="isShow">
    <remote-btn
      direction="left"
      :disabled="leftDisabled"
      @moveBtn="moveBtn"
    ></remote-btn>
    <div class="remote-view-scroll" ref="remoteScroll">
      <div class="remote-view-scroll-inner">
        <remote-view
          v-if="!isTeacher"
          v-show="isInterActive"
          :userid="userid"
          :displayName="displayName"
          :isSelf="true"
        ></remote-view>
        <remote-view
          v-for="user in userList"
          :key="user.userid"
          :userid="user.userid"
          :displayName="user.displayName"
          :subScribedCameraMaster="user.subScribedCameraMaster"
        ></remote-view>
      </div>
    </div>
    <remote-btn
      direction="right"
      :disabled="rightDisabled"
      @moveBtn="moveBtn"
    ></remote-btn>
  </div>
</template>

<script>
import RemoteView from "./RemoteView/RemoteView.vue"
import RemoteBtn from "./RemoteBtn/RemoteBtn.vue"
import { mapState } from 'vuex'
export default {
  components: {
    RemoteBtn,
    RemoteView
  },
  data() {
    return {
      userid: this.$store.state.rtc.userid,
      displayName: this.$store.state.rtc.displayName,
      leftDisabled: true,
      rightDisabled: true
    }
  },
  mounted(){
    this.$refs.remoteScroll.addEventListener("scroll", this.onScroll)
    this.onScroll()
  },
  beforeDestroy() {

  },
  computed: {
    ...mapState({
      userList: (state) => state.rtc.userList,
      isTeacher: (state) => state.rtc.isTeacher,
      isInterActive: (state) => state.rtc.isInterActive,
    }),
    isShow() {
      return (!this.isTeacher && this.isInterActive) || this.userList.length > 0
    }
  },
  methods: {
    moveBtn(type) {
      if(type === "left") {
        this.$refs.remoteScroll.scrollBy({
          left: -50,
          top: 0,
          behavior:"smooth"
        })
      }else if(type === "right") {
        this.$refs.remoteScroll.scrollBy({
          left: 50,
          top: 0,
          behavior:"smooth"
        })
      }
    },
    onScroll() {
      let remoteScroll = this.$refs.remoteScroll
      this.leftDisabled = remoteScroll.scrollLeft === 0
      this.rightDisabled = remoteScroll.scrollLeft + remoteScroll.clientWidth === remoteScroll.scrollWidth
    }
  },
  watch: {
    userList() {
      this.onScroll()
    }
  }
}
</script>

<style lang="scss" scoped>
.remote-view-list{
  padding: 0 vw(16);
  display: flex;
  .remote-view-scroll{
    overflow-x: auto;
    width: 0;
    flex: 1;
    white-space: nowrap;
    overflow-y: hidden;
    &::-webkit-scrollbar {
      display: none;
    }
    .remote-view-scroll-inner {
      // 解决inline-block 间距问题
      font-size: 0;
    }
  }
}
</style>