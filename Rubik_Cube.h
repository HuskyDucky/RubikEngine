/**
    File    : Rubik_Cube.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191102.1

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include <cmath>
#include <array>
#include <cstdio>
#include <chrono>
#include <random>
#include <algorithm>

#include "Rubik_Block.h"

typedef uint8_t CubeSize_T;
using Cube_T = vector<Block>;
using FromTo = pair<CubeSize_T, CubeSize_T>;
using AxisAOPosition_T = pair<CubeSize_T, CubeSize_T>;

#define Layer0to0 {0, 0}
#define Layer0toL {0, this->CubeSize-1}
#define LayerLto0 {this->CubeSize-1, 0}
#define LayerLtoL  {this->CubeSize-1, this->CubeSize-1}

struct RubikCube {
       RubikCube();

       void Flip(const FlipBlocksAt Layer, const CubeSize_T Level, const TurnBlocks isClockWise) noexcept;

       Cube_T Array() const noexcept;
       BlockPosition_T BlockPosition(const CubeSize_T xyz[3]) const noexcept;

       void Randomize(uint16_t NoInterations);

    private:
        const CubeSize_T CubeSize;

        Cube_T Cube;

        CubeSize_T XYZ[3] = {0, 0, 0};

        FlipBlocksAt CurrLayer2Move;
        const FromTo *Abs_Axis = nullptr;
        const FromTo *Ord_Axis = nullptr;
        const FromTo CW_Abs_Axis[4] = {Layer0to0, Layer0toL, LayerLtoL, LayerLto0};     //Abs and Ord Axes determine the block position on the
        const FromTo CW_Ord_Axis[4] = {Layer0toL, LayerLtoL, LayerLto0, Layer0to0};     //CurrLayer2Move to Clockwise flip
        const FromTo CCWAbs_Axis[4] = {Layer0to0, LayerLto0, LayerLtoL, Layer0toL};     //Abs and Ord Axes determine the block position on the
        const FromTo CCWOrd_Axis[4] = {Layer0toL, Layer0to0, LayerLto0, LayerLtoL};     //CurrLayer2Move to CounterClockwise flip

        inline BlockPosition_T CalcBlockPosition_Formula() noexcept;
        AxisAOPosition_T Next_Coords(const CubeSize_T CubeFace, const CubeSize_T BlockNo) const noexcept;
        BlockPosition_T CalcBlockPosition(const AxisAOPosition_T AxesHV) noexcept;
};
