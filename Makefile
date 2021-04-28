compile:
	gcc -g -o ctestfmk -Wall -Wextra ctestfmk.c ctestfmk_asserts.c tests_fake.c main.c

libctestfmk_static:
	mkdir -p lib
	gcc -c -Wall -Wextra ctestfmk.c ctestfmk_asserts.c
	mv ctestfmk.o lib/ctestfmk.o
	mv ctestfmk_asserts.o lib/ctestfmk_asserts.o
	cp ctestfmk.h lib/ctestfmk.h
	ar -rc lib/libctestfmk.a lib/*.o
	ranlib lib/libctestfmk.a
	rm lib/*.o

libctestfmk_dynamic:
	mkdir -p lib
	gcc -c -Wall -Wextra -fPIC ctestfmk.c ctestfmk_asserts.c
	mv ctestfmk.o lib/ctestfmk.o
	mv ctestfmk_asserts.o lib/ctestfmk_asserts.o
	gcc -shared -o lib/libctestfmk.so lib/*.o
	rm lib/*.o