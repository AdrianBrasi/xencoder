build:
	gcc src/*.c -o bin/xencoder -lglfw -lGL -lleif -lclipboard -lxcb -lm

run: 
	./bin/xencoder

clean:
	rm /bin/xencoder
