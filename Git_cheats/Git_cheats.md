# Git Cheat Sheet

A quick reference for essential Git commands and workflows.

## Initial Setup

```bash
# Configure user identity
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# View configuration
git config --list
```

## Repository Basics

```bash
# Initialize a new repository
git init

# Clone a repository
git clone <url>
git clone <url> <directory>  # clone into specific directory

# Check repository status
git status
git status -s              # short format

# View remote repositories
git remote -v
git remote add <name> <url>
git remote remove <name>
```

## Staging & Committing

```bash
# Add files to staging area
git add <file>
git add .                  # stage all changes
git add -A                 # stage all changes (including deletions)
git add -p                 # interactive staging (patch mode)

# View changes
git diff                   # unstaged changes
git diff --staged          # staged changes
git diff <branch1> <branch2>

# Commit
git commit -m "message"
git commit -am "message"   # stage and commit tracked files
git commit --amend         # modify last commit
git commit --amend --no-edit  # add files to last commit without changing message
```

## Branching

```bash
# List branches
git branch                 # local branches
git branch -a              # all branches (local + remote)
git branch -v              # branches with last commit

# Create branch
git branch <branch-name>
git branch <branch-name> <start-point>

# Switch branch
git checkout <branch>
git switch <branch>        # newer syntax

# Create and switch in one command
git checkout -b <branch>
git switch -c <branch>     # newer syntax

# Delete branch
git branch -d <branch>     # safe delete (checks for unmerged changes)
git branch -D <branch>     # force delete

# Rename branch
git branch -m <old-name> <new-name>
git branch -m <new-name>   # rename current branch

# Set upstream branch
git branch -u origin/<branch>
git branch --set-upstream-to=origin/<branch>
```

## Merging & Rebasing

```bash
# Merge branch into current branch
git merge <branch>
git merge --no-ff <branch>  # create merge commit even if fast-forward possible
git merge --squash <branch> # squash commits before merging

# Abort merge
git merge --abort

# Rebase current branch onto another
git rebase <branch>
git rebase -i HEAD~<n>     # interactive rebase last n commits
git rebase --continue      # continue after resolving conflicts
git rebase --abort         # abort rebase

# Cherry-pick commit
git cherry-pick <commit>
git cherry-pick <commit1> <commit2>
```

## History & Logs

```bash
# View commit history
git log                    # full log
git log --oneline          # condensed format
git log --graph --oneline --all  # visual branch graph
git log -n <n>             # last n commits
git log --since="2 weeks ago"
git log --author="name"
git log --grep="pattern"   # search commit messages
git log -p                 # show patch (changes) for each commit
git log -S <string>        # commits that added/removed string

# View specific commit
git show <commit>
git show <commit>:<file>   # show file at specific commit

# Who changed what (blame)
git blame <file>
git blame -L <start>,<end> <file>  # blame specific lines
```

## Restoring & Undoing

```bash
# Discard changes in working directory
git restore <file>        # newer syntax
git checkout -- <file>    # older syntax

# Unstage file
git restore --staged <file>  # newer syntax
git reset HEAD <file>        # older syntax

# Undo last commit (keep changes)
git reset --soft HEAD~1

# Undo last commit (discard changes)
git reset --hard HEAD~1

# Revert commit (create new commit that undoes it)
git revert <commit>

# Clean untracked files
git clean -fd              # force delete untracked files and directories
git clean -fdn             # dry-run: show what would be deleted
```

## Remote Operations

```bash
# Fetch updates from remote
git fetch                  # fetch all remotes
git fetch <remote>         # fetch specific remote

# Pull updates (fetch + merge)
git pull
git pull --rebase          # fetch + rebase instead of merge

# Push to remote
git push
git push <remote> <branch>
git push -u origin <branch>  # set upstream and push
git push --all             # push all branches
git push --tags            # push all tags

# Delete remote branch
git push origin --delete <branch>
git push origin :<branch>  # older syntax
```

## Stashing

```bash
# Save changes temporarily
git stash
git stash save "description"

# List stashes
git stash list

# Apply and remove (pop) stash
git stash pop              # apply latest stash and remove it
git stash pop stash@{n}    # apply specific stash

# Apply without removing
git stash apply            # apply latest stash
git stash apply stash@{n}  # apply specific stash

# Remove stash
git stash drop             # delete latest stash
git stash drop stash@{n}   # delete specific stash
git stash clear            # delete all stashes
```

## Tags

```bash
# Create tag
git tag <tag-name>                    # lightweight tag
git tag -a <tag-name> -m "message"    # annotated tag

# List tags
git tag
git tag -l "<pattern>"

# Show tag details
git show <tag-name>

# Push tags
git push origin <tag-name>
git push origin --tags                # push all tags

# Delete tag
git tag -d <tag-name>                 # local
git push origin --delete <tag-name>   # remote
```

