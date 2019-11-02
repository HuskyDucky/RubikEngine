/**
    File    : Rubik_run.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191026.4

    Rubik Program

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run.h"

int main() {

    RubikCube Cube;

    ShowCube(Cube, true, true);
    ShowCube(Cube, false, false);

    Cube.Flip(FlipBlocksAt::LAYER,  0, TurnBlocks::CLOCKWISE);
    Cube.Flip(FlipBlocksAt::LINE,   1, TurnBlocks::COUNTERCLOCKWISE);
    Cube.Flip(FlipBlocksAt::COLUMN, 2, TurnBlocks::COUNTERCLOCKWISE);

    Cube.Randomize(1000);

   ShowCube(Cube, false, false);
   ShowCube(Cube, true, false);

    cout << "\nPress <ENTER>..."; cin.get();

    return 0;
}
