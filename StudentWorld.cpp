#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
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

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    //add socrates (not in actorList though)
    pSocrates = new Socrates(this);
    
    int L = getLevel();
    
    //QUESTION: does the order that the objects are added in init need to match the spec description
    //add dirt objects
    int numDirt = max(180 - 20 * L, 20);
    for (int i=0; i<numDirt; i++)
    {
        double x,y;
    
        getRandomLocInDish(x, y);
        actorList.push_back(new Dirt(x,y,this));
    }
    
    //add pit objects
    int numPit =  L;
    for (int i=0; i<numPit; i++)
    {
        double x,y;
        getValidNewSpot(x, y);
        actorList.push_back(new Pit(x,y,this));
    }
    
    //add food objects
    int numFood =  min(5 * L, 25);
    for (int i=0; i<numFood; i++)
    {
        double x,y;
        getValidNewSpot(x, y);
        actorList.push_back(new Food(x,y,this));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //call socrates doSomething()
    pSocrates->doSomething();
    
    int L = getLevel();
    
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        (*it)->doSomething();
        if (!pSocrates->isAlive())
            return GWSTATUS_PLAYER_DIED;
        it++;

    }
    
    //delete all dead actors
    it = actorList.begin();
    while (it!=actorList.end())
    {
        if (!(*it)->isAlive())
        {
            delete *it;
            it = actorList.erase(it);
        }
        else
            it++;
    }
    
    
    /*
    2. Generate a random number between [0, ChanceFungus)
    3. If the random number is 0, then add a new fungus at a random angle/position
    around the circumference of the Petri dish, exactly VIEW_RADIUS pixels from
    the center of the Petri dish (which is at VIEW_WIDTH/2, VIEW_HEIGHT/2).*/
    
    int ChanceFungus = max(510 - L * 10, 200);
    int r = randInt(0, ChanceFungus);
    if (r==0)
    {
        double x, y;
        getCircumferenceSpot(x, y);
        actorList.push_back(new Fungus(x, y, getLevel(), this));
        
    }
     
    /*
    4. ChanceGoodie = max(510 – L * 10, 250)
    5. Generate a random number between [0, ChanceGoodie)
    6. If the random number is 0, then add a new goodie at a random angle/position
    around the circumference of the Petri dish, exactly VIEW_RADIUS pixels from
    the center of the Petri dish (which is at VIEW_WIDTH/2, VIEW_HEIGHT/2).
    A. There is a 60% chance the goodie will be a restore health goodie.
    B. There is a 30% chance the goodie will be a flame thrower goodie.
    C. There is a 10% chance the goodie will be an extra-life goodie.*/
    
    int ChanceGoodie = max(510 - L * 10, 250);
    r = randInt(0, ChanceGoodie);
    if (r==0)
    { //CHECK that this probability works out
        double x, y;
        //CHECK actually on circumference
        getCircumferenceSpot(x, y);
        r = randInt(0,99);
        if (r<10)
            actorList.push_back(new ExtraLifeGoodie(x, y, getLevel(), this));
        else if (r<40)
            actorList.push_back(new FlameThrowerGoodie(x, y, getLevel(), this));
        else
            actorList.push_back(new RestoreHealthGoodie(x, y, getLevel(), this));
    }
    
    
//update game stats
    //Score: 004500 Level: 4 Lives: 3 health: 82 Sprays: 16 Flames: 4
    ostringstream gameStats;
    gameStats << "Score: " <<getScore()<<" Level: " <<getLevel()<<" Lives: " <<getLives()<<" Health: " <<pSocrates->getHealth()<<" Sprays: "<<pSocrates->getSprayCharges() <<" Flames: "<< pSocrates->getFlameThrowerCharges()<<endl;
    string gameStatsStr = gameStats.str();
    setGameStatText(gameStatsStr);
    
    
    
    
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



void StudentWorld::addActor(Actor* a) //QUESTION: will using an actor pointer to add a derived object (spray,fire,etc) limit its functionality to what is contained in Actor??
{
    actorList.push_back(a);
}

void StudentWorld::getRandomLocInDish(double &x, double &y) const
{
    x = randInt(0, VIEW_WIDTH);
    y = randInt(0, VIEW_HEIGHT);
    double z = pow((x-VIEW_WIDTH/2), 2) + pow((y-VIEW_HEIGHT/2), 2);
    if (z> pow(120, 2))
        getRandomLocInDish(x, y);
}

bool StudentWorld::overlap(double const x1 , double const y1 , double const x2 , double const y2 ) const
{
    double dist = sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
    if (dist < 2*SPRITE_RADIUS)
        return true;
    return false;
}

bool StudentWorld::isValidNewSpot(double const x, double const y) 
{
    //iterate through actorList
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        double x2 = (*it) -> getX();
        double y2 = (*it) -> getY();
        //if overlaps with any actors return false
        if (overlap(x, y, x2, y2))
            return false;
        it++;
    }
    //if does not overlap with any actors return true
    return true;
}

void StudentWorld::getValidNewSpot(double &x, double &y) 
{
    //get a new random location
    getRandomLocInDish(x, y);
    //check if this location is valid (aka does not overlap w anything
    if (!isValidNewSpot(x, y))
        //if it does overlap with stuff start over until it is a valid spot
        getValidNewSpot(x, y);
}

void StudentWorld::getCircumferenceSpot(double &x, double &y)
{
    x = randInt(0, VIEW_WIDTH);
    y = randInt(0, VIEW_HEIGHT);
    //QUESTION: WHY IS THIS NOT ON THE FULL CIRCUMFERENCE
    double dist = sqrt(pow(x-VIEW_WIDTH/2, 2)+pow(y-VIEW_HEIGHT/2, 2));
       if (static_cast<int>(dist) != VIEW_RADIUS)
           getCircumferenceSpot(x, y);
}

Actor* StudentWorld::amITouchingSomething(Actor* a)
{
 //QUESTION/NOTE: should i pass in a pointer to an actor or an actor itself -- for now its a pointer
    double aX = a-> getX();
    double aY = a -> getY();
    
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        double x = (*it) -> getX();
        double y = (*it) -> getY();
        //if overlaps with any actors (other than itself) return the actor it overlaps with
        if ( (*it)!= a && overlap(aX, aY, x, y))
            return *it;
        it++;
    }
    //if a doesnt overlap with any actor in actorList, return nullptr
    return nullptr;
}

Socrates* StudentWorld::getSocratesP()
{
    return pSocrates;
}

Socrates* StudentWorld::amITouchingSocrates(Actor *a)
{
    double aX = a-> getX();
    double aY = a -> getY();
    
    double sX = pSocrates->getX();
    double sY = pSocrates->getY();
    
    if (overlap(aX, aY, sX, sY))
        return pSocrates;
    else
        return nullptr;
}

bool StudentWorld::movementOverlap(Actor *a, int units)
{
    //return true if there is overlap with a blocking object in actors predicted path
    double x,y;
    a->getPositionInThisDirection(a->getDirection(), units, x, y);

    
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        if ((*it)->blocksMovement())
        {
            double aX = (*it)->getX();
            double aY = (*it)->getY();
            double dist = sqrt(pow(x-aX,2)+pow(y-aY, 2));
            if (dist <= SPRITE_WIDTH/2)
                return true;
        }
        it++;
    }
    return false;
}

bool StudentWorld::leavingPetriDish(Actor *a)
{
    //return true if planned path puts actor outside of the view radius
    double x,y;
    a->getPositionInThisDirection(a->getDirection(), 3, x, y);
    double dist = sqrt(pow(x-VIEW_WIDTH/2,2)+pow(y-VIEW_HEIGHT/2, 2));
    if (dist >= VIEW_RADIUS)
        return true;
    return false;
}

Actor* StudentWorld::closestFood(Actor *a)
{
    double aX = a->getX();
    double aY = a->getY();
    
    double minDist = 150;
    Actor *closest = nullptr;
    list<Actor*>::iterator it = actorList.begin();
    while (it!=actorList.end())
    {
        if ((*it)->isEdible())
        {
            double x = (*it) -> getX();
            double y = (*it) -> getY();
            double dist = sqrt(pow(x-aX,2)+pow(y-aY, 2));
            if (dist<minDist && dist<128)
            {
                minDist = dist;
                closest = *it;
            }
        }
        it++;
    }
    return closest;
}
