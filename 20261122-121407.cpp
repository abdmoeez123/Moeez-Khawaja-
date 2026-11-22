#include <iostream>
using namespace std;

const int CAP = 8;

// Insert x at index pos. Valid pos: 0..size (size = append). Fails if full.
bool insertAt(int a[], int& size, int cap, int pos, int x) {
    if (size >= cap || pos < 0 || pos > size) return false;
    for (int i = size; i > pos; --i) a[i] = a[i - 1];  // shift right, from the END
    a[pos] = x;
    ++size;
    return true;
}

// Delete element at index pos. Valid pos: 0..size-1.
bool deleteAt(int a[], int& size, int pos) {
    if (pos < 0 || pos >= size) return false;           // also covers empty list
    for (int i = pos; i < size - 1; ++i) a[i] = a[i + 1]; // shift left, from the FRONT
    --size;                                              // a[size] is never read
    return true;
}

void display(const int a[], int size) {
    cout << "[";
    for (int i = 0; i < size; ++i) cout << a[i] << (i + 1 < size ? ", " : "");
    cout << "]  size=" << size << "  capacity=" << CAP << "\n"<<endl;
}

void demo() {
    int a[CAP] = {70, 80, 90, 85};
    int size = 4;
    cout << "--- Demo ---\nStart: "; display(a, size);
    
        cout << "Insert 75 at 2: " << insertAt(a, size, CAP, 2, 75) << "  "<<endl; display(a, size);
    cout << "Delete index 1: " << deleteAt(a, size, 1) << "  "<<endl;          display(a, size);
    cout << "Delete beginning: " << deleteAt(a, size, 0) << "  "<<endl;        display(a, size);
    cout << "Delete middle (idx 1): " << deleteAt(a, size, 1) << "  "<<endl;   display(a, size);
    cout << "Delete end (idx size-1): " << deleteAt(a, size, size - 1) << "  "<<endl; display(a, size);

    cout << "Delete index -1: " << deleteAt(a, size, -1) << "\n"<<endl;
    cout << "Delete index==size: " << deleteAt(a, size, size) << "\n"<<endl;

    // Delete last remaining item -> empty, then try deleting from empty
    while (size > 0) deleteAt(a, size, size - 1);
    cout << "After emptying: "<<endl; display(a, size);
    cout << "Delete from empty: " << deleteAt(a, size, 0) << "\n"<<endl;

    // Fill to capacity, then fail an insertion
    for (int i = 0; i < CAP; ++i) insertAt(a, size, CAP, size, 10 * (i + 1));
    cout << "Full: "<<endl; display(a, size);
    cout << "Insert when full: " << insertAt(a, size, CAP, 0, 99) << "  "<<endl; display(a, size);
    cout << "--- End demo ---\n\n"<<endl;
}

int main() {
    demo();

    int a[CAP] = {70, 80, 90, 85};
    int size = 4;
    int choice;
    do {
        cout << "\n1) Display  2) Insert  3) Delete  4) Exit\nChoice: "<<endl;
        if (!(cin >> choice)) break;
        if (choice == 1) {
            display(a, size);
        } else if (choice == 2) {
            int pos, x;
            cout << "Position and value: "<<endl;
            cin >> pos >> x;
            cout << (insertAt(a, size, CAP, pos, x) ? "Inserted.\n" : "Insert failed (full or bad index).\n")<<endl;
        } else if (choice == 3) {
            int pos;
            cout << "Position: "<<endl;
            cin >> pos;
            cout << (deleteAt(a, size, pos) ? "Deleted.\n" : "Delete failed (empty or bad index).\n")<<endl;
        } else if (choice != 4) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
    