#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class SocialNetwork {
public:

    void addUser(int id, string name, int age, string gender) {
        User* newUser = new User(id, name, age, gender);
        users[id] = newUser;
    }

    void deleteUser(int id) {
        auto it = users.find(id);
        if (it != users.end()) {
            delete it->second;
            users.erase(it);
        }
    }

    vector<User*> searchByName(const string name) {
        vector<User*> result;
        for (const auto userPair : users) {
            if (userPair.second->name == name) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    vector<User*> searchByAge(int age) {
        vector<User*> result;
        for (const auto userPair : users) {
            if (userPair.second->age == age) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    vector<User*> searchByHobbies(const string hobby) {
        vector<User*> result;
        for (const auto userPair : users) {
            if (userPair.second->hobbies.find(hobby) != userPair.second->hobbies.end()) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

private:
    unordered_map<int, User*> users;
};
