# NathanPong

## Initial setup

Because this repository contains [LFS objects](https://docs.github.com/en/repositories/working-with-files/managing-large-files/about-git-large-file-storage), it cannot be used as a regular Github template. Thus, there are two options for getting started:
- If you want to keep this repo's history, clone it, create a new remote repo, and switch the upstream remote:
    - `git clone https://github.com/tpstevens/NathanPong.git [optional-path]`
    - `cd <path-to-cloned-repo>`
    - Create a new *empty* repo (on Github or another host of your choice). Copy the URL (https://something/something.git).
    - `git remote remove origin`
    - `git remote add origin <new-repo-URL>`
    - `git push --set-upstream origin master`
- If you don't care to keep this repo's history:
    - Download the archive
    - Extract it (in a new repo or existing repo)
    - Commit and push

## Usage

- Run `Scripts/SetupTemplate.ps1` to change the project name
- Using your favorite text editor (Notepad++):
    - Run a find-and-replace operation to replace all instances of the old GUID (printed from `SetupTemplate.ps1`) to the new GUID (also printed from `SetupTemplate.ps1`)
    - Run a find-and-replace operation to replace all instances of `NathanPong` with `YourProjectName`
- Open the project in Visual Studio
