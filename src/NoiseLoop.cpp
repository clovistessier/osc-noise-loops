#include "NoiseLoop.h"

void NoiseLoop::setup(const ofVec2f &center_, float r, float w, float h, const ofColor &col, const string& name)
{
    if (w == -1)
    {
        w = ofGetWidth();
    }
    if (h == -1)
    {
        h = ofGetHeight();
    }

    angle = 0;
    angleV = 0;

    color = col;

    parameters.setName(name);
    parameters.add(center.set("center", center_, ofVec2f(0, 0), ofVec2f(w, h)));
    parameters.add(radius.set("radius", r, 1.0f, min(w, h) / 2));
    
    value.set(0);
    value.addListener(this, &NoiseLoop::valueChanged);
    center.addListener(this, &NoiseLoop::centerChanged);
    radius.addListener(this, &NoiseLoop::radiusChanged);
}

void NoiseLoop::setup(float x_, float y_, float r)
{
    setup(ofVec2f(x_, y_), r);
}

void NoiseLoop::update()
{
    angle += angleV;
    cursor.x = center->x + cosf(angle) * radius;
    cursor.y = center->y + sinf(angle) * radius;
}

void NoiseLoop::setAngle(float &angle_)
{
    angle = angle_;
    cursor.x = center->x + cosf(angle) * radius;
    cursor.y = center->y + sinf(angle) * radius;
}

void NoiseLoop::draw()
{
    ofPushStyle();

    ofEnableSmoothing();

    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(color);
    ofSetCircleResolution(100);

    ofDrawCircle(center.get(), radius.get());

    ofFill();
    ofDrawCircle(cursor, 4);

    ofPopStyle();
}

void NoiseLoop::setCenter(const ofVec2f &newC)
{
    center = newC;
}

void NoiseLoop::setX(float x)
{
    center.set(ofVec2f(x, center->y));
}

void NoiseLoop::setY(float y)
{
    center.set(ofVec2f(center->x, y));
}

void NoiseLoop::setRadius(float r)
{
    radius = r;
}

void NoiseLoop::setAngleV(float v)
{
    angleV = v;
}

void NoiseLoop::setPeriod(float &t)
{
    float fr = ofGetFrameRate();
    float nFrames = t * fr; // frames per period
    angleV = TWO_PI / nFrames;
}

void NoiseLoop::assignScope(shared_ptr<Scope> p)
{
    scope = p;
}

void NoiseLoop::valueChanged(float &val)
{
    if (scope != nullptr)
    {
        scope->update(value.get(), angle);
    }
}

void NoiseLoop::centerChanged(ofVec2f &c)
{
    if (scope != nullptr)
    {
        scope->clearHistory();
    }
}

void NoiseLoop::radiusChanged(float &r)
{
    if (scope != nullptr)
    {
        scope->clearHistory();
    }
}

//----------------------------------------------------
