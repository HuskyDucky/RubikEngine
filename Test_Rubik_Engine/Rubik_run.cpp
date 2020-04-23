/**
    File    : Rubik_run.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.30            Version: 20200421.1

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
#include "../Lib/Test.h"
#include "../Rubik_Engine/Rubik_Engine.h"

extern TestFunction<Rubik_Engine> Test_CreationCube;
extern TestFunction<Rubik_Engine> Test_TurnedCubeisFinished;
extern TestFunction<Rubik_Engine> Test_SpinedCubeisntFinished;
extern TestFunction<Rubik_Engine> Test_CompareCube;
extern TestFunction<Rubik_Engine> Test_RandomizeCube;
extern TestFunction<Rubik_Engine> Test_CopyCube;
extern TestFunction<Rubik_Engine> Test_InitCopyCube;
extern TestFunction<Rubik_Engine> Test_ResetCube;
extern TestFunction<Rubik_Engine> Test_ScannedFaces_ValidRandomScanFaces3x3;
extern TestFunction<Rubik_Engine> Test_ScannedFaces_InvalidRandomScanFaces3x3;
extern TestFunction<Rubik_Engine> Test_ScannedFaces_NoScannedFace3x3;
extern TestFunction<Rubik_Engine> Test_ScannedFaces_WrongSizeScanFaces3x3;
extern TestFunction<Rubik_Engine> Test_ScannedFaces_commitScannedFaces3x3;
//Invalid color test doesn't compile due to Color_E enum

int main() {
    constexpr char CName[] = "Cube Engine";
    bool result = true;

    result &= Test("Cube Properties - Creating a Cube", CName, Test_CreationCube);
    result &= Test("Cube Properties - Turnned Cube is finished?", CName, Test_TurnedCubeisFinished);
    result &= Test("Cube Properties - Spinned Cube is NOT finished?", CName, Test_SpinedCubeisntFinished);
    result &= Test("Cube Properties - Randomize a Cube", CName, Test_RandomizeCube);
    result &= Test("Cube Properties - Compare Cubes", CName, Test_CompareCube);
    result &= Test("Cube Properties - Copy a Cube", CName, Test_CopyCube);
    result &= Test("Cube Properties - Initialize a Copied Cube", CName, Test_InitCopyCube);
    result &= Test("Cube Properties - Reset Cube", CName, Test_ResetCube);
    result &= Test("Cube Properties - Scan Cube Faces - Pass a valid randomize Cube -Cube3x3"     , CName, Test_ScannedFaces_ValidRandomScanFaces3x3);
    result &= Test("Cube Properties - Scan Cube Faces - Pass a INvalid randomize Cube -Cube3x3"   , CName, Test_ScannedFaces_InvalidRandomScanFaces3x3);
    result &= Test("Cube Properties - Scan Cube Faces - Commit without all faces scanned -Cube3x3", CName, Test_ScannedFaces_NoScannedFace3x3);
    result &= Test("Cube Properties - Scan Cube Faces - Pass a face with a wrong size -Cube3x3"   , CName, Test_ScannedFaces_WrongSizeScanFaces3x3);
    result &= Test("Cube Properties - Scan Cube Faces - Commit the scanned faces -Cube3x3"        , CName, Test_ScannedFaces_commitScannedFaces3x3);

    return !result;
}
