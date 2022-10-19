#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

#define MAXSIZE 5

class staticQueueArray
{
	private:
		int qfront = -1, qback = -1, qtempfront = -1, qtempback = -1;
		int array[MAXSIZE] = {0}, tempArray[MAXSIZE] = {0};

        void emptyWarning(bool affirmativeAnswer = true){
            if(affirmativeAnswer){cout << "- Array is empty.";}
                else {cout << "- Array is not empty: ";}
        }

        void fullWarning(bool affirmativeAnswer = true){
            if(affirmativeAnswer){cout << "- Array is full: ";}
                else {cout << "- Array is not full: ";}
        }

	public:		
        bool isFull(bool displayMessage = true){
            if(qfront == 0 && qback == MAXSIZE - 1 || qback == qfront - 1){
                if(displayMessage) {fullWarning();}
                return true;
            }
            else{
                if (displayMessage) {fullWarning(false);}
                return false;  
            }
        }

        bool isEmpty(bool displayMessage = true){
            if(qback == -1 && qfront == -1){
                if(displayMessage) {emptyWarning();}
                return true;
            }
            else{
                if(displayMessage) {emptyWarning(false);}
                return false;
            }
        }
        
        void enqueue(int value, bool displayFunction = false){
            if(!displayFunction){
                if(!isFull(false)){
                    if(!isEmpty(false)){
                        if(qback != MAXSIZE - 1){
                            qback++;
                            array[qback] = value;
                        }
                        else{
                            qback = 0;
                            array[0] = value;
                        }
                    }
                    else{
                        qfront = 0, qback = 0;
                        array[0] = value;                    
                    }
                }
                else fullWarning(); 
                }
            else{
                qtempfront = 0;
                qtempback++;
                tempArray[qtempback] = value;
            }     
        }

        void dequeue(bool displayFunction = false, bool reverseOrder = false){
            if(!displayFunction){
                if(!isEmpty(false)){
                    if(qfront == qback){
                        qfront = -1, qback = -1;
                    }
                    else if(qfront < qback){
                        qfront++;
                    }
                    else if(qback < qfront && qfront != MAXSIZE - 1){
                        qfront++;
                    }
                    else if(qback < qfront && qfront == MAXSIZE - 1 && qback != 0){
                        qfront = 0;
                    }
                    else{
                        qfront = qback;
                    }
                }
            }
            if(displayFunction && !reverseOrder){qtempfront++;}
            if(reverseOrder){qtempback--;}
        }

        int front(bool displayMessage = true, bool displayFunction = false, bool reverseFunction = false){
            if(!displayFunction){
                if(displayMessage){cout << "- Front element of the queue: ";}
                if(!reverseFunction)cout << array[qfront] << " ";

                return array[qfront];
            }
            else{
                return tempArray[qtempfront];
            }
        }

        int back(bool displayMessage = true, bool reverseFunction = false){
            if(!reverseFunction){
                if(displayMessage){cout << "- Back element of the queue: ";}
                cout << array[qback] << " ";

                return array[qback]; 
            }
            else{
                return tempArray[qtempback];
            }    
        }

        void display(){
            cout << "- ";
            if(!isEmpty(false)){
                while(!isEmpty(false)){
                    enqueue(front(false, false), true);
                    dequeue();
                }

                while(qtempfront != qtempback + 1){
                    enqueue(front(false, true), false);
                    dequeue(true);
                }
                qtempfront = -1, qtempback = -1; 
            }
            else emptyWarning();        
        }

        void reverse(){
            if(!isEmpty(false)){
                while(!isEmpty(false)){
                    enqueue(front(false, false, true), true);
                    dequeue();
                }

                while(qtempfront != qtempback + 1){
                    enqueue(back(false, true), false);
                    dequeue(true, true);
                }
                qtempfront = -1, qtempback = -1; 
            }        
        }

        void clear(){
            qfront = -1, qback = -1;
        }
};

int main(){

    staticQueueArray arr;

    char ch;
    int key, temp;

    cout << "Static Queue Array";
    cout << "\n\nKeymap: 0 - Exits the program. 1 - Enqueues a value. 2 - Dequeues a value.";
    cout << "\n3 - Displays value in the front. 4 - Displays value in the back. 5 - Checks if queue is empty.";
    cout << "\n6 - Checks if queue is full. 7 - Displays the queue. 8 - Reverses the queue. 9 - Clears the queue.";
    cout << "\n";

    while(true){
        if(kbhit()){
            ch = getch();
            ch -= '0';
            key = int(ch);

            switch(key){
                case 0: //exit
                    exit(true);
                    break;
                case 1: //enqueue
                    cout << "\n\n- Enter a value to enqueue: ";
                    cin >> key;
                    arr.enqueue(key);
                    arr.display();
                    break;
                case 2: //dequeue
                    cout << "\n\n- Dequeue: \n";
                    arr.dequeue();
                    arr.display();
                    break;
                case 3: //front
                    cout << "\n\n";
                    arr.front();
                    break;
                case 4: //back
                    cout << "\n\n";
                    arr.back();
                    break;
                case 5: //isEmpty
                    cout << "\n\n";
                    arr.isEmpty();
                    cout << "\n";
                    arr.display();
                    break;
                case 6: //isFull
                    cout << "\n\n";
                    arr.isFull();
                    cout << "\n";
                    arr.display();
                    break;
                case 7: //display
                    cout << "\n\n- Display: \n";
                    arr.display();
                    break;
                case 8: //reverse
                    cout << "\n\n- Reverse: \n";
                    arr.reverse();
                    arr.display();
                    break;
                case 9: //clear
                    cout << "\n\n- Clear: \n";
                    arr.clear();
                    break;
            }
        }
    }

    return 0;
}