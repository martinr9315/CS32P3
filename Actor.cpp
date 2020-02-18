#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//SOCRATES implentation
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
                    //getWorld()->addActor(new Spray(x, y, getDirection(), getWorld()));
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
                        //getWorld()->addActor(new Flame(x, y, getDirection(), getWorld()));
                    }
                   flameThrowerCharges--;
                   //play fire sound effect
                   getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
                break;
            }
            default: //QUESTION: is this where we replenish the spray charges
            {
                if (sprayCharges<20)
                    sprayCharges++;
            }
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


//projectile implementations
void Projectile::doSomething()
{
    //Check to see if it’s still alive. If not, it must immediately return.
    if (!isAlive())
        return;
    //TODO:if overlap -- NEED STUDENT WORLD POINTER TO FIGURE OUT OVERLAP
        //damage object -- virtual thingy : 5 for flame, 2 for spray
        //kill(); //kill projectile
        //return;
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



void Lifetime::doSomething()
{
    if (!isAlive())
        return;
    //TODO:if overlap with Socrates -- NEED STUDENT WORLD POINTER TO FIGURE OUT OVERLAP
    //this stuff goes in if statement
        //editPlayerScore(); //edit points by whatever goodie/fungus does
        //kill();
        //sound();
        //doGoodiesThing();
        //lifetime--;
        //return;
    //if (lifetime<=0)
        //kill();
    
    
    
}
