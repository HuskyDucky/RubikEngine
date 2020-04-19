/**
    File    : Test.h
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20190406.2

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
#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <functional>

using namespace std;

void PressEnter() noexcept;

constexpr bool RESET = true;
string StepCounter(bool Reset = false) noexcept;

void StepCounter(const string& Msg) noexcept;

template <typename T>
using TestFunction = function<bool(T& InitObj)>;

//Need to pass an initialable object
template <typename T>
bool Test(const char* Title, const char* ObjName, function<bool(T& InitObj)>& Execute) {
     cout << '\n' << string(80, '=') << "\nTest " << Title << '\n' << string(80, '-') << "\n\n";


     cout << StepCounter(RESET) << "Creating " << ObjName << ": " << flush;

     T InitObj;

     cout << "done." << flush;

     bool Result = Execute(InitObj);

     cout << '\n' << string(80, '-')
          << '\n' << StepCounter() << "Test Result:\t<<<" << (Result ? "PASSED" :  "FAILED") << ">>>"
          << '\n' << string(80, '=');

     PressEnter();

     return Result;
}

#endif
