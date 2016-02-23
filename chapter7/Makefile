.PHONY : ALL
ALL : t7.2 t7.3.1 t7.3.2

t7.2 : t7.2.c
	gcc -std=c99 -Wall t7.2.c -o t7.2

t7.3.1 : t7.3.1.c
	gcc -std=c99 -Wall t7.3.1.c -o t7.3.1

t7.3.2 : t7.3.2.c
	gcc -std=c99 -Wall t7.3.2.c -o t7.3.2

.PHONY : clean
clean :  
		rm -rf t7.2 t7.3.1 t7.3.2
