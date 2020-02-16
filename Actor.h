#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
<<<<<<< HEAD
public:
    Actor(int imageID, double startX, double startY, Direction dir, int depth): GraphObject(imageID, startX, startY,  dir, depth, 1)
    {
        alive = true;
    }
    
    
    bool isAlive() {return alive;}
    
    virtual void doSomething() = 0;
    
private:
    bool alive;
    
};

class Socrates: public Actor
{
public:
    Socrates(): Actor(IID_PLAYER, 0,  VIEW_HEIGHT/2, 0, 0)
    {
        health = 100;
        sprayCharges = 20;
        flameThrowerCharges = 5;
    }
    virtual void doSomething() {
        //If Socrates is not alive, return immediately (not a specific Part 1 requirement)
        if (!isAlive())
            return;
        
        /*
        Get user input; if player pressed a key, perform the desired action
        If directional keys: move Socrates by 5 degrees in positional angle either clockwise or counterclockwise, and set the direction he is facing
        Other keys (space to use spray, enter to use flamethrower): not Part 1 req
        If player DID NOT press key: (not Part 1 req)
        Replenish spray charges by 1 (if not already at maximum of 20 charges)*/

        
        
    } //do stuff
private:
    int health;
    int sprayCharges;
    int flameThrowerCharges;
        
};

class Dirt: public Actor
{
public:
    Dirt(double x, double y): Actor(IID_DIRT, x, y, 90, 1)
    {}
    
    virtual void doSomething() {}//do nothing
    
    
    //Dirt piles can be damaged. A single spray or flame that hits the dirt pile will destroy it (and cause the spray/flame to dissipate once it has hit the pile).
    //Dirt piles block the movement of all bacteria (the Euclidean distance of the bacterium and of the dirt pile must not be less than SPRITE_WIDTH/2 pixels from each other).
    //Dirt piles block the movement of all spray and flames.
    
};


=======
    
};

>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe
#endif // ACTOR_H_
