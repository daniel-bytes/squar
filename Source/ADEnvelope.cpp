#include "ADEnvelope.h"
#include "Utilities.h"
#include <cmath>

float ADEnvelope::process(float input, int channel)
{
	switch(this->state)
	{
	case kADEnvelopeState_Rising:
		{
			float maxEnv = (1.f / sampleRate);
			float inc = scale(attack, maxEnv * 10.f, maxEnv * .25f);

			if ((level += inc) >= 1.0) {
				state = kADEnvelopeState_Falling;
				level = 1;
			}

			return log(level);
		}
	case kADEnvelopeState_Falling:
		{
			float maxEnv = (1.f / sampleRate);
			float inc = scale(decay, maxEnv * 10.f, maxEnv * .25f);

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
