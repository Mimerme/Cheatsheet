# Cheatsheet
CLI application that's meant to load and save cheatsheets for stuff like vim, i3, etc.

But really all it does is load PDFs, images, and textfiles

## Usage
`cheatsheat [operation] [args]`

### Operations
`list` - lists saved cheatseets

`show` - show a specified cheatseet

`add` - add a cheatsheet to the list of saved cheatsheets 

`help` - shows this list of operations

## Structure
- Everything is saved in `.sheets` file, located in the working directory

### Configuration of `.sheets`

The following should be paths to an binary that takes either a PDF/image/text as an argument. The format for the values of each key should be `[program_specific_stuff] ${cheatsheet}`. In this case `${cheatsheet}` will be replaced by a path to the cheatsheet. 
- PDF_VIEWER : 
- IMAGE_VIEWER : 
- TEXT_VIEWER : set to `none` to print to console

## Recomendations
- Use lightweight PDF & image viewer _(I'm probably releasing one soon)_
- Use a global keybinding manager to be able to access your cheatsheets on the fly
- Modify the source to fit your desktop environemnt/window manager _(For example I have my cheatsheets show up on polybar)_
