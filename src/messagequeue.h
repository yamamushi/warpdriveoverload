//
//  messagequeue.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef warpdriveoverloaded_messagequeue_h
#define warpdriveoverloaded_messagequeue_h

#include <queue>
#include "tr1_threading.h"

template <typename T>
class MsgQueue
{
public:
    
    T pop()
    {
        INSTANTIATE_MLOCK(mutex_);
        while (queue_.empty())
        {
            cond_.wait(mlock);
        }
        auto item = queue_.front();
        queue_.pop();
        return item;
    }
    
    void pop(T& item)
    {
        INSTANTIATE_MLOCK(mutex_);
        while (queue_.empty())
        {
            cond_.wait(mlock);
        }
        item = queue_.front();
        queue_.pop();
    }
    
    void push(const T& item)
    {
        INSTANTIATE_MLOCK(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_.notify_one();
    }
    
    void push(T&& item)
    {
        INSTANTIATE_MLOCK(mutex_);
        queue_.push(std::move(item));
        mlock.unlock();
        cond_.notify_one();
    }
    
    int size()
    {
        INSTANTIATE_MLOCK(mutex_);
        int size = queue_.size();
        mlock.unlock();
        return size;
    }
    
    void clear()
    {
        INSTANTIATE_MLOCK(mutex_);
        while(!queue_.empty())
            queue_.pop();
        mlock.unlock();
    }
    
private:
    std::queue<T> queue_;
    _MUTEX(mutex_);
    CONDITION_VARIABLE(cond_);
};

#endif
