RSHELL
===

Licensing Information: READ LICENSE
---
Author and contributor List
----
Atte Myllykoski

All other bugs and fixes can be sent to amyll001@ucr.edu

Reported bugs/fixes will be submitted to correction.

File List
----

```
.:

Makefile

LICENSE

README.md

./src

./tests
```
```
/src:

main.cpp
```
```
./tests
```
How to run file
----
To download and run RSHELL enter the following into your terminal
```
$ git clone http://github.com/amyll001/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```

RShell will now open up instead of BASH and you can execute many of
the commands as included in the regular terminal.

The connecter is an optional way you can run multiple commands at once. If a command is followed by ;, then the nextcommand is always executed; if a command is followed by &&, then the next command is executed only if the first one succeeds; if a command is followed by ||, then the next command is executed only if the first one fails

**Example**
```
$ ls -a
$ echo hello
$ mkdir test
```
is equivalent to: 
```
$ ls -a; echo hello; mkdir test
```
Program reviewd by the University of California, Riverside.
----
Basic overview of Command Shells: [HERE](http://linuxgazette.net/111/ramankutty.html)

This program is developed to write a simple command shell called "RShell"
* It will offer similarities such as the normal BASH command shell.
* Execute the command of ls to a file (with given instructions above)
* Can call all commands of BASH with execvp function
* Have special built in command "exit" to exit RSHELL and return to your local SHELL

BUGS
----
1. if you use the `||` connector then only the commands before it will execute regardless if they fail or not
2. If you use the `;` connector and don't follow it up with a command then it will cause a segmentation fault.
3. Must format the connectors: no space before semi-colon and yes space after, space before and after `||` and `&&` connector. If not then command will fail.
4. If only enter a connector with no commands program will segfault.
5. Cant use the exit command with a connector.
