/**
    File    : Rubik_Engine_MoveTypes.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200420.1

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
#ifndef MOVETYPES_H
#define MOVETYPES_H

#include "Rubik_Engine_Global.h"

struct SpinTo_T {
       SpinTo_T(const SpinBlocksAt layer, const CubeSideSize_T level, const TurnBlock isclockwise) : Layer(layer),
                                                                                                     Level(level),
                                                                                                     isClockWise(isclockwise) {}
       SpinBlocksAt Layer;
       CubeSideSize_T Level;
       TurnBlock isClockWise;

       bool operator==(const SpinTo_T& c) const noexcept {
            return this->Layer == c.Layer && this->Level == c.Level && this->isClockWise == c.isClockWise; }
};

struct TurnTo_T {
       TurnTo_T(const SpinBlocksAt layer, const TurnBlock isclockwise) : Layer(layer), isClockWise(isclockwise) {}
       const SpinBlocksAt Layer;
       const TurnBlock isClockWise;
};

using LofSpins_T = vector<SpinTo_T>;

#endif
