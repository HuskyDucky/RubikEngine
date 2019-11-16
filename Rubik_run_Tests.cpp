/**
    File    : Rubik_run_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20191116.1

    Rubik Program Show Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run_AuxFuncs.h"

void Test_RandomazidedCube() {
     auto Test = [](Rubik& Cube, const char* Msg,
                    function<void(Rubik& Cube)> RunFunc,
                    const uint8_t ExpectedComparationResult) -> void {

                   if (ExpectedComparationResult) cout << '\n';
                   cout << '\n' << Msg << ": ";

                   Cube_T CurrCube = Cube.CurrentBlocksPositions();
                   RunFunc(Cube);

                   if (ExpectedComparationResult < 2)
                      cout << (ExpectedComparationResult == CompareCubes(CurrCube, Cube.CurrentBlocksPositions()) ? "PASSED" : "FAILED");
                   else
                      ShowCube(Cube, HideSize, HideColors, HidePercentual);
     };

     cout << "\nTest cube's Randomization.\n\nCube created:\n";
     Rubik Cube;
     Rubik const AuxCube;
     ShowCube(Cube, HideSize, HideColors, HidePercentual);

     PressEnter();

     Test(Cube, "Check Saved initial state of cube's randomization", [](Rubik& Cube){ Cube.RecoverRandomizedCube(); }, IsEqual);
     Test(Cube, "Randomize Cube 1000 times",                         [](Rubik& Cube){ Cube.Randomize(1000); },         NotCompare);

     const Cube_T RandomizedState = Cube.CurrentBlocksPositions();

     {
     cout << "\n\nAlso, Are the colors blocks randomized? ";
     bool IsPassed = false;
     const Cube_T AuxCubeState = AuxCube.CurrentBlocksPositions();
     for (CubeSize_T blk = 0; blk < RandomizedState.size(); ++blk)
         if (!CompareBlocks(RandomizedState[blk], AuxCubeState[blk])) {
            IsPassed = true;    //find the first block were the colors changes then confirm it was randomized
            break;
         }
     cout << (IsPassed ? "Yes" : "No");
     }

     Test(Cube, "Check cube's randomization saved",                  [](Rubik& Cube){ Cube.RecoverRandomizedCube(); }, IsEqual);
     Test(Cube, "Cube has been Reset",                               [](Rubik& Cube){ Cube.Reset(); },                 NotCompare);

     cout << "\nIs the Cube in its original state? "
          << (CompareCubes(AuxCube.CurrentBlocksPositions(), Cube.CurrentBlocksPositions()) ? "Yes" : "No");

     Test(Cube, "Compare Reset Cube with the saved randomazed State.", [](Rubik& Cube){ Cube.RecoverRandomizedCube(); }, IsDifferent);

     cout << '\n';

     PressEnter();
}

void ShowFlippedCube() {
     cout << "\n\nTeste Flipping.\n\nCube created:\n";

     Rubik Cube;

     ShowCube(Cube, HideSize, HideColors, HidePercentual);
     ShowCube(Cube);

     PressEnter();

     Cube.Flip(FlipBlocksAt::LAYER,  0, TurnBlocks::CLOCKWISE);
     Cube.Flip(FlipBlocksAt::LINE,   1, TurnBlocks::COUNTERCLOCKWISE);
     Cube.Flip(FlipBlocksAt::COLUMN, 2, TurnBlocks::COUNTERCLOCKWISE);

     cout << "\nCube was flipped few times 'manually'";
     ShowCube(Cube, HideSize, HideColors);
     cout << "(Expected less than 100)";

     PressEnter();

     Cube.Randomize(1000);
     ShowCube(Cube, HideSize, ShowColors, HidePercentual);
     ShowCube(Cube, HideSize, HideColors, HidePercentual);

     cout << "\n\nCube after randomize 1000 times.\n";
}

