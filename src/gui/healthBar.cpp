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

    std::string uText = "Health:" + std::to_string(static_cast<int>(health)) + "/" + std::to_string(static_cast<int>(maxHealth));

    DrawText(uText.c_str(), pos.x, pos.y+size.y+10, 32, BLACK);
}