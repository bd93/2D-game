#ifndef METEORITE_H
#define METEORITE_H


#include "Object.h"


class Meteorite: public Object
{
private:
	bool m_Destroyed;
public:
	Meteorite(glm::vec2 position, glm::vec2 size)
		: Object(position, size), m_Destroyed(false)
	{
	}
	bool& IsDestroyed()
	{
		return m_Destroyed;
	}
};


#endif