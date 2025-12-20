#include <SFML/Graphics.hpp>//Simple Fast Multi-media Library
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "Game.h"
#include "GameEngine.h"



template <typename T>
T custom_lerp(T a, T b, T t) {
    return a + t * (b - a);
}

int main()
{
    std::string config = std::string("assets/config.txt");
    
	GameEngine gameEngine(config);
	gameEngine.run();
    /*
    while (true)
    {
        Game game(config);
        game.run();
    }
    */
    return 0;
}
