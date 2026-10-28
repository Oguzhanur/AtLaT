#include "gui/healthBar.hpp"

void healthBar::draw(float health){
    DrawRectangle(pos.x, pos.y, size.x, size.y, BLACK);

    DrawRectangle(
        pos.x+gap,
        pos.y+gap,
        (size.x-gap*2) * (health/maxHealth),
        size.y-gap*2,
        RED
    );
}