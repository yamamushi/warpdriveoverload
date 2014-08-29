#pragma once
//
//  tr1_threading.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifdef __linux__
#include <chrono>
#include <tr1/memory>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <thread>
#define _THREAD std::thread
#define _MUTEX(MT) std::mutex MT
#define INSTANTIATE_MLOCK(MT) std::unique_lock<std::mutex>mlock(MT)
#define CONDITION_VARIABLE(VAR) std::condition_variable VAR
#define _ATOMIC(THE_ATOM) std::atomic<bool> THE_ATOM
#define _ATOMIC_TRUE true
#define _ATOMIC_FALSE false
#define _ATOMIC_ISTRUE(THE_VAL) (true == THE_VAL)
#define _ATOMIC_ISFALSE(THE_VAL) (false == THE_VAL)
#define _STD_FUNCTION(FUNC_TYPE) std::function< FUNC_TYPE >
#define _STD_BIND std::bind

#else
#ifdef __APPLE__
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#define _THREAD std::thread
#define _MUTEX(MT) std::mutex MT
#define INSTANTIATE_MLOCK(MT) std::unique_lock<std::mutex>mlock(MT)
#define CONDITION_VARIABLE(VAR) std::condition_variable VAR
#define _ATOMIC(THE_ATOM) std::atomic<bool> THE_ATOM
#define _ATOMIC_TRUE true
#define _ATOMIC_FALSE false
#define _ATOMIC_ISTRUE(THE_VAL) (true == THE_VAL)
#define _ATOMIC_ISFALSE(THE_VAL) (false == THE_VAL)
#define _STD_FUNCTION(FUNC_TYPE) std::function< FUNC_TYPE >
#define _STD_BIND std::bind

#endif
#endif

#ifndef nullptr
#define nullptr NULL
#endif

