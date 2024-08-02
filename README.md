## GitMe

Requirements to run:

- Git

```c
winget install Git.git // Windows
sudo apt install git // Linux
brew install git // MacOs
```

- Account GitHub
  - And [Repository to fork/template](https://github.com/Raven-s-Soul/GameSavesDev)
    - Rename your new Repository `GameSaves`.
  - All your saves are in the fork in the differents branches.
- Set your own local machine to have the same `user.name` as on github `username`.

```c
git config user.name // has to be the same on GitHub
git config --global user.name // tecnicly is not needed to be the same
```

**Configs that we need, and set while running the app.**

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
