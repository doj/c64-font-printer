CXXFLAGS+=-Wall -std=c++11

all:	c64-font-printer
	./$< 'LOAD"*",8,1' 'SEARCHING FOR *' 'LOADING' 'READY.' 'RUN'
	./$< 'load"*",8,1' 'searching for *' 'loading' 'ready.' 'run'

c64-font-printer:	c64-font-printer.o
	$(CXX) -o $@ $^

clean:
	$(RM) *.o *~ c64-font-printer
