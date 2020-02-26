/**
    File    : Rubik_Cube_ScanFaceCall.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.2

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

bool Rubik::scan(const FacePosition_E Face, vector<Color_E>&& Colors) noexcept {
     if (this->ScannedFaces.get() == nullptr)
        this->ScannedFaces.reset(new ScanFaces(this->Cube, this->Block_Coordenate));

     return this->ScannedFaces->scan(Face, move(Colors));
}

bool Rubik::commitScannedFaces() noexcept {
     if (this->ScannedFaces.get() != nullptr) {
        ProtoCube_T ProtoCube = this->ScannedFaces->commitScannedFaces();
        if (ProtoCube.size()) {
           Cube_T NewCube;
           BlkPosition_T ProtoBlkIndex = 0;
           do {
               for (auto& oldBlock : this->Cube)
                   if (oldBlock.HasColors(ProtoCube[ProtoBlkIndex]) &&
                      none_of(NewCube.cbegin(), NewCube.cend(), [&](const Block& b) { return b.OriginalBlockPosition() == oldBlock.OriginalBlockPosition(); })) {
                      NewCube.emplace_back(oldBlock.OriginalBlockPosition(), move(ProtoCube[ProtoBlkIndex]));
                      break;
                   }

               if (ProtoBlkIndex != NewCube.size() - 1)
                  return false;

           } while (++ProtoBlkIndex != this->TofBlocks);

           this->Cube.swap(NewCube);

           this->ReleaseScannedFaces();
           return true;
        }
    }

    return false;
}

void Rubik::ReleaseScannedFaces() noexcept {
    if (this->ScannedFaces.get() != nullptr) {
       ScanFaces* ptr = ScannedFaces.release();
       delete ptr;
    }
}
