#pragma once

#include <raylib.h>
#include <raymath.h>
#include "core/ctx.hpp"

#include "gui/textures.hpp"
#include "gui/healthBar.hpp"
#include "gui/text.hpp"
#include "gui/buttons.hpp"

#include "towers/towers.hpp"
#include "enemy/enemys.hpp"

#include "enemy/wawe.hpp"

class baseScreen{
protected:
    bool debugMode=0;
    Vector2 screenSize;
    int status;
    ctx* GData;

    Camera2D camera;
public:
    baseScreen(ctx* GData) : GData(GData) {
        camera.offset = { 0.f, 0.f };
        camera.target = { 0.f, 0.f };
        camera.rotation = 0.f;
        camera.zoom = 1.f;

        screenSize = GData->ScreenSize;
    }

    virtual ~baseScreen() = default;

    virtual void start() = 0;
    virtual void loop() = 0;
    virtual void draw() = 0;

    virtual int getStatus() {return status;}
};