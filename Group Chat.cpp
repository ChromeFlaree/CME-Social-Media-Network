#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class GroupChat {
public:
    void GroupChat::addUser(const shared_ptr<User> user) {
        if (!blockedUsers.count(user) && members.insert(user).second) {
            cout << user->getName() << " joined the group chat." << endl;
        } 
        else {
            cerr << "Error: User " << user->getName() << " cannot join the group chat." << endl;
        }
    }

    void removeUser(const shared_ptr<User> user) { 
        members.erase(user);
        blockedUsers.erase(user);
    }

    void GroupChat::blockUser(const shared_ptr<User> blocker, const shared_ptr<User> blockedUser) {
        if (members.count(blocker) && members.count(blockedUser)) {
            blockedUsers.insert(blockedUser);
            blockedUser->removeFriend(blocker);
            cout << blocker->getName() << " blocked " << blockedUser->getName() << " in the group chat." << endl;
        } 
        else {
            cerr << "Error : Unable to block user. Users must be members of the group." << endl;
        }
    }

    void GroupChat::sendMessage(const shared_ptr<User> sender, const string message) const {
        for (const auto member : members) {
            if (member != sender && !sender->isBlocked(member) && sender->isFriend(member)) {
                cout << sender->getName() << " in group chat: " << message << endl;
            }
        }
    }

    bool GroupChat::isUserInGroup(const shared_ptr<User> user) const {
        return members.count(user) > 0;
    }

private:
    unordered_set<shared_ptr<User>> members;
    unordered_set<shared_ptr<User>> blockedUsers;
    friend class User;
};
