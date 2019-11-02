/**
    File    : Rubik_run.h
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20191102.1

    Rubik Program Show Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include <cmath>
#include <iostream>

#include "Rubik_Cube.h"

const char* TheColorIs(const uint8_t C) noexcept;
const char* ThePositionIs(const uint8_t P) noexcept;
void ShowCube(const RubikCube& Cube, const bool ShowColors, const bool ShowSize);
