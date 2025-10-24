#pragma once
#include <iostream>
#include <vector>
#include <functional>

template<typename ...Args>
class Event
{
public:
	void Subscribe(std::function<void(Args...)> a_callback)
	{
		m_subscribers.push_back(a_callback);
	}

	void Invoke(Args... a_invokeValue)
	{
		for (auto& func : m_subscribers)
		{
			if (func) //If not empty
				func(a_invokeValue...);
		}
	}

	void operator +=(std::function<void(Args...)> a_callback)
	{
		this->Subscribe(a_callback);
	}


private:
	std::vector<std::function<void(Args...)>> m_subscribers{};
};