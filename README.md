# Sheemo
Ever have a mess like this?
![Really Messy Example of having a lot of cheatsheets](https://i.imgur.com/0QCUaDH.jpg)

Having physical cheatsheets/reference papers for all of your keybindings, gameplay guides, passwords, etc. can be handy, but you'll soon realize how much of a mess it is

_Sheemo_ is CLI application meant to fix this.

**Table of Contents**

* [Quickstart](#Quickstart)
* [Usage](#Usage)
* [Workflow](#Work)
* [How it Works](#Works)
* [Manually Building](#Build)
* [Additional Information](#Add)

<a name="Quickstart"/>

# Quickstart
Sheemo is a simple tool that organizes and executes a series of commands through your OS's command line. It is designed to be paired with other applications, and this section explains how to do so.

## Linux

#### [xbindkeys](http://git.savannah.gnu.org/cgit/xbindkeys.git/)
- Great for creating global shortcuts to open cheatsheets
- Check distro for installation instructions

#### [pqiv](https://github.com/phillipberndt/pqiv)
- Amazing lightweight image/pdf viewer. Should fit 90% of your cheatsheet/reference sheet needs
- _NOTE_ : Lower versions of PQIV have a bug that fails to open PDF files. Fix this by either building from source or installing the latest version.

---

### Installation Instructions

###### Debian/Ubuntu
`apt-get install xbindkeys`  
`apt-get install pqiv`

[PQIV Debian package](https://packages.debian.org/en/sid/pqiv)

###### Arch Linux
`pacman -S xbindkeys`  
[PQIV AUR](https://aur.archlinux.org/packages/pqiv/)

###### Other Distros
[xbindkeys](https://github.com/IonicaBizau/xbindkeys/blob/master/INSTALL)  
[Install PQIV](https://github.com/phillipberndt/pqiv#installation)

_Sheemo_ has tools that automatically integrate's itself with `PQIV` and `xbindkeys`, just run `sheemo quickstart` 

## Windows

Unlike the Linux version, Sheemo has a simplified install process on Windows. Just run `sheemo_install.bat` which sets up the following binaries.

#### [Autohotkey](https://autohotkey.com/download/)
- `AHK` has is an alternative to `xbindkeys` on Windows.

#### [pqiv](https://intern.pberndt.com/pqiv_builds/)
- `PQIV` is also avalible on Windows

## MacOS

<a name="Usage"/>

# Usage
`cheatsheat [operation] [args]`

### Operations
`list` - lists saved cheatseets  

`quickstart` - setup _Sheemo_ for Linux based systems

`link` - link a key/key combo to a cheatsheet. Requires _Sheemo_ to have been setup with `quickstart`

`show <file ID>` - show a specified cheatseet  

`add <file ID> <file path> <file type>` - add a cheatsheet to the list of saved cheatsheets  

`binary <associated file type> <binary path>` - add a binary to the list of saved binaries  

`help` - shows this list of operations

<a name="Works"/>

# How it works
### Saving cheatsheets
_Cheatsheet_ creates a `.sheets` file in the current working directory and uses that file to store all of your cheatsheets. The format of the `.sheets` file is as follows

`sheemo add <file ID> <file location> <file type>`

This command adds the following line to the `.sheets` file

`<file ID>:<file location>:<file type>`


- `<file ID>` : when searching through `.sheets`, _Cheatsheet_ will attempt to find the first instance of `file ID`. From there it will parse the rest of the line.
- `<file location>` : the location of your cheatsheet. _NOTE: this value does not have to be a file location. Instead it can also be binary paramters (See Binaries Bellow)_
- `<file type>` : the type/classifcation of the file. This is used to identify which binary to launch the file with (See Binaries Bellow).

__NOTE `.sheets` is parsed by newlines, thus different line endings may cause some errors__
___


### Loading cheatsheets
_Cheatsheet_ loads files from the `.sheets` file with their corresponding binary. Binaries are also stored in `.sheets` (See Binaries bellow)

`cheatsheet show <file ID>`
___


### Adding binaries

`cheatsheet binary <file type> <binary location>`

This command adds the following line to the `.sheets` file

`<file type>:<binary location>:bin`


- `<file type>` : all files associated with this type will be loaded with this binary
- `<binary location>` : the location of the binary. If the binary is loacted in your `PATH` you should also be fine
- `bin` : indicates that this line contains a binary. You __MUST__ have this exact wording & case in order for _Cheatsheet_ to properly distinguish between binaries and files.
___

### Control Flow

1) _Cheatsheet_ starts off detecting what command you just ran
     - _Cheatsheet_ doesn't actually parse the entire command, instead it only parses the first letter. So just typing `a` instead of `add` works just as well.
2) _Cheatsheet_ then splits the `.sheets` file buffer at the newlines, and then parses each line
     - DOS/Windows line endings are not supported
3) It first tries to find the first instance of the `<file ID>`.
4) After finding the first instance of `<file ID>` it then checks for the `<file type>`. It then tries to find the first instance of `<file type>` that also contains `bin` as the term after the second colon
5) Upon finding the binary it then executes the following command

`<binary location> <file location>`

__NOTE: that when executing the command the two values are simply appended together with a space in between. This means that `<file location>` doesn't actually have to be the file location, it can be any aditional parameters that you wish to pass to the binary.__

__ADDITIONAL NOTE: `<binary location>` can also be located in your PATH, it doesn't neceissarly have to be the actual binary location__

___

<a name="Build"/>

# Building
- `make install` builds a release version and installs it to `/usr/local/bin/cheatsheet` by default. This option can be changed
- `make debug` compiles `main.c` with the `-g` flag from `gcc` as `a.out`
- `make` compiles `main.c` as `a.out`

<a name="Add"/>

# Additional Information

### Linux
If you're using a tiling WM like i3, or bspwn...
- you might want to configure your WM so that floating windows are used for the cheatseets