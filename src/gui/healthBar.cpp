#include "gui/healthBar.hpp"

void healthBar::draw(float health){
    DrawRectangle(pos.x, pos.y, size.x, size.y, BLACK);

    DrawRectangle(
        pos.x+10,
        pos.y+10,
        (size.x-20) * (health/maxHealth),
        size.y-20,
        RED
    );
}