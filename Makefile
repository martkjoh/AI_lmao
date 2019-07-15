CXX = g++

EXECUTABLE = fil

SRCS = src/*.cpp
HEAD = header/*.h
OBJS  = *.o

IMFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXECUTABLE) 

$(OBJS): $(SRCS) $(HEAD)
	$(CXX) main.cpp $(SRCS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)