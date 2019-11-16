/**
    File    : Rubik_run_AuxFuncs.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20191115.1

    Rubik Program Show Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run_AuxFuncs.h"

void PressEnter() { cout << "\nPress <ENTER> to continue..."; cin.get(); }

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

string CubeIsFinishORNot(const Rubik& Cube) {
       string Msg = "The Cube is ";

       if (!Cube.isFinished())
          Msg += "NOT ";

       return Msg + "finished";
}

void ShowCube(const Rubik& Cube, const bool ShowSize, const bool ShowColors, const bool ShowPercentual) {
     Cube_T CubeArray = Cube.CurrentBlocksPositions();
     CubeSize_T CubeSize = cbrt(CubeArray.size());
     CubeSize_T xyz[3] = {0, 0, 0};

     if (ShowSize)
        cout << CubeArray.size() << '\n';

     cout << '\n';

     if (ShowColors)
        for (uint32_t IIt = 0; IIt < CubeArray.size(); ++IIt) {
            cout << "\nBlock Original  : " << static_cast<uint16_t>(CubeArray[IIt].OriginalBlockPosition())
                 << "\nCurrent Position: " << IIt << ": ";
            ColorPositionList_T BlocksColors = CubeArray[IIt].ColorsAndPositions();
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

     if (ShowPercentual)
        cout << "\n\nPercentual Resolved: " << Cube.PercentDone() << ". " << CubeIsFinishORNot(Cube) << '\n';
}

bool CompareBlocks(const Block blk1, const Block blk2) {
     ColorPositionList_T blk1_ColPosList = blk1.ColorsAndPositions();
     ColorPositionList_T blk2_ColPosList = blk2.ColorsAndPositions();

     if (blk1_ColPosList.size() != blk2_ColPosList.size()) return false;

     for (auto& C1_CP : blk1_ColPosList)
         if (find(blk2_ColPosList.cbegin(), blk2_ColPosList.cend(), C1_CP) == blk2_ColPosList.cend()) return false;

     return true;   //the blocks are equal
}

bool CompareCubes(const Cube_T& Cube1, const Cube_T& Cube2) {
     const auto C1Size = Cube1.size();

     if (C1Size != Cube2.size()) return false;

     for (uint32_t IIt = 0; IIt < C1Size; ++IIt) {
         if (Cube1[IIt].OriginalBlockPosition() != Cube2[IIt].OriginalBlockPosition()) return false;

         if (!CompareBlocks(Cube1[IIt], Cube2[IIt])) return false;
     }

     return true;   //the cubes are equal
}
