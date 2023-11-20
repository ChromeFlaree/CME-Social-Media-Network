#include "Post.h"
#include "User.h"
using namespace std;

Post::Post(const shared_ptr<User> author, const string content) : author(author), content(content) {}

void Post::addLike(const shared_ptr<User> user) {
    if (user != author && author->isFriend(user) && !author->isBlocked(user)) {
        likes.insert(user);
        cout << user->getName() << " liked the post." << endl;
    } else {
        cerr << "Error: " << user->getName() << " cannot like the post." << endl;
    }
}

void Post::addComment(const shared_ptr<User> user, const string comment) {
    if (user != author && author->isFriend(user) && !author->isBlocked(user)) {
        comments.push_back({user, comment});
        cout << user->getName() << " commented on the post: " << comment << endl;
    } else {
        cerr << "Error: " << user->getName() << " cannot comment on the post." << endl;
    }
}

void Post::displayDetails() const {
    cout << "Post by " << author->getName() << " : " << content << endl;
    cout << "Likes : " << likes.size() << endl;
    for (const auto user : likes) {
        cout << user->getName() << " ";
    }
    cout << endl;
    cout << "Comments : " << comments.size() << endl;
    for (const auto comment : comments) {
        cout << comment.first->getName() << " : " << comment.second << endl;
    }
}
