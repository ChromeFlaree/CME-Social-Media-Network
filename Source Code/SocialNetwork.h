#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class User;

class SocialNetwork {
public:
    void addUser(const shared_ptr<User> user, const string username, const string password);
    void deleteUser(int id);
    unordered_map<int, shared_ptr<User>> getUsers() const;
    vector<shared_ptr<User>> searchByName(const string name);
    vector<shared_ptr<User>> searchByAge(int age);
    vector<shared_ptr<User>> searchByHobbies(const string hobby);
    unordered_set<int> getFriendsOfUser(int userId) const;

private:
    unordered_map<int, shared_ptr<User>> users;
};

#endif
