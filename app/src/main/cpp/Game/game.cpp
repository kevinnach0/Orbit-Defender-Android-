#include "game.hpp"
#include <vector>
#include <math.h>
#include <utility>

void AtackPlayer:: damageSystem(float dt, bool touch_user){
    if (touch_user){
        timeAtaack = timeAtackPlayer;
        isAtackPlayer = true;
    }
    if (isAtackPlayer){
        timeAtaack-= dt;
        if (timeAtaack<0)isAtackPlayer= false;
    }
    if (isenemyhit){
        timeHit-=dt;
        if(timeHit<0) isenemyhit = false;
    }
}
bool AtackPlayer::checkColisionHitbox(float distance, int index, std::pair<float,float>& disEachPoint) {
    if (distance < playerRadius+1.0f && isAtackPlayer){
        if(!isenemyhit){
            timeHit = (float)timeHitEnemy;
            isenemyhit = true;
            return true;
        }
        saveObstacles.insert({index, disEachPoint});
    }
    return false;
}

Color  AtackPlayer::colorHit(Color YourColor) {
    if(isenemyhit&&isenemyhit){
        enemyColor = BROWN;
        return enemyColor;
    }else{
        return YourColor;
    }
}
void AtackPlayer::drawHitbox(Vector2 posPlayer){
    if(isAtackPlayer) {
        DrawCircleV(posPlayer, playerRadius,(Color){0,0, 255, 128} );
        DrawCircleLinesV(posPlayer, playerRadius, BLUE);
    }

}