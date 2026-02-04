# Linux cheat-sheet

In Linux/Unix much we (can) do is done on the command-line shell (bash, sh, ksh,..).
Why? Because it’s fast, scriptable, composable and consistent.

## The most important command
`man <command>`: get help about a command (manual entry). The man-pages of a command, if and when they exist give information about
    - what the command does
    - what parameters the command accepts
    - errors/exceptions
    - examples (sometimes)
Many of the commands in Linux have a -h/--help parameter, which also is a good first point of enquiry.
The man-pages also are available on the internet, but commands and parameters can slightly vary for different Linux
distributions and versions, so what you find on the web might not actually work on your box.

## Configure your own shell
Many commands used in the shell take many optional and mandatory parameters that modify what is done, how output
is displayed etc. You will find the more you use the shell the more you will repeat similar commands. Often the 
commands use a lot of parameters or have non-expressive names etc. If you want to avoid retyping stuff or just 
give yourself mental clues you can create shortcuts by creating aliases.
alias: give (a set of) commands a name

### Example
The `ls` command in its pure form (without parameters) lists files and directories in the current directory as a 
tab-separated list of strings without any information about the file-system objects apart from their names. 
This might be sufficient for some purposes, but often we are interested in 
    - type of object (file, directory, ...)
    - access rights
    - owner
    - …
    
You might normally want to see the name-list annotated/coloured which you can do by e.g: 
`[~/myuser]> ls -F -a -s -l` (but do you really always want to type this?)
By defining an alias you can save yourself from forgetting parameters.
`[~/myuser]> alias l=”ls -F -a -s -l”`

Now if you type 
`[~/myuser]> l` on the command line the command  `ls -F -a -s -l` will be executed.

### Caveat
 The name of the alias can be any C/C++ style identifier, but you should take care not to 	override any 
    already existing command. The command which will give the path of a command and the command alias without
    parameters gives you a list of all currently defined aliases. Use both commands to determine whether an alias
    would override an existing command.

## Make aliases permanent
If you create the alias command on the command line the alias will be known in the current shell only and only until
you quit the current shell. When you start a new shell your alias will be gone.
When bash shell starts it executes a few files if present. In bash there are 2 hidden files located in each user’s 
home-directory: `.bashrc` and `.bash_aliases`  (other shells have similar files).
Those files are batch files executing each shell command in turn. The `.bashrc` file usually checks for the existence
of the .bash_aliases file and executes it, so under normal circumstances .bash_aliases is the only file you need to
modify. If it is not present then you can create it. The file .bash_aliases is intended for users to modify their
environment.
Add here
    - Environment-variables
    - aliases
    - functions
    - sometimes start commands – e.g. use it to start a python virtual environment
Example `.bash_aliases`

```
#!/usr/bin/bash
[[ "${0}" != "${BASH_SOURCE[0]}" ]] && THIS_FILE="${BASH_SOURCE[0]}" || THIS_FILE="${0}"
THIS_DIR=$(realpath "$(dirname ${THIS_FILE})")
alias l="ls -Fax"
alias ll="ls -Fasl"
alias v=vim
alias m=less
alias cls=clear
alias findExe="find . -perm -u+x -type f "
alias h=history

function addPath() {
	PATHS=$(echo "${PATH}" | tr ':' '\ ')
	DONT_ADD=FALSE
	for i in ${PATHS} nomore; do
		if [ "${i}" = "nomore" ]; then
			break
		fi
		if [ "${i}" = "${1}" ]; then
			DONT_ADD=TRUE
		fi
	done
	if [ "${DONT_ADD}" = "FALSE" ]; then
	export PATH="${PATH}:${1}"
	fi
}
```

## Linux commands return value
Each and every Linux command will return an integral return value, whether one is explicitly specified or not. 
The default value is zero (0) and is interpreted as “The command completed successfully”. Any value returned
that is not equal to zero is interpreted as “An error occurred during execution of the command”
The output value of an operation is captured in a special sell variable $?
Example
```
# assume folder /xxx/yyy/zzz does not exist
[~/myuser]> ls  /xxx/yyy/zzz
ls: cannot access '/xxx/yyy/zzz': No such file or directory
[~/myuser]> ERROR_CODE=$?
[~/myuser]> echo “ERROR_CODE=${ERROR_CODE}”
```
This will write a line similar to `ERROR_CODE=2`

In most cases the explicit error value is not needed, see chapter below about command chaining.

## Directory operations
_cd [\<dir\>]_: change directory. Without parameters go to the home directory

_pushd_: change directory, similar to cd, put current directory on a stack

_popd_: change back to the top directory on the stack

_pwd_: complete path of the current directory

_ls [\<dir\>]_: list contents of directory dir
	Important options:
    - -a: Show all (including hidden)
    - -R: recursive into readable subdirectories
    - -t: sort by last modified
    - -l: long list format – shows ownership and access-rights
    - -1: list one file per line, handy for grep’ing and piping into other commands

_mkdir \<dir\>_: make directory dir, if all directories in the given path exist except the last one.
If you want to create a path and the current user has sufficient rights to do so, every directory
in the path will be created.

e.g.:
	- `mkdir /home/myuser/this/is/my/new_directory` will fail if any of the directories in the 
    path /home/myuser/this/is/my/ does not exist
	- `mkdir -p /home/myuser/this/is/my/new_directory` will succeed if all of the directories in 
    the path /home/myuser/this/is/my/ exist or can be created and are writable

## Operation chaining
On the command-line operations can be chained in a few different ways.
Sequential execution

