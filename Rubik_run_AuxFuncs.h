/**
    File    : Rubik_run.h
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20191115.1

    Rubik Program Show Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include <cmath>
#include <iostream>
#include <algorithm>

#include "Rubik_Cube.h"

constexpr bool HideSize       = false;
constexpr bool HideColors     = false;
constexpr bool HidePercentual = false;

constexpr bool ShowSize       = true;
constexpr bool ShowColors     = true;
constexpr bool ShowPercentual = true;

constexpr uint8_t IsDifferent = 0;
constexpr uint8_t IsEqual     = 1;
constexpr uint8_t NotCompare  = 2;

void PressEnter();

const char* TheColorIs(const uint8_t C) noexcept;
const char* ThePositionIs(const uint8_t P) noexcept;

string CubeIsFinishORNot(const Rubik& Cube);

bool CompareBlocks(const Block blk1, const Block blk2);
bool CompareCubes(const Cube_T& Cube1, const Cube_T& Cube2);

void ShowCube(const Rubik& Cube, const bool ShowSize = true, const bool ShowColors = true, const bool ShowPercentual = true);


