#include "Actor.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//TODO: remove this when done debugging
#include <iostream>
using namespace std;

void Dirt::doSomething()
{}
void Food::doSomething()
{}

//SOCRATES implentation
//TODO: socrates dying
//TODO: level implementation
void Socrates::doSomething()
{
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
            case KEY_PRESS_SPACE:
            {
                if (sprayCharges>0)
                {
                    //add new spray to actorList --> NEED POINTER TO studentWorld!!!
                    getPositionInThisDirection(getDirection(), 2*SPRITE_RADIUS, x, y);
                    getWorld()->addActor(new Spray(x, y, getDirection(), getWorld()));
                    sprayCharges--;
                    //play spray sound effect
                    getWorld()->playSound(SOUND_PLAYER_SPRAY);
                }
                break;
            }
            case KEY_PRESS_ENTER:
            {
                if (flameThrowerCharges>0)
                {
                    //add 16 new flames to actorList -->  studentWorld!!!
                    for (int i=0; i<16; i++)
                    {
                        getPositionInThisDirection(getDirection()+(i*22), 2*SPRITE_RADIUS, x, y);
                        getWorld()->addActor(new Flame(x, y, getDirection()+(i*22), getWorld()));
                    }
                   flameThrowerCharges--;
                   //play fire sound effect
                   getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
                break;
            }
                
            default:
                break;
        }
    }
        else
        {
            if (sprayCharges<20)
              sprayCharges++;
        }
/*
Get user input; if player pressed a key, perform the desired action
If directional keys: move Socrates by 5 degrees in positional angle either clockwise or counterclockwise, and set the direction he is facing
Other keys (space to use spray, enter to use flamethrower): not Part 1 req
If player DID NOT press key: (not Part 1 req)
Replenish spray charges by 1 (if not already at maximum of 20 charges)*/

}
//play sound when socrates dies
void Socrates::soundDie()
{
    getWorld()->playSound(SOUND_PLAYER_DIE);
}
//play sound when socrates gets hurt
void Socrates::soundHurt()
{
    getWorld()->playSound(SOUND_PLAYER_HURT);
}



//projectile implementations
void Projectile::doSomething()
{
    //Check to see if it’s still alive. If not, it must immediately return.
    if (!isAlive())
        return;
    //if overlap
    Actor* touching = getWorld()->amITouchingSomething(this);
    if (touching !=nullptr && touching->receiveDamage(0))
    {
        //damage object -- virtual function : 5 for flame, 2 for spray
        damageTarget(touching);
        //kill projectile
        kill();
        return;
    }
    moveForward(2*SPRITE_RADIUS);
    setTravelDistance(getTravelDistance()-2*SPRITE_RADIUS);
    if (getTravelDistance()<=0)
        kill();
    
    //FLAME
    /* Otherwise…
    2. Check to see if it overlaps with a damageable object (e.g., a bacterium of any
    type, goodie, fungus or a dirt pile). To check for overlap, see if the flame has a
    Euclidean distance of <= SPRITE_RADIUS*2 between itself and a target object’s
    (x, y) coordinate. If so, the flame must:
    a. Tell a single impacted object that it has been damaged with 5 hit points of
    damage (if the flame overlaps with multiple objects at the same time, it
    must only damage one of them – which one is left to you to decide. Don’t
    ask us which object you should damage.).
    b. Immediately set its status to not-alive, so the flame goes away
    immediately.
    30
    c. Return immediately.
    3. Otherwise, the flame will move forward in its current direction by
    SPRITE_RADIUS*2 pixels.
    4. If the flame has moved a total of 32 pixels after step 3, then it immediately sets its
    status to not alive (it dissipates) and can cause no more damage*/
}

//SPRAY
/*
Otherwise...
2. Check to see if it overlaps with a damageable object (e.g., a bacterium of any
type, goodie, fungus or a dirt pile). To check for overlap, see if the spray has a
Euclidean distance of <= SPRITE_RADIUS*2 between itself and the target
object. If so, the spray must:
a. Tell a single impacted object that it has been damaged with 2 hit points of
damage (if the spray overlaps with multiple objects at the same time, it
must only damage one of them – which one is left to you to decide. Don’t
ask us which object should be chosen.).
31
b. Immediately set its status to not-alive, so the spray goes away
immediately.
c. Return immediately.
3. Otherwise, the spray will move forward in its current direction by
SPRITE_RADIUS*2 pixels.
4. If the spray has moved a total of 112 pixels after step 3, then it immediately sets
its status to not alive (it dissipates) and can cause no more damage*/


void Flame::damageTarget(Actor *a)
{
    a->receiveDamage(5);
}

