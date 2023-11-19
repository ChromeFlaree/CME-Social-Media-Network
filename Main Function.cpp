#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

int main() { // Main method

    SocialNetwork socialNetwork;
    auto user1 = make_shared<User>(1, "Sourasish", 22, "Male"); // Creating users and passing values
    auto user2 = make_shared<User>(2, "Anushka", 20, "Female");
    auto user3 = make_shared<User>(3, "Aviroopa", 21, "Female");
    auto user4 = make_shared<User>(4, "Sagnik", 30, "Male");

    socialNetwork.addUser(user1); // Adding users to the social network
    socialNetwork.addUser(user2);
    socialNetwork.addUser(user3);
    socialNetwork.addUser(user4);
    
    user1->addHobby({"Reading"}); // Adding hobbies for the users
    user4->addHobby({"Gardening", "Jogging"});
    user3->addHobby({"Jogging"});
    
    user1->addFriend(user2); // Creating friendship between users
    user1->addFriend(user4);
    user1->addFriend(user3);
    user4->addFriend(user3);
    
    user1->blockUser(user4); // User 1 blocks User 4

    user1->createGroup("Friends Group"); // User 1 creates new group for messaging
    user2->joinGroup(*(user1->getGroups().begin())); // Other users joining the group
    user3->joinGroup(*(user1->getGroups().begin()));
    user4->joinGroup(*(user1->getGroups().begin())); // User 4 is blocked thus cannot join the group chat

    user1->sendMessageToGroup(*(user1->getGroups().begin()), "Hello, friends!"); // Sending messages
    user2->sendMessageToGroup(*(user1->getGroups().begin()), "Hello Sourasish");
    user4->sendMessageToGroup(*(user1->getGroups().begin()), "Hello");

    user2->leaveGroup(*(user1->getGroups().begin())); // User 2 leaves the group chat
    user4->leaveGroup(*(user1->getGroups().begin()));
    user2->sendMessageToGroup(*(user1->getGroups().begin()), "Testing Message"); // User 2 trying to send message after leaving the group

    user2->suggestFriends(); // Calling method to suggest friends to User 2

    user1->printDetails(); // Printing details and information of users
    user2->printDetails();
    user3->printDetails();
    user4->printDetails();

    cout << "Users with name 'Sourasish' :" << endl; // Searching and printing users with name Sourasish
    vector<shared_ptr<User>> usersByName = socialNetwork.searchByName("Sourasish");
    for (const auto user : usersByName) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "\nUsers with age 30 :" << endl; // Searching and printing users with age 30 years
    vector<shared_ptr<User>> usersByAge = socialNetwork.searchByAge(30);
    for (const auto user : usersByAge) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "\nUsers with hobbies 'Jogging' :" << endl; // Searching and printing users having jogging as hobby
    vector<shared_ptr<User>> usersByHobbies = socialNetwork.searchByHobbies("Jogging");
    for (const auto user : usersByHobbies) {
        cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
    }

    cout << "\nFriends of Sourasish : "; // Printing the ID of users who are friends of Sourasish
    unordered_set<int> sourasishFriends = socialNetwork.getFriendsOfUser(1);
    for (const auto friendId : sourasishFriends) {
        cout << friendId << " ";
    }
    cout << endl;

    cout << "\nFriends of Sagnik : "; // Printing the ID of users who are friends of Sagnik
    unordered_set<int> sagnikFriends = socialNetwork.getFriendsOfUser(4);
    for (const auto friendId : sagnikFriends) {
        cout << friendId << " ";
    }
    cout << endl;

    user1->unblockUser(user4); // User 1 unblocks User 4
    user1->printDetails(); // Printing details of User 1 to check if the unblock function is executed correctly

    cout << "\nBefore deleting user with ID 1 : " << endl; // Printing ID and names of all users present in the network
    for (const auto userPair : socialNetwork.getUsers()) {
        cout << "User ID : " << userPair.first << ", Name : " << userPair.second->getName() << endl;
    }

    socialNetwork.deleteUser(1); // Deleting User 1 from the network

    cout << "\nAfter deleting user with ID 1 : " << endl; // Printing ID and names of users remaining in the network post deletion of User 1
    for (const auto userPair : socialNetwork.getUsers()) {
        cout << "User ID : " << userPair.first << ", Name : " << userPair.second->getName() << endl;
    }

    return 0;
}
