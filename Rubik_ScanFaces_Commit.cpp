/**
    File    : Rubik_ScanFaces_Commit.cpp
    Author  : Menashe Rosemberg
    Created : 2019.12.09            Version: 20200110.1.2

    Rubik Program - ScanFace Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_ScanFaces.h"

ProtoCube_T ClassScanFaces::ScanFaces::commitScannedFaces() noexcept {
    ProtoCube_T ProtoCube;

    for (auto& CheckScannedFace : this->ScannedFaces)
        if (CheckScannedFace.size() != this->FaceSize)
           return ProtoCube;                        //Not all faces were scanned

    this->AlignBackLeftTopFaces();
    ProtoCube = this->CreateProtoCube();
    this->AlignBackLeftTopFaces();

    return ProtoCube;
}

void ClassScanFaces::ScanFaces::AlignBackLeftTopFaces() noexcept {
     for (QofBlksPerFace_T blkLin = 0; blkLin < this->FaceSize; blkLin+=this->SideSize) {
         CubeSideSize_T blkColL = 0;
         CubeSideSize_T blkColR = this->SideSize - 1;
         do {
             swap(this->ScannedFaces[BACK][blkLin+blkColL], this->ScannedFaces[BACK][blkLin+blkColR]);
             swap(this->ScannedFaces[LEFT][blkLin+blkColL], this->ScannedFaces[LEFT][blkLin+blkColR]);
         } while (++blkColL < --blkColR);
     }

     for (CubeSideSize_T blkCol = 0; blkCol < this->SideSize; ++blkCol) {
         QofBlksPerFace_T blkLinU = 0;
         QofBlksPerFace_T blkLinB = this->FaceSize - this->SideSize;
         do {
            swap(this->ScannedFaces[TOP][blkLinU + blkCol], this->ScannedFaces[TOP][blkLinB + blkCol]);
         } while ((blkLinU += this->SideSize) < (blkLinB -= this->SideSize));
     }
}
