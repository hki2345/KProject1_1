#pragma once
#include <typeinfo>
#include <string>

class KType
{
private:
	const type_info* MyType;
	std::string MyTypeName;

public:
	KType() {};

public:
	std::string ktypename()
	{
		return MyTypeName;
	}

	template <typename T>
	void set_ktypeinfo()
	{
		MyType = &typeid(T);
		MyTypeName = MyType->name();
	}

	const type_info* ktypeinfo()
	{
		return MyType;
	}

	template <typename T>
	bool is_equal()
	{
		return (*MyType) == typeid(T);
	}
};

