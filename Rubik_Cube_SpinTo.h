/**
    File    : Rubik_Cube_SpinTo.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200215.3

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef CUBE_SPINTO_H
#define CUBE_SPINTO_H

#include "Rubik_Cube_Global.h"

struct SpinTo_T {
       SpinTo_T(const SpinBlocksAt layer, const CubeSideSize_T level, const TurnBlocks isclockwise) : Layer(layer),
                                                                                                      Level(level),
                                                                                                      isClockWise(isclockwise) {}
       const SpinBlocksAt Layer;
       const CubeSideSize_T Level;
       const TurnBlocks isClockWise;

       bool operator==(const SpinTo_T& c) const noexcept {
            return this->Layer == c.Layer && this->Level == c.Level && this->isClockWise == c.isClockWise; }
};

using ListOfSpins_T = vector<SpinTo_T>;

#endif
