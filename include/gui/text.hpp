#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

namespace gui{

    class font{
    private:
        Font fontData;
        float fontSize;
    public:
        font(const std::string& path, float fontSize);
        ~font();

        Font getFontData() const {return fontData;};
        float getFontSize() const {return fontSize;};
    };

    struct TextData{
        std::string& data;
        font& fontData;
        Color color;
    };

    Vector2 centeringText(const std::string& text, Vector2 pos, const font& font);
    Vector2 centeringTextEx(const std::string& text, float scale, Vector2 pos, const font& font);

    void drawText(const std::string& data, Vector2 pos, const font& font, Color color);
    void drawCenteredText(const std::string& data, Vector2 pos, const font& font, Color color);

    std::string floatToStr(float f);
};