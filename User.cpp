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

private :
    int id;
    string name;
    int age;
    string gender;
    double height = 0.0;
    unordered_set<string> hobbies;
    unordered_set<shared_ptr<User>> friends;
    unordered_set<shared_ptr<User>> blockedUsers;
    friend class SocialNetwork;
};
