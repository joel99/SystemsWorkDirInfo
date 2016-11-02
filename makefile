all: dirInfo.c
	gcc dirInfo.c -o dirInfoExe  

clean:
	rm *~
	rm *.o

run: dirInfoExe
	./dirInfoExe
