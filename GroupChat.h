#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <iostream>
#include <unordered_set>
#include <memory>

class User;

class GroupChat {
public:
    void addUser(const shared_ptr<User> user);
    void leaveGroup(const shared_ptr<User> user);
    void sendMessage(const shared_ptr<User> sender, const string message) const;

private:
    unordered_set<shared_ptr<User>> members;
    unordered_set<shared_ptr<User>> blockedUsers;
    shared_ptr<User> creator;
    friend class User;
};

#endif
