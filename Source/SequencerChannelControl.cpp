#include "SequencerChannelControl.h"
#include "SliderBoxControl.h"

SequencerChannelControl::SequencerChannelControl(int numSteps, int stepsPerRow)
	: numSteps(numSteps), stepsPerRow(stepsPerRow)
{
	for (int i = 0; i < numSteps; i++) {
		auto control = new SliderBoxControl(SliderBoxControlOrientaton::Vertical);
		this->sliders.add(control);

		addAndMakeVisible(control);
		control->setSize(this->getWidth() / 4, this->getHeight() / 4);
	}

	layoutControls();
}

SequencerChannelControl::~SequencerChannelControl()
{
}

void SequencerChannelControl::resized()
{
	layoutControls();
}

void SequencerChannelControl::paint(Graphics &g)
{
	float thickness = 2.f;

	g.setColour(Colours::black);
	g.drawRect(0.f, 0.f, getWidth() - (thickness * 2.f), getHeight() - (thickness * 2.f));
}

void SequencerChannelControl::layoutControls()
{
	float padding = 5;
	float numRows = numSteps / stepsPerRow;
	float width = (float)(this->getWidth() / stepsPerRow);// - (padding * 2.f);
	float height = (float)(this->getHeight() / numRows);// - (padding * 2.f);
	int numSteps = sliders.size();

	for (int i = 0; i < numSteps; i++) {
		float x = 0;
		float y = 0;
		sliders[i]->setBounds(x, y, width, height);
	}
}