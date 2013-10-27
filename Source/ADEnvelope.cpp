#include "ADEnvelope.h"
#include "Utilities.h"
#include <cmath>

float ADEnvelope::process(float input, int channel)
{
	float result = 0.f;

	switch(this->state)
	{
	case kADEnvelopeState_Rising:
		{
			float maxEnv = (1.f / sampleRate);
			float inc = scale(attack, maxEnv * (sampleRate / 10.0), maxEnv * .25f);

			if ((level += inc) >= 1.0) {
				state = kADEnvelopeState_Falling;
				level = 1;
			}

			result = (level * level);
			//return log(level) / log(2);
		}
	case kADEnvelopeState_Falling:
		{
			float maxEnv = (1.f / sampleRate);
			float inc = scale(decay, maxEnv * 25.f, maxEnv * .25f);

			if ((level -= inc) <= 0.0) {
				state = kADEnvelopeState_Off;
				level = 0;
			}

			result = level;
			//return log(level) / log(2.0);
			//return (level * level);
			//return log(level);
		}
	}

	return result;
}
