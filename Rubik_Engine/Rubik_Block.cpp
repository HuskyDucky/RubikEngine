/**
    File    : Rubik_Block.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20200420.1

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
#include "Rubik_Block.h"

FaceList_T ClassBlock::Block::FacesList() const noexcept { return this->FaceList; }

bool ClassBlock::Block::HasColors(const FaceList_T& colors) const noexcept {

     if (this->FaceList.size() != colors.size()) return false;

     NofFaces_T FacesFound = 0;
     for (auto& CPList : this->FaceList)
         for (auto& Clrs : colors)
             if (CPList.Color == Clrs.Color) ++FacesFound;

     return FacesFound == this->FaceList.size();
}

bool ClassBlock::Block::operator!=(const FaceList_T& FaceList2Comp) const noexcept {

     if (this->FaceList.size() != FaceList2Comp.size()) return false;
     for (auto& face : this->FaceList)
         if (none_of(FaceList2Comp.cbegin(), FaceList2Comp.cend(),
                     [&face](const Face_T f) { return face.Color == f.Color && face.Position == f.Position; }))
             return true;

     return false;
}

void ClassBlock::Block::moveColors(const SpinBlocksAt BlockGroupDir, const TurnBlock isClockWise) noexcept {
     NofFaces_T Pos = 0;

     if (BlockGroupDir == SpinBlocksAt::LINE) {
        if (isClockWise)
           for (; Pos < this->FaceList.size(); ++Pos)
               switch (this->FaceList[Pos].Position) {
                       case FacePosition_E::FRONT : this->FaceList[Pos].Position = FacePosition_E::LEFT;  break;
                       case FacePosition_E::LEFT  : this->FaceList[Pos].Position = FacePosition_E::BACK;  break;
                       case FacePosition_E::BACK  : this->FaceList[Pos].Position = FacePosition_E::RIGHT; break;
                       case FacePosition_E::RIGHT : this->FaceList[Pos].Position = FacePosition_E::FRONT;
               }
        else
           for (; Pos < this->FaceList.size(); ++Pos)
               switch (this->FaceList[Pos].Position) {
                       case FacePosition_E::FRONT : this->FaceList[Pos].Position = FacePosition_E::RIGHT; break;
                       case FacePosition_E::RIGHT : this->FaceList[Pos].Position = FacePosition_E::BACK;  break;
                       case FacePosition_E::BACK  : this->FaceList[Pos].Position = FacePosition_E::LEFT;  break;
                       case FacePosition_E::LEFT  : this->FaceList[Pos].Position = FacePosition_E::FRONT;
               }
     } else if (BlockGroupDir == SpinBlocksAt::COLUMN) {
            if (isClockWise)
               for (; Pos < this->FaceList.size(); ++Pos)
                   switch (this->FaceList[Pos].Position) {
                           case FacePosition_E::FRONT  : this->FaceList[Pos].Position = FacePosition_E::BOTTOM; break;
                           case FacePosition_E::BOTTOM : this->FaceList[Pos].Position = FacePosition_E::BACK;   break;
                           case FacePosition_E::BACK   : this->FaceList[Pos].Position = FacePosition_E::TOP;    break;
                           case FacePosition_E::TOP    : this->FaceList[Pos].Position = FacePosition_E::FRONT;
                   }
            else
               for (; Pos < this->FaceList.size(); ++Pos)
                   switch (this->FaceList[Pos].Position) {
                           case FacePosition_E::FRONT  : this->FaceList[Pos].Position = FacePosition_E::TOP;    break;
                           case FacePosition_E::TOP    : this->FaceList[Pos].Position = FacePosition_E::BACK;   break;
                           case FacePosition_E::BACK   : this->FaceList[Pos].Position = FacePosition_E::BOTTOM; break;
                           case FacePosition_E::BOTTOM : this->FaceList[Pos].Position = FacePosition_E::FRONT;
                   }
     } else if (isClockWise)
            for (; Pos < this->FaceList.size(); ++Pos)
                switch (this->FaceList[Pos].Position) {
                        case FacePosition_E::TOP    : this->FaceList[Pos].Position = FacePosition_E::RIGHT;  break;
                        case FacePosition_E::RIGHT  : this->FaceList[Pos].Position = FacePosition_E::BOTTOM; break;
                        case FacePosition_E::BOTTOM : this->FaceList[Pos].Position = FacePosition_E::LEFT;   break;
                        case FacePosition_E::LEFT   : this->FaceList[Pos].Position = FacePosition_E::TOP;
                }
       else
            for (; Pos < this->FaceList.size(); ++Pos)
                switch (this->FaceList[Pos].Position) {
                        case FacePosition_E::TOP    : this->FaceList[Pos].Position = FacePosition_E::LEFT;   break;
                        case FacePosition_E::LEFT   : this->FaceList[Pos].Position = FacePosition_E::BOTTOM; break;
                        case FacePosition_E::BOTTOM : this->FaceList[Pos].Position = FacePosition_E::RIGHT;  break;
                        case FacePosition_E::RIGHT  : this->FaceList[Pos].Position = FacePosition_E::TOP;
                }
}
