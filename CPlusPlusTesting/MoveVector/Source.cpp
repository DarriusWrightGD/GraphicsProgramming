#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

struct Obj1
{
	Obj1()
	{
	
	}
	void move(const vector<int> & v)
	{
		myVec.resize(v.size());
		std::move(v.begin(), v.end(), myVec.begin());
	}
	void printMyVec()
	{
		for (auto i : myVec)
		{
			cout << i << endl;
		}
	}

private:
	vector<int> myVec;
};

void moveVector(Obj1 & obj1)
{
	vector<int> v{ 1,2,3,4,5,6 };
	obj1.move(v);
}

void main()
{
	Obj1 obj;
	moveVector(obj);
	obj.printMyVec();
	system("pause");
}