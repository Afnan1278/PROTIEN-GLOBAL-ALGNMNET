#include <iostream> 
#include <cstdlib>
using namespace std;


#define stackSize 1000
template <class T>
class stack {
	private:
		T *arr;
		int size;
		int topPointer;
	public:
		
		stack () {
			size=stackSize;
			arr=new T[size];
			topPointer=-1;
		}
		
		stack (int s) {
			size=s;
			arr=new T[size];
			topPointer=-1;
		} 
		
		stack (const stack &rhs) {
			size=rhs.size;
			arr=new T[size];
			topPointer=rhs.topPointer;
			memcpy(arr,rhs.arr,sizeof(T)*size);
		}
		
		stack& operator = (const stack &rhs) {
			if (rhs==*this) {
				return (*this);
			}
			else {
				delete [] arr;
				size=rhs.size;
				arr=new T[size];
				topPointer=rhs.topPointer;
				memcpy(arr,rhs.arr,sizeof(T)*size);
			}
		}
		
		bool isEmpty () {
			if (topPointer==-1) {
				return true;	
			}
			else {
				return false;
			}
		}
		
		void push (T a) {
			if (topPointer>size) {
				cout << "Stack Full";
				exit (1);
			}
			else {
				topPointer++;
				arr[topPointer]=a;
			}
		}
		
		T& pop () {
			if (isEmpty()) {
				cout << "Stack Empty" << endl;
				exit (1);
			}
			else {
				return arr[topPointer--];
			}
		}
		
		T peek () {
			if (isEmpty()) {
				
			}
			else {
				return arr[topPointer];
			}
		}
		
		~stack () {
			delete [] arr;
		}
};

