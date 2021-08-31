<template>
  <div class="slider">
    <i 
      class="slider-btn" 
      @mousedown="mouseHandler"
      @mouseup="mouseHandler"
      @mouseenter="mouseHandler"
      @mouseout="mouseHandler"
      :class="direction"
      :disabled="disabled"
      :style="sliderBtnStyle | bgImageFilter"
    ></i>
  </div>
</template>

<script>
export default {
  props:{
    direction: {
      type: String,
      default: "left"
    },
    disabled: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      isActive: false,
      sliderLeftActiveUrl: require("../../../assets/img/slider-left-active.png"),
      sliderLeftDefaultUrl: require("../../../assets/img/slider-left-default.png"),
      sliderLeftDisabledUrl: require("../../../assets/img/slider-left-disabled.png"),
      sliderRightActiveUrl: require("../../../assets/img/slider-right-active.png"),
      sliderRightDefaultUrl: require("../../../assets/img/slider-right-default.png"),
      sliderRightDisabledUrl: require("../../../assets/img/slider-right-disabled.png"),
      timer: null
    }
  },
  computed: {
    sliderBtnStyle() {
      let silderUrl
      if(this.disabled) {
        if(this.direction === "left") {
          silderUrl = this.sliderLeftDisabledUrl
        }else{
          silderUrl = this.sliderRightDisabledUrl
        }
      }else {
        if(this.direction === "left") {
          silderUrl = this.isActive ? this.sliderLeftActiveUrl : this.sliderLeftDefaultUrl
        }else {
          silderUrl = this.isActive ? this.sliderRightActiveUrl : this.sliderRightDefaultUrl
        }
      }
      return silderUrl
    }
  },
  methods: {
    mouseHandler(e) {
      switch (e.type) {
        case "mouseenter":
          this.isActive = true
          break;
        case "mouseout":
          this.isActive = false
        case "mouseup": 
          clearInterval(this.timer)
          this.timer = null
          break
        case "mousedown": 
          this.$emit("moveBtn", this.direction)
          this.timer = setInterval(()=> {
            this.$emit("moveBtn", this.direction)
          },100)
        break
      }
    }
  }
}
</script>

<style scoped lang="scss">
  .slider{
    height: vh(81);
    margin: vh(16) 0;
    .slider-btn{
      display: block;
      cursor: pointer;
      width: vh(18);
      height: vh(18);
      margin-top: vh(29);
      background-size: vh(18) vh(18);
      background-repeat: no-repeat;
      background-position: center center;
    }
    .slider-btn[disabled]{
      cursor: not-allowed;
    }
    .slider-btn.left{
      margin-right: vw(8);
    }
    .slider-btn.right{
      margin-left: vw(8);
    }
  }
</style>