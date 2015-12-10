
![](http://www.ruanyifeng.com/blogimg/asset/2015/bg2015120901.png)


> 删除工作区文件，并且将这次删除放入暂存区

$ git rm [file1] [file2] ...

> 停止追踪指定文件，但该文件会保留在工作区

$ git rm --cached [file]

> 改名文件，并且将这个改名放入暂存区

$ git mv [file-original] [file-renamed]

> 提交暂存区到仓库区

$ git commit -m [message]

> 提交暂存区的指定文件到仓库区

$ git commit [file1] [file2] ... -m [message]

> 提交工作区自上次commit之后的变化，直接到仓库区

$ git commit -a

> 提交时显示所有diff信息

$ git commit -v

> 使用一次新的commit，替代上一次提交. 如果代码没有任何新变化，则用来改写上一次commit的提交信息

$ git commit --amend -m [message]

> 重做上一次commit，并包括指定文件的新变化

$ git commit --amend [file1] [file2] ...

> 列出所有远程分支

$ git branch -r

> 列出所有本地分支和远程分支

$ git branch -a

> 新建一个分支，但依然停留在当前分支

$ git branch [branch-name]

> 新建一个分支，并切换到该分支

$ git checkout -b [branch]

> 新建一个分支，指向指定commit

$ git branch [branch] [commit]

> 新建一个分支，与指定的远程分支建立追踪关系

$ git branch --track [branch] [remote-branch]

> 切换到指定分支，并更新工作区

$ git checkout [branch-name]

> 建立追踪关系，在现有分支与指定的远程分支之间

$ git branch --set-upstream [branch] [remote-branch]

> 合并指定分支到当前分支

$ git merge [branch]

> 选择一个commit，合并进当前分支

$ git cherry-pick [commit]

> 删除分支

$ git branch -d [branch-name]

> 删除远程分支

$ git push origin --delete [branch-name]
$ git branch -dr [remote/branch]

> 显示有变更的文件

$ git status

> 显示当前分支的版本历史

$ git log

> 显示commit历史，以及每次commit发生变更的文件

$ git log --stat

> 显示某个文件的版本历史，包括文件改名

$ git log --follow [file]
$ git whatchanged [file]

> 显示指定文件相关的每一次diff

$ git log -p [file]

> 显示指定文件是什么人在什么时间修改过

$ git blame [file]

> 显示暂存区和工作区的差异

$ git diff

> 显示暂存区和上一个commit的差异

$ git diff --cached [file]

> 显示工作区与当前分支最新commit之间的差异

$ git diff HEAD

> 显示两次提交之间的差异

$ git diff [first-branch]...[second-branch]

> 显示某次提交的元数据和内容变化

$ git show [commit]

> 显示某次提交发生变化的文件

$ git show --name-only [commit]

> 显示某次提交时，某个文件的内容

$ git show [commit]:[filename]

> 显示当前分支的最近几次提交

$ git reflog

> 下载远程仓库的所有变动

$ git fetch [remote]

> 显示所有远程仓库

$ git remote -v

> 显示某个远程仓库的信息

$ git remote show [remote]

> 增加一个新的远程仓库，并命名

$ git remote add [shortname] [url]

> 取回远程仓库的变化，并与本地分支合并

$ git pull [remote] [branch]

> 上传本地指定分支到远程仓库

$ git push [remote] [branch]

> 强行推送当前分支到远程仓库，即使有冲突

$ git push [remote] --force

> 推送所有分支到远程仓库

$ git push [remote] --all

> 恢复暂存区的指定文件到工作区

$ git checkout [file]

> 恢复某个commit的指定文件到工作区

$ git checkout [commit] [file]

> 恢复上一个commit的所有文件到工作区

$ git checkout .

> 重置暂存区的指定文件，与上一次commit保持一致，但工作区不变

$ git reset [file]

> 重置暂存区与工作区，与上一次commit保持一致

$ git reset --hard

> 重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变

$ git reset [commit]

> 重置当前分支的HEAD为指定commit，同时重置暂存区和工作区，与指定commit一致

$ git reset --hard [commit]

> 重置当前HEAD为指定commit，但保持暂存区和工作区不变

$ git reset --keep [commit]

> 新建一个commit，用来撤销指定commit 后者的所有变化都将被前者抵消，并且应用到当前分支

$ git revert [commit]


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

