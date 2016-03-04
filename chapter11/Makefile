.PHONY : ALL
ALL : t11.3 t11.4

t11.3 : t11.3.c
	gcc -Wall -o t11.3 t11.3.c

.PHONY : clean

t11.4 : t11.4.c
	gcc -Wall -pthread -o t11.4 t11.4.c

clean :
	rm -rf t11.3 t11.4
