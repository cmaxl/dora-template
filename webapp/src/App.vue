<script setup lang="ts">
import { ref } from 'vue';
import { RouterLink, RouterView } from 'vue-router'

import StatusBar from '@/components/StatusBar.vue'
import Modal from '@/components/Modal.vue'
import InfoPnl from '@/components/InfoPnl.vue'

const infoModalOpen = ref(false);

</script>

<template>
  <header>
    <StatusBar />
  </header>
    <div class="container navbar">
      <nav>
        <ul>
          <li><RouterLink to="/">Home</RouterLink></li>
          <li><RouterLink to="/sse">Events</RouterLink></li>
          <li><RouterLink to="/websocket">Websocket</RouterLink></li>
          <li><RouterLink to="/about">About</RouterLink></li>
          <button @click="infoModalOpen=true" style="margin-bottom: 0; width: 40px; padding: .2rem; border-radius: 100px;">i</button>
        </ul>
      </nav>
    </div>

  <RouterView />

  <Modal v-model="infoModalOpen">
    <template #header>Info</template>
    <template #body>
      <InfoPnl />
    </template>
  </Modal>

</template>



<style scoped>
nav a.router-link-exact-active {
  color: var(--pico-primary);
}
nav a {
  color: var(--pico-text);
}

header {
  position: fixed;
  width: 100%;
  z-index: 1000; /* Ensure it sits over other content */
}

.navbar {
  padding-top: 2rem;
}

main {
  padding-top: 0;
}

main article {
  margin: 0;
}

</style>
