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

        void draw();
        void drawEx(Vector2 pos, float scale);
    };
};