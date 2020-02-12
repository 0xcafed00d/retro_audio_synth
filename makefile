CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
#SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_LIB = -L/home/lmw/src/SDL2-2.0.9/build/.libs -lSDL2 -Wl,-rpath=/home/lmw/src/SDL2-2.0.9/build/.libs
SDL_INCLUDE = -I/usr/local/include

CXXFLAGS = -ggdb -Wall -c -std=c++11 $(SDL_INCLUDE)
# CXXFLAGS = -O3 -Wall -c -std=c++11 $(SDL_INCLUDE) 
LDFLAGS = $(SDL_LIB) 
EXE = audio

all: $(EXE)

$(EXE): bin/main.o bin/audio.o bin/wavtools.o bin/adsr_synth.o  bin/wave_synth.o
	$(CXX) $^ $(LDFLAGS) -o $@
	@cowsay "Built All The Things!!!"

bin/audio.o: src/audio.cpp src/audio.h
	$(CXX) $(CXXFLAGS) $< -o $@

bin/adsr_synth.o: src/adsr_synth.cpp src/adsr_synth.h src/sample_source.h
	$(CXX) $(CXXFLAGS) $< -o $@

bin/wave_synth.o: src/wave_synth.cpp src/wave_synth.h src/sample_source.h
	$(CXX) $(CXXFLAGS) $< -o $@

bin/wavtools.o: src/wavtools.cpp src/wavtools.h src/sample_source.h
	$(CXX) $(CXXFLAGS) $< -o $@

bin/main.o: src/main.cpp src/audio.h src/adsr_synth.h src/wave_synth.h src/wavtools.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm bin/*.o && rm $(EXE)
	
run: all
	./$(EXE)

