#include <iostream>

using std::cout;

template<class E>
class ArrayList	{
	
private:
	int len;
	int count;
	E *items = nullptr;

public:
	ArrayList() {
		len = 2;
		count = 0;
		items = new E[len];
	}
	ArrayList(int len) {
		count = 0;
		this->len = len;
		items = new E[len];
	}
	ArrayList(const ArrayList& array) {
		
		copy(array);
		
	}
	~ArrayList() {
		reset();
	}
	
	void add(E item){
		
		if(size() >= length()) growth();
		
		items[count++] = item;
	}
	
	// ! ------------------- insert methods ----------- //
	
	void insert(int index, E item){
		if(index >= 0 && index <= size()) { 
			
			add(item);
			
			for(int i = size()-1; i > index; i--){
				E temp = items[i];
				items[i] = items[i-1];
				items[i-1] = temp;
			}
		}
	}

	void insert(const E *index, E item){
		
		if(index >= begin() && index <= end()) {
			
			int i = index - this->begin();
			insert(i, item);
			
		}
	}
	
	void insert(int index, int n, E item){
		
		for(int i=0;i<n;i++)
			insert(index+i,item);

	}

	void insert(const E *index, const E *first, const E *last){
		
		if(index >= this->begin() && index <= this->end()) {
			int pos = index - this->begin();
		
			insert(pos, first, last);
		}
		
	}

	void insert(int index, const E *first, const E *last){
		
		if(index >= 0 && index <= size()){

			if(first >= begin() && last <= end()){
				
				int to = last - first;
				int start = first - begin();
				E *temp = new E[len];
				
				for(int i = 0; i < to; i++){
					temp[i] = items[start++];
				}
				
				start = 0;
				
				while(first++ != last){
					insert(index++, temp[start++]);
				}
			}
			else {
				while(first != last){
					insert(index++, *first++);
				}
			}
		}
	}
	
	// ------------------- insert methods ----------- !//
	
	int counter(E item) {
		
		int temp = 0;
		
		for(int i = 0; i < size(); i++)
			if(items[i] == item) 
				temp++;
		
		return temp;	
	}
	
	bool contains(E item) {
		
		for(int i = 0; i < size(); i++)
			if(items[i] == item) return true;
		
		return false;
	}
	
	void copy(const ArrayList& array) {
		
		this->len = array.len;
		this->count = array.count;
		this->items = new E[len];

		for(int i = 0; i < array.count; i++){
			this->items[i] = array.items[i];
		}
	}
	
	void print(){
		
		cout<<"[";
		
		for(int i = 0; i < size(); i++){
			
			cout<<items[i];
			if(i+1 < size()) { cout<<", "; }
		}
		
		cout<<"]";
	}
	
	int indexOf(E item){
		
		for(int i = 0; i < size(); i++) 
			if(items[i] == item) return i;
		
		return -1;
	}
	
	// !------------------- get methods ----------- !//
	
	E& get(int index){ // E read only -- E& read and write
		if(isEmpty()){
			throw "Error : ArrayIsEmpty";
		}
		else if(size() <= index){
			throw "Error : IllegalIndex";
		}
		else if(index < 0){
			return *(end()+index);
		}
		else if(index >= 0){
			return *(begin()+index);
		}
	}
	E& operator[](int index){ // Array.get() -> Array[] -- // read only -- E& read and write
		return get(index);
	}
	
	// ------------------- get methods ----------- !//
	
	// !------------------- remove methods ----------- //
	
	bool remove(E item) {
		
		int index = indexOf(item);
		
		if(index != -1) {
			pop(index);
			return true;
		}

		return false;
	}
	
	bool remove(E item, int to) {
		
		int timer = counter(item);
		
		if(to > timer || timer == 0) return false;
		
		while(to-- > 0) {
			remove(item);
		}

		return true;
	}
	
	// ------------------- remove methods -----------! //
	
	// !------------------- pop methods ----------- //
	
	E pop(){
		return pop(-1);
	}
	
	E pop(const E *index){
		
		if(index != end()) {
			
			int i = index - begin();
			
			return pop(i);	
		}
	}
	
	void pop(const E *first, const E* last){
		
		int i = first - begin();
		
		while(first++ != last){
			
			pop(i);
			
		}
	}
	
	E pop(int index){  
		
		if(index < count && index >= (count * -1)){

			if(index < 0){
				index = size() + index;
			}
			
			// E *oldValue = new E[1];
			E oldValue = items[index];

			for(int i = index; i < size() - 1; i++){ // HATA = i < count
				items[i] = items[i+1];
			}
			
			count--;
			
			if(size() <= (int)(length() / 3)) shrink();
			
			return oldValue;
		}
		else{
			throw "Error : IllegalArgumentException";
		}	
	}
	// ------------------- pop methods -----------! //
	
	bool isEmpty() { return size() == 0; }
	
	void clear(){
		reset();
		items = new E[len];
	}
	
	
	E front(){
		if(isEmpty()) { throw "Error : ArrayIsEmpty"; }
		
		return items[0];
	}
	
	E back(){
		if(isEmpty()) { throw "Error : ArrayIsEmpty"; }
		
		return items[size() - 1];
	}
	
	E* begin() { return items; }
	
	E* end() { return items + size(); }
	
	int size() { return count; }
	
private:
	int length() { return len; }
	
	void growth(){
		len = len * 2;
		swap();
	}
	void shrink(){
		len = len / 2;
		swap();
	}
	
	void swap() {
		
		E *newItem = new E[len];
		
		for(int i = 0; i < size(); i++){
			newItem[i] = items[i];
		}
		delete[] items;
		items = newItem;
		newItem = nullptr;
	}

	void reset(int count = 0,int len = 2) {
		
		delete[] items;
		items = nullptr;
		this->count = count;
		this->len = len;
	}
};
