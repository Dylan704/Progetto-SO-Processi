# Dichiarazione dell'eseguibile
a.out: clean main.o Menu.o Area_gioco.o Personaggi.o
	gcc main.o Menu.o Area_gioco.o Personaggi.o -l ncurses

# Regole di compilazione per i file oggetto
main.o: main.c  Menu.h Area_gioco.h Struct_enum.h
	gcc -c main.c -o main.o

Menu.o: Menu.c Menu.h Struct_enum.h
	gcc -c Menu.c -o Menu.o

Area_gioco.o: Area_gioco.c Area_gioco.h Personaggi.h Menu.h Struct_enum.h
	gcc -c Area_gioco.c -o Area_gioco.o

Personaggi.o: Personaggi.c Personaggi.h Area_gioco.h Struct_enum.h
	gcc -c Personaggi.c -o Personaggi.o


# Pulizia dei file oggetto e dell'eseguibile
clean:
	rm -f *.o a.out
