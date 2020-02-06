/**
    File    : Rubik_ScanFaces_Scan.cpp
    Author  : Menashe Rosemberg
    Created : 2019.12.09            Version: 20200110.1.3

    Rubik Program - ScanFace Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_ScanFaces.h"

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
