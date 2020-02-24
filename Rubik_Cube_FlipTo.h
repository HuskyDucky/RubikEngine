/**
    File    : Rubik_Cube_FlipTo.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200215.1

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef CUBE_FLIPTO_H
#define CUBE_FLIPTO_H

#include "Rubik_Cube_Global.h"

struct FlipTo_T {
       FlipTo_T(const FlipBlocksAt layer, const CubeSideSize_T level, const TurnBlocks isclockwise) : Layer(layer),
                                                                                                      Level(level),
                                                                                                      isClockWise(isclockwise) {}
       const FlipBlocksAt Layer;
       const CubeSideSize_T Level;
       const TurnBlocks isClockWise;

       bool operator==(const FlipTo_T& c) const noexcept {
            return this->Layer == c.Layer && this->Level == c.Level && this->isClockWise == c.isClockWise; }
};

using ListOfFlips_T = vector<FlipTo_T>;

#endif
