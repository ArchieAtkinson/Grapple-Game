#include "player.h"
#include "raymath.h"

#define START_POS_X PLAYER_SIZE/2.0f
#define START_POS_Y SCREEN_HEIGHT/4

#define HOOK_SIZE 5
#define ROPE_SIZE 2

#define SPRING_CONST_k 0.9f
#define DAMP_CONST_b 500.0f

#define ROPE_LENGTH 50.0f

float Vector2DCross(Vector2 v1, Vector2 v2){
    Vector3 va  = (Vector3){v1.x, v1.y, 0.0f};
    Vector3 vb  = (Vector3){v2.x, v2.y, 0.0f};
    return Vector3CrossProduct(va, vb).z;
}

void spring(Vector2 mouse_postion){
    //http://www.euclideanspace.com/physics/kinematics/combinedVelocity/
    //https://gafferongames.com/post/spring_physics/
    Vector2 x = Vector2Subtract(mouse_postion, player.body->position);
    Vector2 v = player.body->velocity;
    Vector2 kx = Vector2Scale(x, SPRING_CONST_k);
    Vector2 bv = Vector2Scale(v, -DAMP_CONST_b);
    Vector2 f = Vector2Add(kx, bv);

    PhysicsAddForce(player.body, f);
}
void spring_const_dist(PhysicsBody anchor, PhysicsBody loose, float des_dis){
    //http://www.euclideanspace.com/physics/kinematics/combinedVelocity/
    //https://gafferongames.com/post/spring_physics/
    //F = -k(|x|-d)(x/|x|) - bv
    
    Vector2 speration = Vector2Subtract(anchor->position, loose->position);
    float current_dis = Vector2Length(speration);
    float diff_dis = current_dis - (des_dis - 320.0f/SPRING_CONST_k);
    Vector2 unit_len =  Vector2Scale(speration, 1/current_dis);
    Vector2 x = Vector2Scale(unit_len, diff_dis);
    Vector2 kx = Vector2Scale(x, SPRING_CONST_k);
    Vector2 v = loose->velocity;
    Vector2 bv = Vector2Scale(v, -DAMP_CONST_b);
    Vector2 f = Vector2Add(kx, bv);

    PhysicsAddForce(loose, f);
}

static void is_hook_stuck(){
    static int counts = 0;
    Rectangle rec_top_bar = body_to_rec(top_bar);
    Rectangle rec_hook = body_to_rec(player.grapple.hook);

    rec_top_bar.height += 10;

    if (CheckCollisionRecs(rec_top_bar, rec_hook)){
        player.grapple.hook->enabled = false;
        player.grapple.state = HOOKED;
    }
}

void player_init(){
    player.body = CreatePhysicsBodyRectangle((Vector2){START_POS_X, START_POS_Y}, PLAYER_SIZE,PLAYER_SIZE, 20);
    player.body->enabled = true;
    
    player.grapple.hook = CreatePhysicsBodyRectangle((Vector2){START_POS_X + PLAYER_SIZE, START_POS_Y}, HOOK_SIZE, HOOK_SIZE, 10);
    player.grapple.hook->enabled = true;

    player.grapple.speed = (Vector2){ 0, 0 };
    player.grapple.state = WAITING;
}

Vector2 get_fixed_mouse(){
    Vector2 mouse = GetMousePosition();
    mouse.x -= camera.offset.x - camera.target.x;
    return mouse;
}

void player_draw(){

    // DrawRectangleRec(body_to_rec(player.body), PINK);
    DrawRectanglePro(body_to_rec(player.body), (Vector2){0,0},player.body->orient*RAD2DEG, PINK);

 
    DrawLineV(player.body->position,player.grapple.hook->position, LIME);
    DrawRectanglePro(body_to_rec(player.grapple.hook), (Vector2){0,0} ,player.grapple.hook->orient*RAD2DEG, RED);

}

void reset_hook(){
    player.grapple.hook->enabled = true;
    player.grapple.hook->force = player.body->force;
    player.grapple.hook->velocity = player.body->velocity;
    player.grapple.hook->position.x = player.body->position.x;
    player.grapple.hook->position.y = player.body->position.y - PLAYER_SIZE;
}

void player_update(){

    // printf("vev: %f\n", player.grapple.hook->velocity.x);

    // if (player.grapple.hook->velocity.x > 7.0f){
    //     player.grapple.hook->velocity.x = 7.0f;
    // }

    switch (player.grapple.state){
        case IN_AIR:{
            is_hook_stuck(player);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ 
                player.grapple.state = WAITING;
            }
            break;
        }
        case HOOKED:{
            spring_const_dist(player.grapple.hook, player.body, ROPE_LENGTH);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ 
                player.grapple.state = WAITING;
            }
            break;
        }
        case WAITING:{
            reset_hook();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ 
                
                player.grapple.state = IN_AIR;  
                Vector2 mouse = get_fixed_mouse();
                Vector2 force = Vector2Subtract(mouse, player.grapple.hook->position);
                float scale = Vector2Length(force);
                force = Vector2Normalize(force);
                force = Vector2Scale(force, scale*1.0f);

                PhysicsAddForce(player.grapple.hook, force);
            }
            break;
        }
        default:
            break;
    }

    if (player.body->position.y > SCREEN_HEIGHT + 300){
        init();
    }
}