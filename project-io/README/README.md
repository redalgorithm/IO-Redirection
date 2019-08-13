Created by Shaanan Curtis 2019.

DESCRIPTION ------------------------------------------------------------
This program tests input/output redirection using the following long options:
--input for specifying a file as standard input
--output for creating and using a file as standard output
--segfault for forcing a segmentation fault
--catch for registering a SIGSEGV handler that catches the fault

Note: program designed to take one line of input

Included in this project is an implementation file by the
name of lab0.cpp as well as a Makefile for building/cleaning
the tarball.  

MAIN.CPP
The cpp file contains the source code for the main program 
as well as several functions incorporated within said program.  

MAKEFILE
The Makefile creates several object files which
are used in the compilation process of lab0.cpp and includes additional
options for testing as well as for extracting the tarball.

labio:
anytime a change is made to lab0.cpp,
compile lab0.cpp into the executable lab0.

check:
a smoke test which is expected to do two
things:
1. create a write-only file called test.txt, 
redirecting stdout (fd1) to test.txt.
2. open and read from file, redirecting
stdin (fd0) to test.txt.

dist:
builds a distribution tarball containing
all files within project folder.

extract:
additional target included for tarball
extraction.

clean:
deletes all files created by the 
Makefile and returns the directory
to its freshly untarred state.