#pragma once

template<typename T>
class SingleTon
{
private:
	static T* instance;

protected:
	SingleTon() {}
	virtual ~SingleTon() { }

public:
	static T * getInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

	static void destroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};
template<typename T> T* SingleTon<T>::instance = nullptr;