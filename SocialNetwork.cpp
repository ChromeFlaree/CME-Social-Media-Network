#include "SocialNetwork.h"
#include "User.h"
using namespace std;

void SocialNetwork::addUser(shared_ptr<User> user) {
    auto result = users.emplace(user->getId(), user);
    if (!result.second) {
        cout << "Error: User with ID " << user->getId() << " already exists. Choose a unique ID." << endl;
    }
}

void SocialNetwork::deleteUser(int id) {
    auto it = users.find(id);
    if (it != users.end()) {
        cout << "Deleting user with ID " << id << " : " << it->second->getName() << endl;
        users.erase(it);
    } else {
        cout << "User with ID " << id << " not found." << endl;
    }
}

unordered_map<int, shared_ptr<User>> SocialNetwork::getUsers() const {
    return users;
}

vector<shared_ptr<User>> SocialNetwork::searchByName(const string name) {
    vector<shared_ptr<User>> result;
    for (const auto userPair : users) {
        if (userPair.second->getName() == name) {
            result.push_back(userPair.second);
        }
    }
    return result;
}

vector<shared_ptr<User>> SocialNetwork::searchByAge(int age) {
    vector<shared_ptr<User>> result;
    for (const auto userPair : users) {
        if (userPair.second->getAge() == age) {
            result.push_back(userPair.second);
        }
    }
    return result;
}

vector<shared_ptr<User>> SocialNetwork::searchByHobbies(const string hobby) {
    vector<shared_ptr<User>> result;
    for (const auto userPair : users) {
        if (userPair.second->hobbies.find(hobby) != userPair.second->hobbies.end()) {
            result.push_back(userPair.second);
        }
    }
    return result;
}

unordered_set<int> SocialNetwork::getFriendsOfUser(int userId) const {
    unordered_set<int> friendIds;
    auto it = users.find(userId);
    if (it != users.end()) {
        const auto friends = it->second->getFriendIds();
        friendIds.insert(friends.begin(), friends.end());
    }
    return friendIds;
}
