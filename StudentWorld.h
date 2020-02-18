#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "Actor.h"//am i allowed to do this
#include "GameWorld.h"

#include <string>
#include <list>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor* a);
    void getRandomLocInDish(double &x, double &y) const;
    bool overlap(double const x1, double const y1, double const x2, double const y2) const;
    bool isValidNewSpot(double const x, double const y);
    void getValidNewSpot(double &x, double &y);
    void getCircumferenceSpot(double &x, double &y);
    Actor* amITouchingSomething(Actor *a);

private:
    list<Actor*> actorList;
    Socrates* pSocrates;
};

#endif // STUDENTWORLD_H_
