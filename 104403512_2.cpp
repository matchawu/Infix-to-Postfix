#include<iostream>
#include<fstream>
using namespace std;
#define MAXLEN 100

// 宣告stack結構 
struct stack{
	int top=0;
	char items[MAXLEN];
};

// 宣告line陣列，儲存等下要讀的檔案中 每一行的式子 
char line[MAXLEN];

// 堆疊基本函數 
int IsFull(stack *s){
	if(s->top>=MAXLEN){
		return 1;
	}else{
		return 0;
	}
}

int IsEmpty(stack *s){
	if(s->top==0){
		return 1;
	}else{
		return 0;
	}
}
char Pop(stack *s){
	if(IsEmpty(s)){
		printf("Stack is empty!\n");
		return ' ';
	}else{
		char data = s->items[s->top-1];
		(s->top)--;
		return data;
	}
}

void Push(char item,stack *s){
	if(IsFull(s)){
		printf("Stack is full!\n");
	}
	else{
		(s->top)++;
		s->items[s->top-1]=item;
		
	}
}


//read the file 
int main(){
    fstream file1,file2;
//    open input2.txt to read the lines
    file1.open("input2.txt",ios::in);
//    open output2.txt to write things in
	file2.open("output2.txt", ios::out | ios::trunc);
	
//	read one line every time
    while(file1.getline(line,sizeof(line),'\n')){
    	
    	// infix to postfix 中序式轉後序式 
    	
    	// 宣告s這個堆疊 
		stack s;  
 
		// 初始化postfix陣列 
		char postfix[MAXLEN]={};
		
		// 為postfix陣列的index值，以一個字元一為單位存入後序式 
		int index = 0;
		
		// 一次讀一行 
        for(int n=0;n<sizeof(line);n++){
        	
        	// 設字元變數token為目前所讀到的字元 
        	char token = line[n];
        	
        	// 如果token等於最後一個字元，視為運算式的結束 
        	if(token == line[MAXLEN])
        		break;
        		
        	if(token == ')'){
				// when meet rparen ')'
				// pop the stack until we meet '('
				while (s.items[s.top-1] != '(' && !IsEmpty(&s)){
					// 將pop出來的結果存入postfix陣列 
					postfix[index++] = Pop(&s);
				}
				// pop the '('
				Pop(&s);
			}
			else if(token == '('){
				// when we meet '('
				// push it into the stack directly
				Push(token,&s);
			}
			else if(token == '+' || token == '-'){
				// if we meet + or -
				// if the top of stack is * or / , pop it 
				while(s.items[s.top-1]=='*'||s.items[s.top-1]=='/'||s.items[s.top-1]=='+'||s.items[s.top-1]=='-'){
					// pop出來並存入postfix陣列 
					postfix[index++] = Pop(&s);
				}
				// 把現在遇到的這個+或-放進堆疊 
				Push(token,&s);
			}
			else if(token == '*' || token == '/'){
				// if we meet * or /
				// if the top of stack is * or /
				while(s.items[s.top-1]=='*'||s.items[s.top-1]=='/'){
					// pop出來並存入postfix陣列 
					postfix[index++] = Pop(&s);
				}
				// 把現在遇到的這個*或/放進堆疊 
				Push(token,&s);
			}
			else{
				// if we meet operand
				postfix[index++] = token;
			}
    	}
    	
    	// 做完前面的操作，如果堆疊非空，將剩餘的pop出來存入postfix陣列 
    	while(!IsEmpty(&s)){
    		postfix[index++] = Pop(&s);
		}
		
		// 將postfix後序式寫入file2檔案並換行 
		file2 << postfix;
		file2 << "\n";
		
		// postfix to value 後序式求值 
		
		//宣告一個堆疊 post 
		stack post;
		
		// 以一次一個字元為單位 讀剛剛存入postfix陣列的值 
    	for(int i=0;i<sizeof(postfix);i++){
    		
    		// 宣告 token 變數來存放目前讀到的字元 
    		char token = postfix[i];
    		
    		// 宣告op1、op2兩個整數運算元 
    		int op1, op2;
    		
    		// 當目前讀到的字元和最後一個字元一樣 視為後序式的結束 
    		if(token == postfix[MAXLEN])
        		break;
        	
			// 如果讀到運算子 
			if( token =='+' || token =='-' || token =='*' || token =='/'){
				
				// pop 出來堆疊最上面的兩個運算元 
				// 並將字串轉為整數 -'0' 
				op2= Pop(&post)-'0';
        		op1 = Pop(&post)-'0';
        		
        		// 判斷目前讀到的是哪一個運算子 
        		switch(token){
        		case '+': Push ((op1+op2)+'0',&post);
        					break;
        		case '-': Push ((op1-op2)+'0',&post);
        					break;
        		case '*': Push ((op1*op2)+'0',&post);
        					break;
        		case '/': 
        		// 如果是除號，有可能出現小數的結果
				// 先將結果以float存放到result變數內 
				float result = (float)op1/(float)op2 ;
				// 宣告一個num整數變數 
				int num;
				// 當op1/op2不整除的時候 
				if(op1%op2 != 0){
					// 將result+0.5存入num 當作四捨五入 
					// 因為0.4+0.5不會跳到下一數，0.5以上+0.5會跳到下一數
					// 用num整數就會完全捨棄小數部分，剛好就是我們要的四捨五入的值 
					num = result + 0.5;
				}else{
					// 整除的話，就直接把num設為result結果 
					num = result; 
				}
				//  將結果num整數轉字串，push進堆疊 
				Push (num +'0',&post);
        					break;
				}
				
			}else{
				// 如果讀到運算元 
				// push進堆疊 
				Push(token, &post);
				
			}
			
		}
		
		// 最後留在堆疊的是運算結果
		// 將結果字串轉整數 寫入file2 
		file2 << Pop(&post)-'0';
		file2 << "\n";
	}
    
//    關閉檔案 
    file1.close();
 	file2.close();
 	
    system("pause");
    return 0;
}
