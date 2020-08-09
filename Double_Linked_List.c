#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
#include<unistd.h>


#define Buffersize 4096
#define MaximumInputCount 10000 

typedef struct ST_Node {
    int i_data;
    int i_index;
    struct ST_Node *p_prevnode;
    struct ST_Node *P_nextnode;
} Node ;

Node *g_Head;
Node *g_Tail;

void PushBackNode(int i_data);
void PrintNodeList();
void ReversePrintNodeList();
void InsertNode(unsigned ui_index, int i_data);
void EraseNode(unsigned ui_index);

int CheckMemorryAllocated(void *p_AllocatedAddr, size_t s_RequestSize);

int main()
{
	size_t StringLength = 0;
	// 입력 받는 부분
    // 1. 파일로 입력 받기 (10000개 데이터)


    // 2. 한줄로 입력 받기 
    // 한줄 버퍼가 4096 byte 
    // 입력 받고 나면 버퍼 비우고 새로받기
    // 버퍼 맨 앞이 '\n' 이면 종료 하기 

    //char InputBuffer[4096]
	char *p_InputBuffer = (char *)calloc(Buffersize, sizeof(char));  // calloc 으로 할당 + 초기화

	if(CheckMemorryAllocated(p_InputBuffer, Buffersize))            // custom memory checker 
		return 1;
	
	//char TmpBuffer[4096]
	char *p_TmpBuffer = (char *)calloc(Buffersize, sizeof(char));
	if(CheckMemorryAllocated(p_TmpBuffer, Buffersize))
		return 1;
		
	//int InputNumberArray[10000] 
	int *p_InputNumberArray = (int *)calloc(MaximumInputCount, sizeof(int));	
	if(CheckMemorryAllocated(p_InputNumberArray, MaximumInputCount))
		return 1;
	

	bool b_Stop = false;

	do {
		puts("\nPlease Input int number array or one");
		puts("ex) : 1 10 20 30 40  or  : 1 \n(Separate numbers with a \" \"(space) character)");
		puts("(If you want to stop typing, just enter the \"Enter key\")\n");
		putchar(':');
		putchar(' ');

		// input 
		if( fgets(p_InputBuffer, Buffersize-1, stdin) == NULL) {
			puts("fgets error ourred\n");
			return 1;
		}
		putchar('\n');	


		if(*(p_InputBuffer) == '\n')
			b_Stop = true;
		

		StringLength = strlen(p_InputBuffer);

		printf("[+] iniail lenth : %ld \n", StringLength) ; 

		if(StringLength  > Buffersize-2) {
			puts("Out of maximum inputable size. \n Initialize the input data.");
			printf("max input buffer size : %d ", Buffersize-2);
			memset(p_InputBuffer, 0, Buffersize);
			fflush(stdin);
			continue ;
		}


		// 입력받은 문자열 끝에 개행문자 제거
		*(p_InputBuffer + StringLength) = '\x00';
		StringLength --;


		printf("INPUT lenth : %ld \n",StringLength);
		putchar('\n');		



		//input checker 구현하기 (숫자이외의 문자가 들어가 있는지? ), space가 2개 인지? )
		// 숫자 이외의 문자는 무시하고 숫자 문자만 읽어서 숫자 문자열 생성하기
		// 숫자 다받고 Node List 생성하기 vs 숫자 받으면서 생성하기 
		// 숫자 다받고 입력한 숫자 배열 그리고 입력한 숫자 개수 출력 
		
		
		if(StringLength != 0) {
			puts("current Input array : ");
			for(int i=0; i<Buffersize ; i++)
			{
				printf("%c",*(p_InputBuffer+i));
			}
		}




	// 입력이 끝났으니 InputBuffer 초기화 해주기
	memset(p_InputBuffer, 0, Buffersize);

	}while(b_Stop == false);

}


int CheckMemorryAllocated(void *p_AllocatedAddr, size_t s_RequestSize)
{
	int i_result = 0;

	if(p_AllocatedAddr == NULL) {  // Null-Check
		puts("No memory allocated");
		i_result = 1;
	}	
	else {
		size_t s_AllocatedSize = malloc_usable_size(p_AllocatedAddr); 

		if( s_AllocatedSize < s_RequestSize) { // Check allocated memory size
			puts("Not enough memory has been allocated" );
			printf("Request size : %ld  /  Allocated size : %ld \n", s_RequestSize, s_AllocatedSize);
			malloc_stats();  //print malloc status
			i_result = 2;
		}
	}
	// printf 말고 다르게 ?
	
	if( i_result != 0)
		printf("Memorry error occured ERROR CODE : %d \n" , i_result);
	
	return i_result;
}









