.SUFFIXES:
.SUFFIXES: .o .cpp
#============================================================
TARGET	=  shortest

C_SOURCES =  Shortest_paths.cpp graph.cpp stack.cpp heap.cpp
C_OBJS     =  Shortest_paths.o graph.o stack.o heap.o
MY_INCLUDES = graph.h stack.h heap.h
# merg.h


CCX = g++
CXXFLAGS = -g -std=c++11
# -Wall

#============================================================
all: $(TARGET)

.o:.cpp	$(MY_INCLUDES)
	$(CCX)  -c  $(CXXFLAGS) $<  

$(TARGET) :   $(C_OBJS)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

# Implicit rules: $@ = target name, $< = first prerequisite name, $^ = name of all prerequisites
#============================================================

ALL_SOURCES = Makefile $(C_SOURCES) $(MY_INCLUDES)

NOTES =
%= otherstuff.np 

clean:
	rm -f $(TARGET) $(C_OBJS) core 

tar: $(ALL_SOURCES) $(NOTES)
	tar cvf $(TARGET).tar $(ALL_SOURCES)  $(NOTES)

$(TARGET).ps: $(ALL SOURCES)
	enscript -pcode.ps $(ALL_SOURCES)


