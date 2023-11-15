#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class SocialNetwork {
public:
    void addUser(int id, string name, int age, string gender) {
        if (users.find(id) == users.end()) {
            User* newUser = new User(id, name, age, gender);
            users[id] = newUser;
        }
        else {
            cout << "Error : User with ID " << id << " already exists. Choose a unique ID." << endl;
        }
    }

    void deleteUser(int id) {
        auto it = users.find(id);
        if (it != users.end()) {
            delete it->second;
            users.erase(it);
        }
    }

    void addFriendship(int userId1, int userId2) {
        auto user1It = users.find(userId1);
        auto user2It = users.find(userId2);
        if (user1It != users.end() && user2It != users.end()) {
            user1It->second->addFriend(user2It->second);
            user2It->second->addFriend(user1It->second);
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
            const auto& friends = it->second->getFriendIds();
            friendIds.insert(friends.begin(), friends.end());
        }
        return friendIds;
    }

private:
    unordered_map<int, User*> users;
};
