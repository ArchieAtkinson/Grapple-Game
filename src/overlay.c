#include "overlay.h"

Vector2 mouse_postion;

void overlay_init(){
    HideCursor();
}

void overlay_update(Vector2 *mouse_postion){
    *mouse_postion = GetMousePosition();
}

void overlay_draw(Vector2 *mouse_postion){
    DrawCircleV(*mouse_postion, 3, RED);
}