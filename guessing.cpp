#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class NumberGuessingGame
{
private:
  int secretNumber;
  int attempts;
  int maxAttempts;

  bool isPrime(int n)
  {
    if (n <= 1)
      return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
      if (n % i == 0)
        return false;
    }
    return true;
  }

  string getClosenessHint(int guess)
  {
    int difference = abs(guess - secretNumber);
    if (difference <= 5)
      return "You're very close!";
    if (difference <= 10)
      return "You're getting warm!";
    if (difference <= 20)
      return "You're in the ballpark!";
    return "You're quite far off.";
  }

public:
  NumberGuessingGame(int max) : maxAttempts(max)
  {
    srand(time(0));
    secretNumber = rand() % 100 + 1;
    attempts = 0;
  }

  void play()
  {
    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl;
    cout << "Here's a clue: The number " << (isPrime(secretNumber) ? "is" : "is not") << " prime." << endl;

    while (attempts < maxAttempts)
    {
      int guess;
      cout << "Enter your guess: ";
      cin >> guess;
      attempts++;

      if (guess < secretNumber)
      {
        cout << "Too low! " << getClosenessHint(guess) << endl;
      }
      else if (guess > secretNumber)
      {
        cout << "Too high! " << getClosenessHint(guess) << endl;
      }
      else
      {
        cout << "Congratulations! You guessed the number in " << attempts << " attempts!" << endl;
        return;
      }

      cout << "Attempts left: " << maxAttempts - attempts << endl;

      if (attempts % 3 == 0)
      {
        cout << "Reminder: The number " << (isPrime(secretNumber) ? "is" : "is not") << " prime." << endl;
      }
    }

    cout << "Sorry, you've run out of attempts. The number was " << secretNumber << "." << endl;
  }
};

int main()
{
  NumberGuessingGame game(10);
  game.play();
  return 0;
}