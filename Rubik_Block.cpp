/**
    File    : Rubik_Block.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20191111.2

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Block.h"

BlockPosition_T Block::OriginalBlockPosition() const noexcept { return this->originalBlockPosition; }
ColorPositionList_T Block::ColorsAndPositions() const noexcept { return this->ColorPositionList; }

Position_T Block::ColorPosition(Color_T color) const noexcept {
           for (uint8_t Pos = 0; Pos < this->ColorPositionList.size(); ++Pos)
               if (ColorPositionList[Pos].first == color)
                  return ColorPositionList[Pos].second;

           return PositioningOn::NONEPOSITION;
}

void Block::moveColors(const FlipBlocksAt BlockGroupDir, const TurnBlocks isClockWise) noexcept {
     uint8_t Pos = 0;

     if (BlockGroupDir == FlipBlocksAt::LINE) {
        if (isClockWise)
           for (; Pos < this->ColorPositionList.size(); ++Pos)
               switch (this->ColorPositionList[Pos].second) {
                      case PositioningOn::FRONT : this->ColorPositionList[Pos].second = PositioningOn::LEFT;  break;
                      case PositioningOn::LEFT  : this->ColorPositionList[Pos].second = PositioningOn::BACK;  break;
                      case PositioningOn::BACK  : this->ColorPositionList[Pos].second = PositioningOn::RIGHT; break;
                      case PositioningOn::RIGHT : this->ColorPositionList[Pos].second = PositioningOn::FRONT;
               }
        else
           for (; Pos < this->ColorPositionList.size(); ++Pos)
               switch (this->ColorPositionList[Pos].second) {
                      case PositioningOn::FRONT : this->ColorPositionList[Pos].second = PositioningOn::RIGHT; break;
                      case PositioningOn::RIGHT : this->ColorPositionList[Pos].second = PositioningOn::BACK;  break;
                      case PositioningOn::BACK  : this->ColorPositionList[Pos].second = PositioningOn::LEFT;  break;
                      case PositioningOn::LEFT  : this->ColorPositionList[Pos].second = PositioningOn::FRONT;
               }
     } else if (BlockGroupDir == FlipBlocksAt::COLUMN) {
            if (isClockWise)
               for (; Pos < this->ColorPositionList.size(); ++Pos)
                   switch (this->ColorPositionList[Pos].second) {
                          case PositioningOn::FRONT  : this->ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                          case PositioningOn::BOTTOM : this->ColorPositionList[Pos].second = PositioningOn::BACK;   break;
                          case PositioningOn::BACK   : this->ColorPositionList[Pos].second = PositioningOn::TOP;    break;
                          case PositioningOn::TOP    : this->ColorPositionList[Pos].second = PositioningOn::FRONT;
                   }
            else
               for (; Pos < this->ColorPositionList.size(); ++Pos)
                   switch (this->ColorPositionList[Pos].second) {
                          case PositioningOn::FRONT  : this->ColorPositionList[Pos].second = PositioningOn::TOP;    break;
                          case PositioningOn::TOP    : this->ColorPositionList[Pos].second = PositioningOn::BACK;   break;
                          case PositioningOn::BACK   : this->ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                          case PositioningOn::BOTTOM : this->ColorPositionList[Pos].second = PositioningOn::FRONT;
                   }
     } else if (isClockWise)
            for (; Pos < this->ColorPositionList.size(); ++Pos)
                switch (this->ColorPositionList[Pos].second) {
                       case PositioningOn::TOP    : this->ColorPositionList[Pos].second = PositioningOn::RIGHT;  break;
                       case PositioningOn::RIGHT  : this->ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                       case PositioningOn::BOTTOM : this->ColorPositionList[Pos].second = PositioningOn::LEFT;   break;
                       case PositioningOn::LEFT   : this->ColorPositionList[Pos].second = PositioningOn::TOP;
                }
       else
            for (; Pos < this->ColorPositionList.size(); ++Pos)
                switch (this->ColorPositionList[Pos].second) {
                       case PositioningOn::TOP    : this->ColorPositionList[Pos].second = PositioningOn::LEFT;  break;
                       case PositioningOn::LEFT   : this->ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                       case PositioningOn::BOTTOM : this->ColorPositionList[Pos].second = PositioningOn::RIGHT; break;
                       case PositioningOn::RIGHT  : this->ColorPositionList[Pos].second = PositioningOn::TOP;
                }
}
