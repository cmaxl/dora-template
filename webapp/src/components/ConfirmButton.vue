<script setup lang="ts">
import { ref } from 'vue'

const props = defineProps({
  onConfirm: Function,
  buttonText: {
    type: String,
    default: 'Confirm',
  },
})

const confirm = ref(false)

const handleConfirm = () => {
  if (confirm.value) {
    if (props.onConfirm) {
      props.onConfirm();
    }
  } else {
    confirm.value = true
  }
}
</script>

<template>
  <button class="secondary" @click="handleConfirm">
    <span v-if="confirm">Are you sure?</span>
    <span v-else>{{ buttonText }}</span>
  </button>
</template>
