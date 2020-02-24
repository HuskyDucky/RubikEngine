/**
    File    : Rubik_Block.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20200222.2

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Block.h"

BlkPosition_T ClassBlock::Block::OriginalBlockPosition() const noexcept { return this->originalBlockPosition; }
FaceList_T ClassBlock::Block::FacesList() const noexcept { return this->FaceList; }

bool ClassBlock::Block::HasColors(const FaceList_T& colors) const noexcept {

     if (this->FaceList.size() != colors.size()) return false;

     NofFaces_T FacesFound = 0;
     for (auto& CPList : this->FaceList)
         for (auto& Clrs : colors)
             if (CPList.first == Clrs.first) ++FacesFound;

     return FacesFound == this->FaceList.size();
}

bool ClassBlock::Block::operator!=(const FaceList_T& FaceList2Comp) const noexcept {

     if (this->FaceList.size() != FaceList2Comp.size()) return false;
     for (auto& face : this->FaceList)
         if (none_of(FaceList2Comp.cbegin(), FaceList2Comp.cend(),
                     [&face](const Face_T f) { return face.first == f.first && face.second == f.second; }))
             return true;

     return false;
}

void ClassBlock::Block::moveColors(const FlipBlocksAt BlockGroupDir, const TurnBlocks isClockWise) noexcept {
     NofFaces_T Pos = 0;

     if (BlockGroupDir == FlipBlocksAt::LINE) {
        if (isClockWise)
           for (; Pos < this->FaceList.size(); ++Pos)
               switch (this->FaceList[Pos].second) {
                      case FacePosition_E::FRONT : this->FaceList[Pos].second = FacePosition_E::LEFT;  break;
                      case FacePosition_E::LEFT  : this->FaceList[Pos].second = FacePosition_E::BACK;  break;
                      case FacePosition_E::BACK  : this->FaceList[Pos].second = FacePosition_E::RIGHT; break;
                      case FacePosition_E::RIGHT : this->FaceList[Pos].second = FacePosition_E::FRONT;
               }
        else
           for (; Pos < this->FaceList.size(); ++Pos)
               switch (this->FaceList[Pos].second) {
                      case FacePosition_E::FRONT : this->FaceList[Pos].second = FacePosition_E::RIGHT; break;
                      case FacePosition_E::RIGHT : this->FaceList[Pos].second = FacePosition_E::BACK;  break;
                      case FacePosition_E::BACK  : this->FaceList[Pos].second = FacePosition_E::LEFT;  break;
                      case FacePosition_E::LEFT  : this->FaceList[Pos].second = FacePosition_E::FRONT;
               }
     } else if (BlockGroupDir == FlipBlocksAt::COLUMN) {
            if (isClockWise)
               for (; Pos < this->FaceList.size(); ++Pos)
                   switch (this->FaceList[Pos].second) {
                          case FacePosition_E::FRONT  : this->FaceList[Pos].second = FacePosition_E::BOTTOM; break;
                          case FacePosition_E::BOTTOM : this->FaceList[Pos].second = FacePosition_E::BACK;   break;
                          case FacePosition_E::BACK   : this->FaceList[Pos].second = FacePosition_E::TOP;    break;
                          case FacePosition_E::TOP    : this->FaceList[Pos].second = FacePosition_E::FRONT;
                   }
            else
               for (; Pos < this->FaceList.size(); ++Pos)
                   switch (this->FaceList[Pos].second) {
                          case FacePosition_E::FRONT  : this->FaceList[Pos].second = FacePosition_E::TOP;    break;
                          case FacePosition_E::TOP    : this->FaceList[Pos].second = FacePosition_E::BACK;   break;
                          case FacePosition_E::BACK   : this->FaceList[Pos].second = FacePosition_E::BOTTOM; break;
                          case FacePosition_E::BOTTOM : this->FaceList[Pos].second = FacePosition_E::FRONT;
                   }
     } else if (isClockWise)
            for (; Pos < this->FaceList.size(); ++Pos)
                switch (this->FaceList[Pos].second) {
                       case FacePosition_E::TOP    : this->FaceList[Pos].second = FacePosition_E::RIGHT;  break;
                       case FacePosition_E::RIGHT  : this->FaceList[Pos].second = FacePosition_E::BOTTOM; break;
                       case FacePosition_E::BOTTOM : this->FaceList[Pos].second = FacePosition_E::LEFT;   break;
                       case FacePosition_E::LEFT   : this->FaceList[Pos].second = FacePosition_E::TOP;
                }
       else
            for (; Pos < this->FaceList.size(); ++Pos)
                switch (this->FaceList[Pos].second) {
                       case FacePosition_E::TOP    : this->FaceList[Pos].second = FacePosition_E::LEFT;  break;
                       case FacePosition_E::LEFT   : this->FaceList[Pos].second = FacePosition_E::BOTTOM; break;
                       case FacePosition_E::BOTTOM : this->FaceList[Pos].second = FacePosition_E::RIGHT; break;
                       case FacePosition_E::RIGHT  : this->FaceList[Pos].second = FacePosition_E::TOP;
                }
}
