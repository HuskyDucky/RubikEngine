/**
    File    : Rubik_Block.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20191129.1.1

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Block.h"

BlkPosition_T Block::OriginalBlockPosition() const noexcept { return this->originalBlockPosition; }
ColorPositionList_T Block::ColorsAndPositionsList() const noexcept { return this->ColorPositionList; }
NofFaces_T Block::NofFaces() const noexcept { return this->ColorPositionList.size(); }

bool Block::HasColors(const vector<Color_E>& colors) const noexcept {

     if (this->ColorPositionList.size() != colors.size()) return false;

     NofFaces_T FacesFound = 0;
     for (auto& CPList : this->ColorPositionList)
         for (auto& Clrs : colors)
             if (CPList.first == Clrs) ++FacesFound;

     return FacesFound == this->ColorPositionList.size();
}

void Block::moveColors(const FlipBlocksAt BlockGroupDir, const TurnBlocks isClockWise) noexcept {
     NofFaces_T Pos = 0;

     if (BlockGroupDir == FlipBlocksAt::LINE) {
        if (isClockWise)
           for (; Pos < this->ColorPositionList.size(); ++Pos)
               switch (this->ColorPositionList[Pos].second) {
                      case Position_E::FRONT : this->ColorPositionList[Pos].second = Position_E::LEFT;  break;
                      case Position_E::LEFT  : this->ColorPositionList[Pos].second = Position_E::BACK;  break;
                      case Position_E::BACK  : this->ColorPositionList[Pos].second = Position_E::RIGHT; break;
                      case Position_E::RIGHT : this->ColorPositionList[Pos].second = Position_E::FRONT;
               }
        else
           for (; Pos < this->ColorPositionList.size(); ++Pos)
               switch (this->ColorPositionList[Pos].second) {
                      case Position_E::FRONT : this->ColorPositionList[Pos].second = Position_E::RIGHT; break;
                      case Position_E::RIGHT : this->ColorPositionList[Pos].second = Position_E::BACK;  break;
                      case Position_E::BACK  : this->ColorPositionList[Pos].second = Position_E::LEFT;  break;
                      case Position_E::LEFT  : this->ColorPositionList[Pos].second = Position_E::FRONT;
               }
     } else if (BlockGroupDir == FlipBlocksAt::COLUMN) {
            if (isClockWise)
               for (; Pos < this->ColorPositionList.size(); ++Pos)
                   switch (this->ColorPositionList[Pos].second) {
                          case Position_E::FRONT  : this->ColorPositionList[Pos].second = Position_E::BOTTOM; break;
                          case Position_E::BOTTOM : this->ColorPositionList[Pos].second = Position_E::BACK;   break;
                          case Position_E::BACK   : this->ColorPositionList[Pos].second = Position_E::TOP;    break;
                          case Position_E::TOP    : this->ColorPositionList[Pos].second = Position_E::FRONT;
                   }
            else
               for (; Pos < this->ColorPositionList.size(); ++Pos)
                   switch (this->ColorPositionList[Pos].second) {
                          case Position_E::FRONT  : this->ColorPositionList[Pos].second = Position_E::TOP;    break;
                          case Position_E::TOP    : this->ColorPositionList[Pos].second = Position_E::BACK;   break;
                          case Position_E::BACK   : this->ColorPositionList[Pos].second = Position_E::BOTTOM; break;
                          case Position_E::BOTTOM : this->ColorPositionList[Pos].second = Position_E::FRONT;
                   }
     } else if (isClockWise)
            for (; Pos < this->ColorPositionList.size(); ++Pos)
                switch (this->ColorPositionList[Pos].second) {
                       case Position_E::TOP    : this->ColorPositionList[Pos].second = Position_E::RIGHT;  break;
                       case Position_E::RIGHT  : this->ColorPositionList[Pos].second = Position_E::BOTTOM; break;
                       case Position_E::BOTTOM : this->ColorPositionList[Pos].second = Position_E::LEFT;   break;
                       case Position_E::LEFT   : this->ColorPositionList[Pos].second = Position_E::TOP;
                }
       else
            for (; Pos < this->ColorPositionList.size(); ++Pos)
                switch (this->ColorPositionList[Pos].second) {
                       case Position_E::TOP    : this->ColorPositionList[Pos].second = Position_E::LEFT;  break;
                       case Position_E::LEFT   : this->ColorPositionList[Pos].second = Position_E::BOTTOM; break;
                       case Position_E::BOTTOM : this->ColorPositionList[Pos].second = Position_E::RIGHT; break;
                       case Position_E::RIGHT  : this->ColorPositionList[Pos].second = Position_E::TOP;
                }
}
