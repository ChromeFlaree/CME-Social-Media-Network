#include "UserAuthentication.h"
#include "User.h"

void UserAuthentication::registerUser(const string username, const string password) {
    users[username] = password;
}

bool UserAuthentication::authenticate(const string username, const string password) const {
    auto userIt = users.find(username);
    return (userIt != users.end()) && (userIt->second == password);
}