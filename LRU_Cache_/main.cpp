// building a LRU (Least recently used) cache logic using data structures and classes

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key, value;
    Node *prev;
    Node *next;

    Node(int k, int v)
    {
        key = k;
        value = v;
        prev = next = nullptr;
    }
};

class LRUCache
{
private:
    int capacity;
    unordered_map<int, Node *> cache;

    Node *head; // head of a node  (Most recent used)
    Node *tail; //  tail of a node  (Least Recent used)

    void addToFront(Node *node)
    {
        node->next = head;
        node->prev = nullptr;

        if (head)
            head->prev = node;

        head = node;
        if (!tail)
        {
            tail = node;
        }
    }
    void removeNode(Node *node)
    {
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;
    }
    void moveToFront(Node *node)
    {
        removeNode(node);
        addToFront(node);
    }
    void removeLRU()
    {
        if (!tail)
            return;
        cache.erase(tail->key);
        Node *temp = tail;
        removeNode(tail);
        delete temp;
    }

public:
    LRUCache(int cap)
    {
        capacity = cap;
        head = tail = nullptr;
    }
    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1;

        Node *node = cache[key];
        moveToFront(node);
        return node->value;
    }
    void put(int key, int value)
    {
        if (cache.find(key) != cache.end())
        {
            Node *node = cache[key];
            node->value = value;
            moveToFront(node);
        }
        else
        {
            if (cache.size() == capacity)
                removeLRU();

            Node *node = new Node(key, value);
            addToFront(node);
            cache[key] = node;
        }
    }
    void display()
    {
        Node *curr = head;
        cout << "Cache: ";
        while (curr)
        {
            cout << "[" << curr->key << ":" << curr->value << "]";
            curr = curr->next;
        }
        cout << endl;
    }
    ~LRUCache()
    {
        Node *curr = head;
        while (curr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

int main() {
    int cap;
    cout << "Enter Cache Capacity: ";
    cin >> cap;

    LRUCache myCache(cap);

    int choice, k, v;
    while (true) {
        cout << "\n1. Put (Insert/Update)\n2. Get (Access)\n3. Display\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key and value: ";
                cin >> k >> v;
                myCache.put(k, v);
                break;
            case 2:
                cout << "Enter key: ";
                cin >> k;
                v = myCache.get(k);
                if (v == -1) cout << "Key not found!\n";
                else cout << "Value: " << v << "\n";
                break;
            case 3:
                myCache.display();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}