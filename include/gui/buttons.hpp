#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "gui/text.hpp"

namespace gui{
    class button{
    protected:
        Vector2 pos;
        Texture2D* text;
        Rectangle buttonRec;
        
        Color buttonColor{255,255,255,255};
        float scale=1.f;
        Vector2 oldPos = {0,0};
    public:
        button(Texture2D& text, Vector2 pos): pos(pos), text(&text){}

        virtual Vector2 getPos() const {return pos;};
        
        virtual void effectLoop(Vector2 mousePos);
        virtual bool isClicked(Vector2 mousePos);
        virtual void draw();
    };

    class hiddenButton : public button{
    private:
        bool isActive;
        Texture2D* text2;
    public:
        hiddenButton(Texture2D& text, Texture2D& text2, Vector2 pos, bool isActive) : button(text, pos), isActive(isActive), text2(&text2) {}
        ~hiddenButton() = default;

        bool getActive() {return isActive;};
        void setActive(bool x) {isActive = x;};

        void drawAdd();
        void draw() override;
    };
    

    class textButton : public button{
    private:
        std::string textData;
        font& fontData;
        Color color;
    public:
        textButton(Texture2D& text, std::string textData, font& fontData, Color color, Vector2 pos) : button(text, pos), textData(textData), fontData(fontData), color(color) {}
        ~textButton() = default;

        void draw() override;
    };

    class switchButton : public button {
    private:
        Texture2D* text2;
    public:
        switchButton(Texture2D& text, Texture2D& text2, Vector2 pos) : button(text, pos), text2(&text2) {}
        ~switchButton() = default;

        void draw(bool isOn);
    };

    class switchTextButton : public button {
    private:
        std::string data1;
        std::string data2;
        font& fontData;
        Color color;
    public:
        switchTextButton(Texture2D& text, std::string data1, std::string data2, font& fontData, Color color, Vector2 pos) 
            : button(text, pos), data1(data1), data2(data2), fontData(fontData), color(color) {}
        ~switchTextButton() = default;

        void draw(bool isOn);
    };
};
