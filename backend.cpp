#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

bool detectLoopFloyd(Node* head) {
    if (!head) return false;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

Node* createLinkedList(const vector<int>& values, int loopPos) {
    if (values.empty()) return nullptr;
    
    Node* head = new Node(values[0]);
    Node* current = head;
    Node* loopNode = (loopPos == 1) ? head : nullptr;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new Node(values[i]);
        current = current->next;
        
        if (i == loopPos - 1) {
            loopNode = current;
        }
    }
    
    if (loopNode) {
        current->next = loopNode;
    }
    
    return head;
}

vector<int> parseInput(const string& input) {
    vector<int> values;
    stringstream ss(input);
    string token;
    
    while (getline(ss, token, ',')) {
        try {
            values.push_back(stoi(token));
        } catch (...) {
            // Skip invalid entries
            continue;
        }
    }
    
    return values;
}

int main() {
    string input;
    int loopPos;
    
    cout << "Linked List Loop Detection\n";
    cout << "Enter comma-separated values (e.g., 1,2,3,4,5): ";
    getline(cin, input);
    
    cout << "Enter loop position (0 for no loop, 1 for first node, etc.): ";
    cin >> loopPos;
    
    // Parse input
    vector<int> values = parseInput(input);
    
    if (values.empty()) {
        cout << "Error: No valid numbers entered.\n";
        return 1;
    }
    
    if (loopPos < 0 || loopPos > values.size()) {
        cout << "Error: Invalid loop position. Must be between 0 and " << values.size() << ".\n";
        return 1;
    }
    
    // Create linked list
    Node* head = createLinkedList(values, loopPos);
    
    // Detect loop
    bool hasLoop = detectLoopFloyd(head);
    
    // Display results
    cout << "\nResults:\n";
    cout << "Linked List: ";
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i];
        if (i != values.size() - 1) cout << " -> ";
    }
    
    if (hasLoop) {
        cout << " -> [" << values[loopPos - 1] << "] -> ... (loop)\n";
        cout << "Loop detected! The list loops back to position " << loopPos 
             << " (value: " << values[loopPos - 1] << ")\n";
    } else {
        cout << " -> NULL\n";
        cout << "No loop detected - this is a properly terminated linked list\n";
    }
    
    // Clean up
    Node* current = head;
    unordered_set<Node*> visited;
    while (current && visited.find(current) == visited.end()) {
        visited.insert(current);
        Node* next = current->next;
        delete current;
        current = next;
    }
    
    return 0;
}