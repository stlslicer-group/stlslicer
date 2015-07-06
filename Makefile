BIN = main
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
CC = g++
LFLAGS = -Wall -W -std=c++11
CFLAGS = -Wall -W -std=c++11 -c

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LFLAGS) -o $(BIN) $^

%.o: %.cpp
	@$(CC) $(CFLAGS) -MD -MP -c -o $@ $<

clean:
	rm $(OBJS) *~ $(BIN)

-include $(SRCS:.cpp=.d)
