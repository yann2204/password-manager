
CPP = g++
CFLAGS += -g -Wall 
OBJS = main.o element.o decodage.o codage.o


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