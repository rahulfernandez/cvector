all: vector-test

vector-test: src/*.c src/*.h
	gcc $^ -o $@

clean:
	rm -f vector-test

