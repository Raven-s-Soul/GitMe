# GitMe

> [!NOTE]
> Run the program in CLI parsing some directorys or put a `.GitMe` file in the same folder;
>
> - We read from the CLI or from the file the directorys.
> - Then we move to that directory.
> - Finaly we deploy a branch of your `GameSaves` on that folder if not already there. 😄
> - Yep we git all the files inside and then we push online.
>
> **_Keep your `saves` always with you!_** 😜

```c
GitMe -h //Unix Style
// @Args <- are folder paths
GitMe @Arg1 @Arg2 ... // not sure about the limits
GitMe // Look for .GitMe file containg @Args
```

## Requirements to run:

> - Account GitHub
> - And [Repository to use as a template](https://github.com/Raven-s-Soul/GitMeTemplate)
>   - Rename your new Repository `GameSaves`.
> - All your saves are in the fork in the differents branches.

> - Git
>   - Set your own local machine to have the same `user.name` as on github `username`.

```c
winget install Git.git // Windows
sudo apt install git // Linux
brew install git // MacOs
```

```c
git config user.name // has to be the same on GitHub
git config user.name "YourGitHubUsername"
git config --global user.name // May be needed
```

> If you changed the user after run the program, you may need to delete the hidden .git folder

#### Configs that are used for the right beheviour of the program, don't warry is all automatizated.

```c
git config --global --add --bool push.autoSetupRemote true
```

---

### MacOS & Linux

Drop it here and run everywhere like this.

```c
/usr/local/bin

//Run Everywhere with
GitMe ../<FolderName>
```

### Windows

Add to Environment Variables "PATH".

> **_Cool thing you can edit on the macro.h the name of the repository if u want to use for other things than SaveGames._**

---

### Alternative

> Alternative is to `pwd | GitMe` but is needed make a pipe Wrapper for console.

---

## Do you wanna help this small project?

**_This is what you need:_**

- Git (lol)
- CMake
- C++ compiler
- Some patience

```mermaid
flowchart TD
    A(Program Run) -->|No @Args| B([locate .GitMe in folder])
    A -->|@Args| C
    B --> | Read locations from file| C
    C[Loaded Paths]
    C --> | Empty list | E([ Exit ])
    C --> | Correct using path | F 
    C --> | Failed location | D([ Skip path ])
    F[Found directory] 
    F --> | Not a repository | G

    F --> | Is a repository | H(Git Pull or ask for force update)
    H --> | Git Add | M([Git Commit])
    M --> N([Git Push])
    N --> C
    
    G([Check if there is an online comparison]) --> |Found online branch| I([Git Clone --branch])
    I --> O
    G --> | No online comparison | O([Git Init])
    O --> P([Git Checkout])
    P --> H
```
