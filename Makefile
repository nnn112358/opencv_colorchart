CC = g++
CFLAGS = -g -Wall  -lm

SRCS = opencv_colorchart.cpp
PROG = opencv_colorchart

OPENCV = `pkg-config --cflags opencv4` `pkg-config --libs opencv4` 
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
	

