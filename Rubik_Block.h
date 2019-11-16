/**
    File    : Rubik_Block.h
    Author  : Menashe Rosemberg
    Created : 2019.10.23            Version: 20191111.3

    Rubik Program - Block Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include <vector>
#include <limits>
#include <optional>
#include <cinttypes>

using namespace std;

typedef uint8_t  Color_T;
typedef uint8_t  Position_T;
typedef uint8_t  Direction_T;
typedef uint32_t BlockPosition_T;

enum Color : Color_T {
     WHITE,
     YELLOW,
     RED,
     ORANGE,
     BLUE,
     GREEN
};

enum PositioningOn : Position_T {
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

using ColorPosition_T = pair<Color_T, Position_T>;
using ColorPositionList_T = vector<ColorPosition_T>;


struct Block {
       Block(const BlockPosition_T BlockP, vector<ColorPosition_T>&& ColorPos) : originalBlockPosition(BlockP),
                                                                                 ColorPositionList(ColorPos) {}

    BlockPosition_T OriginalBlockPosition() const noexcept;

    ColorPositionList_T ColorsAndPositions() const noexcept;
    Position_T ColorPosition(Color_T color) const noexcept;    //returns PositioningOn::NONEPOSITION if doesn't find

    void moveColors(const FlipBlocksAt BlockGroupDir, const TurnBlocks isClockWise) noexcept;

    private:
        BlockPosition_T originalBlockPosition;
        ColorPositionList_T ColorPositionList;
};
