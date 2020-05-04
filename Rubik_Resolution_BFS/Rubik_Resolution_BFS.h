/**
    File    : Rubik_Resolution_BFS.h
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200503.3

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
#ifndef BFSRESOLUTION_H
#define BFSRESOLUTION_H

#include "../Rubik_Engine/Rubik_Engine.h"

using Steps_T = uint16_t;
using ListBaseOfSpins_T = vector<SpinTo_T>;

void ShowSolution(const LofSpins_T& AllMoves) noexcept;

struct BFS_ResolveThe {
       BFS_ResolveThe(const Rubik_Engine& cube);

    LofSpins_T Now() noexcept;

    private:
        Rubik_Engine Cube;
        const ListBaseOfSpins_T SpinsListBase;
        vector<Steps_T> Steps;
        vector<Steps_T> DSteps2Solution;

        ListBaseOfSpins_T GenerateListOfMoves() const noexcept;
        bool LeavesIteration() noexcept;
        void BranchesInteration() noexcept;
        LofSpins_T CreateSolutionSteps() const noexcept;
};


#endif
