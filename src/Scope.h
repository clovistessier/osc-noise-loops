#ifndef SCOPE_H
#define SCOPE_H

#include "ofMain.h"

class Scope
{
private:
    float x, y, w, h;
    float val;
    ofVec2f cursor;
    ofPolyline trace;
    std::deque<ofPolyline> history;
    int olds_max;
    ofColor color;

public:
    Scope() = default;
    void setup(float x_, float y_, float w_ = -1, float h_ = 100, const ofColor& col = ofColor::white);
    void update(float v);
    void update(float v, float a);
    void draw();
    void clearHistory();
};

#endif