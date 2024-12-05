<script setup lang="ts">
import { useFetch } from '@vueuse/core';

type UseFetchReturn = ReturnType<typeof useFetch>;

const props = defineProps({
  myFetch: {
    type: Object as () => UseFetchReturn,
    required: true,
  },
  extraFunctions: {
    type: Function as () => void,
    required: false,
    default: () => (() => {}),
  },
});

async function execute() {
  await props.myFetch.execute();
  props.extraFunctions;
}
</script>

<template>
  <span v-if="props.myFetch.isFetching.value" aria-busy="true"></span>
  <a v-else href="#" @click.prevent="execute">
    <span v-if="props.myFetch.statusCode.value === 200">&#10226;</span>
    <span v-else style="color: firebrick;" data-tooltip="request timeout">&#10226;</span>
  </a>
</template>

<style scoped>
span {
  cursor: pointer;
  user-select: none;
    /* font-size: 1.5rem; */
}
</style>