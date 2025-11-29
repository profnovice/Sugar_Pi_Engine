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


template <typename T>
T custom_lerp(T a, T b, T t) {
    return a + t * (b - a);
}

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

    std::ifstream fin("assets/simconfig.txt");

    sf::Vector2i mousePosition;

    const sf::Font bitFont("assets/8bitOperatorPlus8-Regular.ttf");

    sf::Text framesPerSecondText(bitFont);

    framesPerSecondText.setPosition({ (float)windowWidth / 2, 10});

    sf::Text frameTimeText(bitFont);
    frameTimeText.setPosition({ 10,10 });
    frameTimeText.setFillColor(sf::Color(255, 255, 255));


    sf::Text pauseText(bitFont);

   
    pauseText.setString("PAUSED");
    pauseText.setFillColor(sf::Color(255, 255, 255));
    pauseText.setScale({2.0f,2.0f});
    pauseText.setOrigin(pauseText.getLocalBounds().getCenter());
    pauseText.setPosition({(float)windowWidth/2 , (float)windowHeight/2 });

    sf::Text clockText(bitFont);
    clockText.setString("Clock");
    clockText.setFillColor(sf::Color(255, 255, 255));
    clockText.setPosition({ (float)windowWidth-200, 10});

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


    bool isPaused = false;

    EntityManager manager;

    
    int iMax = 40;
	int jMax = 10;
    int gravIn = 1;
    float mouseForce = 1.0f;
    bool grav = true;
    if (fin) {
        fin >> iMax;
        fin >> jMax;
        fin >> mouseForce;
        fin >> gravIn;
        grav = gravIn;
        std::cout << iMax << " " << jMax << " " << mouseForce <<" " << gravIn;
    }
    
    

    for(int i =0; i < iMax; i++)
    {
        for(int j =0; j < jMax; j++)
        {


            int radius = 16;
            SimpEntPtr physicsEntity = manager.addEntity("Physics");
            physicsEntity->cTransform = std::make_shared<CTransform>(Vec2(windowWidth /iMax*i +20, windowWidth / iMax *j + 100));
            physicsEntity->cTransform->previousPos = physicsEntity->cTransform->pos;
            sf::Color specialColor
            (
                custom_lerp(0.0f,255.0f,(float)i/(float)iMax),
                255- custom_lerp(0.0f, 255.0f, (float)j / (float)jMax),
                255 - (custom_lerp(0.0f, 255.0f, (float)i / (float)iMax)+(255 - custom_lerp(0.0f, 255.0f, (float)j / (float)jMax)))/2
            );
            physicsEntity->cShape = std::make_shared<CShape>(radius, 12, specialColor,sf::Color::Red, 3.0f);
            physicsEntity->cCollision = std::make_shared<CCollision>(radius);
            physicsEntity->cRidgedBody = std::make_shared<CRidgedBody>();
            physicsEntity->cRidgedBody->mass = .25;
            physicsEntity->cRidgedBody->useGravity = grav;
		}
        
	}

    manager.update();

    while (window.isOpen())
    {
        manager.update();
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
                clockText.setPosition({ (float)windowWidth - 200, 10 });
                framesPerSecondText.setPosition({ (float)windowWidth / 2, 10 });
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
        frameTimeText.setString(deltaTimeString);
        //window.draw(ceilingSprite);
        window.draw(mouse);
        window.draw(clockText);
        window.draw(frameTimeText);
       
        /*
        manager.addRec();
        EntityVec recVec = manager.getEntitiesWithTag("Rectangle");
        if (recVec.size() > 0)
        {
            recVec.front()->destroy();
            window.draw(*recVec.front()->cRectShape);
        }
        */

        framesSinceClockTick++;
        float elapsedSeconds = framesPerSecondClock.getElapsedTime().asSeconds();
        if (elapsedSeconds >= 1.0f)
        {
            framesPerSecondText.setString
            (
                std::to_string
                ( 
                    (int)(framesSinceClockTick / elapsedSeconds)
                )
            );
            float colorCodedfps = std::clamp((framesSinceClockTick / elapsedSeconds) / frameLimit * 255.0f, 0.0f, 255.0f);
            framesPerSecondText.setFillColor(sf::Color(255 - colorCodedfps, colorCodedfps, .5));
            framesPerSecondClock.restart();
            framesSinceClockTick = 0;

        }

        for(auto& e : manager.getAllEntities())
        {

            if (e->cTransform && e->cCollision && e->cRidgedBody)
            {
                if (e->cTransform->pos.y + e->cCollision->radius >= windowHeight)
                {
                    e->cTransform->pos.y -= 1;
                    e->cRidgedBody->velocity.y *= -1;
                }
                if (e->cTransform->pos.y - e->cCollision->radius <= 0)
                {
                    e->cTransform->pos.y += 1;
                    e->cRidgedBody->velocity.y *= -1;
				}
                if (e->cTransform->pos.x + e->cCollision->radius >= windowWidth)
                {
                    e->cTransform->pos.x -= 1;
                    e->cRidgedBody->velocity.x *= -1;
                }
                if (e->cTransform->pos.x - e->cCollision->radius <= 0)
                {
                    e->cTransform->pos.x += 1;
                    e->cRidgedBody->velocity.x *= -1;
				}


                if (e->cRidgedBody->useGravity)
                {
					e->cRidgedBody->velocity.y += 9.81f * (deltaTime / 1000.0f);
                }
                e->cTransform->pos += e->cRidgedBody->velocity;
                if (mouseDown_LeftButton)
                {
                    Vec2 distance = e->cTransform->pos - Vec2(mousePosition.x,mousePosition.y);
                    distance.normalize();
                    e->cRidgedBody->velocity -= distance * mouseForce;

                }
                if (keyDown_W)
                {
                    e->cTransform->pos = e->cTransform->previousPos;
                    e->cRidgedBody->velocity = Vec2();

                }
            }
            if (e->cTransform && e->cShape)
            {
                e->cShape->circle.setPosition(e->cTransform->pos);
                window.draw(e->cShape->circle);
            }
            
		}
        window.draw(framesPerSecondText);
        
        //end magical draw area
        window.display();

        counterLoop = (counterLoop +1)% 256;

        
       
        
    }
}
