/**
    File    : Rubik_Cube_Private.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191129.4

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

Rubik::Rubik() : SideSize(3),                           //This class is not ready yet to more than 3 blocks per corner
                 TofBlocks(pow(SideSize, 3)),
                 XYZ({0,0,0}) {

                 if (this->SideSize < 3 && this->SideSize < numeric_limits<CubeSideSize_T>::max()-2) {
                    cout << "\n\nThis rubik cube can have 3 to " << static_cast<uint64_t>(numeric_limits<CubeSideSize_T>::max()-2) << " blocks size to every face\n\n";
                    abort();
                 }

                 const BlkPosition_T NofBlocks = pow(this->SideSize, 3);
                 this->Cube.reserve(NofBlocks);

                 this->Reset();
}


BlkPosition_T Rubik::CalcBlockPosition(const AxisAOPosition_T AxesAO) noexcept {
              switch (this->CurrLayer2Move) {
                     case FlipBlocksAt::LINE   :
                          this->XYZ[FlipBlocksAt::COLUMN] = AxesAO.first;
                          this->XYZ[FlipBlocksAt::LAYER ] = AxesAO.second;
                          break;
                     case FlipBlocksAt::COLUMN :
                          this->XYZ[FlipBlocksAt::LINE  ] = AxesAO.second;
                          this->XYZ[FlipBlocksAt::LAYER ] = AxesAO.first;
                          break;
                     default:
                          this->XYZ[FlipBlocksAt::LINE  ] = AxesAO.first;
                          this->XYZ[FlipBlocksAt::COLUMN] = AxesAO.second;
              }

              return this->XYZ[FlipBlocksAt::LINE  ] * this->SideSize +
                     this->XYZ[FlipBlocksAt::COLUMN] +
                     this->XYZ[FlipBlocksAt::LAYER ] * this->SideSize * this->SideSize;
}

AxisAOPosition_T Rubik::Next_Coords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept  {
                 AxisAOPosition_T AxesAO = { (*&Abs_Axis[CubeFace]).first,
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
