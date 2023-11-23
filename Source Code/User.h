#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Post.h"
using namespace std;

class GroupChat;
class Post;

class User : public std::enable_shared_from_this<User> {
public:
    User(int id, string name, int age, string gender);

    int getId() const;
    string getName() const;
    int getAge() const;
    string getGender() const;

    void setHeight(double height);
    void addHobby(const unordered_set<string> newHobbies);
    void addFriend(const shared_ptr<User> friendUser);
    void removeFriend(const shared_ptr<User> friendUser);
    void blockUser(const shared_ptr<User> blockedUser);
    void unblockUser(const shared_ptr<User> unblockedUser);
    bool isBlocked(const shared_ptr<User> user) const;
    bool isFriend(const shared_ptr<User> user) const;
    void suggestFriends() const;

    unordered_set<string> getHobbies() const;
    unordered_set<int> getFriendIds() const;
    const unordered_set<shared_ptr<GroupChat>> getGroups() const;

    void printDetails() const;

    void createGroup(const string groupName);
    void joinGroup(const shared_ptr<GroupChat> group);
    void leaveGroup(const shared_ptr<GroupChat> group);
    void sendMessageToGroup(const shared_ptr<GroupChat> group, const string message);

    void createPost(const string content, PostPrivacy privacy);
    void displayPosts() const;
    const vector<shared_ptr<Post>> getPosts() const;

private:
    int id;
    string name;
    int age;
    string gender;
    double height = 0.0;
    unordered_set<string> hobbies;
    unordered_set<shared_ptr<User>> friends;
    unordered_set<shared_ptr<User>> blockedUsers;
    unordered_set<shared_ptr<GroupChat>> groupChats;
    unordered_set<shared_ptr<GroupChat>> groups;
    vector<shared_ptr<Post>> posts;
    friend class GroupChat;
    friend class SocialNetwork;
    friend class Post;
};

#endif
