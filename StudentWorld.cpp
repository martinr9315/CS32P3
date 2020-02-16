#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream> //just for now

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    //add socrates (not in actorList though
    pSocrates = new Socrates(this);
    //add dirt objects
    int L = getLevel();
    int numDirt = max(180 - 20 * L, 20);
    for (int i=0; i<numDirt; i++) //change 1 to num dirt
    {
        double x,y;
        getRandomLocInDish(x, y);
        actorList.push_back(new Dirt(x,y,this));
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //call socrates doSomething()
    pSocrates->doSomething();
    
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        (*it)->doSomething();
        it++;

    }
    
    //decreases lives and ends level when space bar is pressed
    int key;
    getKey(key);
    if (key == KEY_PRESS_SPACE)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //delete socrates
    delete pSocrates;
    //get rid of everything in actorList
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        delete *it;
        it = actorList.erase(it);
    }
}

void StudentWorld::getRandomLocInDish(double &x, double &y)
{
    x = randInt(0, VIEW_HEIGHT);
    y = randInt(0, VIEW_WIDTH);
    double z = pow((x-VIEW_HEIGHT/2), 2) + pow((y-VIEW_WIDTH/2), 2);
    if (z> pow(120, 2))
        getRandomLocInDish(x, y);
}
