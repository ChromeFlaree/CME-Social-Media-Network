#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class User {
public :
    User(int id, string name) : id(id), name(name) {}

    void setAge(int age) {
        this->age = age;
    }

    void setHeight(double height) {
        this->height = height;
    }

    void setGender(string gender) {
        this->gender = gender;
    }

    void addHobby(string hobby) {
        hobbies.insert(hobby);
    }

    void addFriend(User* friendUser) {
        friends.insert(friendUser);
    }

private :
    int id;
    string name;
    int age = 0;
    double height = 0.0;
    string gender = "";
    unordered_set<string> hobbies;
    unordered_set<User*> friends;
};
