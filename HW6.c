/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node 		// linked list에 데이터를 저장할 노드부분
{
	int key;
	struct Node* link;
} listNode;

typedef struct Head 		// linked list에서 처음을 잡아줄 부분
{
	struct Node* first;		// HeaderNode가 가르키고 있는 첫번째 노드
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);			
int freeList(headNode* h);					

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [이정인] [2019038015] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);		// headnode 만들어 주기
			break;
		case 'p': case 'P':
			printList(headnode);					// 만들어진 linkedlist 출력하기
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);				// 사용자에게 key값을 받아 노드를 만들고 linkedlist에 연결시키기
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);				// 노드 제거
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);				// linkedlist의 맨 마지막에 노드 추가
			break;
		case 'e': case 'E':
			deleteLast(headnode);					// 마지막 노드 없애기
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);				// 맨처음에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);					// 맨처음 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);					// 현재 linkedlist 순서 뒤집기
			break;
		case 'q': case 'Q':
			freeList(headnode);						// 현재 linkedlist 제거
			printf(" Free linkedlist...\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) 
{
	if(h != NULL)					// list의 첫번째인 h(HeaderNode)가 비어있지 않다. 즉, 아직 linkedlist가 존재한다.
		freeList(h);				// headNode를 free해준다(= linkedlist를 삭제한다.)

	headNode* temp = (headNode*)malloc(sizeof(headNode));	// linkedlist의 헤더 자체도 없을 때 headNode구조체 만큼의 동적배열을 받고
	temp->first = NULL;										// temp가 가리키는 곳을 없는 linkedlist의 완전 처음 상태를 만들어 준다.
	return temp;											
}

int freeList(headNode* h)
{
	
	listNode* p = h->first;				// list의 첫번째 부분을 잡는다.
	listNode* prev = NULL;				// 노드를 하나씩 해제하기 위해 임시로 만들어 놓은 prev node이다.

	while(p != NULL) 					// list에 남아있는 노드가 있을 때...
	{
		prev = p;						// 임시 prev 노드에 p를 넣고
		p = p->link;					// p에는 다름 노드를 가르킨다.
										// 즉 prev를 따로 때서 제거한다.
		free(prev);						// prev 제거
	}

	free(h);							// 헤더노드 제거
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) 						// 노드를 삽입하는 함수
{

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 삽입할 노드를 동적할당으로 만든다.
	node->key = key;										// 여기서 key는 사용자가 작성한 값이다.
	node->link = NULL;										// 아직 linked 하지 않았으므로 NULL

	if (h->first == NULL)									// linkedlist에 HeaderNode만 존재할 경우
	{
		h->first = node;									// 그냥 바로 위에다 생성된 노드를 붙여버린다.
		return 0;
	}

	listNode* n = h->first;									// 'node'를 붙이기 위해 임의로 만든 node 'n', 'trail'
	listNode* trail = h->first;								// n은 HeaderNode위에 있는 노드다.(무슨 key값이 있는지는 모름)

	while(n != NULL) 										// headerNode뒤에 다른 Node가 있을 때..
	{
		if(n->key >= key) 									// 사용자가 입력한 key보다 n의 key가 크다면
		{
			if(n == h->first) 								// HeaderNode 바로 뒤에 넣어야 할때
			{
				h->first = node;
				node->link = n;
			} else 											// 노드 중간에 넣을 때
			{ 
				node->link = n;								// 삽입 해야 할 노드가 n노드를 가리키고
				trail->link = node;							// 그전 노드가 삽입할 노드를 가리키면 된다.
			}
			return 0;
		}
		trail = n;											// 삽입해야할 노드 전 값을 trail에 넣는다.
		n = n->link;										// n 노드는 다음 노드를 가리킨다.
	}

	trail->link = node;										// 맨 마지막에 삽입
	return 0;
}

/* list에 key에 대한 노드하나를 추가 */
int insertLast(headNode* h, int key) 						// linkedlist의 맨 마지막에 노드 추가
{

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 새로운 노드 1개를 동적할당으로 생성
	node->key = key;										// 새로운 노드에 사용자가 입력한 값을 넣는다.
	node->link = NULL;										// 새로운 노드 이기도 하고 마지막 노드에 붙일꺼니까 NULL

	if (h->first == NULL)									// linkedlist가 headerNode뿐일 때
	{
		h->first = node;									// 그냥 바로 뒤에 붙인다.
		return 0;
	}

	listNode* n = h->first;									// 임의의 노드 1개를 생성

	while(n->link != NULL) 									// linkedlist의 맨뒤가 나올때 까지
	{														// n을 다음 노드로 계속 옮긴다.
		n = n->link;
	}
	n->link = node;											// 맨 마지막 노드가 나왔으면 새로만든 노드를 연결한다.
	return 0;
}

/* list 처음에 key에 대한 노드하나를 추가 */
int insertFirst(headNode* h, int key) 
{

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 새로운 노드 만들기
	node->key = key;										// 사용자가 입력한 값을 key에 넣기

	node->link = h->first;									// 생성한 노드가 맨처음 노드를 가르키게 한다.
	h->first = node;										// 헤더노드가 생성한 노드를 가르키게 한다.

	return 0;
}

/* list에서 key에 대한 노드 삭제 */

int deleteNode(headNode* h, int key) 			// 노드 삭제
{
	if (h->first == NULL)						// headerNode만 있을 때, 삭제할 노드가 없다.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;						// 임의의 노드 n과 trail 생성
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) 							// headerNode뒤에 노드가 있다면
	{
		if(n->key == key) 						// 사용자가 삭제하고자 하는 값을 찾았으면
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first)					// 삭제할 노드가 headerNode 바로 다음일 때
				h->first = n->link;				// 삭제할 노드 다음 노드를 headerNode에서 연결하면 자동으로 삭제된다.
	
			else 
			{ /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;			// 삭제할 노드 전 노드를 삭제할 노드 다음 노드에 연결한다.
			}
			free(n);							// 삭제할 노드 제거
			return 0;
		}

		trail = n;								// trail에는 n의 값으 넣고
		n = n->link;							// n에는 n다음 노드를 넣으면 된다.
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/*  list의 마지막 노드 삭제 */

