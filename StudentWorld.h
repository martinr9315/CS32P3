#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
<<<<<<< HEAD
#include "Actor.h" //am i allowed to do this
#include <string>
#include <list>
using namespace std;
=======
#include <string>
>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
<<<<<<< HEAD
    void getRandomLocInDish(double &x, double &y);

private:
    list<Actor*> actorList;
    Socrates* pSocrates;
=======

private:
>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe
};

#endif // STUDENTWORLD_H_
