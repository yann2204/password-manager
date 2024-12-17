
CPP = g++
CFLAGS += -Wall -g
OBJS = main.o element.o decodage.o codage.o
OBJSTEST = test.o element.o

all : decrypt
main.o : main.cpp
	$(CPP) $(CFLAGS) -c main.cpp
element.o : element.cpp
	$(CPP) $(CFLAGS) -c element.cpp
codage.o : codage.cpp
	$(CPP) $(CFLAGS) -c codage.cpp
decodage.o : decodage.cpp
	$(CPP) $(CFLAGS) -c decodage.cpp
decrypt: $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $(OBJS) 

clean:
	rm *.o decrypt

test: test.exe
element.o : element.cpp
	$(CPP) $(CFLAGS) -c element.cpp
test.exe : $(OBJSTEST)
	$(CPP) $(CFLAGS) -o $@ $(OBJSTEST)
