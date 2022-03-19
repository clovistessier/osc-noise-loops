#ifndef CLOCKER_H
#define CLOCKER_H

#include "ofMain.h"

inline uint64_t hz2ns(const float &f);

class Clocker : ofThread
{
public:
    Clocker();
    void setup(const float &f = 120.0f);
    void setFrequency(float &f);
    void reset();
    void start();
    void stop();
    bool isRunning();
    void bpmChanged(float &new_bpm);
    ~Clocker();

    ofParameterGroup parameters;
    ofParameter<bool> output;
    ofParameter<float> freq;
    ofParameter<bool> stopped;
    ofParameter<float> bpm;

private:
    ofTimer timer;
    void threadedFunction();
};

#endif