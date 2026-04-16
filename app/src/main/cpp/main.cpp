

#include "raymob.h" // This header can replace 'raylib.h' and includes additional functions related to Android.
#include "android_native_app_glue.h"
#include <math.h>
#include <vector>
#include <map>
#include <variant>
#include <format>
#include<any>
#include "Game//game.hpp"
#include <utility>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
//bool systemButtons(Vector2 touch_user, Rectangle& button);
bool verifyMoveObstacle(bool inition, bool& haveColitionHitbox);

struct ObsRects{
    Vector2 pos;
    Color color;
    Vector2 tam;
    float dange;
    float lifeObstacle;
};
float MyCamp(float value, float min, float max){
    if (value < min) return min;
    if( value > max ) return max ;
    return value;
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "raylib first game");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Vector2 circlePos;
    Vector2 smalCirclePos;
    Vector2  touch;
    float time_for_touch = 0.8f;
    Rectangle atackButton = {110, 90, 150, 100};
    bool userTouchBUtton = false;
    bool isAtackPlayer = false;
    float orbitRadios = 110.7f;
    float angle = 0;
    int enemys = 5;
    float speedCricle = 578.0f;
    float speedEnemy = speedCricle/2.5-0.8f;
    float velocityCricle =0;
    std::vector<ObsRects> obstacles(enemys);
    bool inition = true;
    bool haveColition = true;
    bool haveColitionHitbox = false;
    float timeColition = 1.3f;
    float lifeCircle = 120.0f;
    Color colorCircle = WHITE;

    //Inicialiation :
    for (int i =0 ; i< enemys; i++){
        obstacles[i].pos = (Vector2) {120.0f+ i*240.0f, 350.0f};
        obstacles[i].color = RED;
        obstacles[i].tam = (Vector2){120, 98};
        obstacles[i].dange = 23.5f;
    }
    float screenRotationWidth;
    float screenRotationHeight;
    bool permitMove = true;
    //Atack System
    AtackPlayer playerAtack(20);
    float deltatime;

    // Main game loop1
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        deltatime = GetFrameTime();

            if (IsGestureDetected(GESTURE_DRAG)) {
                isAtackPlayer = true;
                inition = false;
                touch = GetTouchPosition(0);
                float drestX = touch.x - circlePos.x;
                float drestY = touch.y - circlePos.y;
                float distance = sqrtf(drestX * drestX + drestY * drestY);
                float dffX = drestX / distance;
                float dffY = drestY / distance;
                if (distance > 5.0f) {
                    //velocityCricle += speedCricle*GetFrameTime();
                    circlePos.x += dffX * speedCricle * deltatime;
                    circlePos.y += dffY * speedCricle * deltatime;
                }
                angle += 6.5f * deltatime;
                smalCirclePos = (Vector2) {circlePos.x + cosf(angle) * orbitRadios,
                                       circlePos.y + sinf(angle) * orbitRadios};
                //smalCirclePos = (Vector2){circlePos.x + cos((angle))*orbitRadios,circlePos.y, sin(angle) * orbitRadios};
                //if (CheckCollisionPointCircle(touch, circle[i].position, circle[i].radius))
            }else{
                isAtackPlayer = false;
            }


        if (inition){
            screenRotationWidth = GetScreenWidth();
            screenRotationHeight = GetScreenHeight();
            circlePos = (Vector2){(float )screenRotationWidth/2, (float )screenRotationHeight/2};
        }
        //bool temp_variable = systemButtons(GetTouchPosition(0), atackButton);
        playerAtack.damageSystem(deltatime, isAtackPlayer);

        for (int i = 0 ; i< enemys ; i++){
            float closestX = MyCamp(circlePos.x, obstacles[i].pos.x, obstacles[i].pos.x + obstacles[i].tam.x);
            float closestY = MyCamp(circlePos.y, obstacles[i].pos.y, obstacles[i].pos.y + obstacles[i].tam.y);
            float distanceX = circlePos.x - closestX;
            float distanceY = circlePos.y -closestY;
            float distance_all = sqrtf((distanceX * distanceX)+ (distanceY* distanceY));
            auto calculateDistance= [&](){
                closestX = MyCamp(circlePos.x, obstacles[i].pos.x, obstacles[i].pos.x + obstacles[i].tam.x);
                closestY = MyCamp(circlePos.y, obstacles[i].pos.y, obstacles[i].pos.y + obstacles[i].tam.y);
                distanceX = circlePos.x - closestX;
                distanceY = circlePos.y -closestY;
                distance_all = sqrtf((distanceX * distanceX)+ (distanceY* distanceY));
                return distance_all < 30;
            };
            float closesmalltX = MyCamp(smalCirclePos.x, obstacles[i].pos.x, obstacles[i].pos.x + obstacles[i].tam.x);
            float closesmalltY = MyCamp(smalCirclePos.y, obstacles[i].pos.y, obstacles[i].pos.y + obstacles[i].tam.y);
            float distancesmallX = smalCirclePos.x - closesmalltX;
            float distancesmallY = smalCirclePos.y -closesmalltY;//YOus should veriffy becaus dont that dont cause eror
            float distance_small = sqrtf((distancesmallX * distancesmallX)+ (distancesmallY* distancesmallY));
            //bool permitMove = true;
            auto sum_distace = [](int index_actual){
                if (index_actual <= 3){
                    if(index_actual <1) return 0.1f;
                    return (float)index_actual/10;
                }else {
                    return 0.0f;
                }
            };
            //obstacles[i].color = (Color)playerAtack.colorHit((Color)obstacles[i].color);
            std::pair<float, float>  side_distance = {distancesmallX, distancesmallY};
            haveColitionHitbox = playerAtack.checkColisionHitbox(distance_small, i,side_distance);//Chech colition and runthe visual effect if th player is attacking

            if(calculateDistance()) {
                float overclap = 30 - distance_all;
                int loop = 1;
                if (distance_all > 0) {
                    circlePos.x += (distanceX) / distance_all * overclap;
                    circlePos.y += (distanceY) / distance_all * overclap;
                } else {
                    circlePos.y -= overclap;
                }
                permitMove = false;
                //Visual ocations
                colorCircle = BROWN;
                haveColition = true;
                //INTER OCATIONS
                //Dange
                lifeCircle -= obstacles[i].dange;
            };
            if(distance_small<20){
                float overlap = 20 -distance_small;
                if (distance_small>0){
                    smalCirclePos.x += distancesmallX/ distance_small * overlap*deltatime;
                    smalCirclePos.y += distancesmallY/ distance_small * overlap*deltatime;
                }else{
                    smalCirclePos.y -= overlap*deltatime;
                }
            }
            if (verifyMoveObstacle(inition, haveColitionHitbox)){
                //Move enemy, only when this will be in the permitid range
                if (!permitMove && distance_all > 30+2 && distance_small > 20+1){
                    obstacles[i].pos.x += (distanceX/distance_all+sum_distace(i))*speedEnemy*deltatime;
                    obstacles[i].pos.y += (distanceY/distance_all+sum_distace(i))*speedEnemy*deltatime;
                    permitMove = true;
                }else if (permitMove){
                    obstacles[i].pos.x += (distanceX/distance_all+sum_distace(i))*speedEnemy*deltatime;
                    obstacles[i].pos.y += (distanceY/distance_all+sum_distace(i))*speedEnemy*deltatime;
                }
            }
        }

        playerAtack.pugObstacle(deltatime, obstacles, smalCirclePos);

        if (lifeCircle<0){
            lifeCircle = 120.0f;
            inition = true;
        }
        for (int i = 0; i< enemys; i++){
            for (int t =i+1;t< enemys; t++) {

                if (CheckCollisionRecs(
                        (Rectangle) {obstacles[t].pos.x, obstacles[t].pos.y, obstacles[t].tam.x,
                                     obstacles[t].tam.y},
                                     (Rectangle) {obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].tam.x,
                                     obstacles[i].tam.y})
                        ) {
                    Rectangle overlap = GetCollisionRec(
                            (Rectangle) {obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].tam.x,
                                         obstacles[i].tam.y},
                            (Rectangle) {obstacles[t].pos.x, obstacles[t].pos.y, obstacles[t].tam.x,
                                         obstacles[t].tam.y}
                    );
                    if (overlap.width < overlap.height) {
                        if (obstacles[t].pos.x < obstacles[i].pos.x) {
                            obstacles[t].pos.x -= overlap.width;
                        } else {
                            obstacles[t].pos.x += overlap.width;
                        }
                    } else {
                        if (obstacles[t].pos.y < obstacles[i].pos.y) {
                            obstacles[t].pos.y -= overlap.height;
                        } else {
                            obstacles[t].pos.y += overlap.height;
                        }
                    }
                }
            }
        };

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Toca la pantalla para mover/aparecer el circulo ", 34, 198, 33, BLUE);
        if (IsGestureDetected(GESTURE_DRAG)) {
            DrawCircleV(smalCirclePos, 20.f, RED);
        }
        if (haveColition){
            timeColition-=deltatime;
            if(timeColition<0){
                colorCircle = WHITE;
                timeColition = 1.3f;
                haveColition = false;
            }
        }

        playerAtack.drawHitbox(circlePos);
        for (int i = 0 ; i < enemys; i++){
            DrawRectangleV(
                    obstacles[i].pos,
                    obstacles[i].tam,
                    obstacles[i].color

            );
        };
        //DrawRectangleV((Vector2 ){atackButton.x, atackButton.y+100},(Vector2){atackButton.width, atackButton.height}, BLUE);
        DrawCircleV(circlePos, 38, colorCircle);
        EndDrawing();

        //----------------------------------------------------------------------------------
        // De-Initialization
        //--------------------------------------------------------------------------------------
    }
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
bool systemButtons(Vector2 touch_user, Rectangle& button){
    if (CheckCollisionPointRec(touch_user, button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return true;
    }
    return false;
};
bool verifyMoveObstacle(bool inition, bool& haveColitionHitbox){
    if (inition) return false;
    if(haveColitionHitbox){
        haveColitionHitbox = false;
        return false;
    }
    return true;
}