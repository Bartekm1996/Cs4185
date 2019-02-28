NAME=chart

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)        
    LIBS= -L/System/Library/Frameworks -framework glut -framework OpenGL
endif
ifeq ($(UNAME_S),Linux)
    LIBS=  -l glut -l GLU -l GL
endif


SOURCES=\
	chart.cc\
	circlePlot.cc\


CC=gcc
CFLAGS=-g -Wall -Wno-everything

CXX=g++
CXXFLAGS=$(CFLAGS)

LD=g++
LDFLAGS=


OBJECTS=${SOURCES:.cc=.o}


.PHONY: clean
.SUFFIXES: .o .c .cc .cpp


all: program

clean:
	$(RM) $(OBJECTS)
	$(RM) $(NAME)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<


program: $(NAME)
$(NAME): $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

