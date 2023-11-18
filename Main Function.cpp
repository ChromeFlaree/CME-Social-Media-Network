#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

int main() {

    SocialNetwork socialNetwork;
    auto user1 = make_shared<User>(1, "Sourasish", 22, "Male");
    auto user2 = make_shared<User>(2, "Anushka", 20, "Female");
    auto user3 = make_shared<User>(3, "Aviroopa", 21, "Female");
    auto user4 = make_shared<User>(4, "Sagnik", 30, "Male");

    socialNetwork.addUser(user1);
    socialNetwork.addUser(user2);
    socialNetwork.addUser(user3);
    socialNetwork.addUser(user4);
    
    user1->addHobby({"Reading"});
    user4->addHobby({"Gardening", "Jogging"});
    user3->addHobby({"Jogging"});
    
    user1->addFriend(user2);
    user1->addFriend(user4);
    user1->addFriend(user3);
    user4->addFriend(user3);

    auto groupChat = make_shared<GroupChat>();

    user1->joinGroupChat(groupChat);
    user2->joinGroupChat(groupChat);
    user3->joinGroupChat(groupChat);
    user4->joinGroupChat(groupChat);

    user1->sendMessageToGroup(groupChat, "Hi, thanks for having me here!");
    user2->sendMessageToGroup(groupChat, "Hello, Sourasish!");
    user3->sendMessageToGroup(groupChat, "Hey, I have also joined the chat!");
    user4->sendMessageToGroup(groupChat, "Hello guys!");
    user1->sendMessageToGroup(groupChat, "Bye");

    user1->leaveGroupChat(groupChat);
    
    user1->blockUser(user4);

    user2->suggestFriends();

    user1->printDetails();
    user2->printDetails();
    user3->printDetails();
    user4->printDetails();

    cout << "Users with name 'Sourasish' :" << endl;
    vector<shared_ptr<User>> usersByName = socialNetwork.searchByName("Sourasish");
    for (const auto user : usersByName) {
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

    cout << "\nBefore deleting user with ID 1 : " << endl;
    for (const auto userPair : socialNetwork.getUsers()) {
        cout << "User ID : " << userPair.first << ", Name : " << userPair.second->getName() << endl;
    }

    socialNetwork.deleteUser(1);

    cout << "\nAfter deleting user with ID 1 : " << endl;
    for (const auto userPair : socialNetwork.getUsers()) {
        cout << "User ID : " << userPair.first << ", Name : " << userPair.second->getName() << endl;
    }

    return 0;
}
