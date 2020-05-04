/**
    File    : Rubik_Resolution_ResultManager.h
    Author  : Menashe Rosemberg
    Created : 2020.02.08            Version: 20200420.4

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
#ifndef RESULTKEEPER_H
#define RESULTKEEPER_H

#include <cmath>
#include <atomic>
#include <forward_list>
#include "../Rubik_Engine/Rubik_Engine.h"

using NofSteps_T = uint16_t;
using atomic_NofSteps_T = atomic_uint16_t;
using SpinsListBase_T = forward_list<SpinTo_T>;

constexpr NofSteps_T EXPECTEDMAXSTEPS = 21;         ///IMPORTANT!!!! - Determine the level of the tree

struct ResultManager {
       ResultManager(const Rubik_Engine& Cube, const NofSteps_T ExpectedMaxSteps = EXPECTEDMAXSTEPS);

    const SpinsListBase_T SpinsListBase;

    //updates
        void Spins(LofSpins_T&& Steps) noexcept;    //Receive proposals for new results

    //info
        NofSteps_T QuantOfSteps() const noexcept;   //Number of steps of the result. Returns 255 if no result was proposed
        bool hasMoves() const noexcept;             //check if the ResultManager already keeps turns and/or spins

    //results
        LofSpins_T AllMovesMade() const noexcept;

    private:
        atomic_flag Lock = ATOMIC_FLAG_INIT;
        atomic_NofSteps_T StepsMade;

        optional<LofSpins_T> AllMoves;

        SpinsListBase_T GenerateListOfMoves(const Rubik_Engine& Cube) const noexcept;
};

#endif
