#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);

    field.setup();

    for (int i = 0; i < NUM_LOOPS; i++)
    {
        noiseVals.push_back(0.0);
    }



    xf.setup(noiseVals);
    mix.setup(noiseVals);
    
    clock.setup();
    clock.output.addListener(&field, &NoiseField::trigger);
    clock.start();

    gui.setup();
    gui.add(field.parameters);
    gui.add(clock.parameters);
    gui.add(xf.parameters);
    gui.add(mix.parameters);

    ofColor colors[] = {ofColor::red,    ofColor::orange, ofColor::green, 
                        ofColor::yellow, ofColor::blue,   ofColor::purple};
    string names[] = {"red", "orange", "green", "yellow", "blue", "purple"};

    loop_params.setName("Loops");

    for (int i = 0; i < NUM_LOOPS; i++)
    {
        float range = (field.getWidth() / 2) / NUM_LOOPS;
        float r = ofRandom(i*range, (i+1)*range);
        loops[i].setup(field.getCenter(), r, field.getWidth(), field.getHeight(), colors[i], names[i]);
        field.assignLoop(loops[i]);
        mix.setName(i, names[i]);
        loop_params.add(loops[i].parameters);
    }

    gui.add(loop_params);

    sender.setup("localhost", SEND_PORT);
    receiver.setup(RECEIVE_PORT);

    bDrawGui = true;
}

//--------------------------------------------------------------
void ofApp::update()
{
    field.update();
    field.getVals(noiseVals);

    while(receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        receiver.getNextMessage(m);

        if (m.getAddress() == "/noiseloop/xfader")
        {
            xf.set(m.getArgAsFloat(0));
        }
    }

    xf.update();
    mix.update();

    ofxOscMessage m;
    m.setAddress("/noiseloop");
    for (auto val : noiseVals)
    {
        m.addFloatArg(val);
    }
    m.addFloatArg(xf.get());
    m.addFloatArg(mix.get());

    sender.sendMessage(m, false);

    m.clear();
    m.setAddress("/clock");
    m.addBoolArg(clock.output.get());
    sender.sendMessage(m, false);

    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    field.draw();

    if (bDrawGui == true)
    {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
        case 'g':
        bDrawGui = !bDrawGui;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
