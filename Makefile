rsh: rsh.c
	gcc -g -o rsh -Wall -std=gnu11 rsh.c

myspawn: myspawn.c
	gcc -g -o myspawn -Wall -std=gnu11 myspawn.c

@PHONY: clean

clean:
	rm -f rsh

@PHONY: clean_dir

clean_dir:
	rm -rf clean/*
	cp test_cases/* clean/
