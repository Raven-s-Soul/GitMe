# GitMe

> [!NOTE]
> Run the program in CLI parsing some directorys or put a `.txt` file in the same folder;
> - We read from the CLI or from the file the directorys.
> - Then we move to that directory.
> - Finaly we deploy a branch of your `GameSaves` on that folder if not already there. 😄
> - Yep we git all the files inside and then we push online.
>
> ***Keep your `saves` always with you!*** 😜

## Requirements to run:

>- Account GitHub
>  - And [Repository to fork/template](https://github.com/Raven-s-Soul/GameSavesDev)
>    - Rename your new Repository `GameSaves`.
>  - All your saves are in the fork in the differents branches.

>- Git
>    - Set your own local machine to have the same `user.name` as on github `username`.
```c
winget install Git.git // Windows
sudo apt install git // Linux
brew install git // MacOs
```


```c
git config user.name // has to be the same on GitHub
git config user.name "YourGitHubUsername"
git config --global user.name // tecnicly is not needed to be the same
```
> If you changed the user after run the program, you may need to delete the hidden .git folder

#### Configs that are used for the right beheviour of the program, don't warry is all automatizated.

```c
git config --global --add --bool push.autoSetupRemote true
```

---

## Do you wanna help this small project?

**_This is what you need:_**

- Git (lol)
- CMake
- C++ compiler
- Some patience

> If you plan to help this project may build the same project but using the `dev` on the `GameSavesLink()` function.
