<template>
  <div class="hheader">
    {{$store.state.data.role==0?$store.state.data.userName+"的课堂 | ":''}}
    <span
      id="classNum"
    >{{$store.state.data.classNum}}</span>
    <i class="iconfont icon-fuzhi" @click="copy"></i>
    <span class="classState" v-if="$store.state.data.role==0&&$store.state.data.isPublish">上课中</span>
  </div>
</template>
<script>
import Util from "../core/utils/utils";
import { Message } from "element-ui";
export default {
  data() {
    return {};
  },
  methods: {
    /**
     * 拷贝房间号
     */
    copy() {
      if (Util.hCopy("classNum")) {
        Message.info("复制成功");
      } else {
        Message.error("复制失败");
      }
    }
  }
};
</script>

<style lang="scss">
.hheader {
  height: vh(40);
  line-height: vh(40);
  width: vw(1024);
  background-color: #000000;
  text-align: center;
  color: white;
  font-size: vh(22);
  .icon-fuzhi {
    font-size: vh(25);
    cursor: pointer;
    margin-left: vw(5);
  }
  .classState {
    margin-left: vw(20);
    height: vh(26);
    padding:0 vw(10);
    background: #d2e1ff;
    border-radius: vh(24);
    background-color: #d2e1ff;
    font-size: vh(14);
    color: #013ebe;
    vertical-align: bottom;
  }
}
</style>