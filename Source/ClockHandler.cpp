#include "ClockHandler.h"

void ClockHandler::handleClock(AudioPlayHead::CurrentPositionInfo &position)
{
	if (position.isPlaying) {
		int iPos = int(position.ppqPosition) * 24;

		if ((iPos % ppq) == 0) {
			this->onTrigger(iPos / ppq);
		}
	}
}