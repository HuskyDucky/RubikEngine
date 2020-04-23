/**
    File    : Rubik_run_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20200421.1.2

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

//This funcion is located at Lib/Rubik_General_Tests.cpp
bool Test_Spin3x3x3(Rubik_Engine& Cube, const SpinBlocksAt Layer, const uint8_t OnceTwiceThrice, function<bool(Rubik_Engine&)> Avail, const bool ShowPassFail = true);

TestFunction<Rubik_Engine> Test_CreationCube = [](Rubik_Engine& Cube) -> bool {
                           ShowCube(Cube, ShowSize);
                           return pow(Cube.SidesSize(), 3) == Cube.TotalOfBlocks() &&
                                  Cube.isFinished();
};

static bool CheckTurned(Rubik_Engine& Cube) noexcept {
       bool Result = Cube.isFinished();

       cout << "it is";
       if (!Result) cout << "n't";
       cout << '.' << flush;

       return Result;
}

TestFunction<Rubik_Engine> Test_TurnedCubeisFinished = [](Rubik_Engine& Cube) -> bool {
                           const string Msg = "Is Cube finished when turn its front face to ";

                           //TEST 1
                               Test_StepCounterMsg(Msg + "bottom");
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
                               bool result = CheckTurned(Cube);

                           //TEST 2
                               Rubik_Engine Cube2;
                               Test_StepCounterMsg(Msg + "left");
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
                          return CheckTurned(Cube) && result;
};

TestFunction<Rubik_Engine> Test_SpinedCubeisntFinished = [](Rubik_Engine& Cube) -> bool {
    bool Result = true;

    for (SpinBlocksAt Layer = LINE; Layer != NOSPIN; Layer = static_cast<SpinBlocksAt>(Layer + 1))
        for (uint8_t nSpins = 1; nSpins < 4; ++nSpins)
            Result &= Test_Spin3x3x3(Cube, Layer, nSpins, [](Rubik_Engine& Cube) { return !Cube.isFinished(); });

    return Result;
};

TestFunction<Rubik_Engine> Test_RandomizeCube = [](Rubik_Engine& Cube) -> bool {
                           ShowCube(Cube, HideSize);
                           Test_StepCounterMsg("Randomizing 1000 times");
                                Cube.randomize(1000);
                           cout << "done." << flush;
                           ShowCube(Cube, HideSize);

                           return !Cube.isFinished() && AreThesesCubesDifferent(Rubik_Engine(), Cube);
};

TestFunction<Rubik_Engine> Test_CompareCube = [](Rubik_Engine& Cube) -> bool {
                           Test_StepCounterMsg("Creating auxiliary cube");
                                Rubik_Engine AuxCube;
                           cout << "done." << flush;
                           Test_StepCounterMsg("Compare cubes");
                               if (Cube == AuxCube) {
                                  cout << "done." << flush;

                                  cout << '\n' << Test_StepCounter() << "Make some spins: " << flush;
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
                           Test_StepCounterMsg("Creating auxiliary cube");
                                Rubik_Engine AuxCube;
                           cout << "done." << flush;
                           Test_StepCounterMsg("Randomizing auxiliary cube 1000 times");
                                AuxCube.randomize(1000);
                           cout << "done." << flush;
                           Test_StepCounterMsg("Copy auxiliary cube to main cube");
                                Cube(AuxCube);
                           cout << "done." << flush;

                           return AuxCube == Cube; //Also it checks the colors
};

TestFunction<Rubik_Engine> Test_InitCopyCube = [](Rubik_Engine& AuxCube) -> bool {
                           Test_StepCounterMsg("Randomizing auxiliary cube 1000 times");
                                AuxCube.randomize(1000);
                           cout << "done." << flush;
                           Test_StepCounterMsg("Create a new Cube equal to auxiliary cube");
                                Rubik_Engine Cube(AuxCube);
                           cout << "done." << flush;

                           return AuxCube == Cube;
};

TestFunction<Rubik_Engine> Test_ResetCube = [](Rubik_Engine& Cube) -> bool {
                           Test_StepCounterMsg("Randomizing 1000 times");
                                Cube.randomize(1000);
                           cout << "done." << flush;
                           Test_StepCounterMsg("Reseting cube");
                                Cube.reset();
                           cout << "done." << flush;

                           return Cube.isFinished() && Rubik_Engine() == Cube;
};

///Create a general test to ScanFaces to read the scanned faces and commit

static bool ScanFaces_feedCubeWithFaces(Rubik_Engine& Cube,
                                        vector<vector<Color_E>>&& Faces,
                                        const string_view ComplementaryMsg = "") {

            cout << '\n' << Test_StepCounter() << "Try to feed the cube with the scanned faces";
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
                           Test_StepCounterMsg("Commit the scanned faces");
                                Result = Result && Cube.commitScannedFaces();
                           cout << "done." << flush;
                           return Result;
};
