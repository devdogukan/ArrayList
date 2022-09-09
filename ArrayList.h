#include <iostream>

using namespace std;

template<class E>
class ArrayList {
	
private:
	int len;
	int count;
	E *items = NULL; // or nullptr

public:
	ArrayList() {
		len = 2;
		count = 0;
		items = new E[len];
	}
	ArrayList(const ArrayList& array) { // Copy constructor - Deep copy

		this->len = array.len;
		this->count = array.count;
		this->items = new E[len];

		for(int i = 0; i < array.count; i++){
			this->items[i] = array.items[i];
		}
	}
	~ArrayList() {
		this->reset();
	}
	
	void add(E item){
		if(len == count){
			growth();
		}
		items[count++] = item;
	}
	
	void insert(int index, E item){
		if(index >= 0 && index <= length()){ 
			this->add(item);
			for(int i=this->size()-1;i>index;i--){
				int temp = items[i];
				items[i] = items[i-1];
				items[i-1] = temp;
			}
		}
	}

	void insert(const E *index, E item){
		int i = index - this->begin();
		insert(i, item);
	}
	
	void insert(int index, int n, E item){
		for(int i=0;i<n;i++){
			insert(index+i,item);
		}
	}

	void insert(const E *index, const E *first, const E *last){
		
		int pos = index - this->begin();
		
		insert(pos, first, last);
		
	}

	void insert(int index, const E *first, const E *last){
		
		int len = last - first;
		int start = first - this->begin();
		E *temp = new E[len];
		
		for(int i = 0; i < len; i++){
			temp[i] = items[start++];
		}
		
		start = 0;
		
		while(first != last){
			insert(index++, temp[start++]);
			first++;
		}
	}
	
	void print(){
		cout<<"[";
		for(int i=0;i<size();i++){
			cout<<items[i];
			if(i+1 < size()){
				cout<<", ";
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
	
	E& get(int index){ 
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
	E& operator[](int index){ 
		return this->get(index);
	}

	bool isEmpty(){
		return size() == 0;
	}
	void remove(){
		remove(-1);
	}
	void remove(const E *index){
		int i = index == this->end() ? -1 : index - this->begin();
		remove(i);
	}
	void remove(const E *first, const E* last){
		int i = first - this->begin();
		while(first++ != last){
			remove(i);
		}
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
		return items;
	}
	E* end(){
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
		items = newItem; // items artik newItem`in konumunu isaret ediyor
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
		items = NULL; // or nullptr
		this->count = count;
		this->len = len;
	}
};
