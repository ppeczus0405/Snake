CXX = g++
CXXFLAGS = -Wextra -Wshadow -Wall -pedantic -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0 -O2 -std=c++17
CXXLINKFLAGS = -Wextra -Wshadow -Wall -pedantic -O2 -std=c++17 -c

OFILES = Bin/texturemenager.o Bin/texturetype.o Bin/renderedtexture.o Bin/gameobject.o Bin/snake.o Bin/fruit.o Bin/button.o Bin/game.o Bin/inputmenager.o Bin/uibegin.o Bin/uiend.o

all: texturemenager.o texturetype.o gameobject.o renderedtexture.o snake.o button.o game.o fruit.o inputmenager.o uibegin.o uiend.o Snake


game.o: Source/game.cpp Source/game.h
	$(CXX) $(CXXLINKFLAGS) Source/Game.cpp -o Bin/game.o

texturemenager.o: Source/TextureMenager.h Source/TextureMenager.cpp
	$(CXX) $(CXXLINKFLAGS) Source/TextureMenager.cpp -o Bin/texturemenager.o

renderedtexture.o: Source/RenderedTexture.h Source/RenderedTexture.cpp
	$(CXX) $(CXXLINKFLAGS) Source/RenderedTexture.cpp -o Bin/renderedtexture.o

texturetype.o: Source/TextureType.h Source/TextureType.cpp
	$(CXX) $(CXXLINKFLAGS) Source/TextureType.cpp -o Bin/texturetype.o

gameobject.o: Source/GameObject.h Source/GameObject.cpp
	$(CXX) $(CXXLINKFLAGS) Source/GameObject.cpp -o Bin/gameobject.o

snake.o: Source/Snake.h Source/Snake.cpp
	$(CXX) $(CXXLINKFLAGS) Source/Snake.cpp -o Bin/snake.o

fruit.o: Source/Fruit.h Source/Fruit.cpp
	$(CXX) $(CXXLINKFLAGS) Source/Fruit.cpp -o Bin/fruit.o

button.o: Source/Button.h Source/Button.cpp
	$(CXX) $(CXXLINKFLAGS) Source/Button.cpp -o Bin/button.o

inputmenager.o: Source/InputMenager.h Source/InputMenager.cpp
	$(CXX) $(CXXLINKFLAGS) Source/InputMenager.cpp -o Bin/inputmenager.o

uibegin.o: Source/UIBegin.h Source/UIBegin.cpp
	$(CXX) $(CXXLINKFLAGS) Source/UIBegin.cpp -o Bin/uibegin.o

uiend.o: Source/UIEnd.h Source/UIEnd.cpp
	$(CXX) $(CXXLINKFLAGS) Source/UIEnd.cpp -o Bin/uiend.o

Snake: $(OFILES) Source/main.cpp
	$(CXX) $(CXXFLAGS) $(OFILES) Source/main.cpp -o Bin/Snake

clean:
	rm -r $(OFILES) Bin/Snake