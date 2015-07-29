Q: Counting the non-contiguous subsequence as well as substring.
==========

Ex: The number of `wonderland` in the `wonderlandwonderland` is 17.

        wonderlandwonderland
        *********    *
        ********    **
        ********    *      *
        **      **    ******
        ***      *    ****** 

Let's say you didn't want to search for `wonderland`, but just for `w`. Then you'd simply count how many times `w` occurred in the story.

Now let's say you want `wo`. For each first character of the current pattern you find, you add to your count:

- How many times the current pattern without its first character occurs in the rest of the story, after this character you're at: so you have reduced the problem `(story[1..n], pattern[1..n])` to `(story[2..n], pattern[2..n])`
- How many times the entire current pattern occurs in the rest of the story. So you have reduced the problem to `(story[2..n], pattern[1..n])`

Now you can just add the two. There is no overcounting if we talk in terms of subproblems. 

Consider the example `wawo`. Obviously, `wo` occurs 2 times. You might think the counting will go like:

- For the first w, add 1 because o occurs once after it and another 1 because wo occurs once after it.
- For the second w, add 1 because o occurs once after it.

Answer is 3, which is wrong.

But this is what actually happens:

        (wawo, wo) -> (awo, o) -> (wo, o) -> (o, o) -> (-, -) -> 1
                                                    -> (-, o) -> 0
                   -> (awo, wo) -> (wo, wo) -> (o, wo) -> (-, wo) -> 0
                                            -> (o, o) -> (-, -) -> 1
                                                      -> (-, o) -> 0
So you can see that the answer is 2.

If you don't find a `w`, then the count for this position is just how many times `wo` occurs after this current character.

This allows for dynamic programming with memoization:

```python
count(story_index, pattern_index, dp):
  if dp[story_index, pattern_index] not computed:
    if pattern_index == len(pattern):
      return 1
    if story_index == len(story):
      return 0

    if story[story_index] == pattern[pattern_index]:
      dp[story_index, pattern_index] = count(story_index + 1, pattern_index + 1, dp) + 
                                       count(story_index + 1, pattern_index, dp) 
    else:
      dp[story_index, pattern_index] = count(story_index + 1, pattern_index, dp)

  return dp[story_index, pattern_index]
```
  
Call with count(0, 0, dp). Note that you can make the code cleaner (remove the duplicate function call).

Python code, with no memoization:

```python
def count(story, pattern):
  if len(pattern) == 0:
    return 1
  if len(story) == 0:
    return 0

  s = count(story[1:], pattern)
  if story[0] == pattern[0]:
    s += count(story[1:], pattern[1:])

  return s

print(count('wonderlandwonderland', 'wonderland'))
```

     Output: 17

