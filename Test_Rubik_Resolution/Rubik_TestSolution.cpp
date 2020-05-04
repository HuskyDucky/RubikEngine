/**
    File    : Rubik_TestSolution.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200427.2

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
#include <thread>
#include "Rubik_TestSolution.h"
#include "../Lib/ThinkShow.h"

bool TestSolutionTo::CheckSolution(const uint16_t ExpQofSpins) noexcept {

     this->ResolveIt();

     this->AvaliateSolution(ExpQofSpins);

     return this->ApplyingSolution();
}

LofSpins_T TestSolutionTo::ResolveIt() noexcept {
           cout << '\n';
           const string ThreadMSG = Test_StepCounterTab() + "Searching for solution: ";

                   bool KeepThreadAlive = true;
                   thread([&]() { while (KeepThreadAlive) {
                                        ThinkShow(ThreadMSG);
                                        this_thread::sleep_for(125ms);
                                  }
                                  KeepThreadAlive =  true;
                                }).detach();

           #ifdef BFS_SOLUTION
                  this->AllMoves = BFS_ResolveThe(this->Cube).Now();   //BFS solution
           #else
                  this->AllMoves = DFS_ResolveThe(this->Cube);         //DFS solution
           #endif // BFS_SOLUTION

                   KeepThreadAlive = false;
                   while(!KeepThreadAlive) this_thread::yield();

           cout << '\r' << ThreadMSG << "done." << flush;

           return this->AllMoves.value();
}

void TestSolutionTo::AvaliateSolution(const uint16_t ExpQofSpins) noexcept {
     if (this->AllMoves) {
        const bool SpinPass = ExpQofSpins == this->AllMoves->size();

        Test_StepCounterInfo();
        cout << "Number of spins made: " << setw(2) << right << this->AllMoves->size()
                       << ". Expected: " << setw(2) << right << ExpQofSpins << ": " << (SpinPass?"pass":"fail");

        if (SpinPass) return;

     } else
        Test_StepCounterInfo("\tERROR - No moves left found");

     this->AllMoves.reset();
}

bool TestSolutionTo::ApplyingSolution() noexcept {

     Test_StepCounterInfo("Apply solution");
     if (this->AllMoves) {
        for (SpinTo_T spins : this->AllMoves.value())
            this->Cube.spin(spins.Layer, spins.Level, spins.isClockWise);

        if (this->Cube.isFinished()) {
            cout << "pass" << endl;
            return true;
        }
        cout << "fail";
     } else
        cout << "N/A";

     return false;
}
