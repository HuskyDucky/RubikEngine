/**
    File    : Rubik_Block.h
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20191101.1

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include <vector>
#include <cinttypes>

using namespace std;

typedef uint8_t Color_T;
typedef uint8_t Position_T;
typedef uint8_t Direction_T;
typedef uint8_t BlockPosition_T;

enum Color : Color_T {
     WHITE,
     YELLOW,
     RED,
     ORANGE,
     GREEN,
     BLUE
};

enum PositioningOn : Position_T {
     TOP,
     BACK,
     LEFT,
     FRONT,
     RIGHT,
     BOTTOM
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

using ColorPosition_T = pair<Color_T, Position_T>;
struct Block {
       Block(const BlockPosition_T BlockP, vector<ColorPosition_T>&& ColorPos) : originalBlockPosition(BlockP),
                                                                                 ColorPositionList(ColorPos) {}

    void moveColors(FlipBlocksAt BlockGroupDir, TurnBlocks isClockWise) noexcept;
    BlockPosition_T OriginalBlockPosition() const noexcept;
    vector<ColorPosition_T> Colors() const noexcept;

    private:
        BlockPosition_T originalBlockPosition;
        vector<ColorPosition_T> ColorPositionList;
};
