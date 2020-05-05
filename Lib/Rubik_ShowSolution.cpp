/**
    File    : Rubik_ShowSolution.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200505.1

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
#include "Test.h"
#include "../Rubik_Engine/Rubik_Engine_MoveTypes.h"

void ShowSolution(const LofSpins_T& AllMoves) noexcept {
     auto LayerOf = [](const SpinBlocksAt L) -> const char* { switch (L) {
                                                                     case LINE   : return "Line";
                                                                     case COLUMN : return "Column";
                                                                     default     : return "Axis";
                                                            } };

     if (AllMoves.size()) {
        Test_StepCounterInfo("Below the " + to_string(AllMoves.size()) + " steps to solve the cube");
        for (SpinTo_T spin : AllMoves)
            Test_StepCounterInfo(string("\t") + LayerOf(spin.Layer) + " " +
                                 to_string(spin.Level) + " " +
                                 (spin.isClockWise?"Clockwise":"Counterclockwise"));
     } else
       Test_StepCounterInfo("\nERROR - I couldn't show the list of moves to solution the cube.");
}
