
-------------------------------------

**Viewing Unpushed Git Commits**

If you want to see all commits on all branches that aren't pushed yet, you might be looking for something like this:

`git log --branches --not --remotes`

And if you only want to see the most recent commit on each branch, and the branch names, this:

`git log --branches --not --remotes --simplify-by-decoration --decorate --oneline`


`git log origin/master..HEAD`

You can also view the diff using the same syntax

`git diff origin/master..HEAD`

---------------------------------------------

**Revert (Undo) to a previous Git commit**

This depends a lot on what you mean by "revert".

**Temporarily switch to a different commit**

If you want to temporarily go back to it, fool around, then come back to where you are, 
all you have to do is check out the desired commit:

```
# This will detach your HEAD, that is, leave you with no branch checked out:
git checkout 0d1d7fc32
```

Or if you want to make commits while you're there, go ahead and make a new branch while you're at it:

`git checkout -b old-state 0d1d7fc32`

To go back to where you were, just check out the branch you were on again.

**Hard delete unpublished commits**

If, on the other hand, you want to really get rid of everything you've done since then, there are two possibilities.
One, if you haven't published any of these commits, simply reset:

```
# This will destroy any local modifications.
# Don't do it if you have uncommitted work you want to keep.
git reset --hard 0d1d7fc32

# Alternatively, if there's work to keep:
git stash
git reset --hard 0d1d7fc32
git stash pop
# This saves the modifications, then reapplies that patch after resetting.
# You could get merge conflicts, if you've modified things which were
# changed since the commit you reset to.
```

If you mess up, you've already thrown away your local changes, but you can at least get back to where you were before 
by resetting again.

**Undo published commits with new commits**

On the other hand, if you've published the work, you probably don't want to reset the branch, since that's effectively 
rewriting history. In that case, you could indeed revert the commits. With Git, revert has a very specific meaning:
create a commit with the reverse patch to cancel it out. This way you don't rewrite any history.

```
# This will create three separate revert commits:
git revert a867b4af 25eee4ca 0766c053

# It also takes ranges. This will revert the last two commits:
git revert HEAD~2..HEAD

# Reverting a merge commit
git revert -m 1 <merge_commit_sha>

# To get just one, you could use `rebase -i` to squash them afterwards
# Or, you could do it manually (be sure to do this at top level of the repo)
# get your index and work tree into the desired state, without changing HEAD:
git checkout 0d1d7fc32 .

# Then commit. Be sure and write a good message describing what you just did
git commit
```

The git-revert manpage actually covers a lot of this in its description. Another useful link is this git-scm.com blog 
post discussing git-revert.

If you decide you didn't want to revert after all, you can revert the revert (as described here) or reset back to
before the revert (see the previous section).

-------------------------------------------------------

**How do you undo the last commit**

> Undo a commit and redo

> $ git commit ...              (1)

> $ git reset --soft HEAD~1     (2)

> << edit files as necessary >> (3)

> $ git add ....                (4)

> $ git commit -c ORIG_HEAD     (5)

- This is what you want to undo
-  This is most often done when you remembered what you just committed is incomplete, or you misspelled your commit message1,   or both. Leaves working tree as it was before "commit".
-  Make corrections to working tree files.
- Stage changes for commit.
- Commit the changes, reusing the old commit message. reset copied the old head to .git/ORIG_HEAD; commit with -c ORIG_HEAD will open an editor, which initially contains the log message from the old commit and allows you to edit it. If you do not need to edit the message, you could use the -C option instead.

-----------------------------------------------

- **git 自动补全**

```
if [ -f ~/.git-completetion.bash ]; then
  . ~/.git-completion.bash
fi
```

- **谁动了我的代码**

`git blame [file_name]`

- **review history**

`git log --oneline --graph --all`
 
- **不丢失一个提交信息**

`git reflog`

- **暂存一个文件的部分改动**

`git add -p [file_name]`

```
y - 缓存该块
n - 不缓存该块
e - 来人工编辑该块
s - 分割这个块
```

- **合并多次提交**

`git rebase -i HEAD~[number_of_commits]`

- **检查丢失的提交**

`git fsck --lost-found`

- **cherry-pick command**

`git cherry-pick [commit_hash]`

- **修改错误的提交信息（commit message）**

`git commit --amend -m "YOUR-NEW-COMMIT-MESSAGE"`

代码提交推送到远程分支

`git push <remote> <branch> --force`

- **commit之前撤销git add**

`git reset <filename>`

revert all files from `staging area`

`git reset`

- **Git仓库撤销至前一次提交时的状态**

`git checkout <SHA>`

- **删除本地或者远程Git分支**

delete local branch

`git branch --delete --force <branchname>`

delete remote branch

`git push origin --delete <branchname>`

- **移出git分支未追踪的本地文件**

'''
git clean -f -n
git clean -f 
git clean -fd
'''

---------------------------------------------------------------------------------------------

**git revert** _vs_ **git reset**

[Source](https://www.atlassian.com/git/tutorials/resetting-checking-out-and-reverting/commit-level-operations)

- Commit level operation

_git reset_

```
git checkout hotfix
git reset HEAD~2
```

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/02.svg)

> - soft – The staged snapshot and working directory are not altered in any way.
> - mixed – The staged snapshot is updated to match the specified commit, but the working directory is not affected. This is the default option.
> - hard – The staged snapshot and the working directory are both updated to match the specified commit.

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/03.svg)

`git reset --mixed HEAD` has the affect of unstaging all changes, but leaves them in the working directory. 
If you want to completely throw away all your uncommitted changes, you would use `git reset --hard HEAD`.

_git checkout_

```
git checkout hotfix
```

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/04.svg)

```
git checkout HEAD~2
```

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/05.svg)

_git revert_

```
git checkout hotfix
git revert HEAD~2
```

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/06.svg)

Contrast this with `git reset`, which does alter the existing commit history. 
For this reason, `git revert` should be used to undo changes on a _public branch_, and `git reset` should be reserved for undoing changes on a _private branch_.

You can also think of `git revert` as a tool for _undoing committed changes_, while `git reset HEAD` is for _undoing uncommitted changes_.

- **File Level Operation**

_reset_

```
git reset HEAD~2 foo.py
```

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/07.svg)

_checkout_

```
git checkout HEAD~2 foo.py
```

![](https://www.atlassian.com/git/images/tutorials/advanced/resetting-checking-out-and-reverting/08.svg)

--------------------------------------------------

**Summary**


| Command	    | Scope	       | Common use cases        |
|-------------|--------------|-------------------------|
| git reset	  | Commit-level |	Discard commits in a private branch or throw away uncommited changes |
| git reset	  | File-level	 | Unstage a file |
| git checkout|	Commit-level | Switch between branches or inspect old snapshots |
| git checkout|	File-level	 | Discard changes in the working directory |
| git revert	| Commit-level | Undo commits in a public branch |
| git revert	| File-level	 | (N/A) |

