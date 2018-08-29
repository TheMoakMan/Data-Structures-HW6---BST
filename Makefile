SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
HDRS = $(wildcard *.h)
HPPS = ${wildcard *.hpp}
CFLAGS = -std=c++11

CPP = g++

.PHONY: clean
	
default: program

program: ${OBJS}
	${CPP} ${CFLAGS} $^ -o program
	
%.o: %.cpp ${HDRS} ${HPPS}
	${CPP} ${CFLAGS} -c $<
	
clean: 
	-@rm -f program
	-@rm -f ${OBJS}
	


	

