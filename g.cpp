#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<locale.h>

typedef struct{
	char spr[4];//자모
	int stroke;//획수
}spr_matching;

spr_matching CHOSUNG_LIST[19] = {{"ㄱ",1}, {"ㄲ",2}, {"ㄴ",1}, {"ㄷ",2}, {"ㄸ",4}, {"ㄹ",3}, {"ㅁ",3}, {"ㅂ",4}, {"ㅃ",8},
{"ㅅ",2}, {"ㅆ",4},{"ㅇ",1},{"ㅈ",3}, {"ㅉ",6}, {"ㅊ",4}, {"ㅋ",2}, {"ㅌ",3}, {"ㅍ",4}, {"ㅎ",3}};

spr_matching JUNGSUNG_LIST[21] ={ {"ㅏ",2}, {"ㅐ",3}, {"ㅑ",3}, {"ㅒ",4}, {"ㅓ",2}, {"ㅔ",3}, {"ㅕ",3}, {"ㅖ",4}, 
{"ㅗ",2}, {"ㅘ",4},{"ㅙ",5}, {"ㅚ",3}, {"ㅛ",3}, {"ㅜ",2}, {"ㅝ",4}, {"ㅞ",5}, {"ㅟ",3}, {"ㅠ",3}, {"ㅡ",1}, {"ㅢ",2},{"ㅣ",1 }};

spr_matching JONGSUNG_LIST[28] ={{" ",0}, {"ㄱ",1}, {"ㄲ",2}, {"ㄳ",3}, {"ㄴ",1}, {"ㄵ",4}, {"ㄶ",4}, {"ㄷ",2},
{"ㄹ",3}, {"ㄺ",4}, {"ㄻ",6}, {"ㄼ",7}, {"ㄽ",5}, {"ㄾ",6}, {"ㄿ",7}, {"ㅀ",6}, {"ㅁ",3},{"ㅂ",4},
{"ㅄ",6},{"ㅅ",2},{"ㅆ",4}, {"ㅇ",1},{"ㅈ",3},{"ㅊ",4}, {"ㅋ",2}, {"ㅌ",3}, {"ㅍ",4}, {"ㅎ",3}};
typedef int Boolean;//참과 거짓을 나타내는 숫자 1과 0만을 이용하는 방식(ex. 자바에서 쓰임)

void splash();//시작화면
void login(char (*id)[11]);//로그인
void menu(int*);//메뉴
void menu_1(char (*id)[11]);//메뉴1
int menu_2(char (*id)[11]);//메뉴2
int menu_3(char (*id)[11]);//메뉴3
int bunri(wchar_t);//자모분리
void idMatch(char(*str)[11], char id[11]);//사용자 이름 재확인
Boolean is_hangeul(wchar_t*);//입력한 사용자이름이 한글인지 이름 석자를 넘었는지 
Boolean idscan(char*,char[10][11]);//로그인 시, 입력한 사용자이름과 저장된 아이디가 일치 하는지

int main(){
	char id[11];
	int num;//메뉴에 이용
	HANDLE hcon;   // 콘솔의 핸들을 저장할 변수를 선언
	hcon = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔의 핸들 획득
	SetConsoleTextAttribute(hcon, 15<<4 | 12);//배경을 15(흰색), 글씨를 12(빨간색)로 바꿔줌
	splash();//시작화면
	SetConsoleTextAttribute(hcon, 15<<4 | 0);//배경을 15(흰색), 글씨를 0(검은색)로 바꿔줌
	login(&id);//로그인화면
	while(1){
		menu(&num);//메뉴
		switch(num){
		case 1: menu_1(&id);break;//메뉴1 테스트 시작
		case 2: menu_2(&id);break;//메뉴2 테스트 결과보기
		case 3: menu_3(&id);break;//메뉴2 테스트 결과지우기
		case 4: return 1;break;//종료
		default: printf("잘못입력하였습니다.\n");Sleep(1000);system("cls");menu(&num);break;//안내문구 1초간 출력, 화면 리셋, 메뉴 출력
		}
	}
	return 0;
}

