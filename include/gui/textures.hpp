#pragma once

#include <raylib.h>
#include <string>

namespace gui{
    class texture {
    private:
        Texture2D text;
        Vector2 pos;
    public:
        texture(const std::string& path, Vector2 pos);
        ~texture();

        Texture2D getTexture() {return text;};
        Vector2 getPos() {return pos;};
        Vector2 getSize() {return {(float)text.width, (float)text.height};};
        
        void draw();
        void drawEx(Vector2 pos, float scale);
    };
};