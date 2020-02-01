/**
    File    : Rubik_run_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20200131.1

    Rubik Program - Test Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/

///The function member 'void UpdateThe(Cube_T& Cube2Update) const noexcept' wasn't used in this test, but is plenty functional

#include "Rubik_run_Tests.h"

bool Test(const char* Msg, TestFunction& Execute) {
     cout << '\n' << string(80, '=') << "\nTest " << Msg << '\n' << string(80, '-') << "\n\n";


     cout << StepCounter(RESET) << "Creating main cube: " << flush;
     Rubik Cube;
     cout << "done." << endl;

     bool Result = Execute(Cube);

     cout << '\n' << string(80, '-')
          << '\n' << StepCounter() << "Test Result:\t<<<" << (Result ? "PASSED" :  "FAILED") << ">>>"
          << '\n' << string(80, '=');

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
             cout << '\n' << StepCounter() << "Randomized 1000 times: " << flush;
             Cube.randomize(1000);
             cout << "done." << endl;
             ShowCube(Cube, HideSize, HideColors, ShowPercentual);

             return !Cube.isFinished() && Cube.PercentualDone() < 100.0 && !AreThesesCubesEqual(Rubik(), Cube);
};

TestFunction Test_ResetCube = [](Rubik& Cube) -> bool {
             cout << StepCounter() << "Randomized 1000 times: " << flush;
             Cube.randomize(1000);
             cout << "done." << endl;
             cout << StepCounter() << "Reseting cube: " << flush;
             Cube.reset();
             cout << "done." << endl;

             return Cube.isFinished() && Cube.PercentualDone() == 100.0 && AreThesesCubesEqual(Rubik(), Cube);
};

TestFunction Test_CopyCube = [](Rubik& Cube) -> bool {
             cout << StepCounter() << "Creating auxiliary cube: " << flush;
             Rubik AuxCube;
             cout << "done." << endl;
             cout << StepCounter() << "Randomized auxiliary cube 1000 times: " << flush;
             AuxCube.randomize(1000);
             cout << "done." << endl;
             cout << StepCounter() << "Copy auxiliary cube to main cube: " << flush;
             Cube(AuxCube);
             cout << "done." << endl;

             return AreThesesCubesEqual(AuxCube, Cube); //Include check the colors
};

///Create a general test to ScanFaces to read the scanned faces and commit

static bool ScanFaces_feedCubeWithFaces(Rubik& Cube,
                                        vector<vector<Color_E>>&& Faces,
                                        const string_view ComplementaryMsg = "") {

            cout << StepCounter() << "Try to feed the cube with the scanned faces";
            if (ComplementaryMsg.size() > 0) cout << ' ' << ComplementaryMsg;
            cout << ": " << flush;

            if (!Faces.empty())
                for (Position_E Face = FRONT; Face < NONEPOSITION; Face = Position_E(Face + 1)) {
                    if (!Cube.scan(Face, move(Faces[Face]))) {
                       cout << "error." << endl;
                       return false;
                    }
                }
            cout << "done." << endl;

       return true;
}

TestFunction Test_ScannedFaces_ValidRandomScanFaces3x3 = [](Rubik& Cube) -> bool {
             return ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                       {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,ORANGE,RED,   WHITE },  //Position__E::RIGHT
                                                       {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },  //Position__E::BACK
                                                       {RED,   YELLOW,BLUE, WHITE, GREEN, YELLOW,YELLOW,RED,   BLUE  },  //Position__E::LEFT
                                                       {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP
                                                       {YELLOW,RED,   WHITE,GREEN, ORANGE,BLUE,  ORANGE,GREEN, RED   }});//Position__E::BOTTOM
};

TestFunction Test_ScannedFaces_InvalidRandomScanFaces3x3 = [](Rubik& Cube) -> bool {
             return !ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                        {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,BLUE  ,RED,   WHITE },  //Position__E::RIGHT
                                                        {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },  //Position__E::BACK
                                                        {RED,   YELLOW,BLUE, BLUE, GREEN, YELLOW,YELLOW,RED,   BLUE   },  //Position__E::LEFT
                                                        {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP    --- To much BLUE
                                                        {YELLOW,RED,   WHITE,GREEN, ORANGE,BLUE,  ORANGE,GREEN, RED   }});//Position__E::BOTTOM
};

TestFunction Test_ScannedFaces_NoScannedFace3x3 = [](Rubik& Cube) -> bool {
             return !ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                        {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,BLUE  ,RED,   WHITE },  //Position__E::RIGHT
                                                        {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },  //Position__E::BACK
                                                        {RED,   YELLOW,BLUE, WHITE, GREEN, YELLOW,YELLOW,RED,   BLUE  },  //Position__E::LEFT
                                                        {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP
                                                       });                                                                //no Position__E::BOTTOM
};

TestFunction Test_ScannedFaces_WrongSizeScanFaces3x3 = [](Rubik& Cube) -> bool {
             bool Result = !ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                               {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,ORANGE,RED,   WHITE },  //Position__E::RIGHT
                                                               {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE, GREEN },          //Position__E::BACK - error
                                                               {RED,   YELLOW,BLUE, WHITE, GREEN, YELLOW,YELLOW,RED,   BLUE  },  //Position__E::LEFT
                                                               {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP
                                                               {YELLOW,RED,   WHITE,GREEN, ORANGE,BLUE,  ORANGE,GREEN, RED   }}  //Position__E::BOTTOM
                                                               ,"(less elements)");

             return Result && !ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },        //Position__E::FRONT
                                                                  {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,ORANGE,RED,   WHITE, BLUE },  //Position__E::RIGHT error
                                                                  {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },        //Position__E::BACK
                                                                  {RED,   YELLOW,BLUE, WHITE, GREEN, YELLOW,YELLOW,RED,   BLUE  },        //Position__E::LEFT
                                                                  {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},        //Position__E::TOP
                                                                  {YELLOW,RED,   WHITE,GREEN, ORANGE,BLUE,  ORANGE,GREEN, RED   }}        //Position__E::BOTTOM
                                                                  ,"(more elements)");
};

TestFunction Test_ScannedFaces_commitScannedFaces3x3 = [](Rubik& Cube) -> bool {
             bool Result =  ScanFaces_feedCubeWithFaces(Cube, {{RED,    RED,    WHITE, GREEN,  YELLOW, GREEN,  ORANGE, YELLOW, RED   },  //Position__E::FRONT
                                                               {BLUE,   ORANGE, GREEN, WHITE,  BLUE,   YELLOW, WHITE,  BLUE,   GREEN },  //Position__E::RIGHT
                                                               {YELLOW, ORANGE, GREEN, ORANGE, WHITE,  ORANGE, ORANGE, RED,    WHITE },  //Position__E::BACK
                                                               {ORANGE, YELLOW, BLUE,  GREEN,  GREEN,  YELLOW, RED,    RED,    BLUE  },  //Position__E::LEFT
                                                               {YELLOW, WHITE,  RED,   BLUE,   RED,    BLUE,   YELLOW, WHITE,  ORANGE},  //Position__E::TOP
                                                               {YELLOW, RED,    BLUE,  GREEN, ORANGE,  WHITE,  GREEN,  BLUE,  WHITE  }});//Position__E::BOTTOM
             cout << StepCounter() << "Commit the scanned faces: " << flush;
             Result = Result && Cube.commitScannedFaces();
             cout << "done." << endl;
             return Result;
};

void ShowFlippedCube() {
     cout << "\n\nTest Flipping.\n\nCube created:\n";

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
     ShowCube(Cube, HideSize, ShowColorsAndPositions, HidePercentual);
     cout << '\n';
     ShowCube(Cube, HideSize, HideColors, ShowPercentual);

     cout << "\n\nCube after 1000 flips.";

     PressEnter();
}
