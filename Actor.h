#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h" //am i allowed to do this
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
    
    virtual void doSomething() = 0;
    
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
    virtual void doSomething() {
        //If Socrates is not alive, return immediately (not a specific Part 1 requirement)
        if (!isAlive())
            return;
        
        int ch;
        if (getWorld()->getKey(ch))
        {
            double x, y;
            const double PI = 4 * atan(1);
            switch (ch) {
                case KEY_PRESS_RIGHT: //move socrates
                    x = 128 + 128 *cos( (getDirection()-180-5) *1.0 / 360 * 2 * PI);
                    y = 128 + 128 *sin( (getDirection()-180-5) *1.0 / 360 * 2 * PI);
                    moveTo(x, y);
                    setDirection(getDirection()-5);
                    break;
                case KEY_PRESS_LEFT:
                    x = 128 + 128 *cos( (getDirection()-180+5) *1.0 / 360 * 2 * PI);
                    y = 128 + 128 *sin( (getDirection()-180+5) *1.0 / 360 * 2 * PI);
                    moveTo(x, y);
                    setDirection(getDirection()+5);
                    break;
                case KEY_PRESS_UP:
                        moveAngle(90, 128);
                        break;
                case KEY_PRESS_DOWN:
                    moveAngle(-90, 128);
                    break;
                    
                default:
                    break;
            }
        }
        
        /*
        Get user input; if player pressed a key, perform the desired action
        If directional keys: move Socrates by 5 degrees in positional angle either clockwise or counterclockwise, and set the direction he is facing
        Other keys (space to use spray, enter to use flamethrower): not Part 1 req
        If player DID NOT press key: (not Part 1 req)
        Replenish spray charges by 1 (if not already at maximum of 20 charges)*/

        
        
    }
private:
    int positionalAngle;
    int health;
    int sprayCharges;
    int flameThrowerCharges;
        
};

class Dirt: public Actor
{
public:
    Dirt(double x, double y, GameWorld *p): Actor(IID_DIRT, x, y, 90, 1, p)
    {}
    
    virtual void doSomething() {}//do nothing
    
    
    //Dirt piles can be damaged. A single spray or flame that hits the dirt pile will destroy it (and cause the spray/flame to dissipate once it has hit the pile).
    //Dirt piles block the movement of all bacteria (the Euclidean distance of the bacterium and of the dirt pile must not be less than SPRITE_WIDTH/2 pixels from each other).
    //Dirt piles block the movement of all spray and flames.
    
};


#endif // ACTOR_H_
