#include <iostream>
#include <stdexcept>
#include <stdexcept>

template <class T>
class TQueue {
	public:
		T* _data;
		size_t _size;
		size_t _top;
		size_t _current;
		size_t _capacity;
	public:
		TQueue(size_t size = 10);
		~TQueue();
		inline bool is_Empty() const noexcept;
		inline bool is_Full() const noexcept;
		void push(T value);
		void pop();
		int current() const noexcept;
		int top() const noexcept;
};

template <class T>
TQueue<T>::TQueue(size_t size) {
	_data = new T[size];
	_capacity = size;
	_size = 0;
	_top = -1;
	_current = 0;
}

template <class T>
TQueue<T>::~TQueue() {
	delete[] _data;
}

template <class T>
inline bool TQueue<T>::is_Empty() const noexcept {
	return _size == 0;
}

template <class T>
inline bool TQueue<T>::is_Full() const noexcept {
	return _size == _capacity;
}

template <class T>
void TQueue<T>::push(T value) {
	if (is_Full())
		throw std::overflow_error("TStack is full");
	_top = (_top + 1) % _capacity;
	_data[_top] = value;
	_size++;
}

template <class T>
void TQueue<T>::pop() {
	if (is_Empty())
		throw std::overflow_error("TStack is empty");
	_current = (_current + 1) % _capacity;
	_size--;
}

template <class T>
int TQueue<T>::top() const noexcept{
	return _data[_top];
}

template <class T>
int TQueue<T>::current() const noexcept {
	return _data[_current];
}
