/**
    File    : Rubik_Resolution_ShowResults.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200505.1

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
#include "Rubik_TestSolution.h"

//This funcion is located at Lib/Rubik_General_Tests.cpp
bool Test_Spin3x3x3(Rubik_Engine& Cube, const SpinBlocksAt Layer, const uint8_t OnceTwiceThrice, function<bool(Rubik_Engine&)> Avail, const bool ShowPassFail = false);

TestFunction<Rubik_Engine> Test_TurnCube = [](Rubik_Engine& Cube) {
                           const string Msg("Turn Front Face to ");
                           cout << '\n';

                           Test_StepCounterMsg("No move've made on cube");
                                bool Result = TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "Top");
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(COLUMN, t, COUNTERCLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "bottom");
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(COLUMN, t, CLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "Left");
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(LINE, t, CLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "Right");
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(LINE, t, COUNTERCLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "Back");
                                for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes)
                                    for (uint8_t t = 0; t < 3; ++t)
                                        Cube.spin(LINE, t, CLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg("Turn Left Front Face to Right in its axis");
                                for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes)
                                    for (uint8_t t = 0; t < 3; ++t)
                                        Cube.spin(LAYER, t, CLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "Right -> Top -> Left");
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(LINE, t, COUNTERCLOCKWISE);
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(LAYER, t, COUNTERCLOCKWISE);
                                for (uint8_t t = 0; t < 3; ++t)
                                    Cube.spin(LAYER, t, COUNTERCLOCKWISE);
                                Result &= TestSolutionTo(Cube).CheckSolution();

                           Cube.reset();
                           Test_StepCounterMsg(Msg + "Back (form line) and Left Face to Right");
                                for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes)
                                    for (uint8_t t = 0; t < 3; ++t)
                                        Cube.spin(LINE, t, CLOCKWISE);
                                for (uint8_t NoTimes = 0; NoTimes < 2; ++NoTimes)
                                    for (uint8_t t = 0; t < 3; ++t)
                                        Cube.spin(LAYER, t, CLOCKWISE);

                                return TestSolutionTo(Cube).CheckSolution() && Result;
};

uint8_t QofMovesExpected = 0;
auto lambda = [](Rubik_Engine& Cube){ return TestSolutionTo(Cube).CheckSolution(QofMovesExpected); };
TestFunction<Rubik_Engine> Test_SpinLINEOnce      = [](Rubik_Engine& Cube) { QofMovesExpected = 1; return Test_Spin3x3x3(Cube, LINE, 1, lambda); };
TestFunction<Rubik_Engine> Test_SpinLINETwice     = [](Rubik_Engine& Cube) { QofMovesExpected = 2; return Test_Spin3x3x3(Cube, LINE, 2, lambda); };
TestFunction<Rubik_Engine> Test_SpinLINEThrice    = [](Rubik_Engine& Cube) { QofMovesExpected = 1; return Test_Spin3x3x3(Cube, LINE, 3, lambda); };
TestFunction<Rubik_Engine> Test_SpinCOLUMNOnce    = [](Rubik_Engine& Cube) { QofMovesExpected = 1; return Test_Spin3x3x3(Cube, COLUMN, 1, lambda); };
TestFunction<Rubik_Engine> Test_SpinCOLUMNTwice   = [](Rubik_Engine& Cube) { QofMovesExpected = 2; return Test_Spin3x3x3(Cube, COLUMN, 2, lambda); };
TestFunction<Rubik_Engine> Test_SpinCOLUMNThrice  = [](Rubik_Engine& Cube) { QofMovesExpected = 1; return Test_Spin3x3x3(Cube, COLUMN, 3, lambda); };
TestFunction<Rubik_Engine> Test_SpinLAYEROnce     = [](Rubik_Engine& Cube) { QofMovesExpected = 1; return Test_Spin3x3x3(Cube, LAYER, 1, lambda); };
TestFunction<Rubik_Engine> Test_SpinLAYERTwice    = [](Rubik_Engine& Cube) { QofMovesExpected = 2; return Test_Spin3x3x3(Cube, LAYER, 2, lambda); };
TestFunction<Rubik_Engine> Test_SpinLAYERThrice   = [](Rubik_Engine& Cube) { QofMovesExpected = 1; return Test_Spin3x3x3(Cube, LAYER, 3, lambda); };

TestFunction<Rubik_Engine> Test_SpinLevels = [](Rubik_Engine& Cube) {
                           Test_StepCounterMsg("Spinning 3 Diferent levels");

                           Test_StepCounterInfo("\t1st - line   level 0 clockwise");
                           Test_StepCounterInfo("\t2nd - column level 1 counterclockwise");
                           Test_StepCounterInfo("\t3rd - axis   level 2 counterclockwise");
                           Cube.spin(LINE,   0, CLOCKWISE);
                           Cube.spin(COLUMN, 1, COUNTERCLOCKWISE);
                           Cube.spin(LAYER,  2, COUNTERCLOCKWISE);

                           TestSolutionTo scrambledCube(Cube);
                           LofSpins_T MovesToSolveTheCube = scrambledCube.ResolveIt();

                           scrambledCube.AvaliateSolution(3);

                           bool Result = scrambledCube.ApplyingSolution();

                           Test_StepCounterMsg("Show Results");
                           ShowSolution(MovesToSolveTheCube);

                           return Result;
};

TestFunction<Rubik_Engine> Test_SolutionOverScannedCube = [](Rubik_Engine& Cube) {
                           Cube.scan(FRONT, {YELLOW, RED,    BLUE,   YELLOW, WHITE,  RED,   YELLOW, ORANGE, WHITE });
                           Cube.scan(RIGHT, {WHITE,  ORANGE, BLUE,   GREEN,  GREEN,  BLUE,  GREEN,  GREEN,  GREEN });
                           Cube.scan(BACK,  {ORANGE, YELLOW, GREEN,  ORANGE, YELLOW, BLUE,  RED,    RED,    YELLOW});
                           Cube.scan(LEFT,  {RED,    GREEN,  ORANGE, WHITE,  BLUE,   BLUE,  BLUE,   ORANGE, BLUE  });
                           Cube.scan(TOP,   {WHITE,  RED,    WHITE,  YELLOW, RED,    GREEN, GREEN,  BLUE,   RED   });
                           Cube.scan(BOTTOM,{RED,    WHITE,  ORANGE, YELLOW, ORANGE, WHITE, ORANGE, WHITE,  YELLOW});

                           if (!Cube.commitScannedFaces()) return 1;

                           LofSpins_T MovesToSolveTheCube = TestSolutionTo(Cube).ResolveIt();

                           ShowSolution(MovesToSolveTheCube);

                           return 0;
};
