build:
	gcc -std=c17 src/*.c -o bin/xencoder -lglfw -lGL -lleif -lclipboard -lxcb -lm

run: 
	./bin/xencoder

clean:
	rm /bin/xencoder
