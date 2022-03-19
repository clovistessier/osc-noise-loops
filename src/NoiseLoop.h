#ifndef NOISELOOP_H
#define NOISELOOP_H

#include "ofMain.h"
#include "Scope.h"

class NoiseLoop
{
public:
    NoiseLoop()=default;
    void setup(const ofVec2f &center_, float r, float w = -1, float h = -1, const ofColor & col = ofColor::white, const string& name = "loop");
    void setup(float x_, float y_, float r);
    void update();
    void draw();

    void setCenter(const ofVec2f &newC);
    void setX(float x);
    void setY(float y);
    void setRadius(float r);
    void setAngle(float &angle_);
    void setAngleV(float v);
    void setPeriod(float& t);
    void assignScope(shared_ptr<Scope> p);
    void valueChanged(float& val);
    void centerChanged(ofVec2f& c);
    void radiusChanged(float& r);


    shared_ptr<Scope> scope;
    float angle;
    float angleV;
    ofVec2f cursor;
    ofColor color;

    ofParameter<float> value;
    ofParameter<ofVec2f> center;
    ofParameter<float> radius;
    ofParameterGroup parameters;
  
};

#endif