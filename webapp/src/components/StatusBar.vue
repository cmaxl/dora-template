<script setup lang="ts">
import { state } from '@/assets/dora';

import { version } from '@/../package.json'; // adjust the path to your package.json file

</script>

<template>
  <!-- display the current server date and time name and state at the top of the site -->
  <div class="all-inline">
    <p></p>
    <p> DORA app {{ version }}</p>
    <p> foo </p>
  </div>
</template>

<style scoped>
.all-inline {
  padding: 10px;
  background-color: var(--pico-modal-overlay-background-color);
  backdrop-filter: blur(10px);
}

.all-inline p, a {
  font-size: 11pt;
  margin-bottom: 0;
}
</style>