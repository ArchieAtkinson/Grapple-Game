#include "common.h"

Vector2 centre_to_top_left(Vector2 centre, Vector2 size){
    return (Vector2) {centre.x - size.x/2.0f, centre.y - size.y/2.0f};
}

Vector2 top_left_to_centre(Vector2 top_left, Vector2 size){
    return (Vector2) {top_left.x + size.x/2.0f, top_left.y + size.y/2.0f};
}