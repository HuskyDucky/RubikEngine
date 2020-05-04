/**
    File    : Rubik_TestSolution.h
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200504.1

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
#ifndef TESTSOL_H
#define TESTSOL_H

#include <iomanip>
#include "../Lib/Test.h"
#include "../Rubik_Resolution_BFS/Rubik_Resolution_BFS.h"
#include "../Rubik_Resolution_DFS/Rubik_Resolution_DFS.h"

#define BFS_SOLUTION                    //Comment this line to get the DFS solution

struct TestSolutionTo {
       TestSolutionTo(const Rubik_Engine& cube) : Cube(cube) {}

    bool CheckSolution(const uint16_t ExpQofSpins = 0) noexcept;

    LofSpins_T ResolveIt() noexcept;
    void AvaliateSolution(const uint16_t ExpQofSpins) noexcept;
    bool ApplyingSolution() noexcept;

    private:
        Rubik_Engine Cube;
        optional<LofSpins_T> AllMoves;

        inline bool ExistMovesLeft() const noexcept;
};

#endif
