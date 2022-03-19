#include "Clocker.h"

inline uint64_t hz2ns(const float &f)
{
    return static_cast<uint64_t>(1.0 / f * 1000000000);
}

Clocker::Clocker()
{
    freq = 1.0f;
    timer.setPeriodicEvent(hz2ns(freq) / 2);
    startThread();
}

void Clocker::setup(const float &f)
{
    freq.addListener(this, &Clocker::setFrequency);
    bpm.addListener(this, &Clocker::bpmChanged);

    parameters.setName("Clock");
    parameters.add(bpm.set("bpm", f, 1, 240));
    parameters.add(stopped.set("stop", true));
    parameters.add(output.set("out", false));
}

void Clocker::start()
{
    stopped = false;
}

void ::Clocker::stop()
{
    stopped = true;
}

bool Clocker::isRunning()
{
    return !(stopped.get());
}

void Clocker::reset()
{
    timer.reset();
}

void Clocker::setFrequency(float &f)
{
    timer.setPeriodicEvent(hz2ns(f) / 2);
    // timer.reset();
}

void Clocker::threadedFunction()
{
    while (isThreadRunning())
    {
        timer.waitNext();
        if (isRunning())
        {
            output = !(output.get());
        }
        else
        {
            output = false;
        }
    }
}

void Clocker::bpmChanged(float &new_bpm)
{
    freq = new_bpm / 60.0;
}

Clocker::~Clocker()
{
    waitForThread(true, INFINITE_JOIN_TIMEOUT);
}