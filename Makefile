run:
	gcc main.c -lSDL2 -lGL -lm && ./a.out 

clean:
	rm -rf a.out
