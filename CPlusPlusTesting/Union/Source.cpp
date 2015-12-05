#include <iostream>
using namespace std;

template<typename T, 
	typename = typename std::enable_if<std::is_arithmetic<T>::value || std::is_floating_point<std::remove_pointer<T>::type>::value, T>::type >
struct Value
{
	T value;
};

struct S
{
	
};



void main()
{
	float f;
	Value<float*> v1{&f};

	cout << std::is_floating_point<float>::value << endl;
	Value<float> v2{4.0f};
	Value<int> v3{0};
	system("pause");
}