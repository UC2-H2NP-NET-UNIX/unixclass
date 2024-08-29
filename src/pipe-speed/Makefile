all: namedpipe-speed pipe-speed
	@if [ ! -p fifofile ]; then  mkfifo fifofile; fi
	@echo "All done"

namedpipe-speed: namedpipe-speed.c
	gcc -o namedpipe-speed namedpipe-speed.c

pipe-speed: pipe-speed.c
	gcc -o pipe-speed pipe-speed.c

test: namedpipe-speed pipe-speed
	@if [ ! -p fifofile ]; then  mkfifo fifofile; fi
	@echo "Testing named pipe"
	@./namedpipe-speed
	@echo "Testing pipe"
	@./pipe-speed

clean:
	rm -f namedpipe-speed pipe-speed fifofile

# End of Makefile