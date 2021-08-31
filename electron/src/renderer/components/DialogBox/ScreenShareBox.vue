<template>
  <el-dialog
    title="共享屏幕"
    :visible.sync="screenDialogVisible"
    :append-to-body="true"
    :before-close="close"
    :modal="false"
    :show-close="false"
    custom-class="myDialog screenShareDialog"
    center>
    <div class="screen-list">
      <div class="screen-desktop">
        <div class="screen-info"
          v-for="item in desktopList"
          :key="item.sourceId"
          @click="checkScreenShare(0, item.sourceId)"
        >
          <div 
            class="screen-img"
            :class="{'checkedStyle': item.sourceId === sourceId}"
          >
            <img :src="item.src" alt="">
          </div>
          <div class="screen-title" :title="item.sourceTitle">{{item.sourceTitle}}</div>
        </div>
      </div>
      <div class="screen-window">
        <div class="screen-info"
          v-for="item in windowList"
          :key="item.sourceId"
          @click="checkScreenShare(1, item.sourceId)"
        >
          <div 
            class="screen-img"
            :class="{'checkedStyle': item.sourceId === sourceId}"
          >
            <img :src="item.src" alt="">
          </div>
          <div class="screen-title" :title="item.sourceTitle">{{item.sourceTitle}}</div>
        </div>
      </div>
    </div>
    <div class="btn-list">
      <hui-button size="small" plain type="primary" @click="close">取消</hui-button>
      <hui-button size="small" type="primary" :disabled="!sourceId" @click="startScreenShare">确定</hui-button>
    </div>
  </el-dialog>
</template>

<script>
import AliRTCElectronInterrativeEngine from '../../core/client/alirtc-electron-interrative-engine'
import { AliEngineScreenShareType } from "../../core/data/main"
export default {
  props: {
    screenDialogVisible: {
      type: Boolean,
      default: true
    }
  },
  data() {
    return {
      desktopList: [],
      windowList: [],
      type: 0,
      sourceId: ""
    }
  },
  created() {
    AliRTCElectronInterrativeEngine.instance.getScreenShareSourceInfo(AliEngineScreenShareType.AliEngineScreenShareDesktop).then((desktopList)=> {
      if(desktopList instanceof Array) {
        desktopList.forEach(item => {
          if(item.thumbnail) {
            item.src = item.thumbnail.toDataURL()
          }
        })
      }
      this.desktopList = desktopList
    })
    AliRTCElectronInterrativeEngine.instance.getScreenShareSourceInfo(AliEngineScreenShareType.AliEngineScreenShareWindow).then((windowList)=> {
      if(windowList instanceof Array) {
        windowList.forEach(item => {
          if(item.thumbnail) {
            item.src = item.thumbnail.toDataURL()
          }
        })
      }
      this.windowList = windowList
    })
  },
  methods: {
    checkScreenShare(type, sourceId) {
      this.type = type
      this.sourceId = sourceId
    },
    close() {
      this.$emit('close')
    },
    startScreenShare() {
      let res = AliRTCElectronInterrativeEngine.instance.startScreenShare(this.type, this.sourceId)
      this.$emit('close')
    }
  },
  computed: {
    
  }
}
</script>

<style lang="scss" scoped>
  @import url("./theme-default/basic.scss");
   /deep/ .screenShareDialog {
    width: vw(680);
    margin-top: vh(43) !important;
  }
  .screen-list {
    height: vh(412);
    overflow: auto;
    >div{
      padding: 0 vw(8) 0 vw(24);
      display: flex;
      flex-wrap: wrap;
    }
    .screen-info {
      width: vw(143);
      margin-right: vw(16);
      cursor: pointer;
      .screen-img {
        border-radius: 3px;
        height: vh(90);
        width: 100%;
        padding: vh(8) vw(12);
        border: 1px solid #EAEAEA;
        background: #F7F7F7;
        margin-bottom: vh(8);
        img {
          width: 100%;
          height: 100%;
        }
      }
      .checkedStyle {
        border: 1px solid #365AFF;
      }
      .screen-title {
        padding: 0 vw(4);
        width: 100%;
        text-align: center;
        margin-bottom: vh(8);
        overflow: hidden;
        white-space: nowrap;
        text-overflow: ellipsis
      }
    }
  }
  .btn-list {
    height: vh(60);
    padding-right: vw(24);
    display: flex;
    align-items: center;
    justify-content: flex-end;
    button {
      margin-left: vw(8);
    }
    
  }
</style>