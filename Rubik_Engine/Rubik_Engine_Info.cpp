/**
    File    : Rubik_Engine_Cube_Info.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200223.1

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

CubeSideSize_T Rubik_Engine::SidesSize() const noexcept { return this->SideSize; }
QofBlocks_T Rubik_Engine::TotalOfBlocks() const noexcept { return this->TofBlocks; }

bool Rubik_Engine::isFinished() const noexcept {
     vector<Face_T> FacesColors;
                    FacesColors.reserve(TofFACES);

     QofBlocks_T Scan = 0;
     do {
         for (auto& face : this->Cube[Scan].FacesList()) {
             bool NOTFound = true;
             for (auto& Check : FacesColors)
                 if (Check.Color == face.Color) {
                    if (Check.Position != face.Position)
                       return false;
                    NOTFound = false;
                 }
             if (NOTFound)
                FacesColors.push_back(face);
         }
     } while (++Scan < this->TofBlocks);

     return true;
}

bool Rubik_Engine::operator==(const Rubik_Engine& CompCube) noexcept {
     if (CompCube.TotalOfBlocks() == this->TofBlocks) {
        this->XYZ[LAYER] = 0;
        do {
            this->XYZ[LINE] = 0;
            do {
                this->XYZ[COLUMN] = 0;
                do {
                    if (this->Cube[this->Block_Coordenate(XYZ)] != CompCube.Block_FacesList(XYZ))
                        return false;
                } while (++this->XYZ[COLUMN] != this->SideSize);
            } while (++this->XYZ[LINE] != this->SideSize);
        } while (++this->XYZ[LAYER] != this->SideSize);
     }

     return true;
}

FaceList_T Rubik_Engine::Block_FacesList(const Coord_T& xyz) const noexcept {
           return this->Cube[this->Block_Coordenate(xyz)].FacesList();
}
