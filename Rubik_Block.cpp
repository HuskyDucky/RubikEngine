/**
    File    : Rubik_Block.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20191026.2

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Block.h"

BlockPosition_T Block::OriginalBlockPosition() const noexcept { return this->originalBlockPosition; }
vector<ColorPosition_T> Block::Colors() const noexcept { return this->ColorPositionList; }

void Block::moveColors(FlipBlocksAt BlockGroupDir, TurnBlocks isClockWise) noexcept {
     uint8_t Pos = 0;

     if (BlockGroupDir == FlipBlocksAt::LINE) {
        if (isClockWise)
           for (; Pos < ColorPositionList.size(); ++Pos)
               switch (ColorPositionList[Pos].second) {
                      case PositioningOn::FRONT : ColorPositionList[Pos].second = PositioningOn::LEFT;  break;
                      case PositioningOn::LEFT  : ColorPositionList[Pos].second = PositioningOn::BACK;  break;
                      case PositioningOn::BACK  : ColorPositionList[Pos].second = PositioningOn::RIGHT; break;
                      case PositioningOn::RIGHT : ColorPositionList[Pos].second = PositioningOn::FRONT;
               }
        else
           for (; Pos < ColorPositionList.size(); ++Pos)
               switch (ColorPositionList[Pos].second) {
                      case PositioningOn::FRONT : ColorPositionList[Pos].second = PositioningOn::RIGHT; break;
                      case PositioningOn::RIGHT : ColorPositionList[Pos].second = PositioningOn::BACK;  break;
                      case PositioningOn::BACK  : ColorPositionList[Pos].second = PositioningOn::LEFT;  break;
                      case PositioningOn::LEFT  : ColorPositionList[Pos].second = PositioningOn::FRONT;
               }
     } else if (BlockGroupDir == FlipBlocksAt::COLUMN) {
            if (isClockWise)
               for (; Pos < ColorPositionList.size(); ++Pos)
                   switch (ColorPositionList[Pos].second) {
                          case PositioningOn::FRONT  : ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                          case PositioningOn::BOTTOM : ColorPositionList[Pos].second = PositioningOn::BACK;   break;
                          case PositioningOn::BACK   : ColorPositionList[Pos].second = PositioningOn::TOP;    break;
                          case PositioningOn::TOP    : ColorPositionList[Pos].second = PositioningOn::FRONT;
                   }
            else
               for (; Pos < ColorPositionList.size(); ++Pos)
                   switch (ColorPositionList[Pos].second) {
                          case PositioningOn::FRONT  : ColorPositionList[Pos].second = PositioningOn::TOP;    break;
                          case PositioningOn::TOP    : ColorPositionList[Pos].second = PositioningOn::BACK;   break;
                          case PositioningOn::BACK   : ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                          case PositioningOn::BOTTOM : ColorPositionList[Pos].second = PositioningOn::FRONT;
                   }
     } else if (isClockWise)
            for (; Pos < ColorPositionList.size(); ++Pos)
                switch (ColorPositionList[Pos].second) {
                       case PositioningOn::TOP    : ColorPositionList[Pos].second = PositioningOn::RIGHT;  break;
                       case PositioningOn::RIGHT  : ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                       case PositioningOn::BOTTOM : ColorPositionList[Pos].second = PositioningOn::LEFT;   break;
                       case PositioningOn::LEFT   : ColorPositionList[Pos].second = PositioningOn::TOP;
                }
       else
            for (; Pos < ColorPositionList.size(); ++Pos)
                switch (ColorPositionList[Pos].second) {
                       case PositioningOn::TOP    : ColorPositionList[Pos].second = PositioningOn::LEFT;  break;
                       case PositioningOn::LEFT   : ColorPositionList[Pos].second = PositioningOn::BOTTOM; break;
                       case PositioningOn::BOTTOM : ColorPositionList[Pos].second = PositioningOn::RIGHT; break;
                       case PositioningOn::RIGHT  : ColorPositionList[Pos].second = PositioningOn::TOP;
                }
}
