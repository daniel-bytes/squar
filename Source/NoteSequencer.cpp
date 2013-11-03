#include "NoteSequencer.h"

enum class NoteSequencerButtonState
{
	Off,
	On,
	OffCurrentStep,
	OnCurrentStep,
	NumTypes
};

class NoteSequencerButton
	: public Component
{
public:
	NoteSequencerButton(const String &name, int noteNumber, int step, NoteSequencerButtonState state = NoteSequencerButtonState::Off)
		: Component(name),
		  noteNumber(noteNumber), 
		  step(step),
		  state(state)
	{
	}

public:
	void paint(Graphics &graphics);
	void mouseDown (const MouseEvent &event);
	void resized() { repaint(); }

public:
	int getNoteNumber() const { return noteNumber; }
	int getStep() const { return step; }
	NoteSequencerButtonState getState() const { return state; }
	void setState(NoteSequencerButtonState value) { state = value; repaint(); }
	
	NoteSequencerButtonState toggleStateFromUI() {
		switch(state) {
			case NoteSequencerButtonState::Off:
				setState(NoteSequencerButtonState::On);
				break;
			case NoteSequencerButtonState::On:
				setState(NoteSequencerButtonState::Off);
				break;
			case NoteSequencerButtonState::OffCurrentStep:
				setState(NoteSequencerButtonState::OnCurrentStep);
				break;
			case NoteSequencerButtonState::OnCurrentStep:
				setState(NoteSequencerButtonState::OffCurrentStep);
				break;
		}

		return getState();
	}

	NoteSequencerButtonState toggleStateFromClock(bool triggered) {
		switch(state) {
			case NoteSequencerButtonState::Off:
				if (triggered) {
					setState(NoteSequencerButtonState::OffCurrentStep);
				}
				break;
			case NoteSequencerButtonState::On:
				if (triggered) {
					setState(NoteSequencerButtonState::OnCurrentStep);
				}
				break;
			case NoteSequencerButtonState::OffCurrentStep:
				if (!triggered) {
					setState(NoteSequencerButtonState::Off);
				}
				break;
			case NoteSequencerButtonState::OnCurrentStep:
				if (!triggered) {
					setState(NoteSequencerButtonState::On);
				}
				break;
		}

		return getState();
	}

	Rectangle<float> getBounds() {
		Rectangle<float> bounds(padding, padding, (float)this->getWidth() - float(padding * 2), (float)this->getHeight() - float(padding * 2));
		return bounds;
	}

public:
	static const int padding = 4;
	static const int corner = 10;
	static const int thickness = 1;

private:
	int noteNumber;
	int step;
	NoteSequencerButtonState state;
};

void NoteSequencerButton::paint(Graphics &graphics)
{
	graphics.setColour(Colours::black);
	Rectangle<float> bounds = getBounds();
	graphics.drawRoundedRectangle(bounds, corner, thickness);

	if ((int)state > 0)
	{
		if (state == NoteSequencerButtonState::OffCurrentStep) {
			graphics.setColour(Colours::lightgreen);
		}
		else {
			graphics.setColour(Colours::grey);
		}
		
		graphics.fillRoundedRectangle(bounds, corner);
	}
}

void NoteSequencerButton::mouseDown (const MouseEvent &event)
{
	auto state = toggleStateFromUI();
	NoteSequencer *parent = static_cast<NoteSequencer*>(this->getParentComponent());
	parent->buttonStateChanged(this);
	this->repaint();
}

//---------------------------------------------------------------------------

NoteSequencer::NoteSequencer(int numNotes, int numSteps, int clockResolution)
	: ClockHandler(clockResolution), numNotes(numNotes), numSteps(numSteps)
{
	pitches.resize(numSteps);
	velocities.resize(numSteps);

	const int width = getWidth() / numSteps;
	const int height = getHeight() / numNotes;
	
	for (int step = 0; step < numSteps; step++) {
		for (int note = 0; note < numNotes; note++) {
			String buttonName;
			buttonName << "Note " << note << " Step " << step;
			NoteSequencerButton *button = new NoteSequencerButton(buttonName, note, step);
			button->toggleStateFromClock(step == 0);

			int x = step * width;
			int y = note * height;

			button->setBounds(x, y, width, height);
			buttons.add(button);
			addAndMakeVisible(button);
		}
	}
}

NoteSequencer::~NoteSequencer()
{
	for (auto b : buttons) {
		delete b;
	}
}

void NoteSequencer::resized()
{
	const int width = getWidth() / numSteps;
	const int height = getHeight() / numNotes;
	
	for (int step = 0; step < numSteps; step++) {
		for (int note = 0; note < numNotes; note++) {
			int index = getButtonIndex(step, note);
			auto button = buttons[index];

			int x = step * width;
			int y = note * height;

			button->setBounds(x, y, width, height);
		}
	}
}

void NoteSequencer::onTrigger(int step)
{
	int index = step % numSteps;

	for (auto listener : listeners) {
		if (velocities[index] > 0) {
			listener->handleNoteSequencer(pitches[index], velocities[index]);
		}
	}

	for (auto b : buttons) {
		b->toggleStateFromClock(b->getStep() == index);
	}
}

void NoteSequencer::buttonStateChanged(const NoteSequencerButton *button)
{
	pitches.set(button->getStep(), button->getNoteNumber());
	velocities.set(button->getStep(), button->getState() == NoteSequencerButtonState::On ? 127 : 0);

	if (button->getState() == NoteSequencerButtonState::On || button->getState() == NoteSequencerButtonState::OnCurrentStep) {
		for (auto b : buttons) {
			if (b != button && b->getStep() == button->getStep()) {
				if (b->getState() == NoteSequencerButtonState::On) {
					b->setState(NoteSequencerButtonState::Off);
				}
				else if (b->getState() == NoteSequencerButtonState::OnCurrentStep) {
					b->setState(NoteSequencerButtonState::OffCurrentStep);
				}
			}
		}
	}
}

void NoteSequencer::paint(Graphics &graphics)
{
	graphics.setColour(Colours::black);
	graphics.drawRect(0.f, 0.f, (float)getWidth(), (float)getHeight(), 1.f);

	graphics.setColour(Colours::slategrey);

	// draw vertical lines every 4 steps
	int steps = (numSteps / 4);
	int stepWidth = getWidth() / steps;

	for (int i = 1; i < steps; i++) {
		int start = (i * stepWidth);
		graphics.drawLine(start, 0, start, getHeight(), 1.f);
	}

	// draw horizontal lines every 4 notes
	steps = (numNotes / 4);
	stepWidth = getHeight() / steps;

	for (int i = 1; i < steps; i++) {
		int start = (i * stepWidth);
		graphics.drawLine(0, start, getWidth(), start, 1.f);
	}
}