<script setup lang="ts">
import { reactive, computed } from 'vue';

import ConfirmButton from '@/components/ConfirmButton.vue';

import { dora } from '@/assets/dora';


</script>

<template>
  <div >
    <div class="all-inline">

      <button class="secondary" style="width: 48%;" @click="dora.events.open">Reconnect</button>
      <ConfirmButton button-text="Reset" style="width: 48%;" @confirm="dora.reset">Reset</ConfirmButton>
    </div>
  </div>
</template>
