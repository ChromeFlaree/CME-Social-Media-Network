#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class User {
public :
    User(int id, string name, int age, string gender) : id(id), name(name), age(age), gender(gender) {} // Constructor to initialize user with an unique ID and name

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

    int getId() const { 
        return id;
    }

    string getName() const {
        return name;
    }

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
    int age;
    string gender;
    double height = 0.0;
    unordered_set<string> hobbies;
    unordered_set<User*> friends;
    friend class SocialNetwork;
};
