/*Function templates are special functions that can operate 
with generic types. This allows us to create a function 
template whose functionality can be adapted to more than 
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/
#include <iostream>
using namespace std;

template<typename T>
class Queue {
	public:
	Queue();
	~Queue();
	bool isEmpty() const;
	int size() const;
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const;
	string front();
	void printQueue(ofstream &resultFile);

	private:
	struct QueueNode {
		T item;
		QueueNode *next;
		};
	int _size;
	/* to avoid the traversal to the last node, 
	 an additional pointer to the last node is defined*/
	QueueNode *_lastNode;
};

template<typename T>
Queue<T>::Queue() {
    _size=0;

}

template<typename T>
Queue<T>::~Queue() {

}

template<typename T>
bool Queue<T>::isEmpty() const {
    if (_size==0)
        return true;
    return false;
}

template<typename T>
void Queue<T>::enqueue(const T &newItem) {
    auto *temp=new QueueNode();
    if (isEmpty()){
        temp->item=newItem;
        temp->next=temp;
        _lastNode=temp;
    }else{
        temp->next=_lastNode->next;
        temp->item=newItem;
        _lastNode->next=temp;
        _lastNode=temp;
    }
    _size++;
}

template<typename T>
int Queue<T>::size() const {
    return _size;
}

template<typename T>
void Queue<T>::dequeue() {
    if (isEmpty()){

    } else if (size()==1){
        QueueNode* temp= _lastNode->next;
        delete temp;
        _size--;
    } else{
        QueueNode* temp= _lastNode->next;
        _lastNode->next=temp->next;
        delete  temp;
        _size--;
    }
}

template<typename T>
void Queue<T>::getFront(T &queueTop) const {

}

template<typename T>
void Queue<T>::printQueue(ofstream &resultFile) {
    if (!isEmpty()){
        QueueNode *temp=_lastNode->next;
        do {
            resultFile<<temp->item<<endl;
            temp=temp->next;
        }while (temp!=_lastNode->next);
    }
}

template<typename T>
string Queue<T>::front() {
    QueueNode *temp=_lastNode->next;
    return temp->item;
}