int deleteLast(headNode* h) 
{

	if (h->first == NULL)					// headerNode 1개만 있을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;					// 찾아가기 위한 임의의 노드를 생성
	listNode* trail = NULL;

	if(n->link == NULL) 					// 노드 1개만 있을 때
	{
		h->first = NULL;					// headerNode가 NULL를 가르키게 만든다.
		free(n);							// 그리고 마지막 노드를 제거
		return 0;
	}

	while(n->link != NULL) 					// 마지막 노드까지 이동
	{
		trail = n;
		n = n->link;
	}

	trail->link = NULL;						// 삭제한 노드 바로 앞 노드가 이제 마지막 노드가 된다.
	free(n);

	return 0;
}

/* list의 첫번째 노드 삭제  */
int deleteFirst(headNode* h) 				// 첫번째 노드 삭제
{

	if (h->first == NULL)					// linkedlist가 HeaderNode만 있을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;					// 임의의 노드 생성

	h->first = n->link;						// HeaderNode가 두번째 노드를 가르키게 한다.
	free(n);								// 그리고 첫번째 노드를 삭제

	return 0;
}


/*  리스트의 링크를 역순으로 재배치  */
 
int invertList(headNode* h) 				// 현재 존재하는 linkedlist의 순서를 바꾼다.
{
	if(h->first == NULL) 					// HeadNode만 존재 할때
	{
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;					// 첫번째 노드를 가르키는 노드 포인터 n
	listNode *trail = NULL;					// 필요한 노드 2개를 임의로 생성
	listNode *middle = NULL;	

	while(n != NULL)						// linkedlist가 존재할 때
	{
		trail = middle;						// 여기서부터는 정수2개를 서로 바꿀때 알고리즘과 같다.
		middle = n;							// middle에 임시 저정하고 하나에 다른 하나의 값을 저장하고
		n = n->link;						// 그 나머지 변수에 middle에 넣었던 것을 다시 넣는다.
		middle->link = trail;
	}

	h->first = middle;						// 맨처음의 노드를 맨뒤로 보낸다.

	return 0;
}


void printList(headNode* h) 				// 지금까지 만든 linkedlist의 내용을 출력해주는 함수
{
	int i = 0;								// 노드의 개수를 세기 위한 변수 i
	listNode* p;							// 이 함수에서 노드를 출력하기 위해 만든 임의의 노드 포인터 p

	printf("\n---PRINT\n");

	if(h == NULL) 							// headernode가 없을때,(linkedlist 자체가 없을 때)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;							// 헤더 노드가 가르키는 첫번째 노드를 p에 넣는다. (첫번째)

	while(p != NULL) 						// p가 NULL이 아닐때...  <-- 이것은 밑에 p=p->link;를 거치면서 p가 linkedlist를 타고 이동을 하는데 마지막에 도달하면 p가 NULL이 된다.
	{
		printf("[ [%d]=%d ] ", i, p->key);	// i : 노드 순서 +  노드내용 출력
		p = p->link;						// 다음 출력할 노드를 가르킨다.
		i++;								// 노드 개수 를 올린다.
	}

	printf("  items = %d\n", i);			// 이동하면서 거쳤던 노드의 개수를 센다.
}

