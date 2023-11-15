#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

class User {
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

    void addHobby(string hobby) {
        hobbies.insert(hobby);
    }

    void addFriend(User* friendUser) {
        friends.insert(friendUser);
        friendUser->friends.insert(this);
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
    unordered_set<User*> friends;
    friend class SocialNetwork;
};
