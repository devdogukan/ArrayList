#include <iostream>

// Warning!!! -> const function can only call const function
using namespace std;

template<class E>
class Array{
	
	private:
		int len;
		int count;
		E *items;
	
	public:
		Array(){
			len = 2;
			count = 0;
			items = new E[len];
		}
		~Array(){
			this->reset();
		}
		
		void add(E item){
			if(len == count){
				growth();
			}
			items[count++] = item;
		}
		
		void insert(int index, E item){
			if(index >= 0 && index < length()){
				this->add(item);
				for(int i=size()-1;i>index;i--){
					int temp = items[i];
					items[i] = items[i-1];
					items[i-1] = temp;
				}
			}
		}

		void insert(int index,int n,E item){
			for(int i=0;i<n;i++){
				insert(index+i,item);
			}
		}

		void insert(int index,E *first,E *last){
			while(first != last){
				insert(index++,*first++);
			}
		}
		
		void print(){
			cout<<"[";
			for(int i=0;i<size();i++){
				cout<<items[i];
				if(i+1 < size()){
					cout<<",";
				}
			}
			cout<<"]";
		}
		
		int size(){
			return count;
		}
		int length(){
			return len;
		}
		
		int indexOf(E item){
			for(int i=0;i<size();i++){
				if(items[i] == item){
					return i;
				}
			}
			return -1;
		}
		
		E& get(int index){ // E read only -- E& read and write
			if(this->isEmpty()){
				throw "Error : ArrayIsEmpty";
			}
			else if(size() <= index){
				throw "Error : IllegalIndex";
			}
			else if(index < 0){
				return *(this->end()+index);
			}
			else{
				return *(this->begin()+index);
			}
		}
		E& operator[](int index){ // Array.get() -> Array[] -- // read only -- E& read and write
			return this->get(index);
		}
	
		bool isEmpty(){
			return size() == 0;
		}
		void remove(){
			this->remove(-1);
			shrink();
		}
		void remove(int index){
			if(index < count && index >= (count * -1)){

				if(index < 0){
					index = this->size() + index;
				}

				for(int i=index;i<count;i++){
					items[i] = items[i+1];
				}
				count--;
				shrink();
			}
			else{
				throw "Error : IllegalArgumentException";
			}
			
		}
		E front(){
			if(isEmpty()){
				throw "Error : ArrayIsEmpty";
			}
			return items[0];
		}
		E back(){
			if(isEmpty()){
				throw "Error : ArrayIsEmpty";
			}
			return items[size() - 1];
		}
		E* begin(){
			if(isEmpty()){
				throw "Error : ArrayIsEmpty";
			}
			return items;
		}
		E* end(){
			if(isEmpty()){
				throw "Error : ArrayIsEmpty";
			}
			return items + size();
		}
		void clear(){
			reset();
			items = new E[len];
		}
	private:
		void growth(){
			len = len*2;
			E *newItem = new E[len];
			for(int i=0;i<size();i++){
				newItem[i] = items[i];
			}
			delete[] items;
			items = newItem;
		}
		void shrink(){
			if(size() <= len/2){
				len /= 2;
				E *newItem = new E[len];
				for(int i=0;i<size();i++){
					newItem[i] = items[i];
				}
				delete[] items;
				items = newItem;
			}
		}

		void reset(int count = 0,int len = 2){
			delete[] items;
			items = nullptr;
			this->count = count;
			this->len = len;
		}
};
