#ifndef DELTATIME_H
#define DELTATIME_H

#include "../Window.h"

class DeltaTime
{
public:
	DeltaTime() = delete;
	static float m_CurrentTime;
	static float m_PreviousTime;
	static float m_DeltaTime;
	static int m_SecondsChecker;
	static void CalculateDeltaTime()
	{
		m_CurrentTime = glfwGetTime();
		m_DeltaTime = m_CurrentTime - m_PreviousTime;
		m_PreviousTime = m_CurrentTime;
	}
};


#endif