/**
    File    : Rubik_run_AuxFuncs.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200206.4.1

    Rubik Engine - auxiliary functions to test Cube

    Copyright (c) 2019 TheArquitect (Menashe Rosemberg) rosemberg@ymail.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#include "Rubik_run_AuxFuncs.h"

void PressEnter() { cout << "\n\nPress <ENTER> to continue..."; cin.get(); }

string StepCounter(bool Reset) {
       static uint16_t Counter = 0;

       if (Reset)
          Counter = 0;

       return string("step X - ").replace(5, 1, to_string(++Counter));
}

const char* TheColorIs(const uint8_t C) noexcept {
      switch (C) {
             case Color_E::WHITE  : return "WHITE";
             case Color_E::YELLOW : return "YELLOW";
             case Color_E::RED    : return "RED";
             case Color_E::ORANGE : return "ORANGE";
             case Color_E::GREEN  : return "GREEN";
             default:               return "BLUE";
      }
}

const char* ThePositionIs(const uint8_t P) noexcept {
      switch (P) {
             case FacePosition_E::TOP   : return "TOP";
             case FacePosition_E::BACK  : return "BACK";
             case FacePosition_E::LEFT  : return "LEFT";
             case FacePosition_E::FRONT : return "FRONT";
             case FacePosition_E::RIGHT : return "RIGHT";
             default:                     return "BOTTOM";
      }
}

static string CubeIsFinishORNot(const Rubik_Engine& Cube) {
       string Msg = "The Cube is ";

       if (!Cube.isFinished())
          Msg += "NOT ";

       return Msg + "finished";
}

void ShowCube(const Rubik_Engine& Cube, const bool ShowSize, const bool ShowColorsAndPositions, const bool ShowPercentual) {
     if (ShowSize)
        cout << "Cube size is: " << Cube.TotalOfBlocks() << '\n';

     if (ShowColorsAndPositions) {
        for (Coord_T xyz({0, 0, 0}); xyz[2] < Cube.SidesSize(); ++xyz[2])
            for (xyz[0] = 0; xyz[0] < Cube.SidesSize(); ++xyz[0])
                for (xyz[1] = 0; xyz[1] < Cube.SidesSize(); ++xyz[1]) {
                    QofBlocks_T Pos = xyz[0] * Cube.SidesSize() +                   //Line
                                      xyz[1] +                                      //Column
                                      xyz[2] * Cube.SidesSize() * Cube.SidesSize(); //Layer
                    cout << "\nBlock Original  : " << static_cast<uint16_t>(Cube.Block_OriginalPosition(xyz))
                         << "\nCurrent Position: " << Pos << ": ";

                    FaceList_T BlocksColors = Cube.Block_FacesList(xyz);
                    for (auto& Z : BlocksColors)
                        cout << "\n\t\t" << TheColorIs(Z.first) << ' ' << ThePositionIs(Z.second);
                }
        cout << '\n';
     } else {
          const uint8_t ascii = Cube.SidesSize() == 3 ? 97 :
                               (Cube.SidesSize() == 4 ? 48 : 33);

          for (Coord_T xyz({0, 0, 0}); xyz[0] < Cube.SidesSize(); ++xyz[0]) {
              for (xyz[2] = 0; xyz[2] < Cube.SidesSize(); ++xyz[2]) {
                   for (xyz[1] = 0; xyz[1] < Cube.SidesSize(); ++xyz[1])
                       cout << static_cast<char>(ascii + Cube.Block_OriginalPosition(xyz));
                   cout << ' ';
              }
              cout << '\n';
          }
     }

     if (ShowPercentual)
        cout << "Percentual Resolved: " << setprecision(3) << Cube.PercentualDone() << "%. " << CubeIsFinishORNot(Cube) << '\n';
}

