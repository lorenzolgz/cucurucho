#ifndef CUCURUCHO_COLABLOQUEANTE_H
#define CUCURUCHO_COLABLOQUEANTE_H


#include <mutex>
#include <condition_variable>
#include <deque>

// Las definiciones estan puestas aca porque C++ es una garcha. Si queres saber mas leete esto: https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor.

template <typename T>
class ColaBloqueante {
public:
	void push(T const& value)  {
		std::unique_lock<std::mutex> lock(this->d_mutex);
		d_queue.push_front(value);
		this->d_condition.notify_all();
	}
	void push_back(T const& value)  {
		std::unique_lock<std::mutex> lock(this->d_mutex);
		d_queue.push_back(value);
		this->d_condition.notify_all();
	}
	T pop(int cant = -1) {
		std::unique_lock<std::mutex> lock(this->d_mutex);
		this->d_condition.wait(lock, [=] { return !this->d_queue.empty(); });

		if (cant == -1) {
			T rc(std::move(this->d_queue.back()));
			this->d_queue.pop_back();
			return rc;
		} else {
			while (true) {
				T rc(std::move(this->d_queue.back()));
				this->d_queue.pop_back();
				if (d_queue.size() <= cant) {
					return rc;
				}
			}
		}
	}

	bool empty() {
		std::unique_lock<std::mutex> lock(this->d_mutex);
		return d_queue.empty();
	}

    int size() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        return d_queue.size();
    }

private:
	std::mutex              d_mutex;
	std::condition_variable d_condition;
	std::deque<T>           d_queue;
};


#endif //CUCURUCHO_COLABLOQUEANTE_H
