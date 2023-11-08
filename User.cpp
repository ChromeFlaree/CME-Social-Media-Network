#include <iostream>
#include <string>
#include <unordered_set>

class User {
public :
    User(int id, std::string name) : id(id), name(name) {}

    void setAge(int age) {
        this->age = age;
    }

    void setHeight(double height) {
        this->height = height;
    }

    void setGender(std::string gender) {
        this->gender = gender;
    }

    void addHobby(std::string hobby) {
        hobbies.insert(hobby);
    }

    void addFriend(User* friendUser) {
        friends.insert(friendUser);
    }

private :
    int id;
    std::string name;
    int age = 0;
    double height = 0.0;
    std::string gender = "";
    std::unordered_set<std::string> hobbies;
    std::unordered_set<User*> friends;
};