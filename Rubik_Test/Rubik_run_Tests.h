/**
    File    : Rubik_run.h
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200315.1.1

    Test Rubik Engine

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
#ifndef RUN_TEST_H
#define RUN_TEST_H

#include "../Lib/Rubik_run_AuxFuncs.h"

using TestFunction = function<bool(Rubik_Engine& Cube)>;

bool Test(const char* Msg, TestFunction& Execute);

extern TestFunction Test_CreationCube;
extern TestFunction Test_CompareCube;
extern TestFunction Test_RandomizeCube;
extern TestFunction Test_CopyCube;
extern TestFunction Test_InitCopyCube;
extern TestFunction Test_ResetCube;
extern TestFunction Test_ScannedFaces_ValidRandomScanFaces3x3;
extern TestFunction Test_ScannedFaces_InvalidRandomScanFaces3x3;
extern TestFunction Test_ScannedFaces_NoScannedFace3x3;
extern TestFunction Test_ScannedFaces_WrongSizeScanFaces3x3;
extern TestFunction Test_ScannedFaces_commitScannedFaces3x3;
extern TestFunction Test_Turn2StartPosition3x3;
//Invalid color test doesn't compile due to Color_E enum

void ShowSpinnedCube();

#endif
