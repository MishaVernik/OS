#pragma once
class CommonData
{
private:
	static int globalCounter;

public:
	CommonData() {

	}

	static int WAITING_TIME() {
		return 1;
	}
	static int GLOBAL_TIMER() {
		return 1;
	}
	static int CURRENT_PROCESS() {
		return 1;
	}

	static int GET_GLOBAL_COUNTER() {
		return globalCounter;
	}
	static void SET_GLOBAL_COUNTER(int value) {
		globalCounter = globalCounter + value;
	}
};

