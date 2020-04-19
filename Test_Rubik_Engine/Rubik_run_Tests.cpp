/**
    File    : Rubik_run_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20200419.1

    Test Rubik Engine

    Copyright (c) 2019 TheArquitect (Menashe Rosemberg) rosemberg@ymail.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
///The function member 'void UpdateThe(Cube_T& Cube2Update) const noexcept' wasn't used in this test, but is plenty functional
#include "../Lib/Rubik_run_AuxFuncs_CompareCubes.h"
#include "../Rubik_Engine/Rubik_Engine.h"
#include "../Lib/Rubik_ShowCube.h"
#include "../Lib/Test.h"

TestFunction<Rubik_Engine> Test_CreationCube = [](Rubik_Engine& Cube) -> bool {
                           ShowCube(Cube, ShowSize, HideColors, ShowPercentual);
                           return pow(Cube.SidesSize(), 3) == Cube.TotalOfBlocks() &&
                                  Cube.isFinished()                                &&
                                  Cube.PercentualDone() == 100.0;
};

TestFunction<Rubik_Engine> Test_RandomizeCube = [](Rubik_Engine& Cube) -> bool {
                           ShowCube(Cube, HideSize, HideColors, ShowPercentual);
                           StepCounterMsg("Randomizing 1000 times");
                                Cube.randomize(1000);
                           cout << "done." << flush;
                           ShowCube(Cube, HideSize, HideColors, ShowPercentual);

                           return !Cube.isFinished() && Cube.PercentualDone() < 100.0 && AreThesesCubesDifferent(Rubik_Engine(), Cube);
};

TestFunction<Rubik_Engine> Test_CompareCube = [](Rubik_Engine& Cube) -> bool {
                           StepCounterMsg("Creating auxiliary cube");
                                Rubik_Engine AuxCube;
                           cout << "done." << flush;
                           StepCounterMsg("Compare cubes");
                               if (Cube == AuxCube) {
                                  cout << "done." << flush;

                                  cout << '\n' << StepCounter() << "Make some spins: " << flush;
                                  Cube.spin(LINE,   0, CLOCKWISE);
                                  Cube.spin(LINE,   0, CLOCKWISE);
                                  Cube.spin(LAYER,  2, COUNTERCLOCKWISE);
                                  Cube.spin(COLUMN, 2, CLOCKWISE);
                                  Cube.spin(LAYER,  1, COUNTERCLOCKWISE);
                                  Cube.spin(COLUMN, 1, COUNTERCLOCKWISE);
                                  cout << "done." << flush;

                                  bool Result = Cube == AuxCube;

                                  return !Result;
                               }
                           cout << "ERROR" << flush;

                           return false;
};

TestFunction<Rubik_Engine> Test_CopyCube = [](Rubik_Engine& Cube) -> bool {
                           StepCounterMsg("Creating auxiliary cube");
                                Rubik_Engine AuxCube;
                           cout << "done." << flush;
                           StepCounterMsg("Randomizing auxiliary cube 1000 times");
                                AuxCube.randomize(1000);
                           cout << "done." << flush;
                           StepCounterMsg("Copy auxiliary cube to main cube");
                                Cube(AuxCube);
                           cout << "done." << flush;

                           return AuxCube == Cube; //Also it checks the colors
};


TestFunction<Rubik_Engine> Test_InitCopyCube = [](Rubik_Engine& AuxCube) -> bool {
                           StepCounterMsg("Randomizing auxiliary cube 1000 times");
                                AuxCube.randomize(1000);
                           cout << "done." << flush;
                           StepCounterMsg("Create a new Cube equal to auxiliary cube");
                                Rubik_Engine Cube(AuxCube);
                           cout << "done." << flush;

                           return AuxCube == Cube;
};

TestFunction<Rubik_Engine> Test_ResetCube = [](Rubik_Engine& Cube) -> bool {
                           StepCounterMsg("Randomizing 1000 times");
                                Cube.randomize(1000);
                           cout << "done." << flush;
                           StepCounterMsg("Reseting cube");
                                Cube.reset();
                           cout << "done." << flush;

                           return Cube.isFinished() && Cube.PercentualDone() == 100.0 && Rubik_Engine() == Cube;
};

TestFunction<Rubik_Engine> Test_Turn2StartPosition3x3 = [](Rubik_Engine& Cube) -> bool {
                           const char Msg[] = "Positioning front face's central block to ";

                           auto TurnCube = [](Rubik_Engine& Cube) -> bool {
                                cout << "done." << flush;
                                StepCounterMsg("Turn cube to start position");
                                    Cube.TurnCubeToStartPosition();

                                    bool Result = Cube.isFinished();
                                cout << (Result?"pass.":"fail.") << flush;

                                return Result;
                           };

                           //TEST 1
                               cout << '\n' << StepCounter() << Msg << "bottom: " << flush;
                                   for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes) {
                                       Cube.spin(LINE, 0, CLOCKWISE);
                                       Cube.spin(LINE, 1, CLOCKWISE);
                                       Cube.spin(LINE, 2, CLOCKWISE);
                                   }
                                   for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes) {
                                       Cube.spin(LAYER, 0, COUNTERCLOCKWISE);
                                       Cube.spin(LAYER, 1, COUNTERCLOCKWISE);
                                       Cube.spin(LAYER, 2, COUNTERCLOCKWISE);
                                   }
                                   Cube.spin(COLUMN, 0, CLOCKWISE);
                                   Cube.spin(COLUMN, 1, CLOCKWISE);
                                   Cube.spin(COLUMN, 2, CLOCKWISE);
                               bool result = TurnCube(Cube);

                           //TEST 2
                               Cube.reset();
                               cout << '\n' << StepCounter() << Msg << "left: " << flush;
                                  for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes) {
                                      Cube.spin(LAYER, 0, COUNTERCLOCKWISE);
                                      Cube.spin(LAYER, 1, COUNTERCLOCKWISE);
                                      Cube.spin(LAYER, 2, COUNTERCLOCKWISE);
                                  }
                                  Cube.spin(LINE, 0, CLOCKWISE);
                                  Cube.spin(LINE, 1, CLOCKWISE);
                                  Cube.spin(LINE, 2, CLOCKWISE);
                                  for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes) {
                                      Cube.spin(COLUMN, 0, CLOCKWISE);
                                      Cube.spin(COLUMN, 1, CLOCKWISE);
                                      Cube.spin(COLUMN, 2, CLOCKWISE);
                                  }
                               result &= TurnCube(Cube);

                           //TEST 3
                               for (uint16_t RandN = 1; RandN < 5; ++RandN) {
                                  cout << '\n' << StepCounter() << RandN << '/' << 4 << " randomizing cube 1000 times: " << flush;
                                  Cube.randomize(1000);
                                  cout << "done." << flush;
                                  StepCounterInfo("Turning Cube");

                                  Cube.TurnCubeToStartPosition();

                                  bool TmpRes = Cube.isBlockInPosition(Coord_T({1,1,0})) && //Central block of Front face
                                                Cube.isBlockInPosition(Coord_T({0,1,1})) && //central block of top face
                                                Cube.isBlockInPosition(Coord_T({1,0,1}));   //central block of left face

                                  cout << (TmpRes?"pass.":"fail.") << flush;
                                  result &= TmpRes;

                                  Cube.reset();
                               }

                           //TEST 4
                              StepCounterMsg("Central blocks are in position already");

                          return TurnCube(Cube) && result;
};

///Create a general test to ScanFaces to read the scanned faces and commit

static bool ScanFaces_feedCubeWithFaces(Rubik_Engine& Cube,
                                        vector<vector<Color_E>>&& Faces,
                                        const string_view ComplementaryMsg = "") {

            cout << '\n' << StepCounter() << "Try to feed the cube with the scanned faces";
            if (ComplementaryMsg.size() > 0) cout << ' ' << ComplementaryMsg;
            cout << ": " << flush;

            if (!Faces.empty())
                for (FacePosition_E Face = FRONT; Face < NONEPOSITION; Face = FacePosition_E(Face + 1)) {
                    if (!Cube.scan(Face, move(Faces[Face]))) {
                       cout << "ERROR" << flush;
                       return false;
                    }
                }
            cout << "done." << flush;

       return true;
}

TestFunction<Rubik_Engine> Test_ScannedFaces_ValidRandomScanFaces3x3 = [](Rubik_Engine& Cube) -> bool {
                           return ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                                     {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,ORANGE,RED,   WHITE },  //Position__E::RIGHT
                                                                     {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },  //Position__E::BACK
                                                                     {RED,   YELLOW,BLUE, WHITE, GREEN, YELLOW,YELLOW,RED,   BLUE  },  //Position__E::LEFT
                                                                     {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP
                                                                     {YELLOW,RED,   WHITE,GREEN, ORANGE,BLUE,  ORANGE,GREEN, RED   }});//Position__E::BOTTOM
};

TestFunction<Rubik_Engine> Test_ScannedFaces_InvalidRandomScanFaces3x3 = [](Rubik_Engine& Cube) -> bool {
                           return !ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                                      {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,BLUE  ,RED,   WHITE },  //Position__E::RIGHT
                                                                      {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },  //Position__E::BACK
                                                                      {RED,   YELLOW,BLUE, BLUE, GREEN, YELLOW,YELLOW,RED,   BLUE   },  //Position__E::LEFT
                                                                      {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP    --- To much BLUE
                                                                      {YELLOW,RED,   WHITE,GREEN, ORANGE,BLUE,  ORANGE,GREEN, RED   }});//Position__E::BOTTOM
};

TestFunction<Rubik_Engine> Test_ScannedFaces_NoScannedFace3x3 = [](Rubik_Engine& Cube) -> bool {
                           return !ScanFaces_feedCubeWithFaces(Cube, {{RED,   RED,   WHITE,GREEN, YELLOW,GREEN, ORANGE,YELLOW,GREEN },  //Position__E::FRONT
                                                                      {BLUE,  ORANGE,GREEN,WHITE, BLUE,  YELLOW,BLUE  ,RED,   WHITE },  //Position__E::RIGHT
                                                                      {YELLOW,ORANGE,GREEN,ORANGE,WHITE, BLUE,  BLUE,  ORANGE,GREEN },  //Position__E::BACK
                                                                      {RED,   YELLOW,BLUE, WHITE, GREEN, YELLOW,YELLOW,RED,   BLUE  },  //Position__E::LEFT
                                                                      {WHITE, WHITE, RED,  BLUE,  RED,   BLUE,  YELLOW,WHITE, ORANGE},  //Position__E::TOP
                                                                     });                                                                //no Position__E::BOTTOM
};

TestFunction<Rubik_Engine> Test_ScannedFaces_WrongSizeScanFaces3x3 = [](Rubik_Engine& Cube) -> bool {
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

TestFunction<Rubik_Engine> Test_ScannedFaces_commitScannedFaces3x3 = [](Rubik_Engine& Cube) -> bool {
                           bool Result =  ScanFaces_feedCubeWithFaces(Cube, {{RED,    RED,    WHITE, GREEN,  YELLOW, GREEN,  ORANGE, YELLOW, RED   },  //Position__E::FRONT
                                                                             {BLUE,   ORANGE, GREEN, WHITE,  BLUE,   YELLOW, WHITE,  BLUE,   GREEN },  //Position__E::RIGHT
                                                                             {YELLOW, ORANGE, GREEN, ORANGE, WHITE,  ORANGE, ORANGE, RED,    WHITE },  //Position__E::BACK
                                                                             {ORANGE, YELLOW, BLUE,  GREEN,  GREEN,  YELLOW, RED,    RED,    BLUE  },  //Position__E::LEFT
                                                                             {YELLOW, WHITE,  RED,   BLUE,   RED,    BLUE,   YELLOW, WHITE,  ORANGE},  //Position__E::TOP
                                                                             {YELLOW, RED,    BLUE,  GREEN, ORANGE,  WHITE,  GREEN,  BLUE,  WHITE  }});//Position__E::BOTTOM
                           StepCounterMsg("Commit the scanned faces");
                                Result = Result && Cube.commitScannedFaces();
                           cout << "done." << flush;
                           return Result;
};

void ShowSpinnedCube() {
     cout << "\n\nTest spinping.\n\nCube created:\n";

     Rubik_Engine Cube;

     ShowCube(Cube, HideSize, HideColors, HidePercentual);
     ShowCube(Cube);

     PressEnter();

     Cube.spin(LAYER,  0, CLOCKWISE);
     Cube.spin(SpinTo_T(LINE,   1, COUNTERCLOCKWISE));
     Cube.spin(SpinTo_T(COLUMN, 2, COUNTERCLOCKWISE));

     cout << "\nCube was spinped few times 'manually'\n";
     ShowCube(Cube, HideSize, HideColors);
     cout << "(Expected less than 100)";

     PressEnter();

     Cube.randomize(1000);
     ShowCube(Cube, HideSize, ShowColorsAndPositions, HidePercentual);
     cout << '\n';
     ShowCube(Cube, HideSize, HideColors, ShowPercentual);

     cout << "\n\nCube after 1000 spins.";

     PressEnter();
}