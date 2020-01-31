/**
    File    : Rubik_Block.h
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20200129.1

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
///ATTENTION! All enum needs to keep the order as it is.
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <limits>
#include <cinttypes>

using namespace std;

typedef uint8_t  Color_T;
typedef uint8_t  Position_T;
typedef uint8_t  NofFaces_T;

typedef uint8_t  Direction_T;
typedef uint32_t BlkPosition_T;

enum Color_E : Color_T {        //Colors must have the same absolute value than its face position
     WHITE,
     YELLOW,
     RED,
     ORANGE,
     BLUE,
     GREEN
};

enum Position_E : Position_T {  //Face Position must have the same absolute value than its Color
     FRONT,
     RIGHT,
     BACK,
     LEFT,
     TOP,
     BOTTOM,
     NONEPOSITION
};

enum FlipBlocksAt : Direction_T {//Test commit with blocks with wrong colors as block with more than one side with the same color more than one block with one color
     LINE,
     COLUMN,
     LAYER
};

enum TurnBlocks : bool {
     COUNTERCLOCKWISE,
     CLOCKWISE
};

using ColorPosition_T = pair<Color_E, Position_T>;
using ColorPositionList_T = vector<ColorPosition_T>;

struct ClassBlock {
       struct Block {
              Block(const BlkPosition_T BlockP, vector<ColorPosition_T>&& ColorPos) : originalBlockPosition(BlockP),
                                                                                      ColorPositionList(ColorPos) {}

           BlkPosition_T OriginalBlockPosition() const noexcept;

           bool HasColors(const ColorPositionList_T& colors) const noexcept;
           ColorPositionList_T ColorsAndPositionsList() const noexcept;

           void moveColors(const FlipBlocksAt BlockGroupDir, const TurnBlocks isClockWise) noexcept;

           private:
               BlkPosition_T originalBlockPosition;
               ColorPositionList_T ColorPositionList;
       };
};

#endif
