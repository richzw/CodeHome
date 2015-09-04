
**How to match a line does NOT include a word?**

----------

```
Input:

 hoho
 hihi
 haha
 hede

 # grep "Regex for do not contain hede" Input

Output:
 hoho
 hihi
 haha
```

--------------------

`^((?!hede).)*$`

**Explanation**

A string is just a list of n characters. Before, and after each character, there's an empty string. 
So a list of n characters will have n+1 empty strings. Consider the string "ABhedeCD":

```
    +--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+
S = |e1| A |e2| B |e3| h |e4| e |e5| d |e6| e |e7| C |e8| D |e9|
    +--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+

index    0      1      2      3      4      5      6      7
```

where the e's are the empty strings. The regex (?!hede). looks ahead to see if there's no substring "hede" to be seen, 
and if that is the case (so something else is seen), then the . (dot) will match any character except a line break.
Look-arounds are also called zero-width-assertions because they don't consume any characters. 
They only assert/validate something.

So, in my example, every empty string is first validated to see if there's no "hede" up ahead, before a character is consumed
by the . (dot). The regex (?!hede). will do that only once, so it is wrapped in a group, and repeated zero or more times: 
((?!hede).)*. Finally, the start- and end-of-input are anchored to make sure the entire input is consumed: ^((?!hede).)*$

[Ref](http://stackoverflow.com/questions/406230/regular-expression-to-match-line-that-doesnt-contain-a-word)


