
Vim command
--------------

_Command Mode_

- '/' - forward search
- '?' - backward search
- '*' - 向下完全匹配光标下的词
- '#' - 向上完全匹配光标下的词
- 'g*' - 向下部分匹配光标下的词

- **3diw**—delete inside the current word and the next two words
- **dwwP**—swap the current word with the next word
- **d?foo**—delete from the cursor to the previous string “foo”
- **ct.**—change from the cursor until the next period
- **d^**—delete from the cursor to the beginning of the line
- **d>D**—delete from the cursor to the end of the line
- **2J**—join the current line with the line below
- **das**—delete around the current sentence
- **c(**—change from the cursor to the begining of a sentence
- **>}**—go to the end of the current paragraph
- **dapP**—swap current paragraph with the next paragraph
- **:%s/\s\+$//** - 去掉所有的行尾空
- **:%s!\s*//.*!!** - 去掉所有的注释//
- **:%s!\s*/\*\_.\{-}\*/\s*!!g** - 去掉所有的注释/* */
