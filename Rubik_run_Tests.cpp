/**
    File    : Rubik_run_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20191207.1.2

    Rubik Program - Test Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/

///The function member 'void UpdateThe(Cube_T& Cube2Update) const noexcept' wasn't used in this test, but is plenty functional

#include "Rubik_run_Tests.h"

bool Test(const char* Msg, TestFunction& Execute) {
     cout << string(50, '=') << "\nTest " << Msg << ".\n" << string(50, '-') << "\nCreating main cube: " << flush;
     Rubik Cube;
     cout << "done." << endl;

     bool Result = Execute(Cube);

     cout << "\nTest Result: " << (Result ? "PASSED" :  "FAILED");

     PressEnter();

     return Result;
}

TestFunction Test_CreationCube = [](Rubik& Cube) -> bool {
             ShowCube(Cube, ShowSize, HideColors, ShowPercentual);
             return pow(Cube.SideSize, 3) == Cube.TofBlocks &&
                    Cube.isFinished()                       &&
                    Cube.PercentualDone() == 100.0;
};

TestFunction Test_RandomizeCube = [](Rubik& Cube) -> bool {
             ShowCube(Cube, HideSize, HideColors, ShowPercentual);
             cout << "Randomized 1000 times: " << flush;
             Cube.randomize(1000);
             cout << "done." << endl;
             ShowCube(Cube, HideSize, HideColors, ShowPercentual);

             return !Cube.isFinished() && Cube.PercentualDone() < 100.0 && !AreThesesCubesEqual(Rubik(), Cube);
};

TestFunction Test_ResetCube = [](Rubik& Cube) -> bool {
             cout << "Randomized 1000 times: " << flush;
             Cube.randomize(1000);
             cout << "done." << endl;
             cout << "Reseting cube: " << flush;
             Cube.reset();
             cout << "done." << endl;

             return Cube.isFinished() && Cube.PercentualDone() == 100.0 && AreThesesCubesEqual(Rubik(), Cube);
};

TestFunction Test_CopyCube = [](Rubik& Cube) -> bool {
             cout << "Creating auxiliary cube: " << flush;
             Rubik AuxCube;
             cout << "done." << endl;
             cout << "Randomized auxiliary cube 1000 times: " << flush;
             AuxCube.randomize(1000);
             cout << "done." << endl;
             cout << "Copy auxiliary cube to main cube: " << flush;
             Cube(AuxCube);
             cout << "done." << endl;

             return AreThesesCubesEqual(AuxCube, Cube); //Include check the colors
};

void ShowFlippedCube() {
     cout << "\n\nTest Flipping.\n\nCube created:";

     Rubik Cube;

     ShowCube(Cube, HideSize, HideColors, HidePercentual);
     ShowCube(Cube);

     PressEnter();

     Cube.flip(LAYER,  0, TurnBlocks::CLOCKWISE);
     Cube.flip(LINE,   1, TurnBlocks::COUNTERCLOCKWISE);
     Cube.flip(COLUMN, 2, TurnBlocks::COUNTERCLOCKWISE);

     cout << "\nCube was flipped few times 'manually'\n";
     ShowCube(Cube, HideSize, HideColors);
     cout << "(Expected less than 100)";

     PressEnter();

     Cube.randomize(1000);
     ShowCube(Cube, HideSize, ShowColors, HidePercentual);
     cout << '\n';
     ShowCube(Cube, HideSize, HideColors, ShowPercentual);

     cout << "\n\nCube after 1000 flips.";

     PressEnter();
}

