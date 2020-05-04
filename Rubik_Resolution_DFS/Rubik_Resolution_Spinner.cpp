/**
    File    : Rubik_Resolution_Spinner.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.16            Version: 20200425.2

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
#include "Rubik_Resolution_Spinner.h"

Spinner::Spinner(Rubik_Engine cube,
                 ResultManager& result,
                 const SpinTo_T firstspin) : Cube(move(cube)),
                                             Result(result) {
    this->Cube.spin(firstspin);
    this->StepsMade.reserve(this->Result.QuantOfSteps());
    this->StepsMade.emplace_back(firstspin, this->Result.SpinsListBase);
}

bool Spinner::SearchingforSolution() noexcept {
     if (this->Cube.isFinished() && !this->ProposeNewResult())
        return false;

     return this->SpinAgain();
}

bool Spinner::ProposeNewResult() noexcept {
     LofSpins_T ProposalSteps;
     ProposalSteps.reserve(this->StepsMade.size());
     for (auto& NBS : this->StepsMade)
          ProposalSteps.emplace_back(NBS.ThisSpin);

     this->Result.Spins(move(ProposalSteps));

     for (uint8_t stepBack = 0; stepBack < 2; ++stepBack)   //The last 2 steps have no possible solutions
          if (!this->StepBack())
              return false;                                 //No steps left

     return true;
}

bool Spinner::StepBack() noexcept {
     this->Cube.spinback(this->StepsMade.back().ThisSpin);
     this->StepsMade.pop_back();

     return this->StepsMade.size();
}

bool Spinner::SpinAgain() noexcept {
     if (this->Result.QuantOfSteps() > this->StepsMade.size())
        if (optional<SpinTo_T> CurrentSpin = this->StepsMade.back().NextSpin(); CurrentSpin) {
            this->Cube.spin(CurrentSpin.value());
            this->StepsMade.emplace_back(CurrentSpin.value(), this->Result.SpinsListBase);
            return true;
        }

    if (this->StepBack())
        return this->SpinAgain();
    else
        return false;
}

