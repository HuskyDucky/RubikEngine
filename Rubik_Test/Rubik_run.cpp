/**
    File    : Rubik_run.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.30            Version: 20200315.1.1

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
#include "Rubik_run_Tests.h"

int main() {

    if (Test("Cube Properties - Creating a Cube", Test_CreationCube)          &&
        Test("Cube Properties - Randomize a Cube", Test_RandomizeCube)        &&
        Test("Cube Properties - Compare Cubes", Test_CompareCube)             &&
        Test("Cube Properties - Copy a Cube", Test_CopyCube)                  &&
        Test("Cube Properties - Initialize a Copied Cube", Test_InitCopyCube) &&
        Test("Cube Properties - Reset Cube", Test_ResetCube)                  &&
        Test("Cube Properties - Turn Cube", Test_Turn2StartPosition3x3)       &&
        Test("Cube Properties - Scan Cube Faces - Pass a valid randomize Cube (Cube3x3)"     , Test_ScannedFaces_ValidRandomScanFaces3x3)   &&
        Test("Cube Properties - Scan Cube Faces - Pass a INvalid randomize Cube (Cube3x3)"   , Test_ScannedFaces_InvalidRandomScanFaces3x3) &&
        Test("Cube Properties - Scan Cube Faces - Commit without all faces scanned (Cube3x3)", Test_ScannedFaces_NoScannedFace3x3)          &&
        Test("Cube Properties - Scan Cube Faces - Pass a face with a wrong size (Cube3x3)"   , Test_ScannedFaces_WrongSizeScanFaces3x3)     &&
        Test("Cube Properties - Scan Cube Faces - Commit the scanned faces (Cube3x3)"        , Test_ScannedFaces_commitScannedFaces3x3)
        )
        ShowSpinnedCube();

    return 0;
}
