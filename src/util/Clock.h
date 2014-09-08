//
//  Clock.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/6/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//
/*
 
 Using source provided at:
 http://noobtuts.com/cpp/interval
 http://noobtuts.com/cpp/frames-per-second
 https://gist.github.com/jbenet/1087739
 
 */



#ifndef __warpdriveoverloaded__Clock__
#define __warpdriveoverloaded__Clock__

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif



class Clock {
    
    
public:
    
    static void set_current_utc_time(struct timespec *ts) {
        
        
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        ts->tv_sec = mts.tv_sec;
        ts->tv_nsec = mts.tv_nsec;
#else
        clock_gettime(CLOCK_REALTIME, ts);
#endif
        
    }
    
    static double tickCount(void)
    {
        struct timespec now;
        set_current_utc_time(&now);
        
        return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
    }
    
};




/*
 
 // How to use Interval
 
 Interval i;
 while (i.value() < 10) {
    doStuff();
 }
 
*/

class Interval
{
    
public:
    // Ctor
    inline Interval() : initial_(Clock::tickCount())
    {
    }
    
    // Dtor
    virtual ~Interval()
    {
    }
    
    inline unsigned int value() const
    {
        return Clock::tickCount()-initial_;
    }
    
private:
    
    unsigned int initial_;
};







class FpsCounter
{

public:
    
    static FpsCounter* Instance();

    
    // Update
    void update()
    {
        // increase the counter by one
        m_fpscount++;
        
        // one second elapsed? (= 1000 milliseconds)
        if (m_fpsinterval.value() > 1000)
        {
            // save the current counter value to m_fps
            m_fps         = m_fpscount;
            
            // reset the counter and the interval
            m_fpscount    = 0;
            m_fpsinterval = Interval();
        }
    }
    
    // Get fps
    unsigned int get() const
    {
        return m_fps;
    }
    
protected:
    
    unsigned int m_fps;
    unsigned int m_fpscount;
    Interval m_fpsinterval;
    
    
private:
    
    // Constructor
    FpsCounter() : m_fps(0), m_fpscount(0)
    {
    }
    
    FpsCounter(FpsCounter const&){};
    FpsCounter& operator=(FpsCounter const&);
    
    static FpsCounter* m_pInstance;
    
};

#endif /* defined(__warpdriveoverloaded__Clock__) */
