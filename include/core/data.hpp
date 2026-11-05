#pragma once

#include <vector>
#include "towers/towers.hpp"
#include "enemy/enemys.hpp"
#include "enemy/wawe.hpp"

namespace data{
    inline const std::vector<std::vector<towerStats>> TStats = { //? Hasar, Alan, Saldırı Hızı, Maliyet
        {   { 1.f, 150.f, 0.5f, 250, {{TS_NULL}}, "Basic Tower"}, // Normal
            { 1.f, 200.f, 0.5f, 100, {{TS_NULL}}, "Range Update"}, 
            { 2.f, 200.f, 0.5f, 300, {{TS_NULL}}, "Better guns"}},

        {   { 4.f, 250.f, 2.0f, 450, {{TS_NULL}}, "Strong & Slow tower"}, // yavaş ve güçlü
            { 4.f, 400.f, 2.0f, 120, {{TS_NULL}}, "Range Update"},
            { 8.f, 400.f, 1.0f, 400, {{TS_NULL}}, "Faster & Strong reload"}},

        {   { 4.f, 150.f, 4.0f, 350, {{TS_BOMB, 6}}, "Range Attack Tower"}, // Alan vuran, yavaş
            { 8.f, 150.f, 4.0f, 250, {{TS_BOMB, 6}}, "Strong bomb"},
            { 8.f, 200.f, 2.5f, 550, {{TS_BOMB, 6}}, "Mobile bomb"}},

        {   { 0.f, 150.f, 1.0f, 150, {{TS_SLOW, 3}}, "Slowwer Tower"}, // Yavaşlatan
            { 0.f, 300.f, 1.0f, 150, {{TS_SLOW, 3}}, "Range Update"},
            { 0.f, 300.f, 0.5f, 300, {{TS_SLOW, 5}}, "Faster"}}
    };


    inline const std::vector<EnemyStats> eStats = { //? Maksimum can, can, hız
        {  4.f,   4.f, 150.f, {ES_NULL}}, // Normal düşman
        {  2.f,   2.f, 250.f, {ES_NULL}}, // Hızlı düşman
        { 10.f,  10.f, 100.f, {ES_NULL}}, // Yaşlı dayılar
        {150.f, 150.f, 150.f, {ES_BOSS}}, // Güçlü


        // LVL 2
        { 150.f,  150.f,  350.f, {ES_NULL}},// Çok hızlı / Hafif güçlü
        { 300.f,  300.f,  200.f, {ES_NULL}}, // Orta hızlı / Çok güçlü
        {2500.f, 2500.f,  100.f, {ES_BOSS}}  // Boss fight
    };


    inline std::vector<AllWawesData> waweDatas{
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
            {8, {wawe{1.f, E_Heavy, 20, .2},
                wawe{3.f, E_Speed, 20, .3}}, reward{100}},
            {9, {wawe{1.5f, E_Speed, 25, .5},
                wawe{12.f, E_Normal, 20, .5}}, reward{200}},
            {10, {wawe{1.f, E_Normal, 10, 0.5},
                wawe{1.f, E_Speed, 10, 0.5},
                wawe{3.f, E_Boss, 1, 1.}}, reward{250}}
        }, {2,3}},
        {{
            {1, {wawe{1.f, E_LLight, 4, 1.}}, reward{500}},
            {2, {wawe{1.f, E_LHeavy, 3, .5}}, reward{250}},
            {3, {wawe{1.5f, E_LLight, 5, .5}}, reward{500}},
            {4, {wawe{1.f, E_LHeavy, 5, 1.}}, reward{1000}},
            {5, {wawe{1.f, E_LLight, 5, 1.}, 
                wawe{1.f, E_LHeavy, 2, 1.}}, reward{1500}},
            {6, {wawe{1.f, E_LHeavy, 5, 1.},
                wawe{1.f, E_LLight, 10, .5}}, reward{1000}},
            {7, {wawe{1.f, E_LLight, 10, .5}}, reward{1000}},
            {8, {wawe{1.f, E_LHeavy, 10, .2},
                wawe{3.f, E_LLight, 10, .3}}, reward{1000}},
            {9, {wawe{1.5f, E_LLight, 8, .5},
                wawe{12.f, E_LLight, 10, .5}}, reward{2000}},
            {10, {wawe{1.f, E_LLight, 5, 0.5},
                wawe{1.f, E_LLight, 5, 0.5},
                wawe{3.f, E_LBoss, 1, 1.}}, reward{2500}}
        }, {}}
    };
};