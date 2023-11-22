#include "User.h"
#include "GroupChat.h"
#include "Post.h"
#include "SocialNetwork.h"

int main() {

    SocialNetwork socialNetwork;
    auto user1 = make_shared<User>(1, "Sourasish", 22, "Male");
    auto user2 = make_shared<User>(2, "Anushka", 20, "Female");
    auto user3 = make_shared<User>(3, "Aviroopa", 21, "Female");
    auto user4 = make_shared<User>(4, "Sagnik", 30, "Male");
    auto user5 = make_shared<User>(5, "Abhranil", 26, "Male");
    auto user6 = make_shared<User>(6, "Shinjini", 28, "Female");
    auto user7 = make_shared<User>(7, "Oishik", 30, "Male");

    socialNetwork.addUser(user1);
    socialNetwork.addUser(user2);
    socialNetwork.addUser(user3);
    socialNetwork.addUser(user4);
    socialNetwork.addUser(user5);
    socialNetwork.addUser(user6);
    socialNetwork.addUser(user7);
    
    user1->addHobby({"Reading"});
    user4->addHobby({"Gardening", "Jogging"});
    user3->addHobby({"Jogging"});
    user5->addHobby({"Singing", "Dancing"});
    user7->addHobby({"Jogging"});
    
    user1->addFriend(user2);
    user1->addFriend(user3);
    user1->addFriend(user4);
    user1->addFriend(user6);
    user1->addFriend(user7);
    user4->addFriend(user3);
    user2->addFriend(user6);

    user1->blockUser(user4);
    cout << endl;

    user1->createGroup("Friends Group");
    user2->joinGroup(*(user1->getGroups().begin()));
    user3->joinGroup(*(user1->getGroups().begin()));
    user4->joinGroup(*(user1->getGroups().begin()));

    user1->sendMessageToGroup(*(user1->getGroups().begin()), "Hello, friends!");
    user2->sendMessageToGroup(*(user1->getGroups().begin()), "Hello Sourasish");
    user4->sendMessageToGroup(*(user1->getGroups().begin()), "Hello");

    user2->leaveGroup(*(user1->getGroups().begin()));
    user4->leaveGroup(*(user1->getGroups().begin()));
    user2->sendMessageToGroup(*(user1->getGroups().begin()), "Testing Message");

    user2->suggestFriends();
    cout << endl;

    user1->printDetails();
    cout << endl;
    user2->printDetails();
    cout << endl;
    user3->printDetails();
    cout << endl;
    user4->printDetails();
    cout << endl;

    user1->createPost("Enjoying a sunny day!", PostPrivacy::PRIVATE);
    user1->getPosts().front()->addLike(user2);
    user1->getPosts().front()->addLike(user3);
    user1->getPosts().front()->addLike(user7);
    user1->getPosts().front()->addLike(user5);
    user1->getPosts().front()->addLike(user4);
    user1->getPosts().front()->addComment(user2, "Looks amazing!");
    user1->displayPosts();

    auto posts = user1->getPosts();
    if (!posts.empty()) {
        posts.front()->deletePost();
    }

    user1->getPosts().front()->addLike(user6);
    user1->getPosts().front()->addComment(user6, "Interesting!");
    user1->displayPosts();

    user2->createPost("Watching ICC World Cup Final!", PostPrivacy::PUBLIC);
    user2->getPosts().front()->addLike(user1);
    user2->getPosts().front()->addLike(user5);
    user2->getPosts().front()->addLike(user7);
    user2->getPosts().front()->addLike(user4);
    user2->getPosts().front()->addComment(user4, "Kohli will score a century.");
    user2->displayPosts();

    cout << "Users with name 'Sourasish' :" << endl;
    vector<shared_ptr<User>> usersByName1 = socialNetwork.searchByName("Sourasish");
    for (const auto user : usersByName1) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "Users with name 'An' :" << endl;
    vector<shared_ptr<User>> usersByName2 = socialNetwork.searchByName("An");
    for (const auto user : usersByName2) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "\nUsers with age 30 :" << endl;
    vector<shared_ptr<User>> usersByAge = socialNetwork.searchByAge(30);
    for (const auto user : usersByAge) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "\nUsers with hobbies 'Jogging' :" << endl;
    vector<shared_ptr<User>> usersByHobbies = socialNetwork.searchByHobbies("Jogging");
    for (const auto user : usersByHobbies) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "\nFriends of Sourasish : ";
    unordered_set<int> sourasishFriends = socialNetwork.getFriendsOfUser(1);
    for (const auto friendId : sourasishFriends) {
        cout << friendId << " ";
    }
    cout << endl;

    cout << "\nFriends of Sagnik : ";
    unordered_set<int> sagnikFriends = socialNetwork.getFriendsOfUser(4);
    for (const auto friendId : sagnikFriends) {
        cout << friendId << " ";
    }
    cout << endl;

    user1->unblockUser(user4);

    user1->printDetails();
    cout << endl;

    cout << "\nBefore deleting user with ID 1 : " << endl;
    for (const auto userPair : socialNetwork.getUsers()) {
        cout << "User ID : " << userPair.first << ", Name : " << userPair.second->getName() << endl;
    }

    cout << endl;
    socialNetwork.deleteUser(1);

    cout << "\nAfter deleting user with ID 1 : " << endl;
    for (const auto userPair : socialNetwork.getUsers()) {
        cout << "User ID : " << userPair.first << ", Name : " << userPair.second->getName() << endl;
    }

    return 0;
}
