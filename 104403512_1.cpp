#include<iostream>
#include<fstream>
using namespace std;
#define MAXLEN 100

// C++
// �w�q���|��Ƶ��c 
struct stack{
	int top=0;
	char items[MAXLEN];
};

// �s���ɮרC�@�檺��T 
char line[MAXLEN];

// If stack is full
int IsFull(stack *s){
	if(s->top>=MAXLEN){
		return 1;
	}else{
		return 0;
	}
}

// If stack is empty
int IsEmpty(stack *s){
	if(s->top==0){
		return 1;
	}else{
		return 0;
	}
}

// Pop the stack
char Pop(stack *s){
	if(IsEmpty(s)){
//		printf("Stack is empty!\n");
//		printf("Lack of ( ! \n");
		return ' ';
	}else{
		char data = s->items[s->top-1];
		s->top--;
		return data;
	}
}

// Push the stack
void Push(char item,stack *s){
	if(IsFull(s)){
//		printf("Stack is full!\n");
//		printf("Lack of ) ! \n");
	}
	else{
		(s->top)++;
		s->items[s->top-1]=item;
		
	}
}
 
// Read the file   
int main(){
    fstream file1,file2;
    
// Open the file to be read
    file1.open("input1.txt",ios::in);
    
// Open the file to write 
	file2.open("output1.txt", ios::out | ios::trunc);
	
// Read one line each time
    while(file1.getline(line,sizeof(line),'\n')){
    	
		// Declare a stack
		stack s; 
		
		// Read each character one time
        for(int i=0;i<sizeof(line);i++){
        	
        	if(line[i]=='('){
        		// If meet lparen, push it in the stack
    			Push('(',&s);
			}else if(line[i]==')'){
				// If meet rparen, pop the stack
				Pop(&s);
			}else if(line[i]==line[99]){
				// If we meet the end
				break;
			}
			// ��L�i��|�J��Ʀr���A��else���p�A�o�̤�������B�z 
				
		}
		printf("\n");
		
//		To determine it's valid or not
		if(IsEmpty(&s)){
			//1 as valid
			file2<<"1\n";
		}else{
			//0 as invalid
			file2<<"0\n";
		}
	
    }
    
//  Close two files
    file1.close();
 	file2.close();
 	
    system("pause");
    return 0;
}
