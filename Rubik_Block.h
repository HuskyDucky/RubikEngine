/**
    File    : Rubik_Block.h
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20191129.3

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <limits>
#include <optional>
#include <cinttypes>

using namespace std;


typedef uint8_t  Color_T;
typedef uint8_t  Position_T;
typedef uint8_t  NofFaces_T;

typedef uint8_t  Direction_T;
typedef uint32_t BlkPosition_T;

using ColorPosition_T = pair<Color_T, Position_T>;
using ColorPositionList_T = vector<ColorPosition_T>;


enum Color_E : Color_T {
     WHITE,
     YELLOW,
     RED,
     ORANGE,
     BLUE,
     GREEN
};

enum Position_E : Position_T {
     FRONT,
     BACK,
     TOP,
     BOTTOM,
     LEFT,
     RIGHT,
     NONEPOSITION = numeric_limits<Position_T>::max()
};

enum FlipBlocksAt : Direction_T {
     LINE,
     COLUMN,
     LAYER
};

enum TurnBlocks : bool {
     COUNTERCLOCKWISE,
     CLOCKWISE
};

struct Block {
       Block(const BlkPosition_T BlockP, vector<ColorPosition_T>&& ColorPos) : originalBlockPosition(BlockP),
                                                                               ColorPositionList(ColorPos) {}

    BlkPosition_T OriginalBlockPosition() const noexcept;

    NofFaces_T NofFaces() const noexcept;
    bool HasColors(const vector<Color_E>& colors) const noexcept;       //If the size of colors != of NofFaces also return false
    ColorPositionList_T ColorsAndPositionsList() const noexcept;
    //Position_E ColorPosition(const Color_E color) const noexcept;     //returns Position_E::NONEPOSITION if doesn't find

    void moveColors(const FlipBlocksAt BlockGroupDir, const TurnBlocks isClockWise) noexcept;

    private:
        BlkPosition_T originalBlockPosition;
        ColorPositionList_T ColorPositionList;
};

#endif
