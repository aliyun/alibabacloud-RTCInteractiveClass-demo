<template>
  <transition>
    <div class="hui-message-box">
      <div class="hui-message-box__close">
        <div v-if="closeIcon" @click="close">
          x
        </div>
      </div>
      <div class="hui-message-box-divider"></div>
      <div class="hui-message-box__header">
        <div class="hui-message-box__title">
          {{title}}
        </div>
      </div>
      <div class="hui-message-box__content">
        {{message}}
      </div>
      <div class="hui-message-box__btns">
        <hui-button size="medium" v-if="type!='alert'" plain type="primary" @click="handleAction('cancel')">{{cancelButtonText?cancelButtonText:'取消'}}</hui-button>
        <hui-button size="medium" type="primary" @click="handleAction('confirm')">{{confirmButtonText?confirmButtonText:'确定'}}</hui-button>&nbsp;
      </div>
    </div>
  </transition>
</template>

<script  >
export default {
  data() {
    return {
      type:"confirm",// confirm,alert
      message: "", //需要提示用户的内容
      title:"",
      closeIcon: false,
      confirmButtonText:"",
      cancelButtonText:""
    };
  },
  methods: {
    handleAction(action){
        this.close();
        this.$emit("results",action);
    },
    //
    close() {
      this.$el.remove();
    }
  },
  mounted() {}
};
</script>
<style lang="scss">
@import "../../theme-default/messagebox.scss";
</style>