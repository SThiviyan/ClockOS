CXXFLAGS=-I. -I../include -W -Wall -Wextra -Wno-unused-parameter -O3
OBJECTS=timeutils.o
Target=libutils




$(Target).a : $(OBJECTS)
	$(AR) rcs $@ $^


clean:
	rm -f $(OBJECTS) $(Target)
