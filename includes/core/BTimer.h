/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 |

/* 
 * File:   UTime.h
 * Author: ariel
 *
 * Created on 31 de julio de 2017, 05:01 PM
 */

#ifndef UTIME_H
#define UTIME_H

//#include <BPython.h>
#include <chrono>
#include <ctime>    



class BTimer{
public:
    BTimer(void){ restart(); }
    ~BTimer(void){}
    
    inline void pause(void){ paused = true;  }
    inline void start(void){ paused = false; time_previus = std::chrono::system_clock::now(); }
    inline void restart(void){ time_accumulated = 0.0; start(); }
    inline double getTime(void){ return time_accumulated; }
    
    inline bool isPaused(void){ return paused; }

    inline void update(void){
        if(!paused){
            time_lastUpdate = std::chrono::system_clock::now() - time_previus;
            time_accumulated += time_lastUpdate.count();
            time_previus = std::chrono::system_clock::now();
        }
    }

private:
    bool paused;
    double time_accumulated;

    std::chrono::system_clock::time_point time_previus;
    std::chrono::duration<double> time_lastUpdate;
};


#endif /* UTIME_H */

