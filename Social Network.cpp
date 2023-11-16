#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class SocialNetwork {
public:
    void addUser(User* user) {
        if (users.find(user->getId()) == users.end()) {
            users[user->getId()] = user;
        }
        else {
            cout << "Error : User with ID " << user->getId() << " already exists. Choose a unique ID." << endl;
        }
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

    unordered_set<int> getFriendsOfUser(int userId) const {
        unordered_set<int> friendIds;
        auto it = users.find(userId);
        if (it != users.end()) {
            const auto friends = it->second->getFriendIds();
            friendIds.insert(friends.begin(), friends.end());
        }
        return friendIds;
    }

private:
    unordered_map<int, User*> users;
};
