#include <iostream>

class SetMotionState
{
    slot<PhysAttr&> physObj;
    slot<IrrAttr&> irrObj;
    slot<MotionStateArr> motObj;

};


using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
