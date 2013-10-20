#include "ADEnvelope.h"
#include "Utilities.h"

float ADEnvelope::process(float input, int channel)
{
	switch(this->state)
	{
	case kADEnvelopeState_Rising:
		{
			float inc = (1.f / sampleRate);// * scale(attack, sampleRate, 1.f);

			if ((level += inc) >= 1.0) {
				state = kADEnvelopeState_Falling;
				level = 1;
			}

			return (level * level);
		}
	case kADEnvelopeState_Falling:
		{
			float inc = (1.f / sampleRate);// * scale(decay, sampleRate, 1.f);

			if ((level -= inc) <= 0.0) {
				state = kADEnvelopeState_Off;
				level = 0;
			}

			return (level * level);
		}

	default:
		{
			return 0;
		}
	}
}
