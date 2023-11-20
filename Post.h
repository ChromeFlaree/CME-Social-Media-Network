#ifndef POST_H
#define POST_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

class User;

class Post {
public:
    Post(const shared_ptr<User> author, const string content);
    void addLike(const shared_ptr<User> user);
    void addComment(const shared_ptr<User> user, const string comment);
    void displayDetails() const;

private:
    shared_ptr<User> author;
    string content;
    unordered_set<shared_ptr<User>> likes;
    vector<pair<shared_ptr<User>, string>> comments;
};

#endif
