#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

struct CommentResult {
    string maxUser;
    string minUser;

    CommentResult(string maxU, string minU) : maxUser(maxU), minUser(minU) {}
};

struct User {
    string name;
    int birthMonth;
    int comments;
    vector<int> friends;

    User(string n, int bm, int c) : name(n), birthMonth(bm), comments(c) {}
};

class Graph {
private:
    vector<User> users;

public:
    void addUser(const string& name, int birthMonth, int comments) {
        users.push_back(User(name, birthMonth, comments));
    }

    void addFriendship(const string& user1, const string& user2) {
        int index1 = findUserIndex(user1);
        int index2 = findUserIndex(user2);

        if (index1 != -1 && index2 != -1) {
            users[index1].friends.push_back(index2);
            users[index2].friends.push_back(index1);
        }
    }

    string findUserWithMaxFriends() {
        string maxUser;
        int maxFriends = 0;

        for (int i = 0; i < users.size(); ++i) {
            if (users[i].friends.size() > maxFriends) {
                maxFriends = users[i].friends.size();
                maxUser = users[i].name;
            }
        }

        return maxUser;
    }

    CommentResult findUserWithMaxMinComments() {
        string maxUser, minUser;
        int maxComments = INT_MIN;
        int minComments = INT_MAX;

        for (int i = 0; i < users.size(); ++i) {
            if (users[i].comments > maxComments) {
                maxComments = users[i].comments;
                maxUser = users[i].name;
            }
            if (users[i].comments < minComments) {
                minComments = users[i].comments;
                minUser = users[i].name;
            }
        }

        return CommentResult(maxUser, minUser);
    }

    vector<string> findUsersWithBirthdayInMonth(int currentMonth) {
        vector<string> birthdayUsers;

        for (int i = 0; i < users.size(); ++i) {
            if (users[i].birthMonth == currentMonth) {
                birthdayUsers.push_back(users[i].name);
            }
        }

        return birthdayUsers;
    }

    void DFS(const string& startUser) {
        vector<bool> visited(users.size(), false);
        int startIndex = findUserIndex(startUser);
        if (startIndex != -1) {
            DFSUtil(startIndex, visited);
        }
        cout << endl;
    }

private:
    void DFSUtil(int userIndex, vector<bool>& visited) {
        visited[userIndex] = true;
        cout << users[userIndex].name << " ";

        for (int i = 0; i < users[userIndex].friends.size(); ++i) {
            int friendIndex = users[userIndex].friends[i];
            if (!visited[friendIndex]) {
                DFSUtil(friendIndex, visited);
            }
        }
    }

public:
    void BFS(const string& startUser) {
        vector<bool> visited(users.size(), false);
        queue<int> q;
        int startIndex = findUserIndex(startUser);

        if (startIndex != -1) {
            visited[startIndex] = true;
            q.push(startIndex);

            while (!q.empty()) {
                int currentIndex = q.front();
                q.pop();
                cout << users[currentIndex].name << " ";

                for (int i = 0; i < users[currentIndex].friends.size(); ++i) {
                    int friendIndex = users[currentIndex].friends[i];
                    if (!visited[friendIndex]) {
                        visited[friendIndex] = true;
                        q.push(friendIndex);
                    }
                }
            }
        }
        cout << endl;
    }

    int findUserIndex(const string& name) {
        for (int i = 0; i < users.size(); ++i) {
            if (users[i].name == name) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Graph network;
    int choice;
    string name, user1, user2;
    int birthMonth, comments, currentMonth;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add User\n";
        cout << "2. Add Friendship\n";
        cout << "3. Find User with Maximum Friends\n";
        cout << "4. Find User with Maximum and Minimum Comments\n";
        cout << "5. Find Users with Birthday in Current Month\n";
        cout << "6. Perform DFS Traversal\n";
        cout << "7. Perform BFS Traversal\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter user name: ";
                cin >> name;
                cout << "Enter birth month (1-12): ";
                cin >> birthMonth;
                cout << "Enter number of comments: ";
                cin >> comments;
                network.addUser(name, birthMonth, comments);
                break;

            case 2:
                cout << "Enter first user name: ";
                cin >> user1;
                cout << "Enter second user name: ";
                cin >> user2;
                network.addFriendship(user1, user2);
                break;

            case 3:
                cout << "User with maximum friends: " << network.findUserWithMaxFriends() << endl;
                break;

            case 4:
                {
                    CommentResult result = network.findUserWithMaxMinComments();
                    cout << "User with maximum comments: " << result.maxUser << endl;
                    cout << "User with minimum comments: " << result.minUser << endl;
                }
                break;

            case 5:
                cout << "Enter the current month (1-12): ";
                cin >> currentMonth;
                {
                    vector<string> birthdayUsers = network.findUsersWithBirthdayInMonth(currentMonth);
                    cout << "Users with birthdays in the current month:\n";
                    for (const string& user : birthdayUsers) {
                        cout << user << endl;
                    }
                }
                break;

            case 6:
                cout << "Enter starting user for DFS: ";
                cin >> name;
                cout << "DFS traversal starting from " << name << ": ";
                network.DFS(name);
                break;

            case 7:
                cout << "Enter starting user for BFS: ";
                cin >> name;
                cout << "BFS traversal starting from " << name << ": ";
                network.BFS(name);
                break;

            case 8:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
