#pragma once

#include <raylib.h>
#include <string>

namespace gui{
    class timedTexture{
    private:
        Texture2D* text;
        Vector2 pos;
        float lifeTime;
        float startTime;

    public:
        timedTexture(Texture2D& text, Vector2 pos, float lifeTime, float dt) : text(&text), pos(pos), lifeTime(lifeTime), startTime(dt) {}

        bool getActive(float dt) const {return dt<=startTime+lifeTime;};

        void draw() {
            DrawTextureEx(*text , pos, 0.f, 1.f, WHITE);
        }
    };
};
