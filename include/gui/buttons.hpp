#pragma once

#include <raylib.h>
#include <string>

namespace gui{
    class button{
    protected:
        Vector2 pos;
        Texture2D* text;
        Rectangle buttonRec;
    public:
        button(Texture2D& text, Vector2 pos): pos(pos), text(&text){}

        virtual bool isClicked(Vector2 mousePos);
        virtual void draw();
    };

    class switchButton : public button {
    private:
        Texture2D* text2;
    public:
        switchButton(Texture2D& text, Texture2D& text2, Vector2 pos) : button(text, pos), text2(&text2) {}
        ~switchButton() = default;

        void draw(bool isOn);
    };
};
