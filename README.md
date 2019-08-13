#IO-Redirection <br>
Created by Shaanan Curtis 2019. <br>
<br>
DESCRIPTION ------------------------------------------------------------ <br>
This program tests input/output redirection using the following long options: <br>
--input for specifying a file as standard input <br>
--output for creating and using a file as standard output <br>
--segfault for forcing a segmentation fault <br>
--catch for registering a SIGSEGV handler that catches the fault <br>
<br>
Note: program designed to take one line of input <br>
<br>
Included in this project is an implementation file by the <br>
name of lab0.cpp as well as a Makefile for building/cleaning <br>
the tarball.  <br>
<br>
MAIN.CPP<br>
The cpp file contains the source code for the main program <br>
as well as several functions incorporated within said program. <br> 
<br>
MAKEFILE<br>
The Makefile creates several object files which<br>
are used in the compilation process of lab0.cpp and includes additional<br>
options for testing as well as for extracting the tarball.<br>
<br>
labio:<br>
anytime a change is made to lab0.cpp,<br>
compile lab0.cpp into the executable lab0.<br>
<br>
check:<br>
a smoke test which is expected to do two<br>
things:<br>
1. create a write-only file called test.txt, <br>
redirecting stdout (fd1) to test.txt.<br>
2. open and read from file, redirecting<br>
stdin (fd0) to test.txt.<br>
<br>
dist:<br>
builds a distribution tarball containing<br>
all files within project folder.<br>
<br>
extract:<br>
additional target included for tarball<br>
extraction.<br>
<br>
clean:<br>
deletes all files created by the <br>
Makefile and returns the directory<br>
to its freshly untarred state.<br>
<br>
