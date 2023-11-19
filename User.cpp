#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class User : public enable_shared_from_this<User> { // User class 
public :
    User(int id, string name, int age, string gender) : id(id), name(name), age(age), gender(gender) {} // Taking the compulsory parameters as inputs

    int getId() const { // Getter method
        return id; // Return back ID of the user
    }

    string getName() const { 
        return name; // Return back name of the user
    }

    int getAge() const {
        return age; // Return back age of the user
    }

    string getGender() const { 
        return gender; // Return back gender of the user
    }

    void setHeight(double height) { // Setter method
        this->height = height; // Set the height parameter with the value entered
    }

    void addHobby(const unordered_set<string> newHobbies) { // Adding hobbies into the hobby set
    hobbies.insert(newHobbies.begin(), newHobbies.end());
    }

    void addFriend(const shared_ptr<User> friendUser) { // Storing friend list
        friends.insert(friendUser);
        friendUser->friends.insert(shared_from_this()); // Shared pointer for better memory utilization
    }

    void removeFriend(const shared_ptr<User> friendUser) { // Removing friend from the list
        friends.erase(friendUser);
        friendUser->friends.erase(shared_from_this());
    }

    void blockUser(const shared_ptr<User> blockedUser) { // Function to block a user
        blockedUsers.insert(blockedUser);
        removeFriend(blockedUser); // Since user is blocked thus removing from friend list
        blockedUser->removeFriend(shared_from_this());
        cout << getName() << " blocked user with ID " << blockedUser->getId() << " : " << blockedUser->getName() << endl;
    }

    void unblockUser(const shared_ptr<User> unblockedUser) {
        blockedUsers.erase(unblockedUser); // Removing user from the block list
        addFriend(unblockedUser); // Adding back the user to the friend list
        cout << getName() << " unblocked user with ID " << unblockedUser->getId() << " : " << unblockedUser->getName() << endl;
    }

    void suggestFriends() const { // Friend suggestion based on friends of friend
        cout << "Suggested friends for " << name << " : " << endl;
        for (const auto friendUser : friends) { 
            if (blockedUsers.find(friendUser) == blockedUsers.end()) { // Checking if the user is blocked or not
                for (const auto friendOfFriend : friendUser->friends) { // Searching for friends of friend for suggestion
                    if (blockedUsers.find(friendOfFriend) == blockedUsers.end() && friendOfFriend != shared_from_this()) {
                        cout << "User ID : " << friendOfFriend->getId() << ", Name : " << friendOfFriend->getName() << endl;
                    }
                }
            }
        }
    }

    bool isBlocked(const shared_ptr<User> user) const {
        return blockedUsers.count(user) > 0;
    }

    bool isFriend(const shared_ptr<User> user) const {
        return friends.count(user) > 0;
    }

    unordered_set<string> getHobbies() const { // Return the list of hobbies of a user
        return hobbies;
    }

    unordered_set<int> getFriendIds() const { // Return friend list of a user
        unordered_set<int> friendIds;
        for (const auto friendUser : friends) {
            friendIds.insert(friendUser->getId());
        }
        return friendIds;
    }

    void createGroup(const string groupName) {
        auto group = make_shared<GroupChat>();
        group->creator = shared_from_this();
        group->members.insert(shared_from_this());
        groups.insert(group);
        cout << getName() << " created a group named " << groupName << "." << endl;
    }

    void joinGroup(const shared_ptr<GroupChat> group) {
        if (group->creator == shared_from_this() || isFriend(group->creator)) {
            group->members.insert(shared_from_this());
            groups.insert(group);
            cout << getName() << " joined the group chat." << endl;
        } else {
            cerr << "Error: " << getName() << " cannot join the group. User must be a friend of the group creator." << endl;
        }
    }

    void leaveGroup(const shared_ptr<GroupChat> group) {
        if (groups.count(group) > 0) {
            group->leaveGroup(shared_from_this());
        } else {
            cerr << "Error: " << getName() << " cannot leave the group. User must be a member of the group." << endl;
        }
    }

    void sendMessageToGroup(const shared_ptr<GroupChat> group, const string message) {
        if (groups.count(group)) {
            if (group->members.count(shared_from_this()) > 0) {
                group->sendMessage(shared_from_this(), message);
            } else {
                cerr << "Error : " << getName() << " cannot send message. User must be a member of the group." << endl;
            }
        } else {
            cerr << "Error : " << getName() << " cannot send message. User must be a member of the group." << endl;
        }
    }

    const unordered_set<shared_ptr<GroupChat>> getGroups() const {
        return groups;
    }

    void printDetails() const { // Printing all the information about a particular user
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

private : // Private data members
    int id;
    string name;
    int age;
    string gender;
    double height = 0.0;
    unordered_set<string> hobbies;
    unordered_set<shared_ptr<User>> friends;
    unordered_set<shared_ptr<User>> blockedUsers;
    unordered_set<shared_ptr<GroupChat>> groupChats;
    unordered_set<shared_ptr<GroupChat>> groups;
    friend class SocialNetwork; // Friend class 
    friend class GroupChat;
};
