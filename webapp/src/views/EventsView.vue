<script setup lang="ts">
import { dora } from '@/assets/dora'
</script>

<template>
  <p>sse status: {{ dora.events.status.value }}</p>
    <button @click="dora.events.open">connect</button>
    <button @click="dora.events.close">disconnect</button>

    <div v-if="dora.events.status.value === 'OPEN'" >
      <p>we are connected</p>
    </div>

    <div v-else>
      <p v-if="dora.events.status.value === 'CONNECTING'">trying to reconnect<progress /></p>
    </div>

    <p>{{ dora.events.event.value }}</p>
    <p>{{ dora.events.data }}</p>

</template>