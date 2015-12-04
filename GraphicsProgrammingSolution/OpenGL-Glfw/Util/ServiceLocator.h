#pragma once
#include <unordered_map>
#include <string>
#define Services ServiceLocator::Instance()

class ServiceLocator
{
public:
	~ServiceLocator();

	static ServiceLocator & Instance()
	{
		return instance;
	}

	template <class B, class D>
	void Set(D * instance)
	{
		static_assert(!std::is_abstract<D>::value, "Service Locator : Can't use an abstract class!");
		static_assert(std::is_base_of<B, D>::value, "Service Locator : Error derived class does not extend base class!");
		services.insert({ typeid(B).name(),reinterpret_cast<void*>(instance) });
	}

	template <class B, class D>
	void Set()
	{
		static_assert(std::is_default_constructible<D>::value, "Service Locator : Must be able to default construct the class!");
		static_assert(!std::is_abstract<D>::value, "Service Locator : Can't use an abstract class!");
		static_assert(std::is_base_of<B, D>::value, "Service Locator : Error derived class does not extend base class!");
		services.insert({ typeid(B).name(),reinterpret_cast<void*>(new D())});
	}

	
	void CleanUp()
	{
		for (auto service : services)
		{
			delete service.second;
		}
	}
 
	template<class T>
	T * Get()
	{
		auto name = typeid(T).name();
		auto iter = services.find(name);
		return (iter == services.end()) ? nullptr : reinterpret_cast<T*>(iter->second);
	}

private:
	ServiceLocator();
	static ServiceLocator instance;
	std::unordered_map<const char *, void*> services;
};

