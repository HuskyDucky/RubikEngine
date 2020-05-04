/**
    File    : Rubik_Run_Resolution_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200425.2.1

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
#include "../Lib/Test.h"
#include "../Rubik_Engine/Rubik_Engine.h"

extern TestFunction<Rubik_Engine> Test_TurnCube;
extern TestFunction<Rubik_Engine> Test_SpinLINEOnce;
extern TestFunction<Rubik_Engine> Test_SpinLINETwice;
extern TestFunction<Rubik_Engine> Test_SpinLINEThrice;
extern TestFunction<Rubik_Engine> Test_SpinCOLUMNOnce;
extern TestFunction<Rubik_Engine> Test_SpinCOLUMNTwice;
extern TestFunction<Rubik_Engine> Test_SpinCOLUMNThrice;
extern TestFunction<Rubik_Engine> Test_SpinLAYEROnce;
extern TestFunction<Rubik_Engine> Test_SpinLAYERTwice;
extern TestFunction<Rubik_Engine> Test_SpinLAYERThrice;
extern TestFunction<Rubik_Engine> Test_MaxSpins2Solution;
extern TestFunction<Rubik_Engine> Test_SolutionOverScannedCube;
extern TestFunction<Rubik_Engine> Test_SpinLevels;

int main() {
    constexpr char CName[] = "Rubik Engine";
    bool result = true;
    result &= Test("Cube Resolution - Turn Cube in its axis", CName, Test_TurnCube);
    result &= Test("Cube Resolution - Spin Lines once",       CName, Test_SpinLINEOnce);
    result &= Test("Cube Resolution - Spin Lines Twice",      CName, Test_SpinLINETwice);
    result &= Test("Cube Resolution - Spin Lines Thrice",     CName, Test_SpinLINEThrice);
    result &= Test("Cube Resolution - Spin Columns Once",     CName, Test_SpinCOLUMNOnce);
    result &= Test("Cube Resolution - Spin Columns Twice",    CName, Test_SpinCOLUMNTwice);
    result &= Test("Cube Resolution - Spin Columns Thrice",   CName, Test_SpinCOLUMNThrice);
    result &= Test("Cube Resolution - Spin Layer Once",       CName, Test_SpinLAYEROnce);
    result &= Test("Cube Resolution - Spin Layer Twice",      CName, Test_SpinLAYERTwice);
    result &= Test("Cube Resolution - Spin Layer Thrice",     CName, Test_SpinLAYERThrice);
    result &= Test("Cube Resolution - Spin Levels ",          CName, Test_SpinLevels);

    if (result)
        Test("Show Solution to scanned cube", CName, Test_SolutionOverScannedCube);

    return !result;
}
