#pragma once

class IEventListener
{
public:
	virtual void HandleEvent() = 0;
	virtual ~IEventListener() {}
};