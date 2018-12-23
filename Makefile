IDIR=firnlibs
GPP=g++
#CFLAGS=-I$(IDIR) $(shell pkg-config --cflags opencv) -pthread -std=c++14 -O2
CFLAGS=-pthread -std=c++14 -O3 #-DGUARDEDVARDEBUG

ODIR=obj
LDIR=

#LIBS=-lgmpxx -lgmp -lmpfr -ljsoncpp $(shell pkg-config --libs opencv) -lcryptopp
#TAGLIBS=-ltag -lz
BOOSTLIBS=-lboost_filesystem -lboost_system
#SQLITELIBS=-lsqlite3
#MP3LIBS=-lmpg123
#SFMLLIBS=-lsfml-system -lsfml-network -lsfml-audio
LIBS=-lcryptopp -ljsoncpp $(BOOSTLIBS) #$(TAGLIBS) $(BOOSTLIBS) $(SQLITELIBS) $(MP3LIBS) $(SFMLLIBS)

#_DEPS=complex.hpp mandelbrot.hpp buildimage.hpp colors.hpp workerthread.hpp CyclicVar.hpp saveroutine.hpp cryptozip.hpp halfspan.hpp
_DEPS=
DEPS=$(LDEPS)

_LDEPS=
LDEPS=$(patsubst %,$(IDIR)/%,$(_LDEPS))

_OBJ=batterystat.o firnlibs/files/files.o firnlibs/string/string.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS) $(LDEPS)
	mkdir -p $(dir $(@))
	$(GPP) -c -o $@ $< $(CFLAGS)

batterystat: $(OBJ)
	$(GPP) -o $@ $^ $(CFLAGS) $(LIBS)

#pch.h.gch: pch.h
	#$(GPP) -o $@ $< $(CFLAGS)

.PHONY:clean

clean:
	rm -rf $(ODIR)/*

run: batterystat
	./batterystat


test: clean batterystat
	./batterystat

install: clean batterystat
	cp batterystat ~/customscripts/
