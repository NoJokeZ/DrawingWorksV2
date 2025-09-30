#pragma once
#include <iostream>
#include <vector>
#include <functional>

template<typename ...Args>
class Event
{
public:
	void Subscribe(std::function<void(Args...)> callback)
	{
		m_subscribers.push_back(callback);
	}

	void Invoke(Args... invokeValue)
	{
		for (auto& func : m_subscribers)
		{
			if (func) //If not empty
				func(invokeValue...);
		}
	}

	void operator +=(std::function<void(Args...)> callback)
	{
		this->Subscribe(callback);
	}


private:
	std::vector<std::function<void(Args...)>> m_subscribers{};
};

