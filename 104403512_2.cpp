#include<iostream>
#include<fstream>
using namespace std;
#define MAXLEN 100

// �ŧistack���c 
struct stack{
	int top=0;
	char items[MAXLEN];
};

// �ŧiline�}�C�A�x�s���U�nŪ���ɮפ� �C�@�檺���l 
char line[MAXLEN];

// ���|�򥻨�� 
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
    	
    	// infix to postfix ���Ǧ����Ǧ� 
    	
    	// �ŧis�o�Ӱ��| 
		stack s;  
 
		// ��l��postfix�}�C 
		char postfix[MAXLEN]={};
		
		// ��postfix�}�C��index�ȡA�H�@�Ӧr���@�����s�J��Ǧ� 
		int index = 0;
		
		// �@��Ū�@�� 
        for(int n=0;n<sizeof(line);n++){
        	
        	// �]�r���ܼ�token���ثe��Ū�쪺�r�� 
        	char token = line[n];
        	
        	// �p�Gtoken����̫�@�Ӧr���A�����B�⦡������ 
        	if(token == line[MAXLEN])
        		break;
        		
        	if(token == ')'){
				// when meet rparen ')'
				// pop the stack until we meet '('
				while (s.items[s.top-1] != '(' && !IsEmpty(&s)){
					// �Npop�X�Ӫ����G�s�Jpostfix�}�C 
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
					// pop�X�Өæs�Jpostfix�}�C 
					postfix[index++] = Pop(&s);
				}
				// ��{�b�J�쪺�o��+��-��i���| 
				Push(token,&s);
			}
			else if(token == '*' || token == '/'){
				// if we meet * or /
				// if the top of stack is * or /
				while(s.items[s.top-1]=='*'||s.items[s.top-1]=='/'){
					// pop�X�Өæs�Jpostfix�}�C 
					postfix[index++] = Pop(&s);
				}
				// ��{�b�J�쪺�o��*��/��i���| 
				Push(token,&s);
			}
			else{
				// if we meet operand
				postfix[index++] = token;
			}
    	}
    	
    	// �����e�����ާ@�A�p�G���|�D�šA�N�Ѿl��pop�X�Ӧs�Jpostfix�}�C 
    	while(!IsEmpty(&s)){
    		postfix[index++] = Pop(&s);
		}
		
		// �Npostfix��Ǧ��g�Jfile2�ɮרô��� 
		file2 << postfix;
		file2 << "\n";
		
		// postfix to value ��Ǧ��D�� 
		
		//�ŧi�@�Ӱ��| post 
		stack post;
		
		// �H�@���@�Ӧr������� Ū���s�Jpostfix�}�C���� 
    	for(int i=0;i<sizeof(postfix);i++){
    		
    		// �ŧi token �ܼƨӦs��ثeŪ�쪺�r�� 
    		char token = postfix[i];
    		
    		// �ŧiop1�Bop2��Ӿ�ƹB�⤸ 
    		int op1, op2;
    		
    		// ��ثeŪ�쪺�r���M�̫�@�Ӧr���@�� ������Ǧ������� 
    		if(token == postfix[MAXLEN])
        		break;
        	
			// �p�GŪ��B��l 
			if( token =='+' || token =='-' || token =='*' || token =='/'){
				
				// pop �X�Ӱ��|�̤W������ӹB�⤸ 
				// �ñN�r���ର��� -'0' 
				op2= Pop(&post)-'0';
        		op1 = Pop(&post)-'0';
        		
        		// �P�_�ثeŪ�쪺�O���@�ӹB��l 
        		switch(token){
        		case '+': Push ((op1+op2)+'0',&post);
        					break;
        		case '-': Push ((op1-op2)+'0',&post);
        					break;
        		case '*': Push ((op1*op2)+'0',&post);
        					break;
        		case '/': 
        		// �p�G�O�����A���i��X�{�p�ƪ����G
				// ���N���G�Hfloat�s���result�ܼƤ� 
				float result = (float)op1/(float)op2 ;
				// �ŧi�@��num����ܼ� 
				int num;
				// ��op1/op2���㰣���ɭ� 
				if(op1%op2 != 0){
					// �Nresult+0.5�s�Jnum ��@�|�ˤ��J 
					// �]��0.4+0.5���|����U�@�ơA0.5�H�W+0.5�|����U�@��
					// ��num��ƴN�|�����˱�p�Ƴ����A��n�N�O�ڭ̭n���|�ˤ��J���� 
					num = result + 0.5;
				}else{
					// �㰣���ܡA�N������num�]��result���G 
					num = result; 
				}
				//  �N���Gnum�����r��Apush�i���| 
				Push (num +'0',&post);
        					break;
				}
				
			}else{
				// �p�GŪ��B�⤸ 
				// push�i���| 
				Push(token, &post);
				
			}
			
		}
		
		// �̫�d�b���|���O�B�⵲�G
		// �N���G�r������ �g�Jfile2 
		file2 << Pop(&post)-'0';
		file2 << "\n";
	}
    
//    �����ɮ� 
    file1.close();
 	file2.close();
 	
    system("pause");
    return 0;
}
