#pragma once

#include <raylib.h>
#include <string>

namespace gui{
    class button{
    private:
        Vector2 pos;
        Texture2D texture;
        Rectangle buttonRec;
    public:
        button(const std::string& path, Vector2 pos);
        ~button();

        bool isClicked(Vector2 mousePos);
        void draw();
    };
};
