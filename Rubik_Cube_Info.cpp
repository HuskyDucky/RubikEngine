/**
    File    : Rubik_Cube_Info.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.2

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

CubeSideSize_T Rubik::SidesSize() const noexcept { return this->SideSize; }
QofBlocks_T Rubik::TotalOfBlocks() const noexcept { return this->TofBlocks; }

bool Rubik::isFinished() const noexcept {
     QofBlocks_T Scan = 0;

     while (Scan < this->TofBlocks && Scan == this->Cube[Scan].OriginalBlockPosition()) ++Scan;

     return Scan == this->TofBlocks;
}

float Rubik::PercentualDone() const noexcept {
      QofBlocks_T Done = 0;

      for (QofBlocks_T Scan = 0; Scan < this->TofBlocks; ++Scan)
          if (Scan == this->Cube[Scan].OriginalBlockPosition())
             ++Done;

      return 100.0 * Done / this->TofBlocks;
}

bool Rubik::operator==(const Rubik& CompCube) noexcept {
     if (CompCube.TotalOfBlocks() == this->TofBlocks) {
        this->XYZ[LAYER] = 0;
        do {
            this->XYZ[LINE] = 0;
            do {
                this->XYZ[COLUMN] = 0;
                do {
                    if (this->Cube[this->Block_Coordenate(XYZ)] != CompCube.Block_FacesList(XYZ))
                        return false;
                } while (++this->XYZ[COLUMN] < this->SideSize);
            } while (++this->XYZ[LINE] < this->SideSize);
        } while (++this->XYZ[LAYER] != this->SideSize);
     }

     return true;
}

bool Rubik::isBlockInPosition(const Coord_T& xyz) const noexcept {
     const QofBlocks_T Pos = this->Block_Coordenate(xyz);
     return Pos < this->TofBlocks && Pos == this->Cube[Pos].OriginalBlockPosition();
}

FaceList_T Rubik::Block_FacesList(const Coord_T& xyz) const noexcept {
           return this->Cube[this->Block_Coordenate(xyz)].FacesList();
}

BlkPosition_T Rubik::Block_OriginalPosition(const Coord_T& xyz) const noexcept {
              return this->Cube[this->Block_Coordenate(xyz)].OriginalBlockPosition();
}
