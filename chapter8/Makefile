.PHONY : ALL
ALL : t8.2 t8.3 t8.4 t8.6.1 t8.6.2 t8.10.echo t8.10 echo execl

t8.2 : t8.2.c
	gcc -std=c99 -Wall -o t8.2 t8.2.c

t8.3 : t8.3.c
	gcc -std=c99 -Wall -o t8.3 t8.3.c

t8.4 : t8.4.c
	gcc -std=c99 -Wall -o t8.4 t8.4.c

t8.6.1 : t8.6.1.c
	gcc -std=c99 -Wall -o t8.6.1 t8.6.1.c

t8.6.2 : t8.6.2.c
	gcc -std=c99 -Wall -o t8.6.2 t8.6.2.c

t8.10.echo : t8.10.echo.c
	gcc -std=c99 -Wall -o t8.10.echo t8.10.echo.c

t8.10 : t8.10.c
	gcc -std=c99 -Wall -o t8.10 t8.10.c

echo : echo.c
	gcc -std=c99 -Wall -o echo echo.c

execl : execl.c
	gcc -std=c99 -Wall -o execl execl.c

.PHONY : clean
clean :
	rm -rf t8.2 t8.3 t8.4 t8.6.1 t8.6.2 t8.10.echo t8.10 echo execl
