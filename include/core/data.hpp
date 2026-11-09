#pragma once

#include <vector>
#include "towers/towers.hpp"
#include "enemy/enemys.hpp"
#include "enemy/wawe.hpp"

namespace data{
    inline const std::vector<std::vector<towerStats>> TStats = { //? Hasar, Alan, Saldırı Hızı, Maliyet
        {   { 1.f, 150.f, 0.5f, 250, {{TS_NULL}}}, // Normal
            { 1.f, 200.f, 0.5f, 100, {{TS_NULL}}}, 
            { 2.f, 200.f, 0.5f, 300, {{TS_NULL}}}},

        {   { 4.f, 250.f, 2.0f, 450, {{TS_NULL}}}, // yavaş ve güçlü
            { 4.f, 400.f, 2.0f, 120, {{TS_NULL}}},
            { 8.f, 400.f, 1.0f, 400, {{TS_NULL}}}},

        {   { 4.f, 150.f, 4.0f, 350, {{TS_BOMB, 6}}}, // Alan vuran, yavaş
            { 8.f, 150.f, 4.0f, 250, {{TS_BOMB, 6}}},
            { 8.f, 200.f, 2.5f, 550, {{TS_BOMB, 6}}}},

        {   { 0.f, 150.f, 1.0f, 150, {{TS_SLOW, 3}}}, // Yavaşlatan
            { 0.f, 300.f, 1.0f, 150, {{TS_SLOW, 3}}},
            { 0.f, 300.f, 0.5f, 300, {{TS_SLOW, 5}}}}
    };

    inline const std::vector<std::string> ePaths = {

    };

    inline const std::vector<EnemyStats> eStats = { //? Maksimum can, can, hız
        {  4.f,   4.f, 150.f, {ES_NULL}}, // Normal düşman
        {  2.f,   2.f, 250.f, {ES_NULL}}, // Hızlı düşman
        { 10.f,  10.f, 100.f, {ES_NULL}}, // Yaşlı dayılar
        {150.f, 150.f, 100.f, {ES_BOSS}}, // Güçlü


        // LVL 2
        {   8.f,    8.f, 150.f, {ES_NULL}}, // Normal düşman
        {   4.f,    4.f, 250.f, {ES_NULL}}, // Hızlı düşman
        {  20.f,   20.f, 100.f, {ES_NULL}}, // Yaşlı dayılar
        {  50.f,   50.f,  350.f, {ES_NULL}},// Çok hızlı / Hafif güçlü
        { 150.f,  150.f,  200.f, {ES_NULL}}, // Orta hızlı / Çok güçlü
        {1000.f, 1000.f,  100.f, {ES_BOSS}}  // Boss fight
    };


    inline const std::vector<AllWawesData> waweDatas{
        // LVL 1 (DPS/COST = EASY:60, NORMAL:50 HARD:40)
        // LVL 1 (DPS-ATTACK = EASY:3, NORMAL:4 HARD:5)
        {{
            {1, {wawe{1.f, E_Normal, 7, 1.}}, reward{50}},
            {2, {wawe{1.f, E_Normal, 10, .5}}, reward{25}},
            {3, {wawe{1.5f, E_Speed, 10, .5}}, reward{50}},
            {4, {wawe{1.f, E_Heavy, 10, 1.}}, reward{100}},
            {5, {wawe{1.f, E_Normal, 10, 1.}, 
                wawe{1.f, E_Speed, 10, 1.}, 
                wawe{1.f, E_Heavy, 10, 1.}}, reward{150}},
            {6, {wawe{1.f, E_Heavy, 10, 1.},
                wawe{1.f, E_Speed, 20, .5}}, reward{100}},
            {7, {wawe{1.f, E_Heavy, 20, .5}}, reward{100}},
            {8, {wawe{1.f, E_Heavy, 20, .5},
                wawe{3.f, E_Speed, 20, .5}}, reward{100}},
            {9, {wawe{1.5f, E_Speed, 25, .5},
                wawe{12.f, E_Normal, 20, .5}}, reward{200}},
            {10, {wawe{1.f, E_Normal, 10, 0.5},
                wawe{1.f, E_Speed, 10, 0.5},
                wawe{3.f, E_Boss, 1, 1.}}, reward{250}}
        }, {2,3}},
        {{
            {1, {wawe{1.f, E2_Normal, 4, 1.}}, reward{100}},
            {2, {wawe{1.f, E2_Normal, 6, .5}}, reward{100}},
            {3, {wawe{1.f, E2_Normal, 5, .5},
                 wawe{1.5f, E2_Speed, 5, .5}}, reward{150}},
            {4, {wawe{1.f, E2_Heavy, 5, 1.}}, reward{200}},
            {5, {wawe{3.f, E2_Speed, 5, .5}, 
                wawe{1.f, E2_Heavy, 8, 1.}}, reward{250}},
            {6, {wawe{3.f, E2_Heavy, 5, .5},
                wawe{1.f, E2_Speed, 10, .5},
                wawe{1.f, E2_Normal, 5, .5}}, reward{300}},
            {7, {wawe{1.f, E2_Speed, 20, .3}}, reward{250}},
            {8, {wawe{1.f, E2_Heavy, 10, .2},
                wawe{3.f, E2_Speed, 10, .3}}, reward{200}},
            {9, {wawe{1.5f, E2_Speed, 8, .5},
                wawe{3.f, E2_Normal, 10, .5}}, reward{200}},
            {10, {wawe{1.f, E2_Speed, 5, 0.5},
                wawe{1.f, E2_Heavy, 5, 0.5},
                wawe{2.f, E2_Light, 1, 1.}}, reward{300}},
            {11, {wawe{5.f, E2_Light, 2, 1},
                wawe{1.f, E2_Heavy, 10, 0.5}}, reward{450}},
            {12, {wawe{1.f, E2_Heavy, 20, 1},
                wawe{10.f, E2_Light, 3, 2}}, reward{450}},

            {13, {wawe{1.f, E2_Storm, 2, 5},
                wawe{1.f, E2_Speed, 20, 1}}, reward{500}},

            {14, {wawe{1.f, E2_Storm, 2, 5},
                wawe{2.f, E2_Light, 2, 5},
                wawe{1.f, E2_Speed, 24, 0.5}}, reward{400}},

            {15, {wawe{1.f, E2_Storm, 2, 1},
                wawe{10.f, E2_Heavy, 5, 1},
                wawe{1.f, E2_Speed, 24, 0.5}}, reward{200}},

            {16, {wawe{1.f, E2_Storm, 2, 1},
                wawe{1.f, E2_Light, 3, 1}}, reward{400}},

            {17, {wawe{1.f, E2_Storm, 2, 5},
                wawe{1.f, E2_Speed, 24, 0.5}}, reward{500}},

            {18, {wawe{10.f, E2_Storm, 3, 2},
                wawe{5.f, E2_Light, 3, 2},
                wawe{1.f, E2_Speed, 32, 0.5}}, reward{400}},

            {19, {wawe{5.f, E2_Storm, 3, 5},
                wawe{2.f, E2_Normal, 15, 1},
                wawe{1.f, E2_Speed, 24, 0.5},
                wawe{1.f, E2_Heavy, 10, 2}}, reward{400}},

            {20, {wawe{20.f, E2_Boss, 1, 0.1},
                wawe{15.f, E2_Storm, 2, 1},
                wawe{25.f, E2_Light, 2, 0.5},
                wawe{1.f, E2_Heavy, 25, 1},
                wawe{2.f, E2_Speed, 25, 1}}, reward{300}},
        }, {}}
    };
};