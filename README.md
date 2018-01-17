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

## Windows

Unlike the Linux version, Sheemo has a simplified install process on Windows. Just run `sheemo_install.bat` which sets up the following binaries.

#### [Autohotkey](https://autohotkey.com/download/)
- `AHK` is an alternative to `xbindkeys` on Windows.

#### [pqiv](https://intern.pberndt.com/pqiv_builds/)
- `PQIV` is also avalible on Windows

## MacOS



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

###### Windows

_Sheemo_ also has tools that automatically integrate's itself with `PQIV`, `xbindkeys`, and `AutoHotkey`, just run `sheemo quickstart` 

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
_Cheatsheet_ creates a `.sheets` file in the current working directory and uses that file to store all of your cheatsheets.

`sheemo add <file ID> <file location> <file type>`

This command adds the following line to the `.sheets` file

`<file ID>:<file location>:<file type>`


- `<file ID>` : when searching through `.sheets`, _Cheatsheet_ will attempt to find the first instance of `file ID`. From there it will parse the rest of the line.
- `<file location>` : the location of your cheatsheet. _NOTE: this value does not have to be a file location. Instead it can also be binary paramters (See [Additional Information](#Add))_
- `<file type>` : the type/classifcation of the file. This is used to identify which binary to launch the file with (See [Adding Binaries](#AddBin)).

__NOTE `.sheets` is parsed by newlines, thus DOS line endings will cause errors__
___


### Loading cheatsheets
_Cheatsheet_ loads files from the `.sheets` file with their corresponding binary. Binaries are also stored in `.sheets`

`cheatsheet show <file ID>`
___

<a name="AddBin">

### Adding binaries

`cheatsheet binary <file type> <binary location>`

This command adds the following line to the `.sheets` file

`<file type>:<binary location>:bin`


- `<file type>` : all files associated with this type will be loaded with this binary
- `<binary location>` : the location of the binary. If the binary is loacted in your `PATH` you should also be fine
- `bin` : indicates that this line contains a binary. You __MUST__ have this exact wording & lowercase in order for _Cheatsheet_ to properly distinguish between binaries and files.

<a name="Build"/>

# Building
- `make install` builds a release version and installs it to `/usr/local/bin/cheatsheet` by default. This option can be changed
- `make debug` compiles `main.c` with the `-g` flag from `gcc` as `a.out`
- `make` compiles `main.c` as `a.out`

<a name="Add"/>

# Additional Information

- When displaying cheatsheets with `show`, __Sheemo__ appends the `<binary location>` and `<file location>` with a space inbetween and executes the new string as a command with a `system()` call.

- `<binary location>` doesn't have to be a direct location, it can also be located in the PATH environment variable

- __Sheemo__ does _NOT_ support DOS line endings

### Linux
If you're using a tiling WM like i3, or bspwn...
- you might want to configure your WM so that floating windows are used for the cheatseets
