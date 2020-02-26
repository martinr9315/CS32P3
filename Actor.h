#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//for debugging
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld *p): GraphObject(imageID, startX, startY,  dir, depth, 1)
    {
        alive = true;
        pStudentWorld = p;
    }
    
    StudentWorld* getWorld() {return pStudentWorld;}
    bool isAlive() {return alive;}
    void kill() {
        alive = false;
        soundDie();
    }
    
    virtual void soundDie(){}
    virtual void soundHurt(){}
    
    //combine isDamageable and receiveDamage
    virtual bool receiveDamage(int hitPoints){return false;}
    virtual bool isEdible() {return false;}
    virtual bool blocksMovement() {return false;}
    virtual void doSomething()=0;
    
private:
    StudentWorld* pStudentWorld;
    bool alive;
    
};

//TODO: pit class
//PIT CLASS
class Pit: public Actor
{
public:
    Pit(double x, double y, StudentWorld *p):Actor(IID_PIT, x, y, 0, 1, p)
    {
        m_rsalmonella = 5;
        m_asalmonella = 3;
        m_ecoli = 2;
    }
    
    virtual void doSomething();
    
private:
    int m_rsalmonella;
    int m_asalmonella;
    int m_ecoli;
};


//FOOD CLASS
class Food: public Actor
{
public:
    Food(double x, double y, StudentWorld *p): Actor(IID_FOOD, x, y, 90, 1, p)
    {}
    bool isEdible() {return true;}
    virtual void doSomething();
    
};




//DIRT CLASS
class Dirt: public Actor
{
public:
    Dirt(double x, double y, StudentWorld *p): Actor(IID_DIRT, x, y, 0, 1, p)
    {}
    virtual bool blocksMovement() {return true;}
    virtual bool receiveDamage(int hitPoints)
    {
        kill();
        return true;
    }
    virtual void doSomething();
};



//LIFETIME CLASS -- base class for goodies (restore health, flame thrower, extralife) and fungus
class Lifetime: public Actor
{
public:
    Lifetime(int imageID, double x, double y, int level, StudentWorld *p): Actor(imageID, x, y, 1, 1, p)
    {setLifetime(std::max(rand() % (300 - 10 * level), 50));}
    
    void setLifetime(int l) {lifetime=l;}
    int getLifetime() {return lifetime;}
    
    virtual void doSomething();
    virtual void sound();
    virtual void doGoodiesThing()=0;
    virtual bool receiveDamage(int hitPoints);
    
private:
    int lifetime;
};

//RESTORE HEALTH GOODIE
class RestoreHealthGoodie: public Lifetime
{
public:
    RestoreHealthGoodie(double x, double y, int level, StudentWorld *p): Lifetime(IID_RESTORE_HEALTH_GOODIE, x, y, level, p) {}
    virtual void doGoodiesThing();
};

//FLAME THROWER GOODIE
class FlameThrowerGoodie: public Lifetime
{
public:
    FlameThrowerGoodie(double x, double y, int level, StudentWorld *p): Lifetime(IID_FLAME_THROWER_GOODIE, x, y, level, p) {}
    virtual void doGoodiesThing();
};

//EXTRA LIFE GOODIE
class ExtraLifeGoodie: public Lifetime
{
public:
    ExtraLifeGoodie(double x, double y, int level, StudentWorld *p): Lifetime(IID_EXTRA_LIFE_GOODIE, x, y, level, p)
    {}
    virtual void doGoodiesThing();
};

//FUNGUS class
class Fungus: public Lifetime
{
public:
    Fungus(double x, double y, int level, StudentWorld *p): Lifetime(IID_FUNGUS, x, y, level, p)
    {}
    virtual void doGoodiesThing();
    virtual void sound(){}
};


//PROJECTILE CLASS -- base class for flame and spray
class Projectile: public Actor
{
public:
    Projectile(int imageID, double x, double y, Direction dir, int travelD, StudentWorld *p): Actor(imageID, x, y, dir, 1, p)
    {setTravelDistance(travelD);}
    
    virtual void doSomething();
    
