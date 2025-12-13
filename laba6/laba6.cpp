#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Letter {
private:
    char ch;
public:
    Letter(char c) { ch = c; }
    char getChar() const { return ch; }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите предложение: ";
    string sentence;
    getline(cin, sentence);

    queue<Letter> queues[50];
    int countWords = 0;

    string currentWord = "";

    for (int i = 0; i <= sentence.size(); i++) {
        if (i < sentence.size() && sentence[i] != ' ') { currentWord += sentence[i]; }
        else {
            if (currentWord.size() > 0) {
                for (int j = 0; j < currentWord.size(); j++) {
                    Letter obj(currentWord[j]);
                    queues[countWords].push(obj);
                }
                countWords++;
                currentWord = "";
            }
        }
    }

    cout << "\nОчереди слов:\n";

    for (int i = 0; i < countWords; i++) {
        cout << "Очередь слова " << i + 1 << ": ";

        queue<Letter> temp = queues[i];

        while (!temp.empty()) {
            cout << temp.front().getChar();
            temp.pop();
        }

        cout << endl;
    }

    return 0;
}
