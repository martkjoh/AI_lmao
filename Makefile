CXX = g++

EXECUTABLE = main

SRCS = *.cpp
OBJS  = *.o

IMFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXECUTABLE) 

$(OBJS): $(SRCS)
	$(CXX) $(SRCS) -c

clean:
	$(RM) $(OBJS)
	$(RM) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)