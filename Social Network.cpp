#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class SocialNetwork {
public:
    void addUser(shared_ptr<User> user) {
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
            users.erase(it);
        }
    }

    vector<shared_ptr<User>> searchByName(const string name) {
        vector<shared_ptr<User>> result;
        for (const auto userPair : users) {
            if (userPair.second->getName() == name) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    vector<shared_ptr<User>> searchByAge(int age) {
        vector<shared_ptr<User>> result;
        for (const auto userPair : users) {
            if (userPair.second->getAge() == age) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    vector<shared_ptr<User>> searchByHobbies(const string hobby) {
        vector<shared_ptr<User>> result;
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
    unordered_map<int, shared_ptr<User>> users;
};
