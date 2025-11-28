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


/*
Separate subject from body with a blank line
Limit the subject line to 50 characters
Capitalize the subject line
Do not end the subject line with a period
Use the imperative mood in the subject line //if applied this commit will
Wrap the body at 72 characters
Use the body to explain what and why vs. how
*/

//Lecture 3
/*
Lecture 3:
int val = 5; //stack
int* hval = new int; //heap
*hval = 5;

int a[5]; //stack
int* ha = new int[5]; //heap
ha[3] = 10;

MyClass c(args); //stack

MyClass * hc = new MyClass(args);//heap allocation with new



RAII can replace "new"

Stack is "static memory" ie. sizes need to be known at compile time
Memory allocation dependent on runtime variables needs to be heap allocated


PtClass* p = new PtClass(5,4);//address to data is allocated to stack, data is allocated to heap
delete p; // frees up memory at location p 

Why Use Pointers?

1. must use pointer for inheritance
    Base * ptr = new Derived();

2. Pass by value vs. by reference 
    Modifying variable passed into function 

3. Pointing to large data
    Large data can't live on the stack


References: "safe pointers" use &

must point to existing data never nullptr

c++ is pass by value
cost of copying large data
may want to modify the value passed so pass by reference PBR 

Pass By Reference:

void tennify(int & a) { a = 10; }

int i = 12;
tennify(i);

Good idea to pass by reference if data is big even if you dont want to change it 

void machineLearn(const BigData & d);

Should pass const primitives by value 

int add(const int & a, const int & b); <<<Needlessly expensive
int add(const int a, const int b); <<< USE THIS

Pass smart pointers by value rather than reference std::shared_prt<T> 
    The copy does not influence the inc/dec


Resource Acquisition is Initilization RAII
    Binds the life cycle of a resource that must be aquired before use to the lifetime of an object


class IntArray
{
    int * array;
    size_t m_size;
public:
    IntArray(size_t size) { array = new int[size];}
    ~IntArray() {delete array;}
    int & operator [] (size_t i) {return array[i];}
}

{ //new scope
    IntArray arr(10); // mem allocated
    arr[5] = 21;
  //when leaving scope stack allocated variables are deallocated 
  //classes get their destructors called 
}

Smart Pointers track when an object leaves scope and deallocates the data
It also has an internal counter 


{
    auto p = std::make_shared<MyClass>(args); //c = 1
    someOtherThings()
    // c = 0, deallocate
} 

void func(std::shared_ptr<MyClass> p) // increment c (c=2)
{
    p->doSomething();
}// decrement c (c = 1)

How to allocate / pass data?
1. If possible, use the stack: small, local variables, pass variables by const reference if size > 8 bytes
2. If you need heap memory, use smart ptr
    std::shared_ptr<T> myBigData;
    std::shared_ptr<Base> = std::make_shared<Derived>();
3.Only when ABSOLUTELY NECESSARY use raw pointers/new

GENERICS: Template

template <typename T>
class DynamicArray
{
    size_t m_size;
    T * m_arr;
public:
    DynamicArray(size_t size)
        :m_size(size)
        ,m_arr(new T[size])
    {}

    ~DynamicArray()
    {
        delete [] m_arr;
    }

    T get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, T val)
    {
        m_arr[index] = val;
    }

    T & operator [] (size_t index)
    {
        return m_arr[index];
    }


}

*/

//Lecture 5
/*
    //Movement System
    for (e : entities) { e.pos += e.speed; }

    //Collision System
    for (b : bullets)
        for (e : enemies)
            if (Physics:IsCollision(b,e))
                e.health -= b.damage;
                b.destroy();

    Rendering System
    for (e : entities) { window.draw(e.sprite, e.pos); }


    Architecture
    GameEngine
        >Scene
            >Systems
            >EntityManager
                >Entity
                    >Component


    Using Entities

    void doStuff(std::vector<Entity> & entities)
    {
        for (auto & e : entities)
        {
            e.cTransform->pos += e.cTransform->velocity;
            e.cShape->shape.setPosition(e.cTransfrom->pos);
            window.draw(e.cShape->shape);
        }
    }

    void sRender(std::vector<Entity> & entities)
    {
        for (auto & e : entities)
            if (e.cShape && e.cTransform)
            {
                e.cShape->shape.setPosition(e.CTransform->pos);
                window.draw(e.Shape->shape);
            }
        }
    }

*/



