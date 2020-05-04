/**
    File    : Rubik_Engine_Global.h
    Author  : Menashe Rosemberg
    Created : 2019.10.26            Version: 20191228.3.4

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
#ifndef CUBE_GLOBAL_H
#define CUBE_GLOBAL_H

#include <vector>
#include <algorithm>
#include "Rubik_Block.h"

constexpr uint8_t TofFACES = 6;

typedef uint8_t CubeSideSize_T;           //max blocks is 255 (the last value - 256 - is reserved to internal use of the class)
typedef uint16_t QofBlksPerFace_T;        //255 x 255 = 65.025 free to use

//Cube (and ScanFaces)
    using Cube_T = vector<ClassBlock::Block>;
    using Coord_T = array<CubeSideSize_T, 3>;

//Scanfaces (and Cube)
    using BlocksPosToFace_T = vector<QofBlksPerFace_T>;
    using ProtoCube_T = vector<FaceList_T>;

#endif
