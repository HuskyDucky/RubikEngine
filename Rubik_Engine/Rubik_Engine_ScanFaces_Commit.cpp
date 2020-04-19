/**
    File    : Rubik_Engine_ScanFaces_Commit.cpp
    Author  : Menashe Rosemberg
    Created : 2019.12.09            Version: 20200110.1.3

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
#include "Rubik_Engine_ScanFaces.h"

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
