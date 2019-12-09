/**
    File    : Rubik_Cube.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191207.1

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef CUBE_H
#define CUBE_H

#include <cmath>
#include <array>
#include <chrono>
#include <random>
#include <algorithm>

#include <iostream>

#include "Rubik_Block.h"

typedef uint8_t CubeSideSize_T;           //max 256
typedef BlkPosition_T QofBlocks_T;        //CubeSideSize_T(256) ^ 3 = 16.777.216

using Cube_T = vector<Block>;
using Coord_T = array<CubeSideSize_T,3>;
using FromTo = pair<CubeSideSize_T, CubeSideSize_T>;
using AxisAOPosition_T = pair<CubeSideSize_T, CubeSideSize_T>;

#define Layer0to0 {0, 0}
#define Layer0toL {0, this->SideSize-1}
#define LayerLto0 {this->SideSize-1, 0}
#define LayerLtoL {this->SideSize-1, this->SideSize-1}

struct Rubik {
       Rubik();
      ~Rubik() = default;

       const CubeSideSize_T SideSize;
       const QofBlocks_T TofBlocks;

       //Copy Cube
       void operator()(const Rubik& OriCube);

       //Info
       bool isFinished() const noexcept;
       float PercentualDone() const noexcept;

       //Block info
       bool isBlockInPosition(const Coord_T& xyz) const noexcept;
       BlkPosition_T Block_OriginalPosition(const Coord_T& xyz) const noexcept;
       ColorPositionList_T Block_ColorsAndPositions(const Coord_T& xyz) const noexcept;

       //Search
       BlkPosition_T findNearestBlockWith(const vector<Color_E>&& colors, BlkPosition_T StartSearchPos = 0) const noexcept;

       //Move layers
       void flip(const FlipBlocksAt Layer, const CubeSideSize_T Level, const TurnBlocks isClockWise) noexcept;

       //others actions
       Cube_T randomize(uint16_t NoInterations) noexcept;       //Automatically save this new randomization
       void reset() noexcept;

    private:
        Cube_T Cube;

        Coord_T XYZ;

        FlipBlocksAt CurrLayer2Move;
        const FromTo *Abs_Axis = nullptr;
        const FromTo *Ord_Axis = nullptr;
        const FromTo CW_Abs_Axis[4] = {Layer0to0, Layer0toL, LayerLtoL, LayerLto0};     //Abs and Ord Axes determine the block position on the
        const FromTo CW_Ord_Axis[4] = {Layer0toL, LayerLtoL, LayerLto0, Layer0to0};     //CurrLayer2Move to Clockwise flip
        const FromTo CCWAbs_Axis[4] = {Layer0to0, LayerLto0, LayerLtoL, Layer0toL};     //Abs and Ord Axes determine the block position on the
        const FromTo CCWOrd_Axis[4] = {Layer0toL, Layer0to0, LayerLto0, LayerLtoL};     //CurrLayer2Move to CounterClockwise flip

        AxisAOPosition_T Next_Coords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept;
        BlkPosition_T CalcBlockPosition(const AxisAOPosition_T AxesHV) noexcept;
        BlkPosition_T Block_Coordenate(const Coord_T& xyz) const noexcept;

        Rubik(const Rubik&) = delete;
        Rubik& operator=(const Rubik&) = delete;
};

#endif
