run: clean copy paste
clean:
	rm wincopy.exe || true
	rm winpaste.exe || true
copy:
	gcc wincopy.c -g -o wincopy.exe
paste:
	gcc winpaste.c -g -o winpaste.exe
build:
	gcc wincopy.c -O3 -g -o wincopy.exe
	gcc winpaste.c -O3 -g -o winpaste.exe
