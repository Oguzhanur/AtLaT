#include <raylib.h>
#include <string>
#include <vector>

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


    void drawText(const std::string& data, Vector2 pos, const font& font, Color color);
};