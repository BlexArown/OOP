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
    stack<int> chetnie;
    stack<int> nechetnie;

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

    while (!st.empty()) {
        int x = st.top();
        st.pop();

        if (x % 2 == 0)
            chetnie.push(x);
        else
            nechetnie.push(x);
    }

    cout << "Стек четных чисел ";
    printStack(chetnie);

    cout << "Стек нечетных чисел ";
    printStack(nechetnie);

    return 0;
}

