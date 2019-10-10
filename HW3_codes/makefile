.SUFFIXES:
.SUFFIXES: .o .cpp
#============================================================
TARGET	=  bst

C_SOURCES =  tree.cpp mainBST.cpp
C_OBJS     =  tree.o mainBST.o
MY_INCLUDES = tree.h

CCX = g++
CXXFLAGS = -g -std=c++14  -Wall

#============================================================
all: $(TARGET)

.o:.cpp	$(MY_INCLUDES)
	$(CCX)  -c  $(CXXFLAGS) $<  

$(TARGET) :   $(C_OBJS)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

# Implicit rules: $@ = target name, $< = first prerequisite name, $^ = name of all prerequisites
#============================================================

ALL_SOURCES = makeFind $(C_SOURCES) $(MY_INCLUDES) Sorted100K.txt

NOTES =

clean:
	rm -f $(TARGET) $(C_OBJS) core *~

tar: $(ALL_SOURCES) $(NOTES)
	tar cvf $(TARGET).tar $(ALL_SOURCES)  $(NOTES)

$(TARGET).ps: $(ALL SOURCES)
	enscript -pcode.ps $(ALL_SOURCES)


