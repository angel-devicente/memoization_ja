TARGET = memo_ja
FC = gfortran
FFLAGS = -Wall -O3

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = getopt.f90 memoization_ja.f90 memo_ja.f90

.PRECIOUS: $(TARGET) 

$(TARGET): $(OBJECTS)
	$(FC) $(FFLAGS) $(OBJECTS) -o $@

clean:
	-rm -f *.mod
	-rm -f $(TARGET)

