#pragma once

#include <raylib.h>
#include <string>

namespace gui{
    class button{
    private:
        Vector2 pos;
        Texture2D* text;
        Rectangle buttonRec;
    public:
        button(Texture2D& text, Vector2 pos): pos(pos), text(&text){}
        ~button() = default;

        bool isClicked(Vector2 mousePos);
        void draw();
    };
};
