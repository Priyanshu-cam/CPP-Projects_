// // queue implementation using linkedList 

// #include<bits/stdc++.h>
// using namespace std; 

// class Queue {
//     private: 
//     struct Node {
//         int data; 
//         Node* next; 
//     };
//     Node* front; 
//     Node* rear; 

//     public: 
//     Queue() {
//         front = nullptr; 
//         rear = nullptr; 
//     }

//     void enqueue(int value){
//         Node* newNode = new Node(); 
//         newNode->data = value; 
//         newNode->next = nullptr; 

//         if(rear == nullptr){
//             front = rear = newNode; 
//             return; 
//         }
//         rear->next = newNode; 
//         rear = newNode; 
//     }

//     // Dequeue function
//     void dequeue(){
//         if(front == NULL){
//             cout<<"Queue is empty"<<endl;
//             return;
//         }
//         Node* temp = front; 
//         front = front->next; 

//         if(front == nullptr){
//             rear = nullptr; 
//         }

//         delete temp; 
//     }

//     int peek(){
//         if(front == NULL){
//             cout<<"Queue is empty"<<endl;
//             return -1; 
//         }
//         return front->data; 
//     }
    
// };

// int main(){
//     Queue q; 
//     q.enqueue(10);
//     q.enqueue(20);
//     q.enqueue(30);
//     cout<<q.peek()<<endl; // 10
//     q.dequeue();
//     cout<<q.peek()<<endl; // 20
//     return 0;
// }



// Queue implementation using array or circular array

// #include<bits/stdc++.h>
// using namespace std; 

// #define MAX 10

// class Queue {
//     private: 
//     int arr[MAX]; 
//     int front; 
//     int rear; 
//     int size; 

//     public: 
//     Queue() {
//         front = -1; 
//         rear = -1; 
//         size = 0; 
//     }

//     void enqueue(int val){
//         if(size == MAX){
//             cout<<"Queue is full"<<endl;
//             return; 
//         }
//         rear = (rear + 1) % MAX; // to make it circular
//         arr[rear] = val; 

//         if(front == -1){
//             front = rear; 
//         }
//         size++; 
//     }

//     void dequeue(){
//         if(size == 0){
//             cout<<"queue is empty"<<endl;
//             return;
//         }
//         front = (front + 1) % MAX; // to make it circular
//         size--; 
//     }

//     int peek(){
//         if(size == 0){
//             cout<<"queue is empty"<<endl;
//             return -1; 
//         }
//         return arr[front];
//     }


// };
// int main(){
//     Queue q; 
//     q.enqueue(10);
//     q.enqueue(20);   
//     q.enqueue(30);
//     cout<<q.peek()<<endl; // 10
//     q.dequeue();
//     cout<<q.peek()<<endl; // 20
//     return 0;
// }


// queue using stacks

#include<bits/stdc++.h>
using namespace std; 

class Queue {
    private: 
    stack<int> s1; 
    stack<int> s2;

    public: 
    void enqueue(int val){
        s1.push(val);

    }

    void dequeue(){
        if(s1.empty() && s2.empty()){
            cout<<"Queue is empty"<<endl;
            return;
        }
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        s2.pop();
    }
    int peek(){
        if(s1.empty() && s2.empty()){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }


};

int main(){
    Queue q; 
    q.enqueue(10);
    q.enqueue(20);   
    q.enqueue(30);
    cout<<q.peek()<<endl; // 10
    q.dequeue();
    cout<<q.peek()<<endl; // 20
    return 0;
}