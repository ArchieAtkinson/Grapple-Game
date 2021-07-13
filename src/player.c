#include "player.h"
#include "raymath.h"

#define START_POS_X PLAYER_SIZE/2.0f
#define START_POS_Y SCREEN_HEIGHT/4

#define HOOK_SIZE 5
#define ROPE_SIZE 2

#define SPRING_CONST_k 2.0f
#define DAMP_CONST_b 500.0f

#define POINT_VERT 0

#define VELOCITY 1.0f

#define ROPE_MIN 50
#define ROPE_MAX 400

#define ROPE_CHANGE 20

int rope_length;

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

    Vector2 speration = Vector2Subtract(anchor->position, loose->position);
    float current_dis = Vector2Length(speration);
    float diff_dis = current_dis - des_dis;
    Vector2 unit_len =  Vector2Scale(speration, 1/current_dis);
    Vector2 x = Vector2Scale(unit_len, diff_dis);
    Vector2 v = loose->velocity;
    Vector2 kx = Vector2Scale(x, SPRING_CONST_k);
    Vector2 bv = Vector2Scale(v, -DAMP_CONST_b);
    Vector2 f = Vector2Add(kx, bv);

    PhysicsAddForce(loose, f);
}

static bool is_hook_stuck(){
    grapple_t grapple = player.grapple;

    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++)
    {
        PhysicsBody body = GetPhysicsBody(i);
        int vertexCount = GetPhysicsShapeVerticesCount(i);
        if (vertexCount == 4 && body->orient == 0){   
            Rectangle rec_surface = body_to_rec(body);
            Rectangle rec_hook = body_to_rec(grapple.hook);
            if (body->id == player.grapple.hook->id){
                return false;
            }
            rec_hook.height += 4;
            rec_hook.y -= 2;
            rec_hook.width += 4;
            rec_hook.y -= 2;
            if (CheckCollisionRecs(rec_surface, rec_hook)){
                grapple.hook->enabled = false;
                player.grapple.hooked = true;
                Vector2Distance(player.body->position,player.grapple.hook->position);
                return true;
            }
        }
    }
    return false;
}

void player_init(){
    player.body = CreatePhysicsBodyRectangle((Vector2){START_POS_X, START_POS_Y}, PLAYER_SIZE,PLAYER_SIZE, 10);
    player.body->enabled = true;
    
    player.grapple.hook = CreatePhysicsBodyRectangle((Vector2){START_POS_X + PLAYER_SIZE, START_POS_Y}, HOOK_SIZE, HOOK_SIZE, 10);
    player.grapple.hook->enabled = true;

    player.grapple.speed = (Vector2){ 0, 0 };
    player.grapple.active = false;
    player.grapple.hooked = false;
}

Vector2 get_fixed_mouse(){
    Vector2 mouse = GetMousePosition();
    mouse.x -= camera.offset.x - camera.target.x;
    return mouse;
}

void player_draw(){

    // DrawRectangleRec(body_to_rec(player.body), PINK);
    DrawRectanglePro(body_to_rec(player.body), (Vector2){0,0},player.body->orient, PINK);

 
    DrawLineV(player.body->position,player.grapple.hook->position, LIME);
    DrawRectanglePro(body_to_rec(player.grapple.hook), (Vector2){0,0} ,player.grapple.hook->orient, RED);

}


void player_update(){
    grapple_t *grapple = &(player.grapple);

    if (IsKeyDown(KEY_C)){
        if (rope_length < ROPE_MAX){
            rope_length += ROPE_CHANGE;
        }
    }
    else if (IsKeyDown(KEY_D)) {
        if (rope_length > ROPE_MIN){
            rope_length -= ROPE_CHANGE;
        }
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
        spring(get_fixed_mouse());
    }

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && grapple->active == false && grapple->hooked == false){ 
        grapple->active = true;  
        Vector2 mouse = get_fixed_mouse();
        Vector2 force = Vector2Subtract(mouse, grapple->hook->position);
        float scale = Vector2Length(force);
        force = Vector2Normalize(force);
        force = Vector2Scale(force, scale*1.0f);

        PhysicsAddForce(grapple->hook, force);
    }

    else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        grapple->active = false;
        grapple->hooked = false;
        grapple->hook->enabled = true;
        grapple->hook->force = player.body->force;
        grapple->hook->velocity = player.body->velocity;
        grapple->hook->position.x = player.body->position.x;
        grapple->hook->position.y = player.body->position.y - PLAYER_SIZE;
    }

    else if(grapple->active == true && grapple->hooked == false){
        is_hook_stuck(player);
    }

    
    if (grapple->hooked){
        spring_const_dist(player.grapple.hook, player.body, 300);
    }

    if (grapple->active == false && grapple->hooked == false){
        // spring_const_dist(player.body, player.grapple.hook, 30);
    }

    if (player.body->position.y > SCREEN_HEIGHT + 300){
        init();
    }
}