    virtual void damageTarget(Actor *a){}
    
private:
    void setTravelDistance(int d) { travelDistance = d; }
    int getTravelDistance() {return travelDistance;}
    int travelDistance;
};

//FLAME CLASS
class Flame: public Projectile
{
public:
    Flame(double x, double y, Direction dir, StudentWorld *p) : Projectile(IID_FLAME, x, y, dir, 32, p)
    {}
    
    virtual void damageTarget(Actor *a);
};

//SPRAY CLASS
class Spray: public Projectile
{
public:
    Spray(double x, double y, Direction dir, StudentWorld *p) : Projectile(IID_SPRAY, x, y, dir, 112, p)
    {}
    
    virtual void damageTarget(Actor *a);
};

//AGENT CLASS - base class for Socrates and bacteria
class Agent: public Actor
{
public:
    Agent(int imageID, double x, double y, int depth, StudentWorld *p): Actor(imageID, x, y, 0, depth, p) {setHealth(0);}
    void setHealth(int h) {health = h;}
    int getHealth() {return health;}
    
    virtual bool isDamageable(){return true;}
    virtual bool receiveDamage(int hitPoints)
    {
        health-=hitPoints;
        if (health<=0)
            kill();
        else
            soundHurt();
        return true;
    }
private:
    int health; //QUESTION: can my classes that dont have hitPoints still have them but just for me to keep track of???
};

//SOCRATES class
class Socrates: public Agent
{
public:
    Socrates(StudentWorld *p): Agent(IID_PLAYER, 0,  VIEW_HEIGHT/2, 0, p)
    {
        setHealth(100);
        sprayCharges = 20;
        flameThrowerCharges = 5;
    }
    void increaseFlameThrowerCharges() {flameThrowerCharges+=5;}
    int getSprayCharges() {return sprayCharges;}
    int getFlameThrowerCharges() {return flameThrowerCharges;}
    
    virtual void doSomething();

private:
    int sprayCharges;
    int flameThrowerCharges;
    virtual void soundDie();
    virtual void soundHurt();

    
};

//BACTERIA class -- base class for salmonella (regular and aggressive) and ecoli
class Bacteria: public Agent
{
public:
    Bacteria(int imageID, double x, double y, StudentWorld *p): Agent(imageID, x, y, 0, p)
    {
        setDirection(90);
        setMovementPlanDist(0);
    }
    
    void setMovementPlanDist(int d) {movementPlanDist = d;}
    int getMovementPlanDist() {return movementPlanDist;}
    void turnToFood();
    virtual void doSomething();
    virtual void spawn(double x, double y) = 0;
    
    
    
private:
    void setFood(int f) {food=f;}
    void eatFood() {food++;}
    int getFood() {return food;}
    
    
private:
    int movementPlanDist;
    int food;
};

//SALMONELLA class -- base class for regular and aggressive salmonella
class Salmonella: public Bacteria
{
public:
    Salmonella(double x, double y, StudentWorld *p): Bacteria(IID_SALMONELLA, x, y, p)
    {//this is for regular salmonella but just putting it here for testing
        setHealth(4);
    }
    virtual void doSomething();
private:
    virtual void soundDie();
    virtual void soundHurt();
    
};

//REGULAR SALMONELLA class
class RegularSalmonella: public Salmonella
{
public:
    RegularSalmonella(double x, double y, StudentWorld *p): Salmonella(x,y,p)
    {
        setHealth(4);
    }
    virtual void doSomething();
private:
    virtual void spawn(double x, double y);
};


//AGGRESSIVE SALMONELLA class
class AggressiveSalmonella: public Salmonella
{
public:
    AggressiveSalmonella(double x, double y, StudentWorld *p): Salmonella(x,y,p)
    {
        setHealth(10);
    }
    virtual void doSomething();
private:
      virtual void spawn(double x, double y);
};


class Ecoli: public Bacteria
{
public:
    Ecoli(double x, double y, StudentWorld *p): Bacteria(IID_ECOLI, x, y, p)
    {setHealth(5);}
    

    virtual void doSomething();
private:
    virtual void soundDie();
    virtual void soundHurt();
    virtual void spawn(double x, double y);
};


#endif // ACTOR_H_


