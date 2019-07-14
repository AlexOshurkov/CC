#include <memory>
#include <vector>
#include <iostream>

using namespace std;

class MyObject {
	int val = 0;
public:

	MyObject(int v) : val(v) {
		cout << "Creaetd MyObject: " << val << endl;
	}

	~MyObject(){
		cout << "Deleted MyObject: " << val << endl;
	}

	int getVal() const {
		return val;
	}
};

typedef shared_ptr<MyObject> PMyObject;
typedef vector<PMyObject> PMyObjects;

void testInit()
{
	struct mystruct {
		int v1;
		int v3;
		double v4;
		double v2;
		size_t s;

		mystruct() { ::memset(this, 0, sizeof(*this)); 
		s = sizeof(*this); 
		}
	};

	mystruct t1;
}

int main() {

	testInit();
	PMyObjects myObjects;

	// Add elelemnts
	for (size_t i = 0; i < 10; ++i) {
		PMyObject pmyObject(new MyObject(i));
		myObjects.push_back(pmyObject);
	}

	for (const auto& obj : myObjects) 
		cout << "Print value: " << obj->getVal() << endl;

}