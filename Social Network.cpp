#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class SocialNetwork {
public:
    void addUser(shared_ptr<User> user) { // Implementing shared pointer concept for better memory utilization
        if (users.find(user->getId()) == users.end()) {
            users[user->getId()] = user; // Adding users in the network and storing in map with ID as the key
        }
        else { // If same ID exists then throwing error
            cout << "Error : User with ID " << user->getId() << " already exists. Choose a unique ID." << endl;
        }
    }

    void deleteUser(int id) { // Deleting user from the network
        auto it = users.find(id); // Searching for the ID in the map
        if (it != users.end()) {
            cout << "Deleting user with ID " << id << " : " << it->second->getName() << endl;
            users.erase(it); // Erasing user from map to prevent memory leak
        }
        else {
            cout << "User with ID " << id << " not found." << endl; // If no ID found then displaying message
        }
    }

    unordered_map<int, shared_ptr<User>> getUsers() const { // Return all the users currently present in the network
        return users;
    }

    vector<shared_ptr<User>> searchByName(const string name) { // Searching by name and returning all the users with that name
        vector<shared_ptr<User>> result;
        for (const auto userPair : users) {
            if (userPair.second->getName() == name) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    vector<shared_ptr<User>> searchByAge(int age) { // Searching users having the entered age and returning all users list
        vector<shared_ptr<User>> result;
        for (const auto userPair : users) {
            if (userPair.second->getAge() == age) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    vector<shared_ptr<User>> searchByHobbies(const string hobby) { // Searching users based on the hobby and returning list of users
        vector<shared_ptr<User>> result;
        for (const auto userPair : users) {
            if (userPair.second->hobbies.find(hobby) != userPair.second->hobbies.end()) {
                result.push_back(userPair.second);
            }
        }
        return result;
    }

    unordered_set<int> getFriendsOfUser(int userId) const { // Returning friend list of the user
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
