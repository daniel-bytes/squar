#include "ADEnvelope.h"
#include "Utilities.h"
#include <cmath>

float ADEnvelope::process(float input, int channel)
{
	float result = 0.f;

	switch(this->state)
	{
	case ADEnvelopeState::Rising:
		{
			float maxEnv = (1.f / sampleRate);
			float inc = scale<float>(attack, maxEnv * (sampleRate / 10.0f), maxEnv * .25f);

			if ((level += inc) >= 1.0) {
				state = ADEnvelopeState::Falling;
				level = 1;
			}

			result = (level * level);
			//return log(level) / log(2);
		}
	case ADEnvelopeState::Falling:
		{
			float maxEnv = (1.f / sampleRate);
			float inc = scale(decay, maxEnv * 25.f, maxEnv * .25f);

			if ((level -= inc) <= 0.0) {
				state = ADEnvelopeState::Off;
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
