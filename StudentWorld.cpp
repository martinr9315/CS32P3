#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
<<<<<<< HEAD
#include <iostream> //just for now

=======
>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe
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
<<<<<<< HEAD
    //add socrates (not in actorList though
    pSocrates = new Socrates();
    //add dirt objects
    int L = getLevel();
    int numDirt = max(180 - 20 * L, 20);
    for (int i=0; i<numDirt; i++) //change 1 to num dirt
    {
        double x,y;
        getRandomLocInDish(x, y);
        actorList.push_back(new Dirt(x,y));
    }
=======
>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
<<<<<<< HEAD
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
=======
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_PLAYER_DIED;
>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe
}

void StudentWorld::cleanUp()
{
<<<<<<< HEAD
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
=======
>>>>>>> 78609c793fdd9b0c9298b87cdc30ca29bb8fadfe
}
