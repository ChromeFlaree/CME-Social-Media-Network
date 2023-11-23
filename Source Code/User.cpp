#include "User.h"
#include "GroupChat.h"
#include "SocialNetwork.h"
#include "Post.h"
using namespace std;

User::User(int id, string name, int age, string gender) : id(id), name(name), age(age), gender(gender) {}

int User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

int User::getAge() const {
    return age;
}

string User::getGender() const {
    return gender;
}

void User::setHeight(double height) {
    this->height = height;
}

void User::addHobby(const unordered_set<string> newHobbies) {
    hobbies.insert(newHobbies.begin(), newHobbies.end());
}

void User::addFriend(const shared_ptr<User> friendUser) {
    friends.insert(friendUser);
    friendUser->friends.insert(shared_from_this());
}

void User::removeFriend(const shared_ptr<User> friendUser) {
    friends.erase(friendUser);
    friendUser->friends.erase(shared_from_this());
}

void User::blockUser(const shared_ptr<User> blockedUser) {
    blockedUsers.insert(blockedUser);
    removeFriend(blockedUser);
    blockedUser->removeFriend(shared_from_this());
    cout << getName() << " blocked user with ID " << blockedUser->getId() << " : " << blockedUser->getName() << endl;
}

void User::unblockUser(const shared_ptr<User> unblockedUser) {
    blockedUsers.erase(unblockedUser);
    addFriend(unblockedUser);
    cout << getName() << " unblocked user with ID " << unblockedUser->getId() << " : " << unblockedUser->getName() << endl;
}

bool User::isBlocked(const shared_ptr<User> user) const {
    return blockedUsers.count(user) > 0;
}

bool User::isFriend(const shared_ptr<User> user) const {
    return friends.count(user) > 0;
}

void User::suggestFriends() const {
    cout << "Suggested friends for " << name << " : " << endl;
    for (const auto friendUser : friends) {
        if (blockedUsers.find(friendUser) == blockedUsers.end()) {
            for (const auto friendOfFriend : friendUser->friends) {
                if (blockedUsers.find(friendOfFriend) == blockedUsers.end() && friendOfFriend != shared_from_this() && friends.find(friendOfFriend) == friends.end()) {
                    cout << "User ID : " << friendOfFriend->getId() << ", Name : " << friendOfFriend->getName() << endl;
                }
            }
        }
    }
}

unordered_set<string> User::getHobbies() const {
    return hobbies;
}

unordered_set<int> User::getFriendIds() const {
    unordered_set<int> friendIds;
    for (const auto friendUser : friends) {
        friendIds.insert(friendUser->getId());
    }
    return friendIds;
}

const unordered_set<shared_ptr<GroupChat>> User::getGroups() const {
    return groups;
}

void User::printDetails() const {
    cout << "User ID : " << id << ", Name : " << name << ", Age : " << age << ", Gender : " << gender << endl;

    cout << "Hobbies : ";
    for (const auto hobby : hobbies) {
        cout << hobby << " ";
    }
    cout << endl;

    cout << "Friends : ";
    for (const auto friendUser : friends) {
        cout << friendUser->getName() << " ";
    }
    cout << endl;

    cout << "Blocked Users : ";
    for (const auto blockedUser : blockedUsers) {
        cout << blockedUser->getName() << " ";
    }
    cout << endl;
}

void User::createGroup(const string groupName) {
    auto group = make_shared<GroupChat>();
    group->creator = shared_from_this();
    group->members.insert(shared_from_this());
    groups.insert(group);
    cout << getName() << " created a group named " << groupName << "." << endl;
}

void User::joinGroup(const shared_ptr<GroupChat> group) {
    if (group->creator == shared_from_this() || isFriend(group->creator)) {
        group->members.insert(shared_from_this());
        groups.insert(group);
        cout << getName() << " joined the group chat." << endl;
    } else {
        cerr << "Error: " << getName() << " cannot join the group. User must be a friend of the group creator." << endl;
    }
}

void User::leaveGroup(const shared_ptr<GroupChat> group) {
    if (groups.count(group) > 0) {
        group->leaveGroup(shared_from_this());
    } else {
        cerr << "Error: " << getName() << " cannot leave the group. User must be a member of the group." << endl;
    }
}

void User::sendMessageToGroup(const shared_ptr<GroupChat> group, const string message) {
    if (groups.count(group)) {
        if (group->members.count(shared_from_this()) > 0) {
            group->sendMessage(shared_from_this(), message);
        } else {
            cerr << "Error: " << getName() << " cannot send message. User must be a member of the group." << endl;
        }
    } else {
        cerr << "Error: " << getName() << " cannot send message. User must be a member of the group." << endl;
    }
}

const vector<shared_ptr<Post>> User::getPosts() const {
    return posts;
}

void User::createPost(const string content, PostPrivacy privacy) {
    auto post = make_shared<Post>(shared_from_this(), content, privacy);
    posts.push_back(post);
    cout << getName() << " created a new post." << endl;
}

void User::displayPosts() const {
    cout << "Posts by " << getName() << " : " << endl;
    for (const auto post : posts) {
        post->displayDetails();
    }
}
