
function withRetry(asyncAction, retries) {
  if (retries === 0) {
    // Promise.resolve to convert sync throws into rejections.
    return Promise.resolve().then(asyncAction); 
  }
  return Promise.resolve()
    .then(asyncAction)
    .catch(() => withRetry(asyncAction, retries - 1));
}

