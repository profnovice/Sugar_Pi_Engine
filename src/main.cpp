#include <SFML/Graphics.hpp>//Simple Fast Multi-media Library
#include <iostream>
#include <string>
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


    std::ifstream fin("assets/config.txt");

    std::vector<Entity> entityVector;

    int newId;
    int newRadius;
    int newR;
    int newG;
    int newB;
    int newPosx;
    int newPosy;

    
    while (fin >> newId) 
    {
        std::cout << "read once" << std::endl;
        

        fin >> newRadius;
        fin >> newR;
        fin >> newG;
        fin >> newB;
        fin >> newPosx;
        fin >> newPosy;
        sf::CircleShape newCircle(newRadius);
        newCircle.setFillColor(sf::Color(newR, newG, newB));
        Entity newEntity(newId, newCircle);
        newEntity.setVecPosition(Vec2(newPosx, newPosy));

   
        entityVector.push_back(newEntity);


    }


    sf::Font bitFont;

    bitFont.openFromFile("assets/8bitOperatorPlus8-Regular.ttf");

    sf::Text text(bitFont);
    
    text.setPosition({1000, 10});
    text.setFillColor(sf::Color(255, 255, 255));
    

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
        text.setString(std::to_string(counterLoop));

        myEntity.setVecPosition(Vec2(myEntity.getVecPosition().x, myEntity.getVecPosition().y + 1) );
        window.draw(myEntity.getShape());

        text.setFillColor(sf::Color(counterLoop, 255 - counterLoop, .5));

        window.draw(text);
       
        for (Entity ent : entityVector)
        {
            window.draw(ent.getShape());

        }



        //end magical draw area
        window.display();

        counterLoop = (counterLoop +1)% 256;
    }
}
