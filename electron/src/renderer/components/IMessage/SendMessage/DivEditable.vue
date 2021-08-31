<template>
  <div
    class="div-editable"
    ref="editable"
    contenteditable="true"
    v-html="innerText"
    @keypress.enter="sendMsg"
    @input="changeText"
    @focus="isChange = false"
    @blur="isChange = true"></div>
</template>

<script>
  export default {
    name: 'DivEditable',
    props: {
      value: {
        type: String,
        default: ''
      }
    },
    data() {
      return {
        innerText: this.value,
        isChange: true
      }
    },
    watch: {
      value() {
        if (this.isChange) {
          this.innerText = this.value
          this.$el.innerHTML = this.innerText
          this.$refs.editable.focus()
        }
      }
    },
    methods: {
      changeText() {
        this.$emit('input', this.$el.innerHTML)
      },
      sendMsg(event) {
        event.preventDefault()
        this.$refs.editable.blur()
        this.$emit('sendMsg')
      }
    }
  }
</script>


<style lang="scss">
  .div-editable{
    width: 100%;
    height: 100%;
    padding: vh(10);
    line-height: vh(20);
    background: #f7f7f7;
    border-radius: 5px;
    overflow-y: auto;
    word-break: break-all;
    outline: none;
    user-select: text;
    white-space: pre-wrap;
    text-align: left;
    -webkit-user-modify: read-write-plaintext-only;
    &[contenteditable=true]{
      &:empty:before {
        content: "说点什么吧～";
        display: block;
        color: gray;
      }
    }
  }
</style>