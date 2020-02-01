/**
    File    : Rubik_run.h
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200130.2

    Rubik Program - auxiliary functions to test Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef RUN_AUX_H
#define RUN_AUX_H

#include <iomanip>
#include <iostream>
#include <algorithm>

#include "../Rubik_Cube.h"

constexpr bool HideSize       = false;
constexpr bool HideColors     = false;
constexpr bool HidePercentual = false;

constexpr bool ShowSize               = true;
constexpr bool ShowColorsAndPositions = true;
constexpr bool ShowPercentual         = true;

void PressEnter();

constexpr bool RESET = true;
string StepCounter(bool Reset = false);

const char* TheColorIs(const uint8_t C) noexcept;
const char* ThePositionIs(const uint8_t P) noexcept;

bool AreThesesCubesEqual(const Rubik& Cube1, const Rubik& Cube2);

void ShowCube(const Rubik& Cube, const bool ShowSize = true, const bool ShowColors = true, const bool ShowPercentual = true);

#endif
