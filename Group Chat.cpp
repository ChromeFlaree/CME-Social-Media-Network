#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class GroupChat {
public:
    void addUser(const shared_ptr<User> user) {
        members.insert(user);
    }

    void removeUser(const shared_ptr<User> user) {
        members.erase(user);
    }

    void sendMessage(const shared_ptr<User> sender, const string message) const {
        for (const auto member : members) {
            if (member != sender) {
                cout << sender->getName() << " in group chat : " << message << endl;
            }
        }
    }

private:
    unordered_set<shared_ptr<User>> members;
};
