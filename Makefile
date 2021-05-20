compile:
	gcc -g -o example/ctestfmk_example -Wall -Wextra src/ctestfmk.c src/ctestfmk_asserts.c example/tests_fake.c example/main.c

libctestfmk_static:
	mkdir -p lib
	gcc -c -Wall -Wextra src/ctestfmk.c src/ctestfmk_asserts.c
	mv ctestfmk.o lib/ctestfmk.o
	mv ctestfmk_asserts.o lib/ctestfmk_asserts.o
	cp src/ctestfmk.h lib/ctestfmk.h
	ar -rc lib/libctestfmk.a lib/*.o
	ranlib lib/libctestfmk.a
	rm lib/*.o

libctestfmk_dynamic:
	mkdir -p lib
	gcc -c -Wall -Wextra -fPIC src/ctestfmk.c src/ctestfmk_asserts.c
	mv ctestfmk.o lib/ctestfmk.o
	mv ctestfmk_asserts.o lib/ctestfmk_asserts.o
	gcc -shared -o lib/libctestfmk.so lib/*.o
	rm lib/*.o