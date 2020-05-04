/**
    File    : Rubik_Resolution_Spinner.h
    Author  : Menashe Rosemberg
    Created : 2020.02.16            Version: 20200423.1

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
#ifndef SPINNER_H
#define SPINNER_H

#include "../Rubik_Engine/Rubik_Engine.h"
#include "Rubik_Resolution_ResultManager.h"

struct Spinner {
       Spinner(Rubik_Engine cube,
               ResultManager& result,
               const SpinTo_T firstspin);

    bool SearchingforSolution() noexcept;

    private:
        struct SpinMade;

        Rubik_Engine Cube;
        ResultManager& Result;
        vector<SpinMade> StepsMade;

        bool ProposeNewResult() noexcept;
        bool SpinAgain() noexcept;
        bool StepBack() noexcept;
};

struct Spinner::SpinMade {
                SpinMade (const SpinTo_T& thisSpin, SpinsListBase_T possiblespinslist);

       const SpinTo_T ThisSpin;

       optional<SpinTo_T> NextSpin() noexcept;

       private:
            SpinsListBase_T SpinsList;
};

#endif