## Useful Configurations

```bash
# Configure editor
git config --global core.editor "vim"

# Configure merge tool
git config --global merge.tool vimdiff

# Color output
git config --global color.ui true

# Alias for common commands
git config --global alias.st "status"
git config --global alias.co "checkout"
git config --global alias.br "branch"
git config --global alias.unstage "restore --staged"
git config --global alias.last "log -1 HEAD"
git config --global alias.visual "log --graph --oneline --all"
```

## Common Workflows

### Feature Branch Workflow
```bash
git checkout -b feature/new-feature
# ... make changes ...
git add .
git commit -m "Implement new feature"
git push -u origin feature/new-feature
# Create pull request on GitHub/GitLab
git checkout main
git pull
git merge feature/new-feature
git push
```

### Fixing Mistakes

```bash
# Undo unpushed commit but keep changes
git reset --soft HEAD~1

# Undo unpushed commis and discard changes
git reset --hard HEAD~1

# Undo pushed commit (create new commit that reverts it)
git revert <commit>

# Fix last commit message
git commit --amend -m "New message"

# Add forgotten file to last commit
git add <file>
git commit --amend --no-edit
```

### Resolving Conflicts

```bash
# During merge/rebase conflict
git status                 # see which files have conflicts
# ... edit files to resolve conflicts ...
git add <resolved-file>
git commit                 # complete merge
# or
git rebase --continue      # continue rebase
```

## Tips & Tricks

- **Commit often:** Small, logical commits are easier to understand and revert if needed
- **Write good messages:** Use imperative mood ("Add feature" not "Added feature")
- **Branch naming:** Use descriptive names like `feature/login`, `fix/memory-leak`, `docs/readme`
- **Stay current:** Frequently pull to avoid large conflicts
- **Review before push:** Use `git diff` to review changes before committing
- **Use `.gitignore`:** Prevent committing unwanted files (build artifacts, secrets, etc.)

## Real-World Examples: Tutorials Repository

### Clone the tutorials repository
```bash
git clone https://github.com/your-username/Tutorials.git
cd Tutorials
```

### Create a branch to improve the C++ Primer
```bash
git checkout -b docs/cpp-primer-improvements
# Edit CPP_primer/README.md
git add CPP_primer/README.md
git commit -m "Enhance C++ Primer with additional examples"
git push -u origin docs/cpp-primer-improvements
```

### Add a new tutorial (e.g., Python Primer)
```bash
git checkout -b feature/python-primer
mkdir Python_primer
# Create files...
git add Python_primer/
git commit -m "Add Python Primer tutorial"
git push -u origin feature/python-primer
```

### Update only the templateDemo tutorial
```bash
git checkout -b feature/template-demo-fixes
# Edit templateDemo/README.md and related files
git add templateDemo/
git commit -m "Fix and improve templateDemo documentation"
git diff origin/main -- templateDemo/  # review changes
git push origin feature/template-demo-fixes
```

### Tag a tutorial release
```bash
git tag -a v1.0-tutorials -m "Release v1.0: Complete C++, CMake, and Bash tutorials"
git push origin v1.0-tutorials
```

### View history of a specific tutorial folder
```bash
git log --oneline CPP_primer/
git log -p CPP_primer/Step00-ThingsToUnderstand/00-History.md  # show changes
```

### Restore a tutorial file to a previous state
```bash
# See history
git log --oneline Bash_primer/LinuxCheatSheet.md

# Restore to specific commit
git checkout <commit-hash> -- Bash_primer/LinuxCheatSheet.md
git commit -m "Restore Bash primer to previous version"
```

### Merge tutorial improvements from a collaborator
```bash
git fetch origin
git checkout main
git merge --no-ff origin/feature/cmake-updates -m "Merge CMake primer improvements"
git push origin main
```

### Stash unfinished tutorial edits and switch branches
```bash
# Working on templateDemo changes, need to switch to fix a bug
git stash save "WIP: templateDemo enhancements"
git checkout -b fix/critical-bug
# ... fix bug ...
git commit -m "Fix critical bug in documentation"
git push origin fix/critical-bug

# Return to work
git checkout feature/template-tutorial
git stash pop
```

### Update local tutorials from remote
```bash
git pull origin main
# or with rebase to keep history clean
git pull --rebase origin main
```

### Check who last modified files in a tutorial
```bash
git blame CPP_primer/README.md | head -20
git log -p --follow HashDefVsCPP/README.md  # show changes over time
```