void splash(){
	char splash[256];//파일 텍스트 저장할 문자열 선언
	int i;
	FILE *splash_f=fopen("heart.txt","r");//heart.txt 오픈

	for(i=0;i<5;i++){//5번 깜빡이면서 출력
		splash_f=fopen("heart.txt","r");
		while(fgets(splash,256,splash_f)!=NULL)
			printf("%s",splash);
		Sleep(400);
		system("cls");
	}
	fclose(splash_f);//파일 닫기

}
void login(char (*id)[11]){
	char user_info[10][11];//사용자 목록 저장할 문자열
	char str[256];//사용자 목록 파일 내용 저장할 문자열
	FILE *user_info_f;
	int i,j=0,k=0,num;//num은 사용자 이름 저장할지 안할지 물을때 이용

	while(1){
		system("cls");//화면 초기화
		user_info_f=fopen("login.txt","r");//파일을 읽기 모드로 불러옴
		while(fgets(str,256,user_info_f)!=NULL){//str에 파일 내용 복사
			for(i=0;str[i]!='\0';i++){//for문을 내용 끝까지 돌린다
				if(str[i]=='\n'){//사용자 이름을 Enter를 기준으로 구분해 저장한다.
					user_info[k][j]='\0';
					k++;
					j=0;
					continue;
				}
				user_info[k][j]=str[i];
				j++;
			}
		}
		fclose(user_info_f);//파일 닫기
		printf("-	로그인/회원가입	-\n\n\n사용자이름을 입력해 주세요.\n(영어 10자이하 혹은 한글 5자이하 (10byte이하))\n\n\n");
		scanf("%s",id);
		if(idscan(*id,user_info)==1){//입력한 사용자 이름이 저장되있는 이름과 일치하면
			system("cls");
			printf("로그인되었습니다.");
			Sleep(1300);
			break;
		}
		else if(strlen(*id)>10)//입력한 이름이 10byte를 초과하면
			printf("10byte를 초과하였습니다.\n");
		else{//입력한 사용자 이름이 저장되있는 이름과 일치하지 않으면


			while(1){
				system("cls");
				printf("입력을 잘 못 하였거나\n저장된 사용자이름이 아닙니다\n아래 메뉴에서 항목을 선택해주세요.\n\n\n 1: 회원가입을 한다.\n 2: 다시 사용자이름을 입력한다.\n\n\n");
				scanf("%d",&num);
				system("cls");
				if(num==1){//사용자 이름 파일에 저장
					user_info_f=fopen("login.txt","a");
					fputs(*id,user_info_f);
					fputs("\n",user_info_f);
					fclose(user_info_f);
					printf("\n사용자 이름이 저장되었습니다.");
					Sleep(1000);
					break;
				}
				else if(num==2)break;//다시 입력
				else{
					printf("\n1 혹은 2이외의 다른 문자를 입력하였습니다.");
					Sleep(1000);
				}
			}

		}
		Sleep(1000);
	}
}
void menu(int* num){
	system("cls");//화면초기화
	char menu[256];//메뉴 내용 저장 문자열
	FILE *menu_f=fopen("menu.txt","r");//읽기모드로 파일 오픈

	while(fgets(menu,256,menu_f)!=NULL)
		printf("%s",menu);//파일 내용 출력
	fclose(menu_f);//파일 닫기
	scanf("%d",num);//메뉴 선택
}
void menu_1(char (*id)[11]){
	wchar_t in_char[2][4];//두 사용자 이름을 저장할 문자열, 다중바이트를 한 곳에 저장할 수 있다.
	char Directory[15],int2str[3];//Directory: 파일 경로,int2str: int형 자료형을 str형으로 저장할 때 이용
	int num,result,stroke[5][6];//num:메뉴에 이용 ,result: 궁합 결과 저장 ,stroke[5][6]: 글자 획수 저장하고 더할때 이용
	FILE *result_f;
	int i,j,k=0;
	setlocale(LC_ALL, "Korean");//유니코드 로컬 설정

	system("cls");
	printf("┌───────────────────────────────────┐\n\n\n");
	printf("	본 테스트는 재미로 하는 테스트이니 결과에 연연하지 마세요~!\n\n");
	printf("	-테스트 과정-\n\n");
	printf("	 1. 두 사람의 이름(한글 석자)을 입력한다.\n\n");
	printf("	 2. 계산 과정과 결과를 볼 수 있다.\n\n\n");
	printf("└───────────────────────────────────┘\n\n");
	printf("	아무 키나 누르면 테스트 시작합니다. \n\n");
	scanf("%d",&num);

	for(j=0;j<=1;j++){
		system("cls");
		if(j==0)
			printf("첫");
		else
			printf("두");
		printf("번째 사람의 이름을 입력해 주세요: \n(한글 이름 3자만 입력해주세요.)\n\n");
		fflush(stdin);
		wscanf(L"%s",&in_char[j]);
		fflush(stdin);
		if(is_hangeul(in_char[j])==0){//(한글 이름 3자만 입력해주세요.)조건에 일치하지 않을 경우
			printf("이름을 다시 입력해주세요\n");
			Sleep(1000);
			j--;
		}

	}

	fflush(stdin);
	system("cls");	

	for(i=0;i<3;i++){
		for(j=0;j<=1;j++){
			stroke[0][k]=bunri(in_char[j][i]);//한 음절 별로 초중종성으로 분리 후, 획수 저장
			k++;
		}
	}
	fflush(stdin);
	//궁합 결과 과정 및 결과 출력
	//여기부터↓
	printf("  ");
	for(j=0;j<3;j++){
		for(i=0;i<2;i++)
			wprintf(L"%c    ",in_char[i][j]);
	}
	printf("\n");

	for(j=0;j<5;j++){
		for(i=0;i<6-j;i++){
			if(j>=1)
				stroke[j][i]=stroke[j-1][i]%10+stroke[j-1][i+1]%10;
			printf("  %2d  ",stroke[j][i]);

		}
		printf("\n   ");
		for(k=0;k<j;k++){
			printf("   ");
		}
		for(i=0;i<5-j;i++){
			printf("└─┘");
		}
		printf("\n   ");
		for(k=0;k<j;k++){
			printf("   ");
		}
	}
	result=(stroke[4][0]%10)*10+stroke[4][1]%10;
	wprintf(L"\n%s님과 %s님의 궁합 결과 %d%% 입니다.\n",in_char[0],in_char[1],result);
	if(result>=0&&result<20)
		printf("이 몬난아~!\n\n");
	else if(result>=20&&result<40)
		printf("니가 더 아까워\n\n");
	else if(result>=40&&result<50)
		printf("좋은친구되세요\n\n");
	else if(result>=50&&result<60)
		printf("가능성은있어요\n\n");
	else if(result>=60&&result<80)
		printf("용기내서 고백해봐요\n\n");
	else if(result>=80&&result<90)
		printf("사귀어도 되겠어요\n\n");
	else if(result>=90&&result<95)
		printf("예쁜사랑하세요\n\n");
	else if(result>=95&&result<99)
		printf("천생연분이시군요\n\n");
	else if(result==99)
		printf("↖↖축 !결혼! 하↗↗\n\n");

	//여기까지

	//결과 저장
	while(1){
		printf("결과를 저장하시겠습니까?(Yes=1, No=2) ");
		scanf("%d",&num);
		if(num==1){
			strcpy(Directory,*id);
			strcat(Directory,".txt");

			result_f=fopen(Directory,"a");//사용자이름.txt에 저장
			fputws(L"\t",result_f);
			fputws(in_char[0],result_f);
			fputws(L"님과 ",result_f);
			fputws(in_char[1],result_f);
			fputws(L"님의 궁합 결과 ",result_f);
			itoa(result,int2str,10);//int to str (int, str, 몇진수를 문자로 바꿀지)
			fputs(int2str,result_f);
			fputws(L"% 입니다.\n\n\n",result_f);
			fclose(result_f);
			break;
		}
		else if(num==2)
			break;
		else{
			printf("잘못된 입력입니다.\n");
			system("cls");
		}
	}

}
int menu_2(char (*id)[11]){
	int num;
	char str[11];
	char result[256],Directory[15];

	system("cls");
	printf("-테스트 결과 보기-\n\n");
	idMatch(&str, *id);//사용자이름 재확인
	Sleep(1300);
	system("cls");

	strcpy(Directory,str);
	strcat(Directory,".txt");
	FILE *result_file=fopen(Directory,"r");//사용자이름.txt오픈

	if(result_file==NULL){//파일이 없는 경우 종료
		printf("저장한 정보가 없습니다.\n");
		Sleep(1300);
		return 1;
	}

	//여기부터
	printf("%s님의 테스트 결과는 아래와 같습니다.\n\n",str);
	printf("┌───────────────────────────────────┐\n\n\n");
	while(fgets(result,256,result_file)!=NULL)
		printf("%s",result);
	fclose(result_file);

	printf("└───────────────────────────────────┘");
	//여기까지 결과 출력

	//메뉴
	while(1){
		printf("\n메인메뉴로 돌아가시겠습니까?(Yes는 1, No는 2) ");
		scanf("%d",&num);
		if(num==1)
			break;
		else if(num==2)
			exit(0); 
		else{
			printf("잘못된 입력입니다.\n");
		}
	}
	return 0;
}
int menu_3(char (*id)[11]){
	int num;
	char str[11];
	char result[256],Directory[15],del_f_name[19]="del ";

	system("cls");
	printf("-테스트 결과 지우기-\n\n");
	idMatch(&str, *id);//사용자이름 재확인
	Sleep(1300);
	system("cls");

	strcpy(Directory,str);
	strcat(Directory,".txt");
	FILE *del_f=fopen(Directory,"r");//사용자이름.txt오픈

	if(del_f==NULL){//파일이 없는 경우 종료
		printf("저장한 정보가 없습니다.\n");
		Sleep(1300);
		return 1;
	}
	fclose(del_f);
	
	//메뉴
	while(1){
		printf("테스트 결과를 지우겠습니까?(Yes는 1, No는 2) ");
		scanf("%d",&num);
		if(num==1){
			strcat(del_f_name,Directory);//"del"+txt파일 이름
			system("cls");
			system(del_f_name);//system("del text.txt"); del text.txt 파일 제거
			printf("삭제되었습니다.\n");
			Sleep(1300);
			break;
		}
		else if(num==2){
			system("cls");
			printf("메인메뉴로 돌아갑니다.\n");
			Sleep(1000);
			break;
		}
		else{
			printf("잘못된 입력입니다.\n");
		}
	}
	return 0;
}
int bunri(wchar_t in_char){
	int in_cho, in_jung, in_jong;
	in_char = in_char - 44032;//받아온 글자에서 가(44032)를 뺀다.
	in_cho = in_char / 588;//588로 나누면 초성 index번호가 나온다.
	in_jung = (in_char-in_cho*588)/28;//가(44032)를 뺀 값-초성 index번호*588 을 28로 나누면 중성 index번호가 나온다.
	in_jong = in_char-in_cho*588-in_jung*28;//가(44032)를 뺀 값-초성 index번호*588-중성 index번호*28 하면 종성 index 번호가 나온다.

	//각각의 index번호를 이용해서 획수로 바꿔 한 음절의 획수를 계산한후 리턴
	return CHOSUNG_LIST[in_cho].stroke + JUNGSUNG_LIST[in_jung].stroke + JONGSUNG_LIST[in_jong].stroke;
}
void idMatch(char(*str)[11], char id[11]){
	int num;//메뉴에 이용
	
	fflush(stdin);
	printf("\n로그인 했던 사용자이름을 입력해주세요\n");
	gets(*str);//사용자 이름인 재확

	if(strcmp(*str,id)!=0){//이름 불일치 경우
		printf("\n	사용자 이름이 일치하지 않습니다.\n");
		Sleep(1300);
		menu(&num);//메뉴
	}
	printf("\n 사용자 이름이 일치합니다.\n");
}
Boolean idscan(char* id,char user_info[10][11]){
	int i,result=0;
	for(i=0;i<10;i++){
		if(strcmp(id,user_info[i])==0)
			result=1;
	}
	return result;
	//입력한 사용자 이름이 파일에 저장되 있으면 True(1), 없으면 False(0)
}
Boolean is_hangeul(wchar_t* in_char){
	int result=1;
	if(in_char[0]<0xAC00||in_char[0]>0xD7A3||in_char[1]<0xAC00||in_char[1]>0xD7A3||in_char[2]<0xAC00||in_char[2]>0xD7A3||wcslen(in_char)!=3)
		result=0;
	return result;
	//입력한 사용자 이름이 한글 세글자가 맞으면 True(1), 아니면 False(0)
}