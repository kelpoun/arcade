CXX = g++
CXXFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lGL -lglut

all:

mac: src/game.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o arcade $^ $(LIBS)

mac2: src/game2.cpp src/main2.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o arcade $^ $(LIBS)

linux: src/game.cpp src/main.cpp
	$(CXX) -o arcade $^ $(LIBS)

clean:
	rm -f arcade

# USE "make mac" for MACOS SYSTEMS
# EXECUTE USING "DISPLAY=:0 ./arcade" for mac

# USE "make linux" FOR LINUX SYSTEMS (CSIL)
# EXECUTE USING "./arcade" FOR LINUX