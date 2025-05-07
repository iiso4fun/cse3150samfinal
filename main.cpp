#include "TimedSharedPtr.hpp"
#include <iostream>
#include <thread>

using namespace std;
using Clock = chrono::high_resolution_clock;

struct Node {
    Node(int v) : val{v} {}
    int val;
    TimedSharedPtr<Node> next;
};

int main() {
    TimedSharedPtr<Node> myNode(new Node(7), 100);
    TimedSharedPtr<Node> myOtherNode = myNode;

    this_thread::sleep_until(Clock::now() + chrono::milliseconds(50));
    cout << "myNode.get() address: <" << myNode.get() << ">\n";
    cout << "myNode.use_count(): " << myNode.use_count() << "\n";
    cout << "myOtherNode.use_count(): " << myOtherNode.use_count() << "\n";

    this_thread::sleep_until(Clock::now() + chrono::milliseconds(25));
    cout << "myNode.get() address: <" << myNode.get() << ">\n";

    this_thread::sleep_until(Clock::now() + chrono::milliseconds(75));
    cout << "The ptr should have expired:\n";
    cout << "myNode.get() address: <" << myNode.get() << ">\n";

    cout << "-----------\n";
    TimedSharedPtr<int> p(new int(42));
    cout << p.get() << "\n";
    cout << "p.use_count(): " << p.use_count() << "\n";
    TimedSharedPtr<int> q = p;
    cout << "p.use_count(): " << p.use_count() << "\n";
    cout << "q.use_count(): " << q.use_count() << "\n";

    return 0;
}

