#include "gui/text.hpp"


gui::font::font(const std::string& path, float fontSize) : fontSize(fontSize){
    //! AI GENERATED
    std::vector<int> codepoints;
    for (int i = 32; i <= 126; i++) {
        codepoints.push_back(i);
    }

    int turkishCodepoints[] = {
        0x00C7, // Ç
        0x00E7, // ç
        0x011E, // Ğ
        0x011F, // ğ
        0x0130, // İ
        0x0131, // ı
        0x00D6, // Ö
        0x00F6, // ö
        0x015E, // Ş
        0x015F, // ş
        0x00DC, // Ü
        0x00FC  // ü
    };

    for (int cp : turkishCodepoints) {
        codepoints.push_back(cp);
    }
    //! AI GENERATED END
    fontData = LoadFontEx(path.c_str(), fontSize, codepoints.data(), static_cast<int>(codepoints.size()));
}

gui::font::~font(){
    UnloadFont(fontData);
}


// Draw Text
void gui::drawText(const std::string& data, Vector2 pos, const font& font, Color color) {
    DrawTextEx(font.getFontData(), data.c_str(), pos, font.getFontSize(), 2, color);
}