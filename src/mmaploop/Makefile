all: mmaploopread mmaploopwrite mmap.dat
	@echo "All done"

mmap.dat:
	@echo -n "abcdefghijklmnopqrstuvwxyz" > mmap.dat

mmaploopread: mmaploopread.c
	gcc mmaploopread.c -o mmaploopread

mmaploopwrite:mmaploopwrite.c
	gcc mmaploopwrite.c -o mmaploopwrite

clean:
	rm mmaploopread mmaploopwrite mmap.dat

