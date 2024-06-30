#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class User
{
public:
  string username;
  vector<string> friends;
  vector<string> posts;

  User() {}
  User(const string &name) : username(name) {}
};

class SocialNetwork
{
private:
  map<string, User> users;
  string currentUser;

  void saveData()
  {
    ofstream file("network_data.txt");
    for (const auto &pair : users)
    {
      const User &user = pair.second;
      file << user.username << endl;
      file << user.friends.size() << endl;
      for (const auto &friend_ : user.friends)
      {
        file << friend_ << endl;
      }
      file << user.posts.size() << endl;
      for (const auto &post : user.posts)
      {
        file << post << endl;
      }
    }
  }

  void loadData()
  {
    ifstream file("network_data.txt");
    if (!file)
      return;

    string username;
    while (getline(file, username))
    {
      User user(username);
      int friendCount;
      file >> friendCount;
      file.ignore();
      for (int i = 0; i < friendCount; i++)
      {
        string friend_;
        getline(file, friend_);
        user.friends.push_back(friend_);
      }
      int postCount;
      file >> postCount;
      file.ignore();
      for (int i = 0; i < postCount; i++)
      {
        string post;
        getline(file, post);
        user.posts.push_back(post);
      }
      users[username] = user;
    }
  }

public:
  SocialNetwork()
  {
    loadData();
  }

  ~SocialNetwork()
  {
    saveData();
  }

  void createProfile()
  {
    string username;
    cout << "Enter new username: ";
    cin >> username;
    if (users.find(username) == users.end())
    {
      users[username] = User(username);
      cout << "Profile created successfully!\n";
    }
    else
    {
      cout << "Username already exists.\n";
    }
  }

  void login()
  {
    string username;
    cout << "Enter your username: ";
    cin >> username;
    if (users.find(username) != users.end())
    {
      currentUser = username;
      cout << "Logged in as " << username << endl;
    }
    else
    {
      cout << "User not found.\n";
    }
  }

  void addFriend()
  {
    if (currentUser.empty())
    {
      cout << "Please login first.\n";
      return;
    }
    string friendName;
    cout << "Enter friend's username: ";
    cin >> friendName;
    if (users.find(friendName) != users.end() && friendName != currentUser)
    {
      users[currentUser].friends.push_back(friendName);
      users[friendName].friends.push_back(currentUser);
      cout << "Friend added successfully!\n";
    }
    else
    {
      cout << "Invalid username.\n";
    }
  }

  void deleteFriend()
  {
    if (currentUser.empty())
    {
      cout << "Please login first.\n";
      return;
    }
    string friendName;
    cout << "Enter friend's username to delete: ";
    cin >> friendName;

    auto &friends = users[currentUser].friends;
    auto it = find(friends.begin(), friends.end(), friendName);

    if (it != friends.end())
    {
      friends.erase(it);

      // Remove the current user from the friend's friend list as well
      auto &friendsFriends = users[friendName].friends;
      auto friendIt = find(friendsFriends.begin(), friendsFriends.end(), currentUser);
      if (friendIt != friendsFriends.end())
      {
        friendsFriends.erase(friendIt);
      }

      cout << "Friend deleted successfully!\n";
    }
    else
    {
      cout << "Friend not found in your friend list.\n";
    }
  }

  void post()
  {
    if (currentUser.empty())
    {
      cout << "Please login first.\n";
      return;
    }
    string message;
    cout << "Enter your post: ";
    cin.ignore();
    getline(cin, message);
    users[currentUser].posts.push_back(message);
    cout << "Post added successfully!\n";
  }

  void viewProfile()
  {
    if (currentUser.empty())
    {
      cout << "Please login first.\n";
      return;
    }
    User &user = users[currentUser];
    cout << "Username: " << user.username << endl;
    cout << "Friends: ";
    for (const auto &friend_ : user.friends)
    {
      cout << friend_ << " ";
    }
    cout << endl
         << "Posts:" << endl;
    for (const auto &post : user.posts)
    {
      cout << "- " << post << endl;
    }
  }
};

int main()
{
  SocialNetwork network;
  int choice;

  while (true)
  {
    cout << "\n1. Create Profile\n2. Login\n3. Add Friend\n"
         << "4. Delete Friend\n5. Post Message\n6. View Profile\n7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      network.createProfile();
      break;
    case 2:
      network.login();
      break;
    case 3:
      network.addFriend();
      break;
    case 4:
      network.deleteFriend();
      break;
    case 5:
      network.post();
      break;
    case 6:
      network.viewProfile();
      break;
    case 7:
      cout << "Exiting...\n";
      return 0;
    default:
      cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}