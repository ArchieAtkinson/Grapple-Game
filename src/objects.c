#include "common.h"
#include "objects.h"

#define BAR_HEIGHT 30

#define PLATFORM_WIDTH 100
#define PLATFORM_HIGHT 30

#define COIN_WIDTH 40
#define COIN_HEIGHT 80

#define COIN_GAP COIN_WIDTH * 2.5
#define MAX_COIN_IN_SET 10
#define MAX_ACTIVE_COIN_SETS 10
#define VERT_COIN_GAP 300

#define COIN_SET_GAP_MIN COIN_WIDTH * 5
#define COIN_SET_GAP_MAX COIN_WIDTH * 10

#define COIN_START_POS 200

Sound coin_sound;

typedef struct{
    Vector2 position[MAX_COIN_IN_SET];
    int amount;
    Vector2 last_pos;
    bool collected[MAX_COIN_IN_SET];
}coin_set_t;

coin_set_t coin_sets[MAX_ACTIVE_COIN_SETS];

PhysicsBody top_bar;
PhysicsBody start_platform;

static int populate_coin_set(coin_set_t *coin_set, int last_coin_pos){
    coin_set->amount = ran_int_range(5, MAX_COIN_IN_SET);

    int coin_height = ran_int_range(VERT_COIN_GAP, SCREEN_HEIGHT - VERT_COIN_GAP);

    int set_gap = ran_int_range(COIN_SET_GAP_MIN, COIN_SET_GAP_MAX);

    int coin_offset_x = last_coin_pos + set_gap;

    for (int i = 0; i < coin_set->amount; i++){
        coin_set->position[i] = (Vector2){coin_offset_x + (i*COIN_GAP), coin_height};     
        coin_set->collected[i] = false; 
    }
    coin_set->last_pos = (Vector2){coin_offset_x + ((coin_set->amount-1)* COIN_GAP), coin_height};
    
    int new_last_coin_pos = coin_set->last_pos.x + set_gap;

    return new_last_coin_pos;
}


static void create_inital_coin_sets(){
    int last_coin_pos = COIN_START_POS;
    for(int i = 0; i < MAX_ACTIVE_COIN_SETS; i++){
       last_coin_pos =  populate_coin_set(&coin_sets[i], last_coin_pos);
    }
}


void objects_init(){
    coin_sound = LoadSound("resources/coin.wav");

    create_inital_coin_sets();

    top_bar = CreatePhysicsBodyRectangle((Vector2){SCREEN_WIDTH/2, BAR_HEIGHT/2}, SCREEN_WIDTH*2, BAR_HEIGHT, 10);
    top_bar->enabled = false;

    start_platform = CreatePhysicsBodyRectangle((Vector2){PLATFORM_WIDTH/2, SCREEN_HEIGHT/2}, PLATFORM_WIDTH, PLATFORM_HIGHT, 10);
    start_platform->enabled = false;
}

void draw_coin_sets(){
    for (int i = 0; i < MAX_ACTIVE_COIN_SETS; i++){
        coin_set_t set = coin_sets[i];
        for (int j = 0; j < set.amount; j++){
            if (set.collected[j] == false){
                DrawRectangleRounded(centre_to_rec(set.position[j], COIN_WIDTH, COIN_HEIGHT), 1.0f, 10, GOLD);
            }
        }
    }
}

void objects_draw(){
    DrawRectangleRec(body_to_rec(top_bar), GRAY);
    DrawRectangleRec(body_to_rec(start_platform), GRAY);
    draw_coin_sets();
    // printf("%d\n", coin_sets_free_index);
}

static void manage_coin_sets(){
    Vector2 last_coin_screen_pos = world_to_screen(coin_sets[0].last_pos);
    if (last_coin_screen_pos.x <=  COIN_WIDTH*2){
        for (int i = 0; i < MAX_ACTIVE_COIN_SETS - 1; i++){
            coin_sets[i] = coin_sets[i+1];
        }
        populate_coin_set(&coin_sets[MAX_ACTIVE_COIN_SETS - 1], coin_sets[MAX_ACTIVE_COIN_SETS - 2].last_pos.x);
    }
}

static void collect_coins(){
    for(int i = 0; i < MAX_ACTIVE_COIN_SETS; i++){
        if (world_to_screen(coin_sets[i].last_pos).x <  SCREEN_WIDTH){
            for(int j = 0; j < coin_sets[i].amount; j++){
                if (coin_sets[i].collected[j] != true){
                    coin_sets[i].collected[j] = CheckCollisionRecs(body_to_rec(player.body), centre_to_rec(coin_sets[i].position[j], COIN_WIDTH, COIN_HEIGHT));
                    if (coin_sets[i].collected[j]){
                        score++;
                        PlaySound(coin_sound);
                    }                  
                }
            }
        }
    }
}


void objects_update(){
    manage_coin_sets();
    collect_coins();
    top_bar->position.x = player.body->position.x;
    // if (player.grapple.hooked == true && start_platform != 0){
    //     DestroyPhysicsBody(start_platform);
    //     start_platform = 0;
    // }
}