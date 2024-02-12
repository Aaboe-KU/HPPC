Guide to Git/GitHub:

1. Do your work. Change/add/remove files.
   
2. In terminal:
   - Local Changes
     - ***git status*** : Shows modified files in the working directory.
     - ***git add [file]*** : Adds a file to the staging area.
     - ***git add .*** : Adds all modified files to the staging area.
     - ***git commit -m "[commit message]"*** : Commits your staged content as a new commit snapshot.
   - Update & Publish
     - ***git fetch*** : Fetches branches and commits from the remote repository.
     - ***git pull*** : Fetches and merges changes on the remote server to your working directory.
     - ***git push*** : Pushes all local branch commits to the remote repository.
   -  Undo
      -  ***git revert [commit]*** : Creates a new commit that undoes all of the changes made in a specified commit.
      -  ***git reset [file]*** : Unstages the file, but preserves its contents.
      -  ***git reset [commit]*** : Resets your HEAD pointer to a previous commit and discards all changes since that commit.
      -  ***git reset --hard [commit]*** : Resets your HEAD pointer to a previous commit and discards all changes since that commit, including all changes in the working directory.
   - Help
      - ***git help [command]***
   - *And much more*
     
3. In ERDA Git control:
    - Local Changes
       - Select changed files:
          -  If untracked: Press "+" (Track)
          -  If 
