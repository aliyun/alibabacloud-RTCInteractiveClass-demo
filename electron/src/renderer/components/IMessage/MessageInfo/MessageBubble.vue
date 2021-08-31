<template>
  <div class="bubble-wrapper clearfix">
    <div class="bubble" :class="{'right': isSelf, 'left': !isSelf}">
      <div class="message-arrow"></div>
      <div class="message-content">
        {{message}}
      </div>
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
    message: {
      type: [String, Number]
    }
  },
}
</script>

<style lang="scss" scoped>
  .bubble-wrapper {
    margin-top: vh(6);
    width: vw(182);
    padding: 0 vw(12);
    .bubble {
      position: relative;
      max-width: vw(158);
      .message-arrow{
        width: 0px;
        height: 0px;
        border: 5px solid transparent;
        position: absolute;
        top: -10px;
      }
      .message-content{
        min-width: vw(25);
        padding: vh(5) vw(8);
        border-radius: 4px;
        word-break: break-all;
        font-size: vh(12);
        line-height: vh(24);
      }
    }
    .bubble.left{
      .message-arrow {
        left: vw(8);
        border-bottom-color: #e3e3e3;
      }
      .message-arrow:before {
        content: "";
        display: block;
        width: 0px;
        height: 0px;
        border: 5px solid transparent;
        border-bottom-color: #ffffff;
        position: absolute;
        top: -4px;
        left: -5px;
      }
      .message-content{
        display: inline-block;
        border: 1px solid #ececec;
        background: #ffffff;
        color: #333333;
      }
    }
    .bubble.right{
      float: right;
      .message-arrow {
        right: vw(8);
        border-bottom-color: #365AFF;
      }
      .message-content{
        background: #365AFF;
        color: #ffffff;
      }
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