//namespace
namespace globalVariables
{
    float grav = 9.81f;

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

    std::ifstream fin("assets/config.txt");

    std::vector<Entity> entityVector;

    int newId;
    int newRadius;
    int newR;
    int newG;
    int newB;
    int newPosx;
    int newPosy;

    sf::Vector2i mousePosition;
    /*
    while (fin >> newId) 
    {
        //std::cout << "read once" << std::endl;
        

        fin >> newRadius;
        fin >> newR;
        fin >> newG;
        fin >> newB;
        fin >> newPosx;
        fin >> newPosy;
        sf::CircleShape newCircle = sf::CircleShape(newRadius);
        newCircle.setFillColor(sf::Color(newR, newG, newB));
        Entity newEntity(newId, newCircle);
        newEntity.setVecPosition(Vec2(newPosx, newPosy));

   
        entityVector.push_back(newEntity);


    }
    */
    std::vector<std::shared_ptr<sf::Shape>> shared_Shapes;

    std::shared_ptr<sf::Shape> shared_Shape01 = std::make_shared<sf::CircleShape>(20);
    std::shared_ptr<sf::Shape> shared_Shape02 = std::make_shared<sf::RectangleShape>(sf::Vector2f(40,40));
    shared_Shape01->setPosition({200, 200});

    shared_Shapes.push_back(shared_Shape01);
    shared_Shapes.push_back(shared_Shape02);

    /*
    Component testComponent = CTransform(Vec2(50,50),Vec2(50,50));
    Entity testEntity(55, sf::CircleShape(10));
    testEntity.addComponent(testComponent);
    CTransform passComp;
    if (testEntity.getComponent(testComponent)) {
        passComp.print();
    }
    */


    Vec2 vec01(1, 1);
    Vec2 vec02(1, 1);
    Vec2 vec03(1, -3);



    //vec03 += vec02 + vec01;
   //vec03.add(vec01).add(vec02);
   // vec01 -= vec02;
    //vec03.normalize();
    vec02 = Vec2::normalize(vec03);
    //std::cout << vec02.toString() <<std::endl;

    const Vec2 circle1(150, 100);
    const  Vec2 circle2(210 , 200);
    const float circle1rad = 67;
    const float circle2rad = 100;
    sf::CircleShape circleShape1(circle1rad);
    sf::CircleShape circleShape2(circle2rad);
    circleShape1.setOrigin(sf::Vector2f(circle1rad, circle1rad));
    circleShape2.setOrigin(sf::Vector2f( circle2rad, circle2rad));
    circleShape1.setPosition(sf::Vector2f(circle1.x,circle1.y));
    circleShape2.setPosition(sf::Vector2f(circle2.x, circle2.y));
    circleShape1.setFillColor(sf::Color(255, 0, 255, 128));
    circleShape2.setFillColor(sf::Color(255, 255, 0, 128));
   
    
    if(Vec2::circleCollision(circle1,circle2,circle1rad,circle2rad))
    {
        std::cout << "Collision" << std::endl;


    }

    std::cout << (Vec2::circleOverlap(circle1, circle2, circle1rad, circle2rad)).toString() << std::endl;
    //if (Vec2::sphereCollision(Vec2(circleShape1.getPosition().x, circleShape1.getPosition().y), Vec2(circleShape2.getPosition().x, circleShape2.getPosition().y), circleShape1.getRadius(), circleShape2.getRadius()))
    /*
    if (vec01 != vec02) 
    {
        std::cout << "not equal" << std::endl;

    }else{ std::cout << "equal" << std::endl; }
    std::cout << vec03.toString() << std::endl;

    */
    std::vector<SimpleEntity> allSimpleEntites;

    typedef std::vector<std::shared_ptr<SimpleEntity>> EntityVector;
    typedef std::shared_ptr<SimpleEntity> SimpEntPtr;

