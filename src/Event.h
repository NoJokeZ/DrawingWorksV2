/*****************************************************************************
* Project: DrawingWorksV2
* File : Event.h
* Date : 09.09.2025
* Author : Bastian Pfaller (BP)
*
* A custom simple event class that allows subscribing of functions
* and the ability to invoke the event.
*
* History:
* 09.09.25 BP Created
******************************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include <functional>

template<typename ...Args>
class Event
{
public:
	/// <summary>
	/// Subscribes a funtction to an event
	/// </summary>
	/// <param name="a_callback"></param>
	void Subscribe(std::function<void(Args...)> a_callback)
	{
		m_subscribers.push_back(a_callback);
	}

	/// <summary>
	/// Raises the event
	/// </summary>
	/// <param name="...a_invokeValue"></param>
	void Invoke(Args... a_invokeValue)
	{
		for (auto& func : m_subscribers)
		{
			if (func) //If not empty
				func(a_invokeValue...);
		}
	}

	/// <summary>
	/// Subscribes a funtction to an event
	/// </summary>
	/// <param name="a_callback"></param>
	void operator +=(std::function<void(Args...)> a_callback)
	{
		this->Subscribe(a_callback);
	}


private:
	std::vector<std::function<void(Args...)>> m_subscribers{};
};