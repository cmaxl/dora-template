<script setup lang="ts">
import { Teleport, onMounted, watchEffect } from 'vue'

const model = defineModel<Boolean>({ required: true, default: false});
const emit = defineEmits(['onOpen', 'onClose']);

const close = () => {
  emit('onClose');
  model.value = false;
}

onMounted(() => {
  addEventListener('keydown', (e) => {
    if (model.value && e.key === 'Escape') {
      console.log('esc');
      close();
    }
  });
});

watchEffect(() => {
  document.body.style.overflow = model.value ? 'hidden' : '';
  if (model.value) {
    emit('onOpen');
  }
});

</script>

<template>
  <Teleport to="body">
    <div v-if="model" style="position: fixed;">
      <main>
        <dialog open @click.self="close" style="padding-top: 6rem;">
          <article style="min-width: 50%;">
            <header>
              <h3>
                <slot name="header"></slot>
              </h3>
              <a href="" aria-label="Close" class="close" @click.prevent="close"></a>
            </header>
            <slot name="body"></slot>
          </article>
        </dialog>
      </main>
    </div>
  </Teleport>
</template>

<style scoped>
header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0.5rem 1rem;
}

header h3 {
  margin: 0;
  padding: 0;
  display: inline;
}
</style>