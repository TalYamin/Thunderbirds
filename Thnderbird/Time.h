#pragma once

class Time
{
	long tickTime;
public:
	long getTickTime() {
		return tickTime;
	};
	void setTickTime(long newTime) {
		tickTime = newTime;
	};
	Time(long _tickTime) {
		tickTime = _tickTime;
	};
	Time();

private:

};