    EntityVector simpleEntitiesType;
   
 
    /*
    for (int i = 0; i < 20; ++i)
    {
        SimpEntPtr simpEnt = (std::make_shared<SimpleEntity>(i, "Default"));

        std::shared_ptr<std::string> simpEntName;
        simpEntName = std::make_shared<std::string>(std::string("Name") + std::to_string(i));
        simpEnt->cName = simpEntName;
        CTransform intermediateTransform(Vec2(i*69%600, i * 33 % 700), Vec2( i *.02, - i * .02));
        simpEnt->cTransform = std::make_shared<CTransform>(intermediateTransform);
        simpEnt->cShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));
        simpleEntitiesType.push_back(simpEnt);
    }
    */
    SimpEntPtr nullEntity = (std::make_shared<SimpleEntity>(512, "Broke"));

    nullEntity->cName = std::make_shared<std::string>("im so special");
    nullEntity->cShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));
   
    nullEntity->cTransform = std::make_shared<CTransform>(Vec2(900, 900), Vec2(0.1, 1.0));

   // allSimpleEntites.push_back(nullEntity);

    //simpleEntitiesType.push_back(nullEntity);
    nullEntity->cShape->setFillColor(sf::Color::Red);

    
    const sf::Font bitFont("assets/8bitOperatorPlus8-Regular.ttf");
   

    sf::Text text(bitFont);
   
    EntityManager manager;

    for (int i = 0; i < 20; ++i)
    {
        SimpEntPtr simpEnt;

        if(i%2 == 0)
        {
            simpEnt = manager.addEntity("I was Even");
        }else
        {
            simpEnt = manager.addEntity("I was Odd");
        }
       
         
        
        std::shared_ptr<std::string> simpEntName;
        simpEntName = std::make_shared<std::string>(std::string("Name") + std::to_string(i));
        simpEnt->cName = simpEntName;
        CTransform intermediateTransform(Vec2(i * 69 % 600, i * 33 % 700), Vec2(i * .02, -i * .02));
        simpEnt->cTransform = std::make_shared<CTransform>(intermediateTransform);
        simpEnt->cShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));
        simpEnt->cShape->setFillColor(sf::Color(i*10,255-i*10,(i+1*10+i*100)%256));
        simpEnt->cDisplayTag = std::make_shared<CDisplayTag>(bitFont);
        simpEnt->cDisplayTag->text.setString(std::to_string(simpEnt->m_id));
        simpEnt->cDisplayTag->text.setFillColor(sf::Color::Black);
        

    }


    //SimpEntPtr tempEntPtr= manager.addEntity("Default");
    //tempEntPtr->cShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));
    //tempEntPtr->cTransform  = std::make_shared<CTransform>(Vec2(900, 900), Vec2(5, 2.0));
    //tempEntPtr->cShape->setFillColor(sf::Color::Blue);
    //simpleEntitiesType.push_back(tempEntPtr);
    //std::cout << tempEntPtr.use_count() << std::endl;
    
    manager.update();

    //for (auto e : manager.getEntitiesWithTag("I was Odd"))
    {
     //   std::cout << e->m_id << std::endl;

    }

    //std::cout << manager.catEntVec(manager.getAllEntities());
   // std::cout << manager.catMap();
    
  //  for (auto e : manager.getEntitiesWithTag("I was Odd"))
   // {
       // std::cout << e->m_id << std::endl;
      //  e->m_alive = false;
   // }
    
    //manager.update();
    //std::cout << manager.catMap();
    

   // std::cout << "cID: " << *simpEnt.cID << " Name: " << *simpEnt.cName <<  std::endl;
    //if (simpEnt.cShape) {
       // std::cout << "shape is true" << std::endl;
   // }

    
    /*
    for (auto& e : allSimpleEntites)
    {
        if (e.cName && e.cID && e.cTransform)
        {
            std::cout << "cID: " << *e.cID << " cName: " << *e.cName << std::endl;
            e.cTransform->print();
        }

    }
    */

   
    
    text.setPosition({1000, 10});
   // text.setFillColor(sf::Color(255, 255, 255));

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
    
    

    int circleRadius = 64;
    sf::CircleShape myShape(circleRadius);
    myShape.setPosition({512,512});
    sf::Color newColor(255, 255, 255);
    myShape.setFillColor(newColor);

    Entity myEntity =  Entity(1, myShape);


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

    /*
    hypothetical loop:

    m_entityManager.update();
    sUserInput();
    sMovement();
    sCollision();
    sRender();
    m_currentFrame++;
    */

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
        
        manager.update();

        //std::cout<< testSimpleEntity.use_count() << std::endl;
        if(mouseDown_LeftButton)
        {
            
            SimpEntPtr simpEnt;
           
            
               simpEnt = manager.addEntity("I'm new");
         
               int i = simpEnt->m_id % 25;


            std::shared_ptr<std::string> simpEntName;
            simpEntName = std::make_shared<std::string>(std::string("Name") + std::to_string(i));
            simpEnt->cName = simpEntName;
            CTransform intermediateTransform(Vec2(mousePosition.x, mousePosition.y), Vec2(i * .02, -i * .02));
            simpEnt->cTransform = std::make_shared<CTransform>(intermediateTransform);
            simpEnt->cShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));
            simpEnt->cShape->setFillColor(sf::Color(i * 10, 255 - i * 10, (i + 1 * 10 + i * 100) % 256));
            simpEnt->cDisplayTag = std::make_shared<CDisplayTag>(bitFont);
            simpEnt->cDisplayTag->text.setString(std::to_string(simpEnt->m_id));
            simpEnt->cDisplayTag->text.setFillColor(sf::Color::Black);


            std::cout << simpEnt->m_id << " created, ";
           
            manager.getAllEntities().front()->m_alive = false;
            std::cout << manager.getAllEntities().front()->m_id << " marked for death " << std::endl;



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


        //sf::Time elapsed = clock.getElapsedTime();
        std::string deltaTimeString = std::to_string( deltaTime);
        fpsText.setString(deltaTimeString);

        //std::cout << deltaTimeString << std::endl;

        myEntity.setVecPosition(Vec2(myEntity.getVecPosition().x + movementDir.x * movementMultiplyer * deltaTime, myEntity.getVecPosition().y + movementDir.y * movementMultiplyer * deltaTime) );

        window.draw(ceilingSprite);

        window.draw(myEntity.getShape());

        window.draw(mouse);

        window.draw(clockText);
        //window.draw(myShape); //somehow entity is being passed by value to the entity constructor ie. there's now two
        //sf::CircleShape specialShape = myEntity.getShape();
        //window.draw(specialShape);
        
        window.draw(fpsText);
        
        
       /*
        for (auto & s : shared_Shapes)
        {
            window.draw(*s);

        }
        */
        for (auto& e : manager.getAllEntities())
        {

            if (e->cShape && e->cTransform)
            {
                
                if (e->cTransform->pos.x < 0.0f || e->cTransform->pos.x + e->cShape->getSize().x> windowWidth) {
                    e->cTransform->velocity.x = e->cTransform->velocity.x * -1.0f;
                }
                if (e->cTransform->pos.y < 0.0f || e->cTransform->pos.y +e->cShape->getSize().y > windowHeight) {
                    e->cTransform->velocity.y = e->cTransform->velocity.y * -1.0f;
                }

                

                e->cTransform->pos = e->cTransform->pos + e->cTransform->velocity * deltaTime;
                e->cShape->setPosition({e->cTransform->pos.x, e->cTransform->pos.y});
                window.draw(*e->cShape);

            }
            
            if (e->cDisplayTag && e->cTransform)
            {

                e->cDisplayTag->text.setPosition({ e->cTransform->pos.x,e->cTransform->pos.y });
                window.draw(e->cDisplayTag->text);

            }
            

        }



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
        window.draw(circleShape1);
        window.draw(circleShape2);

        window.draw(text);

        //end magical draw area
        window.display();

        counterLoop = (counterLoop +1)% 256;

        
       
        
    }
}
