/**
    File    : Rubik_run_AuxFuncs.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200130.1

    Rubik Program - auxiliary functions to test Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
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
             case Position_E::TOP   : return "TOP";
             case Position_E::BACK  : return "BACK";
             case Position_E::LEFT  : return "LEFT";
             case Position_E::FRONT : return "FRONT";
             case Position_E::RIGHT : return "RIGHT";
             default:                 return "BOTTOM";
      }
}

static string CubeIsFinishORNot(const Rubik& Cube) {
       string Msg = "The Cube is ";

       if (!Cube.isFinished())
          Msg += "NOT ";

       return Msg + "finished";
}

void ShowCube(const Rubik& Cube, const bool ShowSize, const bool ShowColorsAndPositions, const bool ShowPercentual) {
     if (ShowSize)
        cout << "Cube size is: " << Cube.TofBlocks << '\n';

     if (ShowColorsAndPositions) {
        for (Coord_T xyz({0, 0, 0}); xyz[2] < Cube.SideSize; ++xyz[2])
            for (xyz[0] = 0; xyz[0] < Cube.SideSize; ++xyz[0])
                for (xyz[1] = 0; xyz[1] < Cube.SideSize; ++xyz[1]) {
                    QofBlocks_T Pos = xyz[0] * Cube.SideSize +                      //Line
                                      xyz[1] +                                      //Column
                                      xyz[2] * Cube.SideSize * Cube.SideSize;       //Layer
                    cout << "\nBlock Original  : " << static_cast<uint16_t>(Cube.Block_OriginalPosition(xyz))
                         << "\nCurrent Position: " << Pos << ": ";

                    ColorPositionList_T BlocksColors = Cube.Block_ColorsAndPositions(xyz);
                    for (auto& Z : BlocksColors)
                        cout << "\n\t\t" << TheColorIs(Z.first) << ' ' << ThePositionIs(Z.second);
                }
        cout << '\n';
     } else {
          const uint8_t ascii = Cube.SideSize == 3 ? 97 :
                               (Cube.SideSize == 4 ? 48 : 33);

          for (Coord_T xyz({0, 0, 0}); xyz[0] < Cube.SideSize; ++xyz[0]) {
              for (xyz[2] = 0; xyz[2] < Cube.SideSize; ++xyz[2]) {
                   for (xyz[1] = 0; xyz[1] < Cube.SideSize; ++xyz[1])
                       cout << static_cast<char>(ascii + Cube.Block_OriginalPosition(xyz));
                   cout << ' ';
              }
              cout << '\n';
          }
     }

     if (ShowPercentual)
        cout << "Percentual Resolved: " << setprecision(3) << Cube.PercentualDone() << "%. " << CubeIsFinishORNot(Cube) << '\n';
}

static bool CompareBlocks(const Coord_T& xyz, const Rubik& Cube1, const Rubik& Cube2) {
       ColorPositionList_T blk1_ColPosList = Cube1.Block_ColorsAndPositions(xyz);
       ColorPositionList_T blk2_ColPosList = Cube2.Block_ColorsAndPositions(xyz);

       if (blk1_ColPosList.size() != blk2_ColPosList.size()) return false;

       for (auto& C1_CP : blk1_ColPosList)
           if (find(blk2_ColPosList.cbegin(), blk2_ColPosList.cend(), C1_CP) == blk2_ColPosList.cend()) return false;

       return true;
}

bool AreThesesCubesEqual(const Rubik& Cube1, const Rubik& Cube2) {

     if (Cube1.TofBlocks != Cube2.TofBlocks) return false;

     for (Coord_T xyz({0, 0, 0}); xyz[0] < Cube1.SideSize; ++xyz[0])
         for (xyz[2] = 0; xyz[2] < Cube1.SideSize; ++xyz[2])
             for (xyz[1] = 0; xyz[1] < Cube1.SideSize; ++xyz[1])
                 if (Cube1.Block_OriginalPosition(xyz) != Cube2.Block_OriginalPosition(xyz) ||
                    !CompareBlocks(xyz, Cube1, Cube2))
                    return false;

     return true;
}
