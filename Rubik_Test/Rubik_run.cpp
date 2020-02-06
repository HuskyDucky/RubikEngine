/**
    File    : Rubik_run.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.30            Version: 20200206.1

    Rubik Program

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run_Tests.h"

int main() {

    if (Test("Cube Properties - Creating a Cube", Test_CreationCube)          &&
        Test("Cube Properties - Randomize Cube", Test_RandomizeCube)          &&
        Test("Cube Properties - Reset Cube", Test_ResetCube)                  &&
        Test("Cube Properties - Copy Cube", Test_CopyCube)                    &&
        Test("Cube Properties - Initialize a Copied Cube", Test_InitCopyCube) &&
        Test("Cube Properties - Scan Cube Faces - Pass a valid randomize Cube (Cube3x3)"     , Test_ScannedFaces_ValidRandomScanFaces3x3)   &&
        Test("Cube Properties - Scan Cube Faces - Pass a INvalid randomize Cube (Cube3x3)"   , Test_ScannedFaces_InvalidRandomScanFaces3x3) &&
        Test("Cube Properties - Scan Cube Faces - Commit without all faces scanned (Cube3x3)", Test_ScannedFaces_NoScannedFace3x3)          &&
        Test("Cube Properties - Scan Cube Faces - Pass a face with a wrong size (Cube3x3)"   , Test_ScannedFaces_WrongSizeScanFaces3x3)     &&
        Test("Cube Properties - Scan Cube Faces - Commit the scanned faces (Cube3x3)"        , Test_ScannedFaces_commitScannedFaces3x3)
        )
        ShowFlippedCube();

    return 0;
}
