#include <SFML/Graphics.hpp>//Simple Fast Multi-media Library
#include <iostream>
#include <string>
#include <fstream>
#include "Entity.h"
#include "Vec2.h"

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
        sf::CircleShape newCircle = sf::CircleShape(newRadius);
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

    Entity myEntity =  Entity(1, myShape);

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
        window.draw(myShape); //somehow entity is being passed by value to the entity constructor ie. there's now two
        //sf::CircleShape specialShape = myEntity.getShape();
        //window.draw(specialShape);
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
