// 1.implementing stack using array 
// #include<bits/stdc++.h>
// using namespace std; 

// #define max_size 10

// class Stack{
//     int arr[max_size];
//     int top; 
//     public:
//     Stack(){
//         top = -1;
//     }

//     // push Method
//     void push(int x){
//         if(top >= max_size - 1){
//             cout<<"StackOverFlow"<<endl;
//             return; 
//         }
//         arr[++top] = x;
//     }
//     //pop method
//     void pop(){
//         if(top < 0){
//             cout<<"Stack underflow"<<endl; 
//             return; 
//         }
//         top--;
//     }

//     // peek method
//     int peek(){
//         if(top < 0){
//             cout<<"Stack is empty"<<endl;
//             return -1; 
//         }
//         return arr[top];
//     }

//     // isEmpty method
//     void isEmpty(){
//         if(top < 0){
//             cout<<"Stack is empty"<<endl;
//         }
//         else{
//             cout<<"Stack is not empty"<<endl;
//         }
//     }
//     // size method
//     void size(){
//         cout<<"Size of stack is: "<<top + 1<<endl;
//     }

//     // isfull method
//     void isFull(){
//         if(top >= max_size - 1){
//             cout<<"Stack is full"<<endl;
//         }
//         else{
//             cout<<"Stack is not full"<<endl;
//         }
//     }
// };

// int main(){
//     Stack s; 
//     s.push(10); 
//     s.push(20);
//     s.push(30);
//     s.size();
//     cout<<"Top element is: "<<s.peek()<<endl;
//     s.pop();
//     cout<<"Top element is: "<<s.peek()<<endl;
//     s.isEmpty();
//     s.isFull();
//     return 0;
// }


//2. // stack implementation using linked list 
// #include<bits/stdc++.h>
// using namespace std; 

// class Node{
//     public: 
//     int data; 
//     Node* next; 
//     Node(int val){
//         data = val; 
//         next = NULL; 
//     }
// };

// class Stack{
//     public: 
//     Node* top; 

//     Stack(){
//         top = NULL; 
//     }

//     // push method 
//     void push(int x){
//         Node* newNode = new Node(x);
//         newNode->next = top; 
//         top = newNode; 
//     }

//     // pop method
//     void pop(){
//         if(top == NULL){
//             cout<<"Stack underflow: "<<endl;
//             return; 
//         }
//         Node* temp = top; 
//         top = top->next; 
//         delete temp;
//     }

//     // peak method; 
//     int peak(){
//         if(top == NULL){
//             cout<<"Stack is empty"<<endl;
//             return -1; 
//         }
//         return top->data; 
//     }

//     // isEmpty method
//     void isEmpty(){
//         if(top == NULL){
//             cout<<"Stack is empty"<<endl;
//         }
//         else{
//             cout<<"Stack is not empty"<<endl;
//         }
//     }

//     // size method
//     void size(){
//         Node* temp = top; 
//         int count = 0; 
//         while(temp != NULL){
//             count++; 
//             temp = temp->next; 
//         }
//         cout<<"Size of stack is: "<<count<<endl;
//     }
// };

// int main(){
//     Stack s; 
//     s.push(10); 
//     s.push(20);
//     s.push(30); 
//     s.size();
//     cout<<"Top element is: "<<s.peak()<<endl;
//     s.pop();
//     cout<<"Top element is: "<<s.peak()<<endl;
//     s.isEmpty();
//     return 0;
// }


//3. // using dequeue to implement stack
#include<bits/stdc++.h>
using namespace std; 

class Stack{
    int n; 
    deque<int>dq; 
    public: 
    Stack(int size){
        n = size; 
    }

    void push(int x){
        if(dq.size() == n){
            cout<<"Stack Overflow"<<endl;
            return;
        }
        dq.push_back(x);
    }

    void pop(){
        if(dq.empty()){
            cout<<"Stack unuderflow"<<endl;
            return; 
        }
        dq.pop_back(); 
    }

    int peak(){
        if(dq.empty()){
            cout<<"Stack is empty"<<endl;
            return -1; 
        }
        return dq.back(); 
    }

    bool isEmpty(){
        if(dq.empty()){
            cout<<"Stack is empty"<<endl;
        }
        else{
            cout<<"Stack is not empty"<<endl;
        }
    }
    void size(){
        cout<<"Size of stack is: "<<dq.size()<<endl;
    }
};

int main(){
    Stack s(5); 
    s.push(10); 
    s.push(20);
    s.push(30);
    s.push(40);
    s.size();
    cout<<"Top element is: "<<s.peak()<<endl;
    s.pop();
    cout<<"Top element is: "<<s.peak()<<endl;
    s.isEmpty();
    return 0;
}
