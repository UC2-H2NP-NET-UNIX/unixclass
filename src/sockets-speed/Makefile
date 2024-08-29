all: afinet-speed aflocal-speed
	@echo "All done."

afinet-speed: afinet-speed.c
	gcc -o $@ $<

aflocal-speed: aflocal-speed.c
	gcc -o $@ $<

test: all
	./afinet-speed
	./aflocal-speed

clean:	
	rm -f afinet-speed aflocal-speed
	@echo "All cleaned up."
