## Guide to Git/GitHub:

### 0. Initialise Git in ERDA (Must be done every time):
   -   Open repository folder (/erda_mount/HPPC/)
   -   Open a terminal and run: "git config --global --add safe.directory /home/jovyan/erda_mount/HPPC"
   -   Leave the folder and open it again.
   -   Now the Git tab is active.

### 2. Do your work. Change/add/remove files.

### 3. In ERDA Git control:
   - How to operate Git in ERDA:
       - Select changed files:
          -  If files are under "Untracked": Press "+" (Track)
          -  If files are under "Changed": Press "+" (Stage)
       - At the bottom:
          -  Write a summary.
          -  Press "COMMIT" (Might need credentials)
       - Update & Publish
          - **Before anything else!** : Press "↻" at the top right to update local and remote changes!
          - Pull changes: Press "🡇" at the top right to pull any changes from the remote repository. (It'll show a little orange circle if there is anything to pull)
          - Push changes: Press "🡅" at the top right to push any committed files to the remote repository. (It'll show a little orange circle if there is anything to push)
             - Will probably need credentials. 

# **Remember!**:
#    - Update "↻" and pull "🡇" before making any changes in the code and files!

### 4. In terminal:
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