void Spray::damageTarget(Actor *a)
{
    a->receiveDamage(2);
}


void AggressiveSalmonella::doSomething()
{
    if (!isAlive())
        return;
    bool stuck = false;
    //The aggressive salmonella must check to see if it’s less than or equal to 72 pixel away from Socrates
    double x = this-> getX();
    double y = this -> getY();
    double sX = getWorld()->getSocratesP()->getX();
    double sY = getWorld()-> getSocratesP()->getY();
    double dist = sqrt(pow(x-sX,2)+pow(y-sY, 2));
    if (dist<=72)
    {
        //It will try to move forward 3 pixels in the direction toward Socrates
        const double PI = 4 * atan(1);
        //get angle from bacteria to Socrates
        double angle = atan2(sY-y, sX-x);
        //convert from rads to degrees
        angle = angle *(180/PI);
        //set salmonella's direction to that angle
        setDirection(angle);
        
        if (!getWorld()->movementOverlap(this, 3) )
            //if moving towards food is possible, move 3 units toward the food
            moveAngle(getDirection(), 3);
        else
            stuck = true;
    }
    //check if touching socrates
    Socrates* soc = getWorld()->amITouchingSocrates(this);
    if (soc!=nullptr)
        //damage socrates by 2 points
           getWorld()->getSocratesP()->receiveDamage(2);
    
    else if (!stuck)
        Salmonella::doSomething();
}

void RegularSalmonella::doSomething()
{
    if (!isAlive())
        return;
    Socrates* soc = getWorld()->amITouchingSocrates(this);
    if (soc!=nullptr)
    {
        //this is for regular salmonella
        getWorld()->getSocratesP()->receiveDamage(1);
    }
    else
        Salmonella::doSomething();
}

void Salmonella::doSomething()
{
    Bacteria::doSomething();
    
    Actor* closestFood = getWorld()->closestFood(this);
    
    //5. check if movement plan distance is greater than zero
        if (getMovementPlanDist()>0)
        {
        //decrement movement plan distance by 1
        setMovementPlanDist(getMovementPlanDist()-1);
        if (!getWorld()->movementOverlap(this, 3) && !getWorld()->leavingPetriDish(this))
        {
            //if it CAN move forward, move forward 3 units
            moveAngle(getDirection(), 3);
        }
        else
        {
            //if it cannot move forward, pick random direction and reset movement plan distance
            setDirection(randInt(0, 359));
            setMovementPlanDist(10);
        }
        //immediately return
        return;
        }
        //if movementPlanDistance is 0, get directional angle to closest food within 128 pixels
        if (closestFood!=nullptr)
        {
            //if there is food within 128 pixels
            const double PI = 4 * atan(1);
            //get angle from bacteria to closest food
            double angle = atan2((closestFood->getY())-getY(),(closestFood->getX())-getX());
            //convert from rads to degrees QUESTION: is this right???
            angle = angle *(180/PI);
            //set salmonella's direction to that angle
            setDirection(angle); //QUESTION: is this right?
            
            //DEBUGGING STUFF
            //cout << "food x,y: "<< closestFood->getX()<<", "<<closestFood->getY()<<" x,y: " << getX()<<", "<<getY()<<endl;
            //cout << "the value i got for angle is: "<<angle<<endl;
            //cout << "direction: "<<getDirection()<<endl;
            
            
            //if moving towards food will cause salmonella to hit dirt
            if (getWorld()->movementOverlap(this, 3) )//|| getWorld()->leavingPetriDish(this))
            {
                //pick random direction and reset movement plan distance
                setDirection(randInt(0, 359));
                setMovementPlanDist(10);
                //immediately return
                return;
            }
            //if moving towards food is possible, move 3 units toward the food
            moveAngle(getDirection(), 3);
            
        }
        else
        {
            //if no food can be found within 128 pixels
            //pick random direction and reset movement plan distance
            setDirection(randInt(0, 359));
            setMovementPlanDist(10);
        }
}

void Ecoli::doSomething()
{
    Socrates* soc = getWorld()->amITouchingSocrates(this);
    if (soc!=nullptr)
        //damage socrates by 2 points
           getWorld()->getSocratesP()->receiveDamage(4);
    
    Bacteria::doSomething();
    
    double x = this-> getX();
    double y = this -> getY();
    double sX = getWorld()->getSocratesP()->getX();
    double sY = getWorld()-> getSocratesP()->getY();
    double dist = sqrt(pow(x-sX,2)+pow(y-sY, 2));
    if (dist<=256)
    {
        const double PI = 4 * atan(1);
        //get angle from bacteria to Socrates
        double angle = atan2(sY-y, sX-x);
        //convert from rads to degrees
        angle = angle *(180/PI);
        //set salmonella's direction to that angle
        setDirection(angle);
        for (int i=0; i<10; i++)
        {
            //if is possible to move two units toward socrates, do so
            if (!getWorld()->movementOverlap(this, 2))
            {
                moveAngle(getDirection(), 2);
                return;
            }
            else
            {
                setDirection(getDirection()+10);
            }
        }
        //QUESTION: what does it stays still mean???
    }
}


