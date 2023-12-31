#include "GroupChat.h"
#include "User.h"
using namespace std;

void GroupChat::addUser(const shared_ptr<User> user) {
    if (!blockedUsers.count(user) && members.insert(user).second) {
        cout << user->getName() << " joined the group chat." << endl;
    } else {
        cerr << "Error: User " << user->getName() << " cannot join the group chat." << endl;
    }
}

void GroupChat::leaveGroup(const shared_ptr<User> user) {
    if (members.count(user) > 0) {
        members.erase(user);
        blockedUsers.erase(user);
        cout << user->getName() << " left the group." << endl;
    } else {
        cerr << "Error: " << user->getName() << " cannot leave the group. User must be a member of the group." << endl;
    }
}

void GroupChat::sendMessage(const shared_ptr<User> sender, const string message) const {
    if (members.count(sender) > 0) {
        cout << sender->getName() << " in group : " << message << endl;
    } else {
        cerr << "Error: " << sender->getName() << " cannot send message. User must be a member of the group." << endl;
    }
}
