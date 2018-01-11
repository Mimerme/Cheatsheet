# Cheatsheet
Ever have a mess like this?
![Really Messy Example of having a lot of cheatsheets](https://i.imgur.com/0QCUaDH.jpg)

Having physical cheatsheets/reference papers for all of your keybindings, gameplay guides, passwords, etc. can be handy, but unless you have ~~a yuge wall~~ a lot of space on your desk you'll soon realize how much of a mess it is

_Cheatsheet_ (better name incomming) is CLI application that's meant to fix this.


## Workflow integration
You're sitting at your computer. _"Oh crap how do I exit vim"_ you think to yourself. No problem I'll just pull up one of my many cheatsheets by typing `cheatsheet show vim` into my terminal. And all of a sudden __POOF__, an image file with a vim cheatsheet you found online and downloaded previously pops up. Now you can safely exit vim without closing your entire terminal.

## How it works
### Saving cheatsheets
_Cheatsheet_ creates a `.sheets` file in the current working directory and uses that file to store all of your cheatsheets. The format of the `.sheets` file is as follows

`cheatsheet add <key name>:<file location>:<file type>`

- `<key name>` : when searching through `.sheets`, _Cheatsheet_ will attempt to find the first instance of `key name`. From there it will parse the rest of the line.
- `<file location>` : the location of your cheatsheet. _NOTE: this value does not have to be a file location. Instead it can also be binary paramters (See Binaries Bellow)_
- `<file type>` : the type/classifcation of the file. This is used to identify which binary to launch the file with (See Binaries Bellow).

__`.sheets` is parsed by newlines, thus different line endings may cause some errors__
___


### Loading cheatsheets
_Cheatsheet_ loads files from the `.sheets` file with their corresponding binary. Binaries are also stored in `.sheets` (See Binaries bellow)

`cheatsheet show <file type>:<binary location>:bin`

- `<file type>` : all files associated with this type will be loaded with this binary
- `<binary location>` : the location of the binary. If the binary is loacted in your `PATH` you should also be fine
- `bin` : indicates that this line contains a binary. You __MUST__ have this exact wording & case in order for _Cheatsheet_ to properly distinguish between binaries and files.
___


### Adding binaries
`cheatsheet binary <file type>:<binary location>`

- `<file type>` : all files associated with this type will be loaded with this binary
- `<binary location>` : the location of the binary. If the binary is loacted in your `PATH` you should also be fine
___


## Binaries
By itself _Cheatsheet does nothing besides run commands. It must be coupled with other tools to prove effective, but before that let's break past some layers of abstraction

### Control Flow
1) _Cheatsheet_ starts off detecting what command you just ran
⋅⋅* _Cheatsheet_ doesn't actually parse the entire command, instead it only parses the first letter. So just typing `a` instead of `add` works just as well.
2) _Cheatsheet_ then splits the `.sheets` file buffer at all of its newlines, and then parses each line
3) It first tries to find the first instance of the `<key name>`.
4) After finding the first instance of `<key name>` it then checks for the `<file type>`. It then tries to find the first instance of `<file type>` that also contains `bin` as the term after the second colon
5) Upon finding the binary it then executes the following command

`<binary location> <file location>`

__NOTE that when executing the command the two values are simply appended together with a space in between. This means that `<file location>` doesn't actually have to be the file location, it can be any aditional parameters that you wish to pass to the binary.__

__ADDITIONAL NOTE `<binary location>` can also be located in your PATH, it doesn't neceissarly have to be the actual binary location__

___

## Additional Information

### LINUX
If you're running linux you shouldn't have any problems, as this entire program was designed for Linux. If your on OSX that may be a different story but most of the guide should still apply

On Linux you should...
- set up global hotkeys with `xbindkeys`
- use a lightweight image viewer like `PQIV`
- use a lightweight PDf viewer like
- use a lightweight text file viewer like 

If you're using a tiling WM like i3, or bspwn...
- you might want to configure your WM so that floating windows are used for the cheatseets


## CLI Usage
`cheatsheat [operation] [args]`

### Operations
`list` - lists saved cheatseets

`show` - show a specified cheatseet

`add` - add a cheatsheet to the list of saved cheatsheets 

`binary` - add a binary to the list of saved binaries

`help` - shows this list of operations

## Structure
- Everything is saved in a `.sheets` file --located in the working directory

### Configuration of `.sheets`

The following should be paths to an binary that takes either a PDF/image/text as an argument. The format for the values of each key should be `[program_specific_stuff] ${cheatsheet}`. In this case `${cheatsheet}` will be replaced by a path to the cheatsheet. 
- PDF_VIEWER : 
- IMAGE_VIEWER : 
- TEXT_VIEWER : set to `none` to print to console

## Recomendations
- Use lightweight PDF & image viewer _(I'm probably releasing one soon)_
- Use a global keybinding manager to be able to access your cheatsheets on the fly
- Modify the source to fit your desktop environemnt/window manager _(For example I have my cheatsheets show up on polybar)_
