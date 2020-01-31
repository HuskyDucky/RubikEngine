/**
    File    : Rubik_Cube_Private.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191223.2

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
                    cout << "\n\nThis rubik cube can have 3 to " << static_cast<uint64_t>(numeric_limits<CubeSideSize_T>::max()-2) << " blocks size to every face only\n" << endl;
                    abort();
                 }

                 //It could be a regular function but inheritaged class will use it by passing it as parameter (better than use friend)
                 this->Block_Coordenate = [&](const Coord_T& xyz) -> BlkPosition_T {
                                          return xyz[LINE  ] * this->SideSize +
                                                 xyz[COLUMN] +
                                                 xyz[LAYER ] * this->SideSize * this->SideSize;
                 };

                 this->reset();
}

Rubik::~Rubik() { this->ReleaseScannedFaces(); }

BlkPosition_T Rubik::CalcBlockPosition(const AxisPosition_T AxesAO) noexcept {
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

AxisPosition_T Rubik::Next_Coords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept  {
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