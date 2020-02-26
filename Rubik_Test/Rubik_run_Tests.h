/**
    File    : Rubik_run.h
    Author  : Menashe Rosemberg
    Created : 2019.10.27            Version: 20200206.2.1

    Rubik Program - Test Cube

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef RUN_TEST_H
#define RUN_TEST_H

#include "Rubik_run_AuxFuncs.h"

using TestFunction = function<bool(Rubik& Cube)>;

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
//Invalid color test doesn't compile due to Color_E enum

void ShowSpinnedCube();

#endif
