RSHELL
===

Licensing Information: READ LICENSE
---
Project source can be downloaded from https://github.com/amyll001/rshell.git
----

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
Once you have cloned the directory to your local machine, 
Follow the directions below:
----
1. `cd` into rshell directory
2. Call `make`
3. `cd` into `bin`
4. Call `rshell`
5. Can do steps 3 & 4 by calling bin/rshell

RShell will now open up instead of BASH and you can execute many of
the commands as included in the regular terminal.

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


