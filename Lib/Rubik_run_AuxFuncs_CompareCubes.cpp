/**
    File    : Rubik_run_AuxFuncs_CompareCubes.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200206.3.1

    Rubik Engine - auxiliary functions to test Cube

    Copyright (c) 2019 TheArquitect (Menashe Rosemberg) rosemberg@ymail.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#include "Rubik_run_AuxFuncs_CompareCubes.h"

static bool CompareBlocks(const Coord_T& xyz, const Rubik_Engine& Cube1, const Rubik_Engine& Cube2) {
       FaceList_T blk1_ColPosList = Cube1.Block_FacesList(xyz);
       FaceList_T blk2_ColPosList = Cube2.Block_FacesList(xyz);

       if (blk1_ColPosList.size() != blk2_ColPosList.size()) return false;

       for (auto& C1_CP : blk1_ColPosList)
           if (find(blk2_ColPosList.cbegin(), blk2_ColPosList.cend(), C1_CP) == blk2_ColPosList.cend()) return false;

       return true;
}

bool AreThesesCubesDifferent(const Rubik_Engine& Cube1, const Rubik_Engine& Cube2) {
     if (Cube1.TotalOfBlocks() != Cube2.TotalOfBlocks()) return false;

     for (Coord_T xyz({0, 0, 0}); xyz[0] < Cube1.SidesSize(); ++xyz[0])
         for (xyz[2] = 0; xyz[2] < Cube1.SidesSize(); ++xyz[2])
             for (xyz[1] = 0; xyz[1] < Cube1.SidesSize(); ++xyz[1])
                 if (Cube1.Block_OriginalPosition(xyz) != Cube2.Block_OriginalPosition(xyz) ||
                    !CompareBlocks(xyz, Cube1, Cube2))
                    return true;

     return false;
}
