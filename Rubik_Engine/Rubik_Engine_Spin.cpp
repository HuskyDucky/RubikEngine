/**
    File    : Rubik_Engine_Spin.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200501.1

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
#include "Rubik_Engine.h"

void Rubik_Engine::spin(const SpinBlocksAt Layer, const CubeSideSize_T Level, const TurnBlock isClockWise) noexcept {
     this->spin(SpinTo_T(Layer, Level, isClockWise));
}

void Rubik_Engine::spinback(const SpinTo_T& spinThe) noexcept {
     this->spin(spinThe.Layer,
                spinThe.Level,
               !spinThe.isClockWise);
}

void Rubik_Engine::spin(const SpinTo_T& spinThe) noexcept {
     if (spinThe.Level < this->SideSize) {

        this->CurrLayer2Move = spinThe.Layer;
        this->XYZ[spinThe.Layer] = spinThe.Level;   //Define which layer will be moved: Line, column or face(center)

        if (spinThe.isClockWise) {
           Abs_Axis = CW_Abs_Axis;
           Ord_Axis = CW_Ord_Axis;
        } else {
           Abs_Axis = CCWAbs_Axis;
           Ord_Axis = CCWOrd_Axis;
        }

        CubeSideSize_T Block2Move = 0;
        do {
            const BlkPosition_T Coords0 = this->spin_CalcBlockPosition(this->spin_NextCoords(0, Block2Move));
            const BlkPosition_T Coords1 = this->spin_CalcBlockPosition(this->spin_NextCoords(1, Block2Move));

            Block NextBlock = this->Cube[Coords1]; NextBlock.moveColors(this->CurrLayer2Move, spinThe.isClockWise);
            this->Cube[Coords1] = this->Cube[Coords0]; this->Cube[Coords1].moveColors(this->CurrLayer2Move, spinThe.isClockWise);
            swap(NextBlock, this->Cube[this->spin_CalcBlockPosition(this->spin_NextCoords(2, Block2Move))]); NextBlock.moveColors(this->CurrLayer2Move, spinThe.isClockWise);
            swap(NextBlock, this->Cube[this->spin_CalcBlockPosition(this->spin_NextCoords(3, Block2Move))]); NextBlock.moveColors(this->CurrLayer2Move, spinThe.isClockWise);
            this->Cube[Coords0] = NextBlock;

            ++Block2Move;

        } while (Block2Move != this->SideSize-1);
        ///It doesn't work for cube 4x4 and so on. To do so the program needs to loop on the face's interval blocks
     }
}

BlkPosition_T Rubik_Engine::spin_CalcBlockPosition(const AxisPosition_T AxesAO) noexcept {
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

AxisPosition_T Rubik_Engine::spin_NextCoords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept  {
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

