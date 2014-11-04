 Introduce to Sublime Text 2 
===============================

Please refer to official documentation from [Sublime Text 2 doc1][STD1] and [Sublime Text 2 doc2][STD2].

I will bring topics for some major functionalities as below.

http://zh.lucida.me/blog/sublime-text-complete-guide/

Some good plugin can be found here

http://ipestov.com/the-best-plugins-for-sublime-text/

### Download and Installation
Open it up in shell by creating a symbol link:

    $ sudo ln -s "/path/to/sublimetext2" /bin/subl

### Overview
- Directory (Default and User)
- Textmate and Vintage Mode
- Go to anything - `#`, `@`, `:` [^note-FS]
    - Use *symbol* inside __js__ and __css__ by typing `CMD+R` or `CMD+P+@`
- MiniMap
- Command Palette (ext is .sublime-commands) [^note-FS]
- Command console ex. run `view.run_command("goto_line", {"line": 10})`
- Key bindings
- Settings
- Tab Completion
- Color Scheme
- Comment

### Commands
- Copy by `CMD+SHIFT+P`
- Join Line by `^+J`
- Zoom in/out by `CMD+=` or `CMD+-`
- Multiple Cursor, `CMD+D`
- Select all by `CMD+^+G` [^note-FS]
- Column selection by `OPTION+SELECT`
- Select multi line and then `CMD+^+L`
- `CMD+LEFT`
- Increament Search by `CMD+I`

### Snippets [^note-snippet]
- Retrieve existing snippets by `CMD+P`
- How to create your own code snippet
- Download snippet
    - Package control
        - ex. jquery mobile code snippet
    - Manually
        - ex. `$ git clone /path/to/snippet folder_name`

### Build Systems

### Window Split
- `CMD+OPTION+1` or `+2` or `+3` or `+4` or `+5`
- `SHIFT+^+1` or `+2` or `+3` or `+4`
- `^+1` or `+2` or `+3` or `+4`
 
### Package Control

#### Install Package Manually
`$ git clone /path/to/sublime/package package_name`

#### Install Package Control
- Download from [wbond][PC]
- Open console by `^+\``, run installation command and then restart ST
    - ex. CoffeeScript

#### Interesting Packages

> Emmet

>> HTML (lorem10)

>> CSS

> PlainTasks

> LiveReload

> AdvancedNewFile

> SidebarEnhancement

> SublimeLinter

> MarkdownEditing/MarkdownPreview

TIP: accessibilty -> enable sticky keys 

### Extension

- .sublime-build
- .sublime-keymap
- .sublime-macro
- .sublime-menu
- .sublime-snippet
- .sublime-settings
- .sublime-project
- .sublime-workspace
- .py
- .tmPreferences
- .tmLanguage
- .tmTheme


[^note-FS]: Use fuzzy search
[^note-snippet]: File extension should be sublime-snippet

 [STD1]: http://www.sublimetext.com/docs/2/
 [STD2]: http://docs.sublimetext.info/en/sublime-text-2/
 [PC]: http://wbond.net/sublime_packages/package_control


