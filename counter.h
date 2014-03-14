/*
 * counter.h
 *
 *  Created on: 03 Apr 2012
 *      Author: simon
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#include <iostream>
#include <string>
#include <typeinfo>

namespace sjp {

template <typename T>
struct counter
{
	static std::size_t objects_created;
	static std::size_t objects_alive;
	static std::size_t objects_destroyed;
	counter()
		{ ++objects_created; ++objects_alive; }

	static void print_counts(std::ostream & out, const std::string & type)
	{
		out << "Created " << objects_created << ' ' << type << "(s). "
			<< "Destroyed " << objects_destroyed << ". "
			<< objects_alive << " still alive." << std::endl;
	}
protected:
	~counter() // objects should never be removed through pointers of this type
		{ --objects_alive; ++objects_destroyed; }
};

template <typename T> std::size_t counter<T>::objects_created( 0 );
template <typename T> std::size_t counter<T>::objects_destroyed( 0 );
template <typename T> std::size_t counter<T>::objects_alive( 0 );

};

#endif /* COUNTER_H_ */
