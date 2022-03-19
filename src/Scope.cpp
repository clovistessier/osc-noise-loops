#include "Scope.h"

void Scope::setup(float x_, float y_, float w_, float h_, const ofColor &col)
{
    if (w_ == -1)
    {
        w = ofGetWidth();
    }
    x = x_;
    y = y_;
    w = w_;
    h = h_;
    val = 0.5;
    cursor = ofVec2f(0, 0);
    trace.clear();
    olds_max = 10;
    color = col;
}

void Scope::update(float v, float a)
{
    float old = cursor.x;
    cursor.x = ofMap(a, 0, TWO_PI, x, x + w);
    if (cursor.x < old) // if we wrapped over the edge of the window
    {
        history.push_front(trace);
        if (history.size() > olds_max)
        {
            history.pop_back();
        }

        trace.clear();
    }
    val = v;
    cursor.y = ofMap(val, 0.0f, 1.0f, y + h, y);
    trace.addVertex(cursor.x, cursor.y);
}

void Scope::update(float v)
{
    float angle = ofMap(cursor.x + 1, 0, w, 0, TWO_PI);
    while (angle > TWO_PI)
    {
        angle -= TWO_PI;
    }
    update(v, angle);
}

void Scope::draw()
{
    ofPushStyle();
    ofFill();

    int alpha = 255;
    ofSetColor(color, alpha);

    trace.draw();
    ofDrawCircle(cursor, 2);

    for (auto i : history)
    {
        alpha *= 0.80;
        ofSetColor(color, alpha);
        i.draw();
    }

    ofPopStyle();
}

void Scope::clearHistory()
{
    history.clear();
}