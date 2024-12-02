#include <iostream>
#include <cmath> // For log2
#include <string> // For string spaces
#include <algorithm> // For find() function
#include <sstream> // For string stream handling

using namespace std;

int ghostPower[100]; // Array to store the ghosts' power
int size = 0;      // Current size of the heap
bool MaxH = true;

// Compare ghost powers based on heap type
bool compare(int a, int b) {
    if (MaxH)
        return a > b;
    else
        return a < b;
}

// Restore heap property after adding a new ghost (insert)
void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (compare(ghostPower[index], ghostPower[parent])) {
            swap(ghostPower[index], ghostPower[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Restore heap property after defeating a ghost (delete)
void heapifyDown(int index) {
    int left, right, extreme;
    while (true) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        extreme = index;

        if (left < size && compare(ghostPower[left], ghostPower[extreme]))
            extreme = left;
        if (right < size && compare(ghostPower[right], ghostPower[extreme]))
            extreme = right;

        if (extreme != index) {
            swap(ghostPower[index], ghostPower[extreme]);
            index = extreme;
        } else {
            break;
        }
    }
}

// Add a new ghost to the heap
void addGhost(int power) {
    if (size == 100) {
        cout << "Ghost hunter can't handle more ghosts!" << endl;
        return;
    }
    ghostPower[size] = power;
    size++;
    heapifyUp(size - 1);
}

// Defeat a specific ghost based on its power level
bool defeatGhost(int power) {
    int index = -1;

    // Find the ghost in the heap
    for (int i = 0; i < size; i++) {
        if (ghostPower[i] == power) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << " Ghost not found!" << endl;
        return false;  // Return false if ghost is not found
    }

    // Replace the defeated ghost with the last ghost in the heap
    ghostPower[index] = ghostPower[size - 1];
    size--;

    // Reorganize the heap
    heapifyDown(index);
    heapifyUp(index);
    return true;  // Return true when ghost is defeated
}

// Convert between Max-Heap and Min-Heap (Switch strategy)
void switchStrategy() {
    MaxH = !MaxH; // Toggle between stronger and weaker ghosts
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapifyDown(i); // Rebuild the heap based on the new strategy
    }
}

// Display the heap as a diagram
void displayDiagram() {
    if (size == 0) {
        cout << " No ghosts to fight!" << endl;
        return;
    }

    int levels = log2(size) + 1; // Calculate the number of levels in the heap
    int index = 0;

    for (int i = 0; i < levels; i++) {
        int levelCount = pow(2, i); // Number of nodes at the current level
        int spacing = pow(2, levels - i); // Adjust spacing for visualization

        for (int j = 0; j < levelCount && index < size; j++) {
            if (j == 0)
                cout << string(spacing / 2, ' '); // Add leading spaces

            cout << ghostPower[index++];
            cout << string(spacing - 1, ' '); // Add spaces between ghosts
        }
        cout << endl; // Move to the next level
    }
}

void displayExitMessage() {
    cout << "      .-." << endl;
    cout << "    (o o)  Boo!" << endl;
    cout << "    | O |" << endl;
    cout << "     `- -'" << endl;
    cout << endl;
    cout << " Ghosts terminated!" << endl;
    cout << " Until next time ghost hunter!" << endl;
}

int main(void) {
    int power;
    char choice;

    // Display menu options
    cout << "\n Ghost Hunter Task Board:" << endl;
    cout << " 0. View Task Board" << endl;
    cout << " 1. Insert Ghost Power" << endl;
    cout << " 2. Defeat Specific Ghost" << endl;
    cout << " 3. Switch Strategy (Max/Min-Heap)" << endl;
    cout << " 4. Exit" << endl;

    while (true) {
        cout << "\n Unveil your ghostly quest! (0-4): ";
        cin >> choice;
        cin.ignore();  // Clear the newline from input buffer
        cout << endl;

        switch (choice) {
            case '0': {
                cout << "\n Ghost Hunter Task Board:" << endl;
                cout << " 0. View Task Board" << endl;
                cout << " 1. Insert Ghost Power" << endl;
                cout << " 2. Defeat Specific Ghost" << endl;
                cout << " 3. Switch Strategy (Max/Min-Heap)" << endl;
                cout << " 4. Exit" << endl;
                cout << endl;
                break;
            }

            case '1': {
                // Insert ghost powers
                cout << " Enter ghost levels (space-separated): ";
                string line;
                getline(cin, line); // Get the entire line of inputs
                stringstream ss(line);
                bool validInput = false;

                while (ss >> power) {
                    if (power < 0) {
                        break;
                    }
                    addGhost(power); // Add each ghost power to the heap
                    validInput = true;
                }

                if (validInput) {
                    cout << "\n The hunter has called upon new spirits. Ghost levels added to the crypt!\n";
                    displayDiagram();
                } else {
                    cout << " The spirits refuse to show themselves." << endl;
                }
                break;
            }

            case '2': {
                // Defeat multiple ghosts at once
                cout << " Enter the power levels of ghosts you want to defeat (space-separated): ";
                string line;
                getline(cin, line);  // Get the entire line of input
                stringstream ss(line);  // Extract individual values
                bool validInput = false;

                while (ss >> power) {
                    if (defeatGhost(power)) {  // Attempt to defeat each ghost entered
                        validInput = true;
                    }
                }

                if (validInput) {
                    cout << "\n Ghosts defeated! The crypt shifts...\n";
                    displayDiagram();
                } else {
                    cout << " The ghost you seek is not here, hunter!" << endl;
                }
                break;
            }

            case '3': {
                // Switch strategy (Max-Heap/Min-Heap)
                switchStrategy();
                cout << " Strategy switched. Updated Ghost Power Diagram:\n";
                displayDiagram();
                break;
            }

            case '4': {
                // Exit the program
                displayExitMessage();
                return 0;
            }

            default:
                cout << " A ghostly chill fills the air... That choice won't work." << endl;
        }
    }

    return 0;
}
