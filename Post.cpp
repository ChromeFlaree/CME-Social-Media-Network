#include "Post.h"
#include "User.h"
using namespace std;

Post::Post(const shared_ptr<User> author, const string content, PostPrivacy privacy) : author(author), content(content), privacy(privacy), deleted(false) {}

void Post::addLike(const shared_ptr<User> user) {
    if (deleted) {
        cerr << "Error : Cannot like since post has been deleted." << endl;
    } else if ((privacy == PUBLIC || author->isFriend(user)) && !author->isBlocked(user)) {
        likes.insert(user);
        cout << user->getName() << " liked the post." << endl;
    } else {
        cerr << "Error : " << user->getName() << " cannot like the post." << endl;
    }
}

void Post::addComment(const shared_ptr<User> user, const string comment) {
    if (deleted) {
        cerr << "Error : Cannot comment since post has been deleted." << endl;
    } else if ((privacy == PUBLIC || author->isFriend(user)) && !author->isBlocked(user)) {
        comments.push_back({user, comment});
        cout << user->getName() << " commented on the post: " << comment << endl;
    } else {
        cerr << "Error : " << user->getName() << " cannot comment on the post." << endl;
    }
}

void Post::deletePost() {
    deleted = true;
    cout << author->getName() << " has deleted the post." << endl;
}

void Post::displayDetails() const {
    if (deleted) {
        cout << "This post has been deleted." << endl;
    } else {
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
}
