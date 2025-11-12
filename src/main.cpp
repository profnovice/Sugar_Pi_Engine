#include <SFML/Graphics.hpp>//Simple Fast Multi-media Library
#include <fstream>
#include "Entity.h"
#include "Vec2.h"






//namespace
namespace globalVariables
{
    float grav = 9.81f;

}


int main()
{

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    int circleRadius = 64;
    sf::CircleShape myShape(circleRadius);
    myShape.setPosition({512,512});
    sf::Color newColor(255, 255, 255);
    myShape.setFillColor(newColor);

    Entity myEntity(1,myShape);
    int counterLoop = 0;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

           
     
        }
        
        window.clear();
        //magical draw area
        myEntity.setVecPosition(Vec2(myEntity.getVecPosition().x, myEntity.getVecPosition().y + 1) );
        window.draw(myEntity.getShape());

       



        //end magical draw area
        window.display();

        counterLoop = (counterLoop +1)% 256;
    }
}
