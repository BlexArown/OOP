#include <iostream>
#include <stack>
using namespace std;

void printStack(stack<int> st) {
    cout << "(верх → низ): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    stack<int> st;
    int n;

    cout << "Введите количество чисел: ";
    cin >> n;

    cout << "Введите элементы стека:" << endl;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.push(x);
    }

    cout << "\nИсходный стек ";
    printStack(st);

    stack<int> result;

    int maxValue = -99999999;

    while (!st.empty()) {
        int x = st.top();
        st.pop();

        if (x > maxValue) {
            result.push(x);
            maxValue = x;
        }
    }

    stack<int> finalStack;
    while (!result.empty()) {
        finalStack.push(result.top());
        result.pop();
    }

    cout << "Полученный стек ";
    printStack(finalStack);

    return 0;
}
