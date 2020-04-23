/**
    File    : ThreadPool.cpp
    Modifier: Menashe Rosemberg
    Created : 2019.11.15            Version: 20200423.1

    Copyright (c) 2012 Jakob Progsch, Václav Zeman

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would
       be appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not
       be misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
**/
#include "ThreadPool.h"

ThreadPool_T::ThreadPool_T() : EventStop(false) {
    const size_t iTThreads = thread::hardware_concurrency() * 2;
    this->ThreadList.reserve(iTThreads);

    size_t IIt = 0;
    do {
        this->ThreadList.emplace_back([this]() {
                                                for (;;) {
                                                    function<void()> LocalTask;
                                                    {
                                                        unique_lock<mutex> Lock(this->EventMutex);
                                                        this->EventFlag.wait(Lock, [this]{ return this->EventStop || !this->Tasks.empty(); });

                                                        if (this->EventStop && this->Tasks.empty())
                                                            break;

                                                        LocalTask = move(this->Tasks.front());
                                                        this->Tasks.pop_front();
                                                    }
                                                    LocalTask();
                                                }
                                               });
    } while (++IIt != iTThreads);
}

ThreadPool_T::~ThreadPool_T() {
    {
        unique_lock<mutex> Lock(this->EventMutex);
        this->EventStop = true;
    }

    for (thread &ThL: ThreadList)
        ThL.join();

    this->EventFlag.notify_all();
}
