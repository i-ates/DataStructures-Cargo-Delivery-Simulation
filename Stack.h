/*Function templates are special functions that can operate 
with generic types. This allows us to create a function 
template whose functionality can be adapted to more than 
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/
#include <iostream>
using namespace std;

template <typename T>
class Stack {
	public:
	Stack();
	~Stack();
	bool isEmpty() const;
	int size() const;
	
	//Push: Place item on top of the stack
	void push(const T& newItem);
	//Top: Take a look at the topmost item without removing it
	void getTop(T& stackTop) const;
	//Pop: Remove item from the top of the stack
	void pop();
	void printStack(ofstream &resultFile);
	string top();
	private:
	struct ListNode {
		T item;
		ListNode* next;
		};
	ListNode* _head;
	int _size;
};

template<typename T>
Stack<T>::Stack() {
    _head= nullptr;
    _size=0;
}

template<typename T>
Stack<T>::~Stack() {

}

template<typename T>
bool Stack<T>::isEmpty() const {
    if (size()==0)
        return true;
    return false;
}

template<typename T>
int Stack<T>::size() const {
    return _size;
}

template<typename T>
void Stack<T>::push(const T &newItem) {
    auto* temp=new ListNode();
    temp->item=newItem;
    temp->next=_head;
    _head=temp;
    _size++;
}

template<typename T>
void Stack<T>::getTop(T &stackTop) const {

}

template<typename T>
void Stack<T>::pop() {
    ListNode* temp;
    if (_head== nullptr){

    } else{
        temp=_head;
        _head=_head->next;
        temp->next= nullptr;
        delete temp;
        _size--;
    }

}

template<typename T>
void Stack<T>::printStack(ofstream &resultFile) {
    if (!isEmpty()){
        ListNode *temp=_head;
        while (temp!= nullptr){
            resultFile<<temp->item<<endl;
            temp=temp->next;
        }
    }
}

template<typename T>
string Stack<T>::top() {

    return _head->item;
}
	
	
