CXXFLAGS+=-Wall -std=c++11

all:	c64-font-printer
	./$< "POKE53280,0" "poke53280,0"

c64-font-printer:	c64-font-printer.o
	$(CXX) -o $@ $^

clean:
	$(RM) *.o *~ c64-font-printer
