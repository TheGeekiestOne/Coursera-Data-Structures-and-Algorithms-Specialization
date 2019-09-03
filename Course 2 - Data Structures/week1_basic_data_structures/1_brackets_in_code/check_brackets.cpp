#include <iostream>
#include <stack>
#include <string>

using namespace std;


struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']') {
            return true;
        }
        if (type == '{' && c == '}') {
            return true;
        }
        if (type == '(' && c == ')') {
            return true;
        }
        return false;
    }

    char type;
    int position;
};

void print_stack(stack<Bracket> st) {
    char c;
    while (st.size()) {
        c = st.top().type;
        cout << c;
        st.pop();
    }
    cout << endl;
}

int main() {
    std::string text;
    getline(std::cin, text);
    int faulty_position = -1;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket *b = new Bracket(next, position + 1);
            opening_brackets_stack.push(*b);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.size() == 0) {
                faulty_position = position + 1;
                break;
            } else if (opening_brackets_stack.top().Matchc(next)) {
                // pop it
                opening_brackets_stack.pop();
            } else {
                faulty_position = position + 1;
                break;
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.size() == 0 && faulty_position == -1) {
        cout << "Success" << endl;
    } else {
        if (opening_brackets_stack.size() && faulty_position == -1) {
            faulty_position = opening_brackets_stack.top().position;
        }
        cout << faulty_position << endl;
    }

    return 0;
}