void Bacteria::doSomething()
{
    Actor* touching = getWorld()->amITouchingSomething(this);
    //3. check to see if total of 3 food has been eaten
    if (getFood()==3)
    {
    //calculate where to spawn new bacteria
    //Plus SPRITE_RADIUS if its x coordinate is < VIEW_WIDTH/2
    //Minus SPRITE_RADIUS if its x coordinate is > VIEW_WIDTH/2
        double newx;
        if (getX()<VIEW_WIDTH/2)
            newx = getX()+SPRITE_RADIUS;
        else if (getX()>VIEW_WIDTH/2)
            newx = getX()-SPRITE_RADIUS;
        else
            newx = getX();
        
        double newy;
            if (getY()<VIEW_HEIGHT/2)
                newy = getY()+SPRITE_RADIUS;
            else if (getY()>VIEW_HEIGHT/2)
                newy = getY()-SPRITE_RADIUS;
            else
                newy = getY();
        
        spawn(newx, newy);
        setFood(0);
        }
    //4. check to see if it overlaps with food
    else if (touching !=nullptr && touching->isEdible())
    {
        eatFood();
        touching->kill();
    }
    
}

void Bacteria::turnToFood()
{
    int r = randInt(0, 1);
    if (r==1)
    {
        getWorld()->addActor(new Food(getX(), getY(), getWorld()));
    }
}

//play sound when salmonella dies
void Salmonella::soundDie()
{
    getWorld()->increaseScore(100);
    Bacteria::turnToFood();
    getWorld()->playSound(SOUND_SALMONELLA_DIE);
}
//play sound when salmonella gets hurt
void Salmonella::soundHurt()
{
    getWorld()->playSound(SOUND_SALMONELLA_HURT);
}

//ECOLI IMPLEMENTATION
//play sound when ecoli dies
void Ecoli::soundDie()
{
    Bacteria::turnToFood();
    getWorld()->increaseScore(100);
    getWorld()->playSound(SOUND_ECOLI_DIE);
}
//play sound when ecoli gets hurt
void Ecoli::soundHurt()
{
    getWorld()->playSound(SOUND_ECOLI_HURT);
}


//BACTERIA SPAWNING FUNCTIONS
void RegularSalmonella::spawn(double x, double y)
{
    getWorld()->addActor(new RegularSalmonella(x, y, getWorld()));
}
void AggressiveSalmonella::spawn(double x, double y)
{
    getWorld()->addActor(new AggressiveSalmonella(x, y, getWorld()));
}
void Ecoli::spawn(double x, double y)
{
    getWorld()->addActor(new Ecoli(x, y, getWorld()));
}



//LIFETIME IMPLEMENTATION

void Lifetime::doSomething()
{
    if (!isAlive())
        return;
    //if overlap with Socrates
    Socrates* soc = getWorld()->amITouchingSocrates(this);
    if (soc!=nullptr)
    {
        kill();
        sound();
        doGoodiesThing();
    }
    lifetime--;
    if (lifetime<=0)
        kill();
}

bool Lifetime::receiveDamage(int hitPoints)
{
    kill();
    return true;
}

void Lifetime::sound()
{
    getWorld()->playSound(SOUND_GOT_GOODIE);
    
}
//GOODIE IMPLEMENTATIONS
void RestoreHealthGoodie::doGoodiesThing()
{
    //increase player score by 250
    getWorld()->increaseScore(250);
 //Tell socrates to restore health
    getWorld()->getSocratesP()->setHealth(100);
}
void FlameThrowerGoodie::doGoodiesThing()
{
    //increase player score by 300
    getWorld()->increaseScore(300);
    //tell socrates to add 5 flame throwers to arsenal
    getWorld()->getSocratesP()->increaseFlameThrowerCharges();
}
void ExtraLifeGoodie::doGoodiesThing()
{
    //increase player score by 500
    getWorld()->increaseScore(500);
    //tell studentworld to increase lives by one
    getWorld()->incLives();
}
void Fungus::doGoodiesThing()
{
    //decrease player score by -50
    getWorld()->increaseScore(-50);
    //tell Socrates to decrease health by 20
    getWorld()->getSocratesP()->receiveDamage(20);
}
