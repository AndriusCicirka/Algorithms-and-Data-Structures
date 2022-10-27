#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stack>

using namespace std;

struct node
{
	int data;
	node *next;	
};

class linkedList
{
	private:
		node *head;
		node *tail;

		void emptyWarning(bool affirmativeAnswer = true){
            if(affirmativeAnswer){cout << "\n- List is empty.";}
                else {cout << "\n- List is not empty.";}
        }

	public:
		linkedList()
		{
			head = NULL; 
			tail = NULL;
		}
		
		void display()
		{	
			node *temp = head;
			if(!isEmpty(false)){
				cout << "\n- ";
				while(temp != NULL)
				{	
					cout << temp -> data << "\t";
					temp = temp -> next;
				}
			}
			else emptyWarning();	
		}

		bool isEmpty(bool display = true){
			if(head == NULL){
				if(display) {emptyWarning();}
				return true;
			}
			else{
				if(display) {emptyWarning(false);}
				return false;
			}
		}

		int size(bool display = true){
			if(isEmpty(false)){emptyWarning();}
			else{
				int count = 0;
				node *temp = head;
				while(temp != NULL)
				{	
					count++;
					temp = temp -> next;
				}

				if(display){cout << "\n- List size: " << count;}
				return count;
			}
		}
		
		void addNodeStart(int value)
		{	
			node *temp = new node;
			if(!isEmpty(false)){
				
				temp -> data = value;
				temp -> next = head;

				head = temp;
			}
			else{

				temp -> data = value;
				temp -> next = NULL;

				head = temp;
				tail = temp;
			}		
		}

		void addNodePos(int pos, int value)
		{
			bool validOperation = true;

			if(pos == 1){
			addNodeStart(value);
			}
			else{
				node *temp = new node;
				node *pre, *cur = head;

				for(int i = 1; i < pos; i++){
					if(i != (pos - 1) && cur -> next == NULL){
						cout << "\n- Operation is invalid!";
						validOperation = false;
						break;
					}

					pre = cur;
					cur = cur -> next;
				}

				if(validOperation){
					pre -> next = temp;
					temp -> data = value;
					temp -> next = cur;
				}
			}
		}	

		void addNodeEnd(int value)
		{
			node *temp = new node;
			temp -> data = value;
			temp -> next = NULL;

			if(isEmpty(false))
			{
				head = temp;
				tail = temp;
			}
			else
			{	
				tail -> next = temp;
				tail = temp;
			}
		}

		void deleteNodeStart(){
			if(!isEmpty(false)){
				node *temp = head;
				if(head != tail){
					head = head -> next;
				}
				else{
					head = NULL;
					tail = NULL;		
				}
				delete temp;
			}
		}

		void deleteNodePos(int pos){

			if(!isEmpty(false)){			
				node *temp = head;

				if(head == tail && pos != 1){
					cout << "\n- Operation is invalid / Node does not exist.";
				}
				else if(pos == 1){
					deleteNodeStart();
				}
				else{
					for (int i = 1; temp != NULL && i < pos - 1; i++){
						temp = temp -> next;
					}
						
					if (temp == NULL || temp -> next == NULL){
						cout << "\n- Operation is invalid / Node does not exist.";
					}
					else{
						node* next = temp->next->next;
						delete temp -> next;
						temp -> next = next;
					}	
				}
			}
		}

		void deleteNodeEnd(){
			if(!isEmpty(false)){
				node *temp = head;

				if(head == tail){
					head = NULL;
					tail = NULL;
					delete temp;
				}
				else {
					while(temp -> next -> next != NULL)
						temp = temp -> next;
					
					tail = temp;
      				temp -> next = NULL;
					temp = temp -> next;
      				delete temp; 
				}		
			}
		}

		void search(int searchItem){
			node *temp = head;
			bool exists = false;
			int i = 0;
			if(!isEmpty(false)){
				while(temp != NULL){
					i++;
					if(temp -> data == searchItem){
						if(!exists){cout << "- Item is in position number " << i; exists = true;}
						else{cout << ", " << i;}
						temp = temp -> next;
					}
					else{
						temp = temp -> next;
					}
				}
				if(!exists){cout << "- Item does not exist.";}
			}
			else emptyWarning();
		}

