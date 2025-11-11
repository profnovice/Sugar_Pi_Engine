#include <SFML/Graphics.hpp>
//Hello GitWorld!

class Entity 
{
    int m_entityID;


public:
    Entity(int entityID)
        :m_entityID(entityID)
    {


    }
    const int getEntityID()
    {
        return m_entityID;
    }


};






int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    int circleRadius = 64;
    sf::CircleShape myShape(circleRadius);
    myShape.setPosition({512,512});
    sf::Color newColor(255, 255, 255);
    myShape.setFillColor(newColor);


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

        window.draw(myShape);

        myShape.setPosition({ myShape.getPosition().x, myShape.getPosition().y - 1});




        //end magical draw area
        window.display();
    }
}
