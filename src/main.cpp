#include <SFML/Graphics.hpp>//Simple Fast Multi-media Library
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "Entity.h"
#include "Vec2.h"
#include "Components.h"
#include "SimpleEntity.h"
#include "EntityManager.h"


int main()
{
    unsigned int windowWidth = 1920u;
    unsigned int windowHeight = 1080u;

    int frameLimit = 120;

    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "CMake SFML Project", sf::Style::Default);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(frameLimit);
    sf::Image iconImage("assets/SFMLPracticeIcon.png");
    window.setIcon(iconImage);
 
    sf::ConvexShape mouse;

    mouse.setPointCount(3);
    mouse.setPoint(0, {0,0});
    mouse.setPoint(1, { 30,30 });
    mouse.setPoint(2, { 0,50});
    mouse.setFillColor(sf::Color(64, 64, 64));
    mouse.setOutlineColor(sf::Color(255, 255, 255));

    std::ifstream fin("assets/config.txt");

    sf::Vector2i mousePosition;

    const sf::Font bitFont("assets/8bitOperatorPlus8-Regular.ttf");

    sf::Text text(bitFont);

    text.setPosition({1000, 10});

    sf::Text fpsText(bitFont);
    fpsText.setPosition({ 100,10 });
    fpsText.setFillColor(sf::Color(255, 255, 255));


    sf::Text pauseText(bitFont);

   
    pauseText.setString("PAUSED");
    pauseText.setFillColor(sf::Color(255, 255, 255));
    pauseText.setScale({2.0f,2.0f});
    pauseText.setOrigin(pauseText.getLocalBounds().getCenter());
    pauseText.setPosition({(float)windowWidth/2 , (float)windowHeight/2 });

    sf::Text clockText(bitFont);
    clockText.setString("Clock");
    clockText.setFillColor(sf::Color(255, 255, 255));
    clockText.setPosition({ (float)windowWidth-200, 100.0f});

    int counterLoop = 0;

    Vec2 movementDir(0,0);
    float movementMultiplyer = .5f;
    float sprintMultiplyer = 2.0f;

    int keysDown = 0;

    sf::Clock clock;
    


    sf::Texture ceilingTexture("assets/CeilingSquareAltered.png");
    ceilingTexture.setSmooth(false);
    sf::Sprite ceilingSprite(ceilingTexture);
    ceilingSprite.setPosition({ (float)windowWidth - 256.0f, (float)windowHeight - 256.0f });


    bool keyDown_A = false;
    bool keyDown_D = false;
    bool keyDown_W = false;
    bool keyDown_S = false;
    bool keyDown_Shift = false;
    bool mouseDown_LeftButton = false;
    

    sf::Clock deltaTimeClock;
    float deltaTime = 0.0f;

    sf::Clock framesPerSecondClock;
    size_t framesSinceClockTick = 0;

    //SimpEntPtr testSimpleEntity = manager.addEntity("test entity");

    bool isPaused = false;


    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.getElapsedTime().asMicroseconds() / 1000.0f;
        deltaTimeClock.restart();
        mouseDown_LeftButton = false;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            //window.setKeyRepeatEnabled(false) use if I want to make the press a single action rather than on a heartbeat 
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    if (!isPaused)
                    {
                        isPaused = true;
                        clock.stop();
                    }
                    else 
                    {
                        isPaused = false; 
                        clock.start();

                    }

                if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                {
                    keyDown_A = true;


                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                {
                    keyDown_D = true;


                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                {
                    keyDown_W = true;


                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    keyDown_S = true;


                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::LShift)
                {
                    keyDown_Shift = true;


                }

                
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->scancode == sf::Keyboard::Scancode::A)
                {

                    keyDown_A = false;
                }

                if (keyReleased->scancode == sf::Keyboard::Scancode::D)
                {

                    keyDown_D = false;
                }
                if (keyReleased->scancode == sf::Keyboard::Scancode::W)
                {

                    keyDown_W = false;
                }

                if (keyReleased->scancode == sf::Keyboard::Scancode::S)
                {

                    keyDown_S = false;
                }
                if (keyReleased->scancode == sf::Keyboard::Scancode::LShift)
                {

                    keyDown_Shift = false;
                }

                
            }
            else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                //std::cout << "x" << (float)mousePosition.x << "y" << (float)mousePosition.y << std::endl;
                mousePosition = mouseMoved->position;
                mouse.setPosition({(float)mousePosition.x,(float)mousePosition.y});

            }
            else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseClick->button == sf::Mouse::Button::Left)
                {
                    mouseDown_LeftButton = true;
                    std::cout << "button down" << std::endl;
                }

            }
            else if (const auto* mouseRelease = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseRelease->button == sf::Mouse::Button::Left)
                {
                    mouseDown_LeftButton = false;
                }

            }

            else if (const auto* resized = event->getIf<sf::Event::Resized>()) 
            {
                windowWidth = resized->size.x;
                windowHeight = resized->size.y;
                window.create(sf::VideoMode({ windowWidth, windowHeight }), "CMake SFML Project", sf::Style::Default);
                window.setMouseCursorVisible(false);
                window.setFramerateLimit(frameLimit);
                sf::Image iconImage("assets/SFMLPracticeIcon.png");
                window.setIcon(iconImage);
                pauseText.setPosition({ (float)windowWidth / 2 , (float)windowHeight / 2 });
            }

        }

        if (isPaused)
        {

            window.clear();
            window.draw(pauseText);
            window.display();
            continue;
        }

        //std::cout<< testSimpleEntity.use_count() << std::endl;
        if(mouseDown_LeftButton)
        {
            
  
        }
        movementDir.x = 0;
        movementDir.y = 0;

        if (keyDown_A) 
        {
            movementDir.x += -1;
        }

        if (keyDown_D)
        {
            movementDir.x += 1;
        }
        if (keyDown_W)
        {
            movementDir.y += -1;
        }

        if (keyDown_S)
        {
            movementDir.y += 1;
        }
        if (keyDown_Shift) 
        {
            movementDir.x = movementDir.x * sprintMultiplyer;
            movementDir.y = movementDir.y * sprintMultiplyer;
        }

      

        
        window.clear();
        //magical draw area

        std::string clockString = std::to_string(clock.getElapsedTime().asSeconds());
        clockText.setString(clockString);

        std::string deltaTimeString = std::to_string( deltaTime);
        fpsText.setString(deltaTimeString);
        window.draw(ceilingSprite);
        window.draw(mouse);
        window.draw(clockText);
        window.draw(fpsText);

        framesSinceClockTick++;
        float elapsedSeconds = framesPerSecondClock.getElapsedTime().asSeconds();
        if (elapsedSeconds >= 1.0f)
        {
            text.setString(std::to_string(framesSinceClockTick / elapsedSeconds));
            float colorCodedfps = std::clamp((framesSinceClockTick / elapsedSeconds) / frameLimit * 255.0f, 0.0f, 255.0f);
            text.setFillColor(sf::Color(255 - colorCodedfps, colorCodedfps, .5));
            framesPerSecondClock.restart();
            framesSinceClockTick = 0;

            

        }
 
        window.draw(text);
        //end magical draw area
        window.display();

        counterLoop = (counterLoop +1)% 256;

        
       
        
    }
}
