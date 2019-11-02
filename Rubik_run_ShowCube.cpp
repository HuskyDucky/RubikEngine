/**
    File    : Rubik_run_ShowCube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20191102.1

    Rubik Program Show Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run.h"

const char* TheColorIs(const uint8_t C) noexcept {
      switch (C) {
             case Color::WHITE  : return "WHITE";
             case Color::YELLOW : return "YELLOW";
             case Color::RED    : return "RED";
             case Color::ORANGE : return "ORANGE";
             case Color::GREEN  : return "GREEN";
             default:             return "BLUE";
      }
}

const char* ThePositionIs(const uint8_t P) noexcept {
      switch (P) {
             case PositioningOn::TOP   : return "TOP";
             case PositioningOn::BACK  : return "BACK";
             case PositioningOn::LEFT  : return "LEFT";
             case PositioningOn::FRONT : return "FRONT";
             case PositioningOn::RIGHT : return "RIGHT";
             default:                    return "BOTTOM";
      }
}

void ShowCube(const RubikCube& Cube, const bool ShowColors, const bool ShowSize) {

     Cube_T CubeArray = Cube.Array();
     CubeSize_T CubeSize = cbrt(CubeArray.size());
     CubeSize_T xyz[3] = {0, 0, 0};

     if (ShowSize)
        cout << CubeArray.size() << '\n';

     cout << '\n';

     if (ShowColors)
        for (uint32_t X = 0; X < CubeArray.size(); ++X) {
            cout << "\nBlock Original  : " << static_cast<uint16_t>(CubeArray[X].OriginalBlockPosition())
                 << "\nCurrent Position: " << X << ": ";
            vector<ColorPosition_T> BlocksColors = CubeArray[X].Colors();
            for (auto& Z : BlocksColors)
                cout << "\n\t\t" << TheColorIs(Z.first) << ' ' << ThePositionIs(Z.second);
        }
     else {
          const uint8_t ascii = CubeSize == 3 ? 97 :
                               (CubeSize == 4 ? 48 : 33);

          for (xyz[0] = 0; xyz[0] < CubeSize; ++xyz[0]) {
              for (xyz[2] = 0; xyz[2] < CubeSize; ++xyz[2]) {
                   for (xyz[1] = 0; xyz[1] < CubeSize; ++xyz[1])
                       cout << static_cast<char>(ascii + CubeArray[Cube.BlockPosition(xyz)].OriginalBlockPosition());
                   cout << ' ';
              }
              cout << '\n';
          }
     }

     cout << '\n';
}
