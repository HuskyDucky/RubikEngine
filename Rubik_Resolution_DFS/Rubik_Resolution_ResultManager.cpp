/**
    File    : Rubik_Resolution_ResultManager.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.08            Version: 20200504.1

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
#include "Rubik_Resolution_ResultManager.h"
#include <iostream>

ResultManager::ResultManager(const Rubik_Engine& Cube,
                             const NofSteps_T ExpectedMaxSteps) : SpinsListBase(this->GenerateListOfMoves(Cube)),
                                                                  StepsMade(ExpectedMaxSteps) {}

bool ResultManager::hasMoves() const noexcept { return this->AllMoves.has_value(); }
NofSteps_T ResultManager::QuantOfSteps() const noexcept { return this->StepsMade.load(); }
LofSpins_T ResultManager::AllMovesMade() const noexcept { return this->AllMoves.value(); }

void ResultManager::Spins(LofSpins_T&& Steps) noexcept {
     while (this->Lock.test_and_set());

     if (this->StepsMade > Steps.size()) {
         this->StepsMade.store(Steps.size());
         this->AllMoves = move(Steps);
     }

     Lock.clear();
}

SpinsListBase_T ResultManager::GenerateListOfMoves(const Rubik_Engine& Cube) const noexcept {
SpinsListBase_T PossiblesSpins;
//                constexpr uint8_t MinOfPossibleMoves =  18;
//                PossiblesSpins.reserve(MinOfPossibleMoves * ((Cube.SidesSize() - (Cube.SidesSize() % 2)) / 2));
                CubeSideSize_T Level = Cube.SidesSize();
                do { --Level;
                    bool Direction = COUNTERCLOCKWISE; //false
                    do {
                        for (SpinBlocksAt layer = LINE; layer != NOSPIN; layer = SpinBlocksAt(layer +1))
                            PossiblesSpins.emplace_front(layer, Level, Direction);
                    } while ((Direction = !Direction));
                } while (Level);

                return PossiblesSpins;
}

