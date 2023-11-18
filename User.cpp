#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class User : public enable_shared_from_this<User> {
public :
    User(int id, string name, int age, string gender) : id(id), name(name), age(age), gender(gender) {}

    int getId() const { 
        return id;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getGender() const {
        return gender;
    }

    void setHeight(double height) {
        this->height = height;
    }

    void addHobby(const unordered_set<string> newHobbies) {
    hobbies.insert(newHobbies.begin(), newHobbies.end());
    }

    void addFriend(const shared_ptr<User> friendUser) {
        friends.insert(friendUser);
        friendUser->friends.insert(shared_from_this());
    }

    void removeFriend(const shared_ptr<User> friendUser) {
        friends.erase(friendUser);
        friendUser->friends.erase(shared_from_this());
    }

    void blockUser(const shared_ptr<User> blockedUser) {
        blockedUsers.insert(blockedUser);
        removeFriend(blockedUser);
        blockedUser->removeFriend(shared_from_this());
        cout << getName() << " blocked user with ID " << blockedUser->getId() << " : " << blockedUser->getName() << endl;
    }

    void unblockUser(const shared_ptr<User> unblockedUser) {
        blockedUsers.erase(unblockedUser);
        addFriend(unblockedUser);
        cout << getName() << " unblocked user with ID " << unblockedUser->getId() << " : " << unblockedUser->getName() << endl;
    }

    void suggestFriends() const {
        cout << "Suggested friends for " << name << " : " << endl;
        for (const auto friendUser : friends) {
            if (blockedUsers.find(friendUser) == blockedUsers.end()) {
                for (const auto friendOfFriend : friendUser->friends) {
                    if (blockedUsers.find(friendOfFriend) == blockedUsers.end() && friendOfFriend != shared_from_this()) {
                        cout << "User ID : " << friendOfFriend->getId() << ", Name : " << friendOfFriend->getName() << endl;
                    }
                }
            }
        }
    }

    void joinGroupChat(const shared_ptr<GroupChat> group) {    
        group->addUser(shared_from_this());
        groupChats.insert(group);
        cout << getName() << " joined the group chat." << endl;
    }

    void leaveGroupChat(const shared_ptr<GroupChat> group) {
        group->removeUser(shared_from_this());
        groupChats.erase(group);
        cout << getName() << " left the group chat." << endl;
    }

    void sendMessageToGroup(const shared_ptr<GroupChat> group, const string message) {
        group->sendMessage(shared_from_this(), message);
    }

    unordered_set<string> getHobbies() const {
        return hobbies;
    }

    unordered_set<int> getFriendIds() const {
        unordered_set<int> friendIds;
        for (const auto friendUser : friends) {
            friendIds.insert(friendUser->getId());
        }
        return friendIds;
    }

     void printDetails() const {
        cout << "User ID : " << id << ", Name : " << name << ", Age : " << age << ", Gender : " << gender << endl;

        cout << "Hobbies : ";
        for (const auto hobby : hobbies) {
            cout << hobby << " ";
        }

        cout << "Friends : ";
        for (const auto friendUser : friends) {
            cout << friendUser->getName() << " ";
        }

        cout << "Blocked Users : ";
        for (const auto blockedUser : blockedUsers) {
            cout << blockedUser->getName() << " ";
        }
    }

private :
    int id;
    string name;
    int age;
    string gender;
    double height = 0.0;
    unordered_set<string> hobbies;
    unordered_set<shared_ptr<User>> friends;
    unordered_set<shared_ptr<User>> blockedUsers;
    unordered_set<shared_ptr<GroupChat>> groupChats;
    friend class SocialNetwork;
};
