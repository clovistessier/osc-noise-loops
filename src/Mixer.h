#ifndef MIXER_H
#define MIXER_H

#include "ofMain.h"

#define GAIN_MAX 2.0f

class Mixer
{
public:
    Mixer();
    void setup(vector<float> &in);
    void set(int input_num, float level);
    void setName(int input_num, const string &name);
    void update();
    void levelChanged(float &level);
    float get();
    ~Mixer();

    ofParameterGroup parameters;
    ofParameter<float> gain;
    ofParameter<float> offset;
    ofParameterGroup levels;

    ofParameter<float> output;

private:
    vector<float> *inputs;
    bool initialized;
};

// N input crossfader

class Xfader
{
public:
    Xfader();
    void setup(vector<float> &in);
    void set(float &level);
    void update();
    void enableCircular(bool cir);
    void faderChanged(float &fader);
    void smoothingChanged(float &smooth);
    float get();
    ~Xfader();

    ofParameterGroup parameters;
    ofParameter<float> fader;
    ofParameter<bool> circular;
    ofParameter<float> smoothing;

    ofParameter<float> output;

private:
    vector<float> *inputs;
    float fader_follower;
};

#endif