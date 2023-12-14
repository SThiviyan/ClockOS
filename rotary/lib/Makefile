CXXFLAGS=-I. -I../include -W -Wall -Wextra -Wno-unused-parameter -O3 -pthread
OBJECTS= rotary.o GPIO.o
Target= librotary





$(Target).a : $(OBJECTS)
	$(AR) rcs $@ $^


clean:
	rm -f $(OBJECTS) $(Target)
