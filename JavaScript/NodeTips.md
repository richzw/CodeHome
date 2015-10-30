
- **Check directory / file exist?**

```javascript
try {
			var protoPath = path.resolve(__dirname, './message');
			var stats = fs.statSync(protoPath);
		} catch (e) {
		
		}

```
