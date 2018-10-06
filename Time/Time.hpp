struct Time
{
	int hours;
	int minutes;
	
	// Method returns the time delta between dep and arr time arguments
	static Time getDeltaTime(Time dep, Time arr) {
		if (dep.hours > arr.hours) {
			arr.hours += 24;
		}

		Time difference;
		difference.hours = arr.hours - dep.hours - 1;
		difference.minutes = arr.minutes + (60 - dep.minutes);
		if (difference.minutes >= 60) {
			difference.hours++;
			difference.minutes = difference.minutes - 60;
		}

		return difference;
	}

	//	Method returns the greater of the two time arguments
	static Time greater(Time t1, Time t2) {
		if (t1.hours < t2.hours) {
			return t2;
		}
		else if (t1.hours > t2.hours) {
			return t1;
		}
		else {
			return t1.minutes >= t2.minutes ? t1 : t2;
		}
	}

	//	Method returns the smaller of the two time arguments
	static Time lesser(Time t1, Time t2) {
		if (t1.hours < t2.hours) {
			return t1;
		}
		else if (t1.hours > t2.hours) {
			return t2;
		}
		else {
			return t1.minutes >= t2.minutes ? t2 : t1;
		}
	}
};