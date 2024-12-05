<script setup lang="ts">
import { dora } from '@/assets/dora'
</script>

<template>
  <main>
    <p>sse status: {{ dora.ws.status.value }}</p>
    <button @click="dora.ws.open()">connect</button>
    <button @click="dora.ws.close()">disconnect</button>

    <div v-if="dora.ws.status.value === 'OPEN'" >
      <p>we are connected</p>
    </div>

    <div v-else>
      <p v-if="dora.ws.status.value === 'CONNECTING'">trying to reconnect<progress /></p>
    </div>

  </main>
</template>