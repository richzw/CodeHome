
How does require find a module?
-------------------

Searches:

- **Core modules**: Built in modules
- **node_modules**: works up path until it matches or hits the root
- **NODE_PATH**: includes globally installed packages
- $HOME/.node_modules
- $HOME/.node-libraries

How does require work?
-------------------

`moduler.require` which wraps `Module._load()`, `_load` steps:

- Check **Module._cache** for a cached copy
- Create a new Module instance if cache miss
- Save it to the cache
- Call load with the given filename
- Compile the file contents
- If there was an error delete from cache
- Return **module.exports**

How does compile work?
-------------------

- Create a standalone require function that calls `module.require`
- Attaches other helper methods to require
- wrap the loaded JS codes in a function that provides the require from step1, module, and variables to the module scope
- run the function

```js
(function(exports, require, module, __filename, __dirname) {
      // code injected here
});
```