\<command1\>;\<command2\>;…;\<command_n\>: chaining with a semicolon will execute each of the given commands in turn.
If any commands in the chain fails the next command is executed regardless

\<command1\>&&\<command2\>&&…&&\<command_n\>: chaining with a double ampersand (and) will execute each of the given
commands in turn. If any commands in the chain fails (i.e. if the return code of the command is not equal to zero)
the execution stops

\<command1>||\<command2\>||…||\<command_n\>: chaining with a double pipe (or) will try to execute the commands from left
to right and execution will stop at the first successfully completed command

\<command1\>|\<command2\>|…|\<command_n\>: chaining with a single pipe will execute the commands from left to right and the
output of each command will be the input of the command to the right of the pipe.

xargs: build and execute command lines from standard input. This is helpful when chaining commands. It can be used to
interpret one commands output as a new command and execute it

## Background execution
Unix had from its first incarnation the concept of multiple processes running concurrently (unlike DOS). To run a command
in a background process just append a single ampersand after the command you want to execute (after any parameters that
your command might take).
This will run the command in the background and lets you carry on doing something else on the command line.
A typical use-case for this is when you want to test a client/server application where the server processes requests in an
infinite loop and the client sends a requests and finishes.
```
[~/myuser]> server –host localhost:4711 &         # start the server in the background and return to the command-line
[~/myuser]> client –request ‘do something’        # send request to server for processing
[~/myuser]> client –request ‘do something else’   # send request to server for processing
[~/myuser]> fg                                    # bring the server to the foreground then we can use Ctrl-C to terminate it
```
When any of the processes you started in the background are still running when you close your terminal, they will be terminated.


## IO Redire­ction
On the linux command-line there are 3 special files defined:
- stdin: for input e.g. by keyboard (File 0)
- stdout: for standard output (File 1)
- stderr: for standard error output (File 2)

The input and output files can be redirected to/from files

```
cmd < file          # Input of cmd from file
cmd1 <(cmd2)        # Output of cmd2 as file input to cmd1
cmd > file          # Standard output (stdout) of cmd to file
cmd > /dev/null     # Discard stdout of cmd; literally "write to the special null-file"
cmd >> file         # Append stdout to file
cmd 2> file         # Error output (stderr) of cmd to file
cmd 1>&2            # stdout to same place as stderr
cmd 2>&1            # stderr to same place as stdout
cmd &> file         # Every output of cmd to file
```

## File Operations
```
touch file                      # update the timestamp on a file-system-object (file, dir. ...). Create the file
cat file1 file2 ...file_n       # Cat­enate files to output
less file                       # View and paginate file
file file1                      # Get type of file1
cp file1 file2                  # Copy file1 to file2
mv file1 file2                  # Move file1 to file2
rm file1                        # Delete file1
head -n <num> file1             # Show first <num> lines of file1
tail -n <num> file1             # Show last <num> lines of file1
tail -f file1                   # Output last lines of file1 as it changes
```

## File Permis­sions
chmod 775 file                  # Change mode of file to 775
chmod +x file                   # Make file executable
chmod -x file                   # Make file not executable
chmod +w file                   # Make file writeable
chmod -w file                   # Make file not writeable
chmod -R 600 folder             # Recurs­ively chmod folder to 600
chown user:group file           # Change file owner to user and group to group

## Process Management
```
ps                              # Show snapshot of my processes
ps -aef                         # Show snapshot of *all* processes
top                             # Show information about currently active processes
kill <pid>                      # Kill process with id <pid> as found with "ps" command
pkill name                      # Kill process with name name
killall name                    # Kill all processes with names beginning name
```

## Search contents of files
```
grep <pattern> file1 ...        # Search for pattern in files file1 ... where patterns is a basic regular expression
grep -i                         # Case insens­itive search
grep -r                         # Recursive search
grep -v                         # Inverted search
grep -o                         # Show matched part of file only
```
### Example
Find all lines containing the word "class" in python files:
```
[~/myuser]> grep class *.py
```

Find all lines containing the word "class <classname>" in python files:
```
[~/myuser]> grep "class [a-zA-Z_][a-zA-Z_0-9]*" *.py
```

Find all lines containing the word "class <classname>" in python files and only show the matching strings:
```
[~/myuser]> grep "class -o [a-zA-Z_][a-zA-Z_0-9]*" *.py
```

## Search Files
```
find <dir> -name "name*"        # Find files starting with name in dir
find <dir> -user name           # Find files owned by name in dir
find <dir> -mmin num            # Find files modifed less than num minutes ago in dir
```
### logical parameters
```
-o                              # logical "or"
-a                              # logical "and"
```
### Example
Recursively find all C++ files in a directory:
```
[~/myuser]> find /in/this/directory -name "*.cpp" -o -name "*.cxx" -o -name "*.cc" -o -name "*.h" -o -name "*.hh" -o -name "*.hpp"
```

## Search origin of binaries
```
which command                   # Find the path of a command
whereis command                 # Find binary / source / manual for command
locate file                     # Find file (quick search of system index)
```

## More complex examples
The above tools and techniques is only a subset of what is available on Linux and if you have a particular question 
then google your problem - chances are you find a stackexchange question that answers yours.
Below are some examples that I have used in the past ant that illustrate the power of the commandline.

### Query and filter logfiles as they are written
```
find /my/log/directory -name "*.log" -type f | xargs -I{} tail -f {} | grep "productid=CP-[0-9]+"
```
This command would first find all regular files (`-type f`) with extension "log" in the folder /my/log/directory.
All the found files would then be tailed as they change.
The output would then be filtered to only include lines with matching substrings to "productid=CP-[0-9]+"

