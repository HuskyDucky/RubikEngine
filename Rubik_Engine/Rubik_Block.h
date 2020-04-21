/**
    File    : Rubik_Block.h
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
///ATTENTION! don't change the order of the enums' elements
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <limits>
#include <cinttypes>
#include <algorithm>

using namespace std;

typedef uint8_t  Color_T;
typedef uint8_t  NofFaces_T;
typedef uint8_t  FacePosition_T;

typedef uint8_t  Layer_T;
typedef uint32_t BlkPosition_T;

enum Color_E : Color_T {                //Colors must have the same absolute value than its face position
     WHITE,
     YELLOW,
     RED,
     ORANGE,
     BLUE,
     GREEN
};

enum FacePosition_E : FacePosition_T {  //Face Position must have the same absolute value than its Color
     FRONT,
     RIGHT,
     BACK,
     LEFT,
     TOP,
     BOTTOM,
     NONEPOSITION
};

enum SpinBlocksAt : Layer_T {
     LINE,
     COLUMN,
     LAYER,
     NOSPIN
};

using TurnBlock = bool;
constexpr TurnBlock CLOCKWISE = true;
constexpr TurnBlock COUNTERCLOCKWISE = false;

struct Face_T {
       Face_T(Color_E color, FacePosition_T pos) : Color(color), Position(pos) {}
       Color_E Color;
       FacePosition_T Position;

       bool operator==(const Face_T face) const noexcept { return this->Color == face.Color && this->Position == face.Position; }
};
using FaceList_T = vector<Face_T>;

struct ClassBlock {
       struct Block {
              Block(FaceList_T&& ColorPos) : FaceList(ColorPos) {}

           bool HasColors(const FaceList_T& colors) const noexcept;
           bool operator!=(const FaceList_T& FaceList2Comp) const noexcept;
           FaceList_T FacesList() const noexcept;

           void moveColors(const SpinBlocksAt BlockGroupDir, const TurnBlock isClockWise) noexcept;

           private:
               FaceList_T FaceList;
       };
};

#endif
