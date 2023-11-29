# MAKE FILE FOR MAC
CXX = g++
CXXFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lGL -lglut

TARGET = arcade

$(TARGET): src/arcade.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $^ $(LIBS)

clean:
	rm -f $(TARGET)

# EXECUTE USING "DISPLAY=:0 ./arcade"