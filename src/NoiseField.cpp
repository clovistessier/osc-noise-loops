#include "NoiseField.h"

void NoiseField::setup()
{
    width = ofGetWidth() / 2;
    height = ofGetHeight();
    img.allocate(width, height, OF_IMAGE_GRAYSCALE);
    bIsChanged = true;
    z = 0.0;
    angle = 0.0;
    angleV = 0.0;
    cBeat = 0;

    scaleFactor.addListener(this, &NoiseField::sfChanged);
    period.addListener(this, &NoiseField::setAngleV);

    parameters.setName("Noise Field");
    parameters.add(scaleFactor.set("scale", 0.005, 0.0001, 0.5));
    parameters.add(period.set("period", 10.0f, 0.01, 60.0f));
    parameters.add(dz.set("dz", 0.025, -0.5, 0.5));
    parameters.add(bpmSync.set("BPM Sync", false));
    parameters.add(nBeats.set("num beats", 4, 1, 100));

    targetPeriod = period.get();
}

void NoiseField::update()
{
    angle += angleV;

    while (angle.get() > TWO_PI)
    {
        angle -= TWO_PI;
        incZ();
    }

    for (auto loop : loops)
    {
        float noiseVal = getVal(loop->cursor);
        loop->value.set(noiseVal);
    }

    if (bIsChanged)
    {
        ofFloatPixels pix = img.getPixels();
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                ofFloatColor noise = ofNoise(x * scaleFactor, y * scaleFactor, z);
                pix.setColor(x, y, noise);
            }
        }
        img.setFromPixels(pix);
        img.update();
        bIsChanged = false;
    }

    //period = ofLerp(period, targetPeriod, 0.1);
}

void NoiseField::draw()
{
    img.draw(0, 0);
    for (auto loop : loops)
    {
        loop->draw();
    }
    for (auto scope : scopes)
    {
        scope->draw();
    }
}

void NoiseField::setScaleFactor(float sf)
{
    scaleFactor = sf;
    bIsChanged = true;
}

float NoiseField::getVal(const ofVec2f &pos)
{
    return img.getPixels().getColor(pos.x, pos.y).getBrightness();
}

float NoiseField::getWidth()
{
    return width;
}

float NoiseField::getHeight()
{
    return height;
}

ofVec2f NoiseField::getCenter()
{
    return ofVec2f(width / 2, height / 2);
}

void NoiseField::incZ()
{
    z += dz;
    bIsChanged = true;
}

void NoiseField::setZ(float newZ)
{
    z = newZ;
    bIsChanged = true;
}

void NoiseField::setDz(float newDz)
{
    dz = newDz;
}

void NoiseField::sfChanged(float &sf)
{
    bIsChanged = true;
    for (auto scope : scopes)
    {
        scope->clearHistory();
    }
}




// void NoiseField::assignLoop(shared_ptr<NoiseLoop> p)
// {
//     auto loop = p;
//     loops.push_back(loop);
//     float t = period.get();
//     loop->setPeriod(t);
//     period.addListener(loop.get(), &NoiseLoop::setPeriod);
//     angle.addListener(loop.get(), &NoiseLoop::setAngle);

//     int nScopes = scopes.size() / sizeof(Scope);
//     float next_y = height + (nScopes * SCOPE_HEIGHT);

//     Scope s;
//     s.setup(0, next_y, width, SCOPE_HEIGHT, loop->color);
//     auto scope = make_shared<Scope>(s);
//     loop->assignScope(scope);
//     scopes.push_back(scope);
// }

void NoiseField::assignLoop(NoiseLoop& loop)
{
    loops.push_back(&loop);
    float t = period.get();
    loop.setPeriod(t);
    period.addListener(&loop, &NoiseLoop::setPeriod);
    angle.addListener(&loop, &NoiseLoop::setAngle);

    assignScope(loop);
}

void NoiseField::assignScope(NoiseLoop& loop)
{
    int nScopes = scopes.size();
    float next_y = 0 + (nScopes * SCOPE_HEIGHT);

    Scope s;
    s.setup(width, next_y, ofGetWidth() - width, SCOPE_HEIGHT, loop.color);
    auto scope = make_shared<Scope>(s);
    loop.assignScope(scope);
    scopes.push_back(scope);
}

void NoiseField::setAngleV(float &t)
{
    float fr = ofGetFrameRate();
    float nFrames = t * fr; // frames per period
    angleV = TWO_PI / nFrames;
}

void NoiseField::getVals(vector<float>& results)
{
    results.clear();
    for (auto loop : loops)
    {
        results.push_back(getVal(loop->cursor));
    }
}

void NoiseField::setAngle(float &a)
{
    angle = a;
}


void NoiseField::resync()
{
    angle = 0.0f;
}

void NoiseField::trigger(bool& in)
{
    if ((bpmSync.get() == true) && (in == true)) // clock transitioned to high
    {
        cBeat = (cBeat + 1) % nBeats;
        if (cBeat == 0)
        {
            resync();
        }
        period = ((ofGetElapsedTimeMicros() - lastTriggered) / 1000000.0f) * nBeats.get();
        lastTriggered = ofGetElapsedTimeMicros();
    }
}
