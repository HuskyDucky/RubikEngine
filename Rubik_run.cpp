/**
    File    : Rubik_run.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191115.2

    Rubik Program

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run_Tests.h"

//Godś number - https://ruwix.com/the-rubiks-cube/gods-number/

int main() {

    Test_RandomazidedCube();

    ShowFlippedCube();

    PressEnter();

    return 0;
}
