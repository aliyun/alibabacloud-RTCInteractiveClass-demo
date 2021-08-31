<template>
  <el-dialog
    title="连麦消息"
    :visible.sync="showLinkMicMessage"
    :before-close="close"
    :append-to-body="true"
    :modal="false"
    custom-class="myDialog"
    width="40%"
    center>
    <div class="link-list">
      <div class="link-info" 
        v-for="linkInfo in linkList"
        :key="linkInfo.userid"
      >
        <div class="link-name">{{linkInfo.displayName}}</div>
        <div class="link-handler">
          <hui-button size="small" type="primary" @click="acceptHandUp(linkInfo.userid)">同意</hui-button>
          <hui-button size="small" type="danger" @click="rejectHandUp(linkInfo.userid)">拒绝</hui-button>
        </div>
      </div>
    </div>
  </el-dialog>
</template>

<script>
import {mapState} from 'vuex'
import AliRTCElectronInterrativeEngine from '../../core/client/alirtc-electron-interrative-engine'
export default {
  props: {
    showLinkMicMessage: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {}
  },
  computed: {
    ...mapState({
      linkList: (state) => state.rtc.linkList
    })
  },
  methods: {
    close() {
      this.$emit('close')
    },
    /**
     * 同意学生举手
     */
    acceptHandUp(userid) {
      AliRTCElectronInterrativeEngine.instance.backHandUp(userid, true)
      this.$store.commit("DELETE_LINK", userid)
    },
    /**
     * 拒绝学生举手
     */
    rejectHandUp(userid) {
      AliRTCElectronInterrativeEngine.instance.backHandUp(userid, false)
      this.$store.commit("DELETE_LINK", userid)
    }
  }
}
</script>

<style lang="scss" scoped>
  @import url("./theme-default/basic.scss");
  .link-list {
    height: vh(424);
    overflow: auto;
    .link-info {
      &:hover {
        background: #FAFAFA;
      }
      cursor: pointer;
      height: vh(44);
      display: flex;
      justify-content: space-between;
      line-height: vh(44);
      padding: 0 vw(24);
      .link-name {
        font-size: vh(12);
        color: #333333;
        margin-right: vw(8);
      }
    }
  }
</style>