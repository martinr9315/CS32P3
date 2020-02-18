#ifndef ACTOR_H_
#define ACTOR_H_


//QUESTION/NOTE: do i need a pointer to studentWorld for every actor or just for socrates???
#include "GraphObject.h"
#include "GameWorld.h" //QUESTION: am i allowed to do this
//just for debugging
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, Direction dir, int depth, GameWorld *p): GraphObject(imageID, startX, startY,  dir, depth, 1)
    {
        alive = true;
        pStudentWorld = p;
    }
    
    GameWorld* getWorld() {return pStudentWorld;}
    bool isAlive() {return alive;}
    void kill() {alive = false;}
    
    virtual bool isDamageable(){return false;}
    virtual void doSomething(){}
    
private:
    GameWorld* pStudentWorld;
    bool alive;
    
};

class Socrates: public Actor
{
public:
    Socrates(GameWorld *p): Actor(IID_PLAYER, 0,  VIEW_HEIGHT/2, 0, 0, p)
    {
        positionalAngle=0;
        health = 100;
        sprayCharges = 20;
        flameThrowerCharges = 5;
    }
    
    virtual void doSomething();
    
private:
    int positionalAngle;
    int health;
    int sprayCharges;
    int flameThrowerCharges;
};

//FOOD CLASS
class Food: public Actor
{
public:
    Food(double x, double y, GameWorld *p): Actor(IID_FOOD, x, y, 90, 1, p)
    {}
};

//DAMAGEABLE CLASS - base class for dirt, bacteria, fungi, goodie
class Damageable: public Actor
{
public:
    Damageable(int imageID, double x, double y, GameWorld *p): Actor(imageID, x, y, 0, 1, p) {setHealth(0);}
    void setHealth(int h) {health = h;}
    int getHealth() {return health;}
    
    virtual bool isDamageable(){return true;}
    virtual void receiveDamage(int hitPoints) {health -= hitPoints;}
private:
    int health;
};

//DIRT CLASS
class Dirt: public Damageable
{
public:
    Dirt(double x, double y, GameWorld *p): Damageable(IID_DIRT, x, y, p)
    {}
    //if dirt recieves damage, automatically killed
    virtual void recieveDamage(int hitPoints) {kill();}
};



//LIFETIME CLASS -- base class for goodies (restore health, flame thrower, extralife) and fungus
class Lifetime: public Damageable
{
public:
    Lifetime(int imageID, double x, double y, int level, GameWorld *p): Damageable(imageID, x, y, p)
    {setLifetime(max(rand() % (300 - 10 * level), 50));}
    
    void setLifetime(int l) {lifetime=l;}
    int getLifetime() {return lifetime;}
    
    virtual void recieveDamage(int hitPoints) {kill();}
    virtual void editPlayerScore(){}
    virtual void doSomething();
    virtual void sound(){getWorld()->playSound(SOUND_GOT_GOODIE);}
    virtual void doGoodiesThing(){}
private:
    int lifetime;
};

//RESTORE HEALTH GOODIE
class RestoreHealthGoodie: public Lifetime
{
public:
    RestoreHealthGoodie(double x, double y, int level, GameWorld *p): Lifetime(IID_RESTORE_HEALTH_GOODIE, x, y, level, p) {}
    //virtual void doSomething();
    virtual void editPlayerScore() {getWorld()->increaseScore(250);}
    //virtual void doGoodiesThing(){} //TODO:tell socrates to restore health
};

//FLAME THROWER GOODIE
class FlameThrowerGoodie: public Lifetime
{
public:
    FlameThrowerGoodie(double x, double y, int level, GameWorld *p): Lifetime(IID_FLAME_THROWER_GOODIE, x, y, level, p) {}
    //virtual void doSomething();
    virtual void editPlayerScore() {getWorld()->increaseScore(300);}
    //virtual void doGoodiesThing(){} //TODO:tell socrates to add 5 flame throwers to arsenal
};

//EXTRA LIFE GOODIE
class ExtraLifeGoodie: public Lifetime
{
public:
    ExtraLifeGoodie(double x, double y, int level, GameWorld *p): Lifetime(IID_EXTRA_LIFE_GOODIE, x, y, level, p)
    {}
    //virtual void doSomething();
    virtual void editPlayerScore() {getWorld()->increaseScore(500);}
    //virtual void doGoodiesThing(){getWorld()->incLives();}
};

//FUNGUS
class Fungus: public Lifetime
{
public:
    Fungus(double x, double y, int level, GameWorld *p): Lifetime(IID_FUNGUS, x, y, level, p)
    {}
    //virtual void doSomething();
    virtual void editPlayerScore() {getWorld()->increaseScore(-50);}
    //virtual void doGoodiesThing(){} //TODO:damage socrates by 20 points
    virtual void sound(){}
};

//PROJECTILE CLASS -- base class for flame and spray
class Projectile: public Actor
{
public:
    Projectile(int imageID, double x, double y, Direction dir, GameWorld *p): Actor(imageID, x, y, dir, 1, p)
    {}
    virtual void doSomething();
    void setTravelDistance(int d) { travelDistance = d; }
    int getTravelDistance() {return travelDistance;}
private:
    int travelDistance;
};

//FLAME CLASS
class Flame: public Projectile
{
public:
    Flame(double x, double y, Direction dir, GameWorld *p) : Projectile(IID_FLAME, x, y, dir, p)
    {setTravelDistance(32);}
    
    virtual void doSomething();
};

//SPRAY CLASS
class Spray: public Projectile
{
public:
    Spray(double x, double y, Direction dir, GameWorld *p) : Projectile(IID_SPRAY, x, y, dir, p)
    {setTravelDistance(112);}
    
    virtual void doSomething();
};





#endif // ACTOR_H_


