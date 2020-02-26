/**
    File    : Rubik_Cube_Flip.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.2

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

void Rubik::flip(const FlipBlocksAt Layer, const CubeSideSize_T Level, const TurnBlocks isClockWise) noexcept {
     this->flip(FlipTo_T(Layer, Level, isClockWise));
}
void Rubik::flip(const FlipTo_T& FlipThe) noexcept {

     if (FlipThe.Level < this->SideSize) {

        this->CurrLayer2Move = FlipThe.Layer;
        this->XYZ[FlipThe.Layer] = FlipThe.Level;   //Define which layer will be moved: Line, column or face(center)

        if (FlipThe.isClockWise) {
           Abs_Axis = CW_Abs_Axis;
           Ord_Axis = CW_Ord_Axis;
        } else {
           Abs_Axis = CCWAbs_Axis;
           Ord_Axis = CCWOrd_Axis;
        }

        CubeSideSize_T Block2Move = 0;
        do {
            const BlkPosition_T Coords0 = this->flip_CalcBlockPosition(this->flip_NextCoords(0, Block2Move));
            const BlkPosition_T Coords1 = this->flip_CalcBlockPosition(this->flip_NextCoords(1, Block2Move));

            Block NextBlock = this->Cube[Coords1]; NextBlock.moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            this->Cube[Coords1] = this->Cube[Coords0]; this->Cube[Coords1].moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            swap(NextBlock, this->Cube[this->flip_CalcBlockPosition(this->flip_NextCoords(2, Block2Move))]); NextBlock.moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            swap(NextBlock, this->Cube[this->flip_CalcBlockPosition(this->flip_NextCoords(3, Block2Move))]); NextBlock.moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            this->Cube[Coords0] = NextBlock;

            ++Block2Move;

        } while (Block2Move != this->SideSize-1);
        ///It doesn't work for cube 4x4 and so on. To do so the program needs to loop on the face's interval blocks
     }
}

BlkPosition_T Rubik::flip_CalcBlockPosition(const AxisPosition_T AxesAO) noexcept {
              switch (this->CurrLayer2Move) {
                     case LINE   :
                          this->XYZ[COLUMN] = AxesAO.first;
                          this->XYZ[LAYER ] = AxesAO.second;
                          break;
                     case COLUMN :
                          this->XYZ[LINE  ] = AxesAO.second;
                          this->XYZ[LAYER ] = AxesAO.first;
                          break;
                     default:
                          this->XYZ[LINE  ] = AxesAO.first;
                          this->XYZ[COLUMN] = AxesAO.second;
              }

              return this->XYZ[LINE  ] * this->SideSize +
                     this->XYZ[COLUMN] +
                     this->XYZ[LAYER ] * this->SideSize * this->SideSize;
}

AxisPosition_T Rubik::flip_NextCoords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept  {
               AxisPosition_T AxesAO = { (*&Abs_Axis[CubeFace]).first,
                                         (*&Ord_Axis[CubeFace]).first };

               if (AxesAO.first < this->Abs_Axis[CubeFace].second)
                   AxesAO.first += BlockNo;
               else if (AxesAO.first > this->Abs_Axis[CubeFace].second)
                        AxesAO.first -= BlockNo;

               if (AxesAO.second < this->Ord_Axis[CubeFace].second)
                   AxesAO.second += BlockNo;
               else if (AxesAO.second > this->Ord_Axis[CubeFace].second)
                        AxesAO.second -= BlockNo;

               return AxesAO;
}

