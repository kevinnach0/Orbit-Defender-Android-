
#pragma once
#include "raymob.h"
#include <vector>
#include<unordered_set>
#include <math.h>
#include<map>
#include <utility>
class AtackPlayer{
private:
    std::map<int, std::pair<float,float>>saveObstacles;
    //std::unordered_set<int>saveObstacles;
    //std::vector<Vector2> saveObstacles;
    float distance_pug = sqrtf(38*38+38*38);
    float atackEnemy = 24.5f;
    float timeAtackPlayer = 1.8f;
    float timeAtaack;
    int radiosHitbox = 10;
    //Enemy
    bool isenemyhit = false;
    float timeHitEnemy = 1.8f;
    float timeHit = 0.0f;

public:
    AtackPlayer()= default;
    AtackPlayer( int radius) :playerRadius(radius) {};
    void damageSystem(float dt, bool tocuh_user);
    bool checkColisionHitbox(float distance, int index, std::pair<float,float>& disEachPoint);
    void drawHitbox(Vector2 posPlayer);
    template<typename T>
    void pugObstacle( float dt, std::vector<T>& all_obstacles , Vector2 circleSmallPos) {
        if (isenemyhit && isAtackPlayer && !saveObstacles.empty()) {
            for (auto &[index_vector,disPoints]: saveObstacles) {
                float dirrX = all_obstacles[index_vector].pos.x- circleSmallPos.x ;
                float dirrY = all_obstacles[index_vector].pos.y- circleSmallPos.y  ;
                distance_pug = float(sqrtf((dirrX * dirrX+ dirrY * dirrY)));
                if (distance_pug > 0) {

                    all_obstacles[index_vector].pos.x += (dirrX / distance_pug) * 688.0f * dt;
                    all_obstacles[index_vector].pos.y += dirrY / distance_pug *688.0f * dt;
                } else {
                    all_obstacles[index_vector].pos.y -= 688.0f * dt;

                }
            }
                //if (abs(disPoints.first) > abs(disPoints.second)){
                    //if(disPoints.first>0){
                        //all_obstacles[index_vector].pos.x += 320.0f* dt;

                    //}else{
                        //all_obstacles[index_vector].pos.x -= 320.0f* dt;


                    //}
                //}else{
                    //if(disPoints.second>0){
                        //all_obstacles[index_vector].pos.y += 320.0f* dt;

                        //all_obstacles[index_vector].pos.y +=(38.0f/distance_pug)*128.0f*dt;
                    //}else{
                        //all_obstacles[index_vector].pos.y -= 320.0f* dt;

                    //}
                //}
            //}
        } else {
            saveObstacles.clear();
        }
    };
    Color colorHit(Color YourColor);
    Color enemyColor = RED;
    int playerRadius;
    bool isAtackPlayer = false;

};