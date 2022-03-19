#include "Mixer.h"

Mixer::Mixer()
{
    inputs = nullptr;
    initialized = false;
}

void Mixer::setup(vector<float> &in)
{
    inputs = &in;

    parameters.setName("mixer");
    parameters.add(gain.set("gain", 1.0f, 0.0f, GAIN_MAX));
    parameters.add(offset.set("offset", 0.0f, -1.0f, 1.0f));


    levels.setName("levels");

    for (int i = 0; i < inputs->size(); i++)
    {
        ofParameter<float> level;
        // ofParameter<float> level;
        const char name = '0' + i;
        levels.add(level.set(&name, 0.0f, -1.0f, 1.0f));
        level.addListener(this, &Mixer::levelChanged);
    }
    parameters.add(levels);

    gain.addListener(this, &Mixer::levelChanged);
    offset.addListener(this, &Mixer::levelChanged);
    initialized = true;
}

void Mixer::update()
{
    if (!initialized)
    {
        return;
    }
    float temp = 0;

    for (int i = 0; i < inputs->size(); i++)
    {
        temp += inputs->at(i) * levels.get(i).cast<float>().get();
    }
    temp *= gain.get();

    temp = ofClamp(temp + offset.get(), 0.0f, 1.0f);
    output = temp;
}

void Mixer::set(int input_num, float level)
{
    if (!initialized)
    {
        return;
    }
    if (input_num < 0 || input_num >= inputs->size())
    {
        return;
    }
    levels.get(input_num).cast<float>().set(level);

}

void Mixer::setName(int input_num, const string &name)
{
    if (!initialized)
    {
        return;
    }
    if (input_num < 0 || input_num >= inputs->size())
    {
        return;
    }
    levels.get(input_num).cast<float>().setName(name);
}

float Mixer::get()
{
    return output.get();
}

void Mixer::levelChanged(float &level)
{
    update();
}

Mixer::~Mixer()
{
    inputs = nullptr;
}

//-----------------------------------------------------------------------------------
Xfader::Xfader()
{
    inputs = nullptr;
}

void Xfader::setup(vector<float> &in)
{
    inputs = &in;

    parameters.setName("crossfader");
    parameters.add(fader.set("fader", 0.0f, 0.0f, 1.0f));
    parameters.add(circular.set("circular", false));
    parameters.add(smoothing.set("smoothing", 0.0f, 0.0f, 0.999f));

    fader_follower = fader.get();

    fader.addListener(this, &Xfader::faderChanged);
    smoothing.addListener(this, &Xfader::smoothingChanged);
}

// level should be normalized to [0.0, 1.0]
void Xfader::set(float &level)
{
    fader = level;
    // update will be called bc addListener
}

void Xfader::faderChanged(float &fader)
{
    update();
}

float Xfader::get()
{
    return output.get();
}

void Xfader::smoothingChanged(float &smooth)
{
    update();
}

void Xfader::update()
{

    if (inputs == nullptr)
    {
        return;
    }

    fader_follower = ofLerp(fader_follower, fader, 1.0 - smoothing.get());

    size_t nIns = inputs->size() - 1;

    if (circular == true)
    {
        nIns += 1;
    }

    float faderIndex = fader_follower * nIns;
    int leftIndex = static_cast<int>(floor(faderIndex)) % inputs->size();
    int rightIndex = static_cast<int>(ceil(faderIndex)) % inputs->size();
    float left = inputs->at(leftIndex);
    float right = inputs->at(rightIndex);

    output = ofLerp(left, right, faderIndex - leftIndex);
}

void Xfader::enableCircular(bool cir)
{
    circular = cir;
}

Xfader::~Xfader()
{
    inputs = nullptr;
}