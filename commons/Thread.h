#ifndef CUCURUCHO_THREAD_H
#define CUCURUCHO_THREAD_H


#include <thread>

class Thread {
public:
	void start();
	void join();
	virtual void run() = 0;

private:
	std::thread thread;
};


#endif //CUCURUCHO_THREAD_H
