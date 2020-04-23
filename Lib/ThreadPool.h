/**
    File    : ThreadPool.h
    Modifier: Menashe Rosemberg
    Created : 2018.11.25            Version: 2020023.1

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
///This is a modified version of Jakob Progsch and Václav Zeman ThreadPool.
///Some microprocess was changed focussing on eficience of memory and speed
///some microprocess.
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <thread>
#include <memory>
#include <future>
#include <vector>
#include <functional>
#include <forward_list>
#include <condition_variable>

using namespace std;

struct ThreadPool_T {
       ThreadPool_T();
      ~ThreadPool_T();

    template<typename Task, typename... Args>
    auto Enqueue(Task&& task, Args&&... args) -> future<typename result_of<Task(Args...)>::type> {
         using return_type = typename result_of<Task(Args...)>::type;

         auto RunTask = make_shared<packaged_task<return_type()>>(bind(forward<Task>(task), forward<Args>(args)...));
         future<return_type> Result = RunTask->get_future();

         {
            unique_lock<mutex> lock(EventMutex);
            this->Tasks.emplace_front([RunTask](){ (*RunTask)(); });
         }

         EventFlag.notify_one();

         return Result;
    }

    private:
        bool EventStop;
        mutex EventMutex;
        vector<thread> ThreadList;
        condition_variable EventFlag;
        forward_list<function<void()>> Tasks;
};

#endif
