import { fileURLToPath, URL } from 'node:url'
import gzipPlugin from "rollup-plugin-gzip";

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

const proxy_target = process.env.PROXY_TARGET || "http://10.1.2.3"; // the IP is faster than "http://dora.local"

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
    // {
    //   ...gzipPlugin({
    //     filter: /\.(js|css|html|svg)$/,
    //     additionalFiles: [],
    //     customCompression: (content) =>
    //       brotliCompressSync(Buffer.from(content)),
    //     fileName: ".br",
    //   }),
    //   enforce: "post",
    //   apply: "build",
    // },
    {
      ...gzipPlugin({ 
        filter: /\.(js|css|html|svg)$/,
        additionalFiles: [],
      }),
      enforce: "post",
      apply: "build",
    },
  ],
  build: {
    outDir: "../_static",
    rollupOptions: {
      output: {
        entryFileNames: 'assets/[name].js',
        chunkFileNames: 'assets/[name].js',
        assetFileNames: 'assets/[name].[ext]',
      },
    },
  },
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
  server: {
    open: "/", // auto open browser in dev mode
    host: false, // dev on local and network
    proxy: {
      "/api": proxy_target,
      "/events": proxy_target,
      "/ws": proxy_target,
      "/reset": proxy_target,
    },
  },
})
