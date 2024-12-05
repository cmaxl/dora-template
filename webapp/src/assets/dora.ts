import { useEventSource, useWebSocket, useFetch } from '@vueuse/core';

import { showResetOverlay } from './utils';
import { reactive, watch } from 'vue';

export const events = useEventSource("/events", ["state"], {
  immediate: false,
  autoReconnect: {
    retries: 3,
    delay: 1000,
    onFailed() {
      alert('Failed to connect after 3 retries')
    },
  }
});

// as soon as the event source is connected, we can start listening to events
watch(
  () => events.eventSource.value,
  (newEventSource) => {
    if (newEventSource) {

      // generic event listener ('message' event)
      // newEventSource.onmessage = (e) => {
      //   console.log(e.type, e.data);
      // };

      // specific event listener

      newEventSource.addEventListener('state', (e) => {
        console.log(e.type, e.data);
      });
    }
  }
);

export const ws = useWebSocket("/ws", {
  immediate: false,
  autoReconnect: {
    retries: 3,
    delay: 1000,
    onFailed() {
      alert('Failed to connect after 3 retries')
    },
  },
});

// as soon as the websocket is connected, we can start listening to messages
watch(
  () => ws.ws.value,
  (newWebSocket) => {
    if (newWebSocket) {

      newWebSocket.onmessage = (e) => {
        console.log('WebSocket message', e.data);
      };
    }
  }
);

export async function reset() {
  showResetOverlay();
  await useFetch("/reset", {
    timeout: 2000,
  }).get();
  // go to home after 5 seconds
  setTimeout(() => {
    window.location.href = '/';
  }, 5000);
};

export const state = reactive({
  count: 0,
});

export * as dora from './dora';