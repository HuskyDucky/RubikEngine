/**
    File    : Rubik_ShowCube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200420.1

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
#include "Rubik_ShowCube.h"

const string ThePositionIs(const uint8_t P) noexcept {
      switch (P) {
             case FacePosition_E::TOP   : return "TOP";
             case FacePosition_E::BACK  : return "BACK";
             case FacePosition_E::LEFT  : return "LEFT";
             case FacePosition_E::FRONT : return "FRONT";
             case FacePosition_E::RIGHT : return "RIGHT";
             default:                     return "BOTTOM";
      }
}

const string TheColorLetterIs(const Color_E C) noexcept {
      switch (C) {
             case Color_E::WHITE  : return "W";
             case Color_E::YELLOW : return "Y";
             case Color_E::RED    : return "R";
             case Color_E::ORANGE : return "O";
             case Color_E::GREEN  : return "G";
             default:               return "B";
      }
}

void ShowCube(Rubik_Engine& Cube, const bool ShowSize) {
     if (ShowSize) {
        Test_StepCounterInfo("Cube size is");
        cout << Cube.TotalOfBlocks() << '\n';
     }
     array<vector<Color_E>, TofFACES> Faces;
     for (Coord_T xyz({0, 0, 0}); xyz[0] < Cube.SidesSize(); ++xyz[0])
         for (xyz[2] = 0; xyz[2] < Cube.SidesSize(); ++xyz[2])
             for (xyz[1] = 0; xyz[1] < Cube.SidesSize(); ++xyz[1])
                 for (auto& facelist : Cube.Block_FacesList(xyz))
                     Faces[facelist.Position].emplace_back(facelist.Color);

     for (FacePosition_T Pos = 0; Pos < NONEPOSITION; ++Pos) {
         Test_StepCounterInfo(ThePositionIs(Pos));
         CubeSideSize_T Line = 0;
         for (auto& Cor : Faces[Pos]) {
             cout << TheColorLetterIs(Cor) << ' ';
             if (++Line == Cube.SidesSize()) {
                 Line = 0;
                 Test_StepCounterInfo(); cout << string(ThePositionIs(Pos).size()+2, ' ');
             }
         }
     }
}
