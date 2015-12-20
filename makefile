all: 
	cd SP; make all
	$(MAKE) ex3
ex3: 	main.o SP_Aux.o SP_Tree.o
	gcc -std=c99 -Wall -Werror -pedantic-errors  main.o SP_Aux.o SP_Tree.o -o ex3

main.o: main.c SP_Aux.h SP_Tree.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c main.c 


SP_Tree.o: SP_Tree.c SP_Tree.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c SP_Tree.c

SP_Aux.o: SP_Aux.c SP_Aux.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c SP_Aux.c

clean:
	rm -f main.o SP_Aux.o SP_Tree.o;cd SP; make clean
