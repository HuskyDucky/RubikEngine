/**
    File    : Rubik_Cube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200206.3

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

Rubik::Rubik() : SideSize(3),   //This class is not ready yet to more than 3 blocks per corner
                 TofBlocks(pow(SideSize, 3)),
                 XYZ({0,0,0}) {
      this->Rubik_Initializer();

      this->reset();
}

Rubik::Rubik(const Rubik& OriCube) : SideSize(3),   //This class is not ready yet to more than 3 blocks per corner
                                     TofBlocks(pow(SideSize, 3)),
                                     XYZ({0,0,0}) {
      this->Rubik_Initializer();

      this->operator()(OriCube);
}

void Rubik::Rubik_Initializer() noexcept {
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
}

Rubik::~Rubik() { this->ReleaseScannedFaces(); }
