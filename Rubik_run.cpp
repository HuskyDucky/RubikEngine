/**
    File    : Rubik_run.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.30            Version: 20191207.1

    Rubik Program

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_run_Tests.h"

int main() {

    if (Test("Creating a Cube", Test_CreationCube) &&
        Test("Randomize Cube", Test_RandomizeCube) &&
        Test("Reset Cube", Test_ResetCube)         &&
        Test("Copy Cube", Test_CopyCube))
        ShowFlippedCube();

    return 0;
}