		void clear(bool display = true){
  			node *temp = new node;
  			while(head != NULL) {
				temp = head;
				head = head -> next;
				delete temp;
  			}
			if(display){cout << "- List has been cleared.";}
		}

		void reverse(bool byStack = false){
			if(!isEmpty(false)){
				if(!byStack){
					node *prev = head, *temp = head, *cur = head -> next;
				
					prev -> next = NULL;
					tail = head;
					while(cur != NULL) {
						temp = cur -> next;
						cur -> next = prev;
						prev = cur;
						cur = temp;
					}
					head = prev;
				}
				else{
					node *temp = head;
					stack <int> stack;

					while(temp != NULL){
						stack.push(temp -> data);
						temp = temp -> next;
					}
					
					temp = head;
					
					while(temp != NULL){
						temp -> data = stack.top();
						stack.pop();
						temp = temp -> next;
					}
				}
			}
		}

		~linkedList(){
			clear(false);
		}
};

int getCH(){
	char ch = getch();
    ch -= '0';
    return int(ch);
}

int main()
{
	linkedList list;

    int key, temp;

    cout << "Dynamic Linked List";
    cout << "\n\nKeymap: 0 - Exit the program. 1 - Enqueue a value. 2 - Dequeue a value";
    cout << "\n3 - Check the size of the list. 4 - Search for a value. 5 - Check if the list is empty.";
    cout << "\n6 - Display the list. 7 - Reverse the list. 8 - Clear out the list.";
    cout << "\n";

    while(true){
        if(kbhit()){
            key = getCH();

            switch(key){
                case 0: //exit
                    exit(true);
                    break;
                case 1: //enqueue
					cout << "\n\n- Enqueue: ";
					cout << "\n- Enqueue in the front - 1; In a selected position - 2; Enqueue in the back - 3: ";
					key = getCH();
					if(key == 1){
						cout << "\n- Enter the value to be inserted: ";
						cin >> key;
						list.addNodeStart(key);
						list.display();
					}
					else if(key == 2){
						cout << "\n- Enter the value to be inserted: ";
						cin >> key;
						cout << "- Enter the insertion position: ";
						cin >> temp;
						list.addNodePos(temp, key);
						list.display();
					}
					else if(key == 3){
						cout << "\n- Enter the value to be inserted: ";
						cin >> key;
						list.addNodeEnd(key);
						list.display();
					}
					else{
						cout << "\n- Operation is invalid!";
					}
                    break;
                case 2: //dequeue
                    cout << "\n\n- Dequeue: ";
					cout << "\n- Dequeue from the front - 1; From a selected position - 2; Dequeue from the back - 3: ";
					key = getCH();
					if(key == 1){
						list.deleteNodeStart();
						list.display();
					}
					else if(key == 2){
						cout << "\n- Enter the removal position: ";
						cin >> key;
						list.deleteNodePos(key);
						list.display();
					}
					else if(key == 3){
						list.deleteNodeEnd();
						list.display();
					}
					else{
						cout << "\n- Operation is invalid!";
					}
                    break;
                case 3: //size
                    cout << "\n\n- Size: ";
                    list.size();
                    break;
                case 4: //search
                    cout << "\n\n- Search: ";
					cout << "\n- Insert the value to search for: ";
					cin >> key;
					list.search(key);                    
                    break;
                case 5: //isEmpty
                    cout << "\n\n- is Empty: ";
					list.isEmpty();                    
                    break;
                case 6: //display
                    cout << "\n\n- Display:";
                    list.display();
                    break;
                case 7: //reverse
                    cout << "\n\n- Reverse:";
					cout << "\n- Reverse by pointers - 1; Reverse by stack - 2;";
					key = getCH();

					if(key == 1){
						list.reverse(false);
						list.display();
					}
					else if(key == 2){
						list.reverse(true);
						list.display();
					}
					else{
						cout << "\n- Operation is invalid!";
					}
                    break;
                case 8: //clear
                    cout << "\n\n- Clear: \n";
					list.clear();                    
                    break;
				
			}
		}
	}

	return 0;
}