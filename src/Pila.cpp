#include "Basics.h"
#include "Pila.h"

void Pila::push(int i) {
	_pila.push_back(i);
	_size++;
}

int Pila::pop() {
	int res;
	if (_size == 0) {
		res = 0;
	} else {
		res = _pila[_size-1];
		_pila.pop_back();
		_size--;
	}
	return res;
}

int Pila::size() {
	return _size;
}