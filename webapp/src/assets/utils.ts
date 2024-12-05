
export function showResetOverlay() {
  document.body.style.overflow = 'hidden';

  const overlay = document.createElement('div');
  overlay.style.position = 'fixed';
  overlay.style.top = '0';
  overlay.style.left = '0';
  overlay.style.width = '100%';
  overlay.style.height = '100%';
  overlay.style.backgroundColor = 'rgba(0, 0, 0, 0.5)';
  overlay.style.zIndex = '1000';

  const content = document.createElement('div');
  content.style.position = 'absolute';
  content.style.top = '50%';
  content.style.left = '50%';
  content.style.transform = 'translate(-50%, -50%)';
  content.style.backgroundColor = 'white';
  content.style.padding = '20px';
  content.style.borderRadius = '5px';
  content.style.boxShadow = '0 0 10px rgba(0, 0, 0, 0.5)';

  const header = document.createElement('h1');
  header.textContent = 'Resetting...';
  header.style.marginBottom = '10px';

  const progress = document.createElement('progress');
  progress.style.width = '100%';

  const text = document.createElement('p');
  text.textContent = 'Please wait while the device is resetting.';

  content.appendChild(header);
  content.appendChild(progress);
  content.appendChild(text);
  overlay.appendChild(content);
  document.body.appendChild(overlay);
}

export * as u from './utils';