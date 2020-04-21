/**
    File    : Test.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20200419.2

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

static uint16_t Counter = 0;

void PressEnter() noexcept { cout << "\n\nPress <ENTER> to continue..."; cin.get(); }

string Test_StepCounter(bool Reset) noexcept {
       if (Reset)
          Counter = 0;

       return string("step X - ").replace(5, 1, to_string(++Counter));
}

void Test_StepCounterMsg(const string& Msg) noexcept {
     cout << '\n' << Test_StepCounter() << Msg << ": " << flush;
}

void Test_StepCounterInfo(const string& Msg) noexcept {
     cout << '\n' << string(8 + QofDigitsOf(Counter), ' ');
     if (Msg.size())
        cout << Msg << ": ";
}
