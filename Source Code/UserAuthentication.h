#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
using namespace std;

class User;
class SocialNetwork;

class UserAuthentication {
public:
    void registerUser(const string username, const string password);
    bool authenticate(const string username, const string password) const;

private:
    unordered_map<string, string> users;
};

#endif