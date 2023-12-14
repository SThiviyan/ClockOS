CXXFLAGS=-Wall -O3 -g
OBJECTS=main.cpp
BINARIES=main

RGB_INCDIR=matrix/include
RGB_LIBDIR=matrix/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a

ROTARY_INCDIR=rotary/include
ROTARY_LIBDIR=rotary/lib
ROTARY_LIBRARY_NAME=rotary
ROTARY_LIBRARY=$(ROTARY_LIBDIR)/lib$(ROTARY_LIBRARY_NAME).a

MAGICK_CXXFLAGS?=$(shell GraphicsMagick++-config --cppflags --cxxflags)
MAGICK_LDFLAGS?=$(shell GraphicsMagick++-config --ldflags --libs)

LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) \
	 -L$(ROTARY_LIBDIR) -l$(ROTARY_LIBRARY_NAME) \
         -lrt -lm -lpthread $(MAGICK_CXXFLAGS) $(MAGICK_LDFLAGS) 

all : main

main : $(OBJECTS) $(RGB_LIBRARY) $(ROTARY_LIBRARY)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

$(ROTARY_LIBRARY): FORCE
	$(MAKE) -C $(ROTARY_LIBDIR)

clock.o : main.cpp

%.o : %.cpp
	$(CXX) -I$(ROTARY_INCDIR) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(BINARIES)
	$(MAKE) -C $(RGB_LIBDIR) clean
	$(MAKE) -C $(ROTARY_LIBDIR) clean

FORCE:
.PHONY: FORCE
