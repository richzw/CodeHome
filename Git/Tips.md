
[Source](http://www.alexkras.com/19-git-tips-for-everyday-use/)

------------------------------

 `git log --author="Benz" --after="1 week ago" --oneline`

-----------------------------

**查看文件的详细变更**

`git log -p filename`

-----------------------------

**查看文件中指定位置的变更**

`git log -L 1,10:some_file.txt`

-------------------------

**查看尚未合并的变更**

`git log --no-merges master..`

你也可以运行 `git show --no-merges master..` 或者 `git log -p --no-merges master..` 命令来查看一下尚未合并的文件变更。

--------------------------

**查看其他分支中的文件**

`git show some-branch:some-file.js`

如果你想查看另一个分支上文件与当前分支上文件的差异，只要运行下面的命令就可以了：

`git diff some-branch some-filename.js`

------------------------

**rebase**

假设你正在master分支的一个本地版本上工作，你已经向仓库提交了一小部分变更。与此同时，也有人向master分支提交了他一周的工作成果。
当你尝试推送本地变更时，git提示你需要先运行一下 git pull 

`git pull --rebase`

------------------------

**本地合并之后保留分支结构**

`git merge –no-ff some-branch-name`


--------------------------------

**修复而非新建提交**

`git commit --amend`

**If you haven’t pushed to the remote branch yet**, you can simply do the following:

- Fix your typo
- Stage the newly fixed file via git add some-fixed-file.js
- Run `git commit --amend` which would add the most recent changes to your latest commit. 
It will also give you a chance to edit the commit message. Push the clean branch to remote, when ready

-----------------------------------

**Three stages in git**








