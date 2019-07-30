CXX = g++

EXECUTABLE = AI_lmao

SRCS = src/*.cpp *.cpp
HEAD = header/*.h
OBJS  = *.o

IMFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`

$(EXECUTABLE): $(OBJS)
	$(CXX) $(IMFLAGS) $(OBJS) -o $(EXECUTABLE) 

$(OBJS): $(SRCS) $(HEAD)
	$(CXX) $(SRCS) $(IMFLAGS) -c $<

clean:
	$(RM) $(OBJS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)