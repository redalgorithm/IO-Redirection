#Project-IO Makefile
#Description in README.md

labio: main.cpp
	g++ -g -Wall -Wextra main.cpp -o labio

check: labio
	./labio --output=test.txt --input=test.txt

dist:
	tar pczf project-io.tar.gz *

extract:
	tar xzvf project-io.tar.gz

clean:
	rm -r *.dSYM
	rm labio
	rm *.tar.gz
	rm *.txt
