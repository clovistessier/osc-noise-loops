#ifndef NOISEFIELD_H
#define NOISEFIELD_H

#include "ofMain.h"
#include "NoiseLoop.h"
#include "Scope.h"

#define SCOPE_HEIGHT 100

class NoiseField
{
private:
    float height;
    float width;
    ofFloatImage img;
    bool bIsChanged;
    float z;
    vector<NoiseLoop*> loops;
    float angleV;
    vector<shared_ptr<Scope>> scopes;
    uint64_t lastTriggered;
    float targetPeriod;
    int cBeat;

public:
    NoiseField() = default;
    void setup();
    void update();
    void draw();
    void setScaleFactor(float sf);
    ofVec2f getCenter();
    float getVal(const ofVec2f &pos);
    float getWidth();
    float getHeight();
    void incZ();
    void setZ(float newZ);
    void setDz(float newDz);
    void sfChanged(float &sf);
    // void assignLoop(shared_ptr<NoiseLoop> loop);
    void assignLoop(NoiseLoop& loop);
    void assignScope(NoiseLoop& loop);
    void setAngleV(float &t);
    void getVals(vector<float>& results);
    void setAngle(float &a);
    void resync();
    void trigger(bool& in);

    ofParameter<float> scaleFactor;
    ofParameter<float> period;
    ofParameter<float> dz;
    ofParameter<float> angle;
    ofParameter<int> nBeats;
    ofParameter<bool> bpmSync;
    ofParameterGroup parameters;
};

#endif