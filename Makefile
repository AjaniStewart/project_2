# A Sample Makefile

SRCS       = $(wildcard *.cpp)
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  
EXEC       := project2 
CXX        := g++-9
CXXFLAGS   += -Wall -g -std=c++11
LDFLAGS    := -image_base %s -pagezero_size 1000400000

$(EXEC): $(OBJS) new_main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@  $(OBJS) new_main.o

.PHONY: clean cleanall
cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJS)


