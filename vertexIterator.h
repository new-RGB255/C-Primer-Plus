#pragma once
#ifndef _VERTEX_ITERATOR_H
#define _VERTEX_ITERATOR_H

template<class T>
class vertexIterator {
public:
	virtual ~vertexIterator() {}
	virtual int next() = 0;
	virtual int next(T&) = 0;
};

#endif // !_VERTEX_ITERATOR_H
