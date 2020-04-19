/**
    File    : Rubik_Engine_ScanFaces_Scan.cpp
    Author  : Menashe Rosemberg
    Created : 2019.12.09            Version: 20200110.1.4

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

ClassScanFaces::ScanFaces::ScanFaces(Cube_T& cubebase, function<BlkPosition_T(const Coord_T&)>& block_coordenate) : CubeBase(cubebase),
                                                                                                                    SideSize(cbrt(cubebase.size())),
                                                                                                                    FaceSize(SideSize * SideSize),
                                                                                                                    Block_Coordenate(block_coordenate) {}

bool ClassScanFaces::ScanFaces::scan(const FacePosition_E Face, vector<Color_E>&& FaceColors) noexcept {
     vector<Color_E> OldScannedFace;                    //Will keep the current Face State

     if (Face >= TofFACES ||
         FaceColors.size() != this->FaceSize ||
         any_of(FaceColors.cbegin(), FaceColors.cend(), [](Color_E c){ return c >= TofFACES; }))
        return false;

    OldScannedFace.swap(this->ScannedFaces[Face]);      //Save the current Face state

    if (this->scan_ValidateNewFace(FaceColors)) {
        this->ScannedFaces[Face] = move(FaceColors);    //Add the scanned face
        return true;
    }

    OldScannedFace.swap(this->ScannedFaces[Face]);      //restore the Face state

    return false;
}

inline bool ClassScanFaces::ScanFaces::scan_ValidateNewFace(const vector<Color_E>& FaceColors) const noexcept {
       vector<Color_E>   UniqColors; UniqColors.reserve(this->FaceSize);
       BlocksPosToFace_T QtdUColors; QtdUColors.reserve(this->FaceSize);

       //Check the quantity of FaceColors found in the new face
       QofBlksPerFace_T colorsSize = this->FaceSize;
       do {
           if (auto IIt = find(UniqColors.cbegin(), UniqColors.cend(), FaceColors[--colorsSize]); IIt == UniqColors.cend()) {
              UniqColors.emplace_back(FaceColors[colorsSize]);
              QtdUColors.emplace_back(1);
           } else
             ++QtdUColors[distance(UniqColors.cbegin(), IIt)];
       } while(colorsSize != 0);

       //check the quantity of colors already saved in this->ScannedFaces
       for (auto& FCS : this->ScannedFaces)
           for (auto& regcor : FCS) {
               colorsSize = UniqColors.size()-1;
               do {
                   if (regcor == UniqColors[--colorsSize] && ++QtdUColors[colorsSize] > this->FaceSize)
                      return false; //Found More of the same color than expected for the cube
               } while (colorsSize != 0);
           }
       return true;
}
