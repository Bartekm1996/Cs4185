PROGRAMS=\
	gasket\
	
gasket_SOURCES=\
	gasket.cc

CC=gcc
CFLAGS=-g -Wall

CXX=g++
CXXFLAGS=$(CFLAGS)

LD=g++
LDFLAGS=

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)        
    LIBS= -L/System/Library/Frameworks -framework glut -framework OpenGL
endif
ifeq ($(UNAME_S),Linux)
    LIBS=  -l glut -l GLU -l GL
endif




all: $(PROGRAMS)

PHONY: clean
.SUFFIXES: .o .c .cc .cpp


define PROGRAM_template
  $(1)_OBJECTS = $${$(1)_SOURCES:.cc=.o}
  OBJECTS += $$($(1)_OBJECTS)

  $(1): $$($(1)_OBJECTS)
endef

$(foreach program, $(PROGRAMS), $(eval $(call PROGRAM_template,$(program))))


clean:
	$(RM) $(OBJECTS)
	$(RM) $(PROGRAMS)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<
.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(PROGRAMS):
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^ 


