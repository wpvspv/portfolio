#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void map(); //맵출력 함수
void gotoxy(int x, int y); //좌표함수
void Random_Dice(); //주사위 굴리기 함수
void Move(); //말 움직이기 함수
void Desert_island(); //더블 2번일 때 정신과 시간의 방 함수
void build(); //좌표별로 건물 건설 함수
void State(); //사용자 상태 함수
void Icon(); //사용자의 말 아이콘 함수
void Color(); //색 함수
int Money(); //돈 관리 함수
void build_print(); //건물 출력 함수
void remove_Icon(); //아이콘 지우기 함수
int map_count(); //좌표별로 누가 땅의 주인인지 알려주는 함수
void T_Color(); //사용자의 색 함수
void Rank(); //순위 함수
void line_cover(); //맵 왼쪽에 잘린 부분을 커버해주는 함수
int map_money(); //땅값을 반환해주는 함수

int main()
{
	char user[4][5]; //최대 사람수와 이름 배열 선언
	int NUM, i;

	printf("사람 수를 넣어주세요(2명~4명) : ");
	scanf("%d", &NUM);

	for (i = 0; i<NUM; i++) //이름 입력
	{
		getchar();
		printf("%d번째 사람의 닉네임을 넣어주세요(영문3글자 한글 2글자)", i + 1);
		scanf("%s", user[i]);//이름 삽입
	}

	getchar();
	system("cls");

	map(); //맵 출력
	for (i = 0; i<NUM; i++) //사용자 별로 상태 출력
	{
		gotoxy(120, 8 + i * 14);
		{
			T_Color(i);
			printf("%s", user[i]);
			Color(15);
		}
	}
	for (i = 0; i<NUM; i++) //시작점에 말 출력
	{
		if (i == 0)
		{
			Color(3);
			gotoxy(6, 52);
			printf("☆");
			Color(15);
		}
		else if (i == 1)
		{
			Color(6);
			gotoxy(10, 52);
			printf("○");
			Color(15);
		}
		else if (i == 2)
		{
			Color(4);
			gotoxy(6, 54);
			printf("□");
			Color(15);
		}
		else if (i == 3)
		{
			Color(2);
			gotoxy(10, 54);
			printf("◇");
			Color(15);
		}
	}
	getchar();
	for (i = 0;; i++)
	{
		static int x[4] = { 8,8,8,8 }, y[4] = { 53,53,53,53 }; //처음 좌표
		gotoxy(50, 42);
		printf("%d번째 말이 하는 중\n", i%NUM + 1);

		Random_Dice(i%NUM, user, NUM, 0, x, y); //주사위 굴리기 
		line_cover();//맵 왼쪽에 잘린 부분을 커버
	}
	return 0;
}

void State(int t, char p[][5], int NUM, int Money[]) //용자 상태(닉네임 자산) 출력
{
	int i;
	Color(0); //출력된걸 지워준다
	for (i = 0; i<NUM; i++)
	{
		gotoxy(120, 8 + i * 14);
		{
			if (t == 0)
			{
				printf("%s 보유자산 : %d원          ", p[i], Money[i]);
			}
		}
	}
	for (i = 0; i<NUM; i++)
	{
		gotoxy(120, 8 + i * 14);
		{
			T_Color(i);
			printf("%s 보유자산 : %d원", p[i], Money[i]);
			Color(15);
		}
	}
}

void map() //맵출력
{
	// 복붙 : ─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼
	printf("┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐\n");
	printf("│   정신과   │    대전    │    광주    │  ▲설악산  │    부산    │    춘천    │    포항    │   ♨쉼터   │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│  시간의방  │            │            │            │            │            │            │            │\n");
	printf("├──────┼──────┴──────┴──────┴──────┴──────┴──────┼──────┤\n");
	printf("│    강릉    │                                                                                  │    목포    │\n");
	printf("│            │                                                                                  │	        │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("├──────┤                                                                                  ├──────┤\n");
	printf("│    인천    │                                                                                  │  ▲한라산  │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("├──────┤                                                                                  ├──────┤\n");
	printf("│  ▲지리산  │                                                                                  │    진주    │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("├──────┤                                                                                  ├──────┤\n");
	printf("│    세종    │                                                                                  │    광주    │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("├──────┤                                                                                  ├──────┤\n");
	printf("│    대구    │                                                                                  │    원주    │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("├──────┤                                                                                  ├──────┤\n");
	printf("│    울산    │                                                                                  │  ▲치악산  │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("│            │                                                                                  │            │\n");
	printf("├──────┼──────┬──────┬──────┬──────┬──────┬──────┼──────┤\n");
	printf("│    시작    │    서울    │  ▲도봉산  │    독도    │    여수    │  ▲관악산  │    통영    │   ♨쉼터   │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("│            │            │            │            │            │            │            │            │\n");
	printf("└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘\n");
}

void gotoxy(int x, int y) //좌표
{
	COORD pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Color(int a) //색
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void Move(int a, int t, char user[][5], int NUM, int c, int x[], int y[]) //말 이동
{
	int s;
	//gotoxy(x[t],y[t]);
	//Icon(t);
	getchar();
	Color(0);
	gotoxy(50, 14); //주사위 출력 지움
	printf("┌─┐    ┌─┐\n");
	gotoxy(50, 15);
	printf("│%2d│    │%2d│\n");
	gotoxy(50, 16);
	printf("└─┘    └─┘\n");
	Color(15);


	if (t == 0) //주사위 굴리기전 좌표에 있는 말 지움
	{
		gotoxy(x[t] - 2, y[t] - 1);
		remove_Icon(t);
	}
	else if (t == 1)
	{
		gotoxy(x[t] + 2, y[t] - 1);
		remove_Icon(t);
	}
	else if (t == 2)
	{
		gotoxy(x[t] - 2, y[t] + 1);
		remove_Icon(t);
	}
	else if (t == 3)
	{
		gotoxy(x[t] + 2, y[t] + 1);
		remove_Icon(t);
	}
	for (; a>0;) //말 이동할게 남아있을 때
	{
		if (x[t] == 8 && y[t] - 7 * a<4 && y[t] != 4)
		{


			s = (y[t] - 4) / 7; //이동거리

								//gotoxy(x,y-7*s);
								//printf("ㅁ");
			y[t] = y[t] - 7 * s;
			a = a - s;


		}
		else if (x[t] + 14 * a>106 && x[t] != 106 && y[t] == 4)
		{


			s = (106 - x[t]) / 14;

			//gotoxy(x+14*s,y);
			//printf("ㅁ");
			x[t] = x[t] + 14 * s;
			a = a - s;


		}

		else if (x[t] == 106 && y[t] + 7 * a>53 && y[t] != 53)
		{


			s = (53 - y[t]) / 7;

			//gotoxy(x,y+7*s);
			//printf("ㅁ");
			y[t] = y[t] + 7 * s;
			a = a - s;


		}
		else if (x[t] - 14 * a<8 && x[t] != 8 && y[t] == 53)
		{


			s = (x[t] - 8) / 14;

			//gotoxy(x-14*s,y);
			//printf("ㅁ");
			x[t] = x[t] - 14 * s;
			a = a - s;


		}
		else //말 출력 부분
		{
			if (x[t] == 8 && y[t] <= 53 && y[t] >= 11) //왼쪽
			{
				if (t == 0)
				{
					gotoxy(x[t] - 2, (y[t] - 7 * a) - 1);
					Icon(t);
				}
				else if (t == 1)
				{
					gotoxy(x[t] + 2, (y[t] - 7 * a) - 1);
					Icon(t);
				}
				else if (t == 2)
				{
					gotoxy(x[t] - 2, (y[t] - 7 * a) + 1);
					Icon(t);
				}
				else if (t == 3)
				{
					gotoxy(x[t] + 2, (y[t] - 7 * a) + 1);
					Icon(t);
				}
				y[t] = y[t] - 7 * a;

				a = 0;
				build(t, x, y, user, NUM);
			}
			else if (x[t] <= 92 && x[t] >= 8 && y[t] == 4) //위쪽
			{
				if (t == 0)
				{
					gotoxy((x[t] + a * 14) - 2, y[t] - 1);
					Icon(t);
				}
				else if (t == 1)
				{
					gotoxy((x[t] + a * 14) + 2, y[t] - 1);
					Icon(t);
				}
				else if (t == 2)
				{
					gotoxy((x[t] + a * 14) - 2, y[t] + 1);
					Icon(t);
				}
				else if (t == 3)
				{
					gotoxy((x[t] + a * 14) + 2, y[t] + 1);
					Icon(t);
				}
				x[t] = x[t] + a * 14;

				a = 0;
				build(t, x, y, user, NUM);
			}
			else if (x[t] == 106 && y[t] >= 4 && y[t] <= 46) //오른쪽
			{
				if (t == 0)
				{
					gotoxy(x[t] - 2, (y[t] + a * 7) - 1);
					Icon(t);
				}
				else if (t == 1)
				{
					gotoxy(x[t] + 2, (y[t] + a * 7) - 1);
					Icon(t);
				}
				else if (t == 2)
				{
					gotoxy(x[t] - 2, (y[t] + a * 7) + 1);
					Icon(t);
				}
				else if (t == 3)
				{
					gotoxy(x[t] + 2, (y[t] + a * 7) + 1);
					Icon(t);
				}
				y[t] = y[t] + a * 7;

				a = 0;
				build(t, x, y, user, NUM);
			}
			else if (x[t] <= 106 && x[t] >= 22 && y[t] == 53) //아래쪽
			{
				if (t == 0)
				{
					gotoxy((x[t] - a * 14) - 2, y[t] - 1);
					Icon(t);
				}
				else if (t == 1)
				{
					gotoxy((x[t] - a * 14) + 2, y[t] - 1);
					Icon(t);
				}
				else if (t == 2)
				{
					gotoxy((x[t] - a * 14) - 2, y[t] + 1);
					Icon(t);
				}
				else if (t == 3)
				{
					gotoxy((x[t] - a * 14) + 2, y[t] + 1);
					Icon(t);
				}
				x[t] = x[t] - a * 14;

				a = 0;
				build(t, x, y, user, NUM);
			}
		}
	}
}

void Random_Dice(int t, char user[][5], int NUM, int c, int x[], int y[]) //주사위 굴리기
{
	int sum = 0, i = 0, j = 0;
	//static int count[t]={0,0,0,0};
	srand(time(NULL)); //주사위 값 랜덤
	getchar();
	i = rand() % 6 + 1;
	j = rand() % 6 + 1;

	gotoxy(50, 14); //주사위 출력
	printf("┌─┐    ┌─┐\n");
	gotoxy(50, 15);
	printf("│%2d│    │%2d│\n", i, j);
	gotoxy(50, 16);
	printf("└─┘    └─┘\n");

	sum = i + j;//주사위의 합
	if (i == j) //한번 더블일 때
	{
		gotoxy(52, 17);
		printf("더블");
		gotoxy(55, 20);
		printf("합 : %d", sum); //함 출력
		getchar();
		gotoxy(52, 17);
		printf("     ");
		gotoxy(55, 20);
		printf("            ");
		Move(sum, t, user, NUM, c, x, y); //말 이동 함수로 이동


		Color(15); //한번더 주사위 출력
		i = rand() % 6 + 1;
		j = rand() % 6 + 1;
		getchar();
		gotoxy(50, 14);
		printf("┌─┐    ┌─┐\n");
		gotoxy(50, 15);
		printf("│%2d│    │%2d│\n", i, j);
		gotoxy(50, 16);
		printf("└─┘    └─┘\n");

		sum = i + j;//주사위의 합

		if (i == j) //2번 더블일 때 정신과 시간의 방으로 감
		{
			gotoxy(52, 17);
			printf("더블");
			getchar();
			gotoxy(52, 17);
			printf("     ");
			gotoxy(45, 20);
			printf("정신과 시간의 방으로 가세요");
			if (t == 0) //전에 있는 말 지움
			{
				gotoxy(x[t] - 2, y[t] - 1);
				remove_Icon(t);
			}
			else if (t == 1)
			{
				gotoxy(x[t] + 2, y[t] - 1);
				remove_Icon(t);
			}
			else if (t == 2)
			{
				gotoxy(x[t] - 2, y[t] + 1);
				remove_Icon(t);
			}
			else if (t == 3)
			{
				gotoxy(x[t] + 2, y[t] + 1);
				remove_Icon(t);
			}
			Desert_island(t, user, NUM, x, y); //무인도 함수로 이동

			Color(0);
			gotoxy(45, 20);
			printf("정신과 시간의 방으로 가세요");

			Color(15);
		}
		else
		{
			gotoxy(52, 17);
			printf("     ");
			gotoxy(55, 20);
			printf("합 : %d", sum); //함 출력
			Move(sum, t, user, NUM, c, x, y); //말 이동 함수로 이동
			getchar();
			Color(0);
			gotoxy(55, 20);
			printf("합 : %d", sum);

			Color(15);
		}
	}
	else
	{
		gotoxy(55, 20);
		printf("합 : %d", sum); //합 출력
		Move(sum, t, user, NUM, c, x, y); //말 이동 함수로 이동
		getchar();
		Color(0);
		gotoxy(55, 20);
		printf("합 : %d", sum);

		Color(15);
	}
}

void Desert_island(int t, char user[][5], int NUM, int x[], int y[]) //정신과 시간의 방
{
	getchar();
	Color(0); //주사위 출력 지움 
	gotoxy(50, 14);
	printf("┌─┐    ┌─┐\n");
	gotoxy(50, 15);
	printf("│%2d│    │%2d│\n");
	gotoxy(50, 16);
	printf("└─┘    └─┘\n");
	Color(15);
	x[t] = 8, y[t] = 4;//정신과 시간의 방으로 보냄
	if (t == 0)
	{
		gotoxy(x[t] - 2, y[t] - 1);
		Icon(t);
	}
	else if (t == 1)
	{
		gotoxy(x[t] + 2, y[t] - 1);
		Icon(t);
	}
	else if (t == 2)
	{
		gotoxy(x[t] - 2, y[t] + 1);
		Icon(t);
	}
	else if (t == 3)
	{
		gotoxy(x[t] + 2, y[t] + 1);
		Icon(t);
	}
	build(t, x, y, user, NUM); //좌표별로 건물 건설 함수로 이동
}

void build(int t, int x[], int y[], char user[][5], int NUM) //좌표별로 건물 건설
{
	int Q, J;//Q는 yes or no, J는 돈의 판단
	if (x[t] == 8 && y[t] == 4) //정신과 시간의 방일 때
	{
		int i;
		gotoxy(40, 24);
		printf("%d번째 말이 정신의 시간의 방에 도착했습니다.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                                  ");
		gotoxy(40, 24);
		printf("당신은 돈의 5~10퍼센트를 잃습니다.(자연수)             ");//5,6,7,8,9,10%중에 랜덤으로 돈이 깍인다
		srand(time(NULL));
		i = rand() % 6 + 5;
		Money(t, i, 2, user, NUM, 0); //돈 관리 함수로 이동
		gotoxy(40, 24);
		printf("                                                   ");
		getchar();
		if (x[t] == 8)
		{
			getchar();
			gotoxy(40, 24);
			printf("턴을 넘깁니다.");
			getchar();
			gotoxy(40, 24);
			printf("                ");
		}
		/*
		static int count[4]={0,0,0,0};
		if(count[t]==0)
		{
		gotoxy(40,24);
		printf("2번 쉬기");
		getchar();
		gotoxy(40,24);
		printf("턴을 넘깁니다.");
		getchar();
		gotoxy(40,24);
		printf("                ");
		count[t]++;
		gotoxy(40,28);
		//printf("count=%d\n",count[t]);
		}
		else if(count[t]==1)
		{
		gotoxy(40,24);
		printf("1번 쉬기");
		getchar();
		gotoxy(40,24);
		printf("턴을 넘깁니다.");
		getchar();
		gotoxy(40,24);
		printf("                ");
		count[t]++;
		}
		else if(count[t]==2)
		{
		gotoxy(40,24);
		printf("탈출!");
		getchar();
		gotoxy(40,24);
		printf("        ");
		getchar();
		gotoxy(40,24);
		printf("                 ");
		count[t]=0;
		}
		*/
		/*
		else if(count[t]==-2)
		{
		gotoxy(36,24);
		printf("탈출!");
		getchar();
		gotoxy(36,24);
		printf("      ");
		getchar();
		count[t]=0;
		Random_Dice(t,user,NUM,-3);
		gotoxy(36,24);
		printf("주사위 굴림");
		}
		*/
	}
	/*
	else if(x[t]==106)
	{
	static int count_t[4]={0,0,0,0};
	if(count_t[t]==0)
	{
	gotoxy(36,24);
	printf("%d번 쉬기",count_t[t]+2);
	getchar();
	gotoxy(36,24);
	printf("턴을 넘깁니다.");
	getchar();
	gotoxy(36,24);
	printf("                 ");
	count_t[t]=-1;
	}
	else if(count_t[t]==-1)
	{
	gotoxy(36,24);
	printf("%d번 쉬기",count_t[t]+2);
	getchar();
	gotoxy(36,24);
	printf("턴을 넘깁니다.");
	getchar();
	gotoxy(36,24);
	printf("                 ");
	count_t[t]=-2;
	}
	else if(count_t[t]==-2)
	{
	gotoxy(36,24);
	printf("탈출!");
	getchar();
	gotoxy(36,24);
	printf("        ");
	getchar();
	count_t[t]=0;
	Random_Dice(t,user,NUM,-2);
	gotoxy(36,24);
	printf("주사위 굴림");
	}
	}
	*/
	else if (x[t] == 8 && y[t] == 25 || x[t] == 50 && y[t] == 4 || x[t] == 106 && y[t] == 18 || x[t] == 106 && y[t] == 46 || x[t] == 78 && y[t] == 53 || x[t] == 36 && y[t] == 53) //관광지 일 때
	{
		gotoxy(40, 24);
		printf("%d번째 말이 도착했습니다.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                    ");
		if (map_count((t + 1) % NUM, x[t], y[t], -1)>0 || map_count((t + 2) % NUM, x[t], y[t], -1)>0 || map_count((t + 3) % NUM, x[t], y[t], -1)>0) //주인이 있을 때
		{
			gotoxy(40, 26);
			printf("다른 사람의 관광지입니다. 통행료를 지불합니다.");
			getchar();
			gotoxy(40, 26);
			printf("                                                 ");
			J = Money(t, map_money(t, x, y, 4, 2), 1, user, NUM, 0); //돈 관리 함수로 이동
			if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1)
				Money((t + 1) % NUM, map_money(t, x, y, 4, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
			else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 1)
				Money((t + 2) % NUM, map_money(t, x, y, 4, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
			else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
				Money((t + 3) % NUM, map_money(t, x, y, 4, 2), 0, user, NUM, 0); //돈 관리 함수로 이동

			if (J == 1) //파산
			{
				gotoxy(40, 26);
				printf("파산!");
				Money(t, 0, -1, user, NUM, 1); //돈을 0으로
				exit(0);
			}
			else
			{
				gotoxy(40, 24);
				printf("턴을 넘깁니다.");
				getchar();
				gotoxy(40, 24);
				printf("                 ");
			}
		}
		else if (map_count(t, x[t], y[t], -1) == 1) //자신의 관광지일 때
		{
			gotoxy(40, 26);
			printf("자신의 관광지이므로 턴을 넘깁니다.");
			getchar();
			gotoxy(40, 26);
			printf("                                            ");
		}
		else //주인이 없을 때
		{
			gotoxy(40, 26);
			{
				printf("관광지를 사시겠습니까?(No는 0, Yes는 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                                 ");
				getchar();
				J = Money(t, map_money(t, x, y, 4, 1), 1, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1) //돈이 없을 때
				{
					gotoxy(40, 24);
					printf("돈이 부족하므로 턴을 넘깁니다.");
					getchar();
					gotoxy(40, 24);
					printf("                                 ");
				}
				else
				{
					gotoxy(40, 24);
					printf("관광지를 삽니다.");
					build_print(t, x[t], y[t] + 3, 1); //건물 출력
					getchar();
					gotoxy(40, 24);
					printf("                     ");
					map_count((t) % NUM, x[t], y[t], 1); //좌표별로 누가 땅의 주인인지 알려주는 함수로 이동
					gotoxy(40, 24);
					printf("턴을 넘깁니다.");
					getchar();
					gotoxy(40, 24);
					printf("                 ");
				}
			}
			else if (Q == 0)
			{
				gotoxy(40, 26);
				printf("                                                  ");
				gotoxy(40, 24);
				printf("턴을 넘깁니다.");
				getchar();
				gotoxy(40, 24);
				printf("                 ");
			}
		}

	}
	else if (x[t] == 8 && y[t] <= 46 && y[t] >= 11 && y[t] != 25 || x[t] >= 22 && x[t] <= 92 && x[t] != 50 && y[t] == 4 || x[t] == 106 && y[t] >= 11 && y[t] <= 39 && y[t] != 18 || x[t] <= 92 && x[t] >= 22 && x[t] != 78 && x[t] != 36) //왼쪽 땅 에 도착했을 때
	{
		gotoxy(40, 24);
		printf("%d번째 말이 도착했습니다.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                    ");
		if (map_count((t + 1) % NUM, x[t], y[t], -1)>0 || map_count((t + 2) % NUM, x[t], y[t], -1)>0 || map_count((t + 3) % NUM, x[t], y[t], -1)>0) //다른 사람의 땅일 때
		{
			if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1 || map_count((t + 2) % NUM, x[t], y[t], -1) == 1 || map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
			{
				gotoxy(40, 26);
				printf("다른 사람의 땅입니다. 통행료를 지불합니다.");
				getchar();
				gotoxy(40, 26);
				printf("                                              ");
				J = Money(t, map_money(t, x, y, 1, 2), 1, user, NUM, 0);  //돈 관리 함수로 이동

				if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1)
					Money((t + 1) % NUM, map_money(t, x, y, 1, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 1)
					Money((t + 2) % NUM, map_money(t, x, y, 1, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
					Money((t + 3) % NUM, map_money(t, x, y, 1, 2), 0, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1) //파산
				{
					gotoxy(40, 26);
					printf("파산!");
					Money(t, 0, -1, user, NUM, 1); //돈 관리 함수로 이동
					exit(0);
				}
				else
				{
					gotoxy(40, 26);
					{
						printf("땅을 인수하시겠습니까?(No는 0, Yes는 1) : ");
						scanf_s("%d", &Q);
					}
					if (Q == 1)
					{
						gotoxy(40, 26);
						printf("                                                   ");
						J = Money(t, map_money(t, x, y, 1, 3), 1, user, NUM, 0); //돈 관리 함수로 이동
						if (J == 1)
						{
							gotoxy(40, 24);
							printf("돈이 부족하므로 턴을 넘깁니다.");
							getchar();
							gotoxy(40, 24);
							printf("                                  ");
						}
						else
						{
							if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1)
								Money((t + 1) % NUM, map_money(t, x, y, 1, 3), 0, user, NUM, 0); //돈 관리 함수로 이동
							else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 1)
								Money((t + 2) % NUM, map_money(t, x, y, 1, 3), 0, user, NUM, 0); //돈 관리 함수로 이동
							else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
								Money((t + 3) % NUM, map_money(t, x, y, 1, 3), 0, user, NUM, 0); //돈 관리 함수로 이동
							gotoxy(40, 26);
							printf("인수값을 지불했습니다.");
							getchar();
							gotoxy(40, 26);
							printf("                          ");
							build_print(t, x[t] - 3, y[t] + 3, 0);
							map_count((t + 1) % NUM, x[t], y[t], 0);
							map_count((t + 2) % NUM, x[t], y[t], 0);
							map_count((t + 3) % NUM, x[t], y[t], 0);
							map_count((t) % NUM, x[t], y[t], 1);
							gotoxy(40, 26);
							printf("인수를 완료했습니다.");
							getchar();
							gotoxy(40, 26);
							printf("                        ");
							gotoxy(40, 27);
							{
								printf("건물을 짓겠습니까?(No는 0, Yes는 1) : ");
								scanf_s("%d", &Q);
							}
							getchar();
							gotoxy(40, 27);
							printf("                                              ");
							if (Q == 1)
							{
								J = Money(t, map_money(t, x, y, 2, 1), 1, user, NUM, 0); //돈 관리 함수로 이동
								if (J == 1)
								{
									gotoxy(40, 24);
									printf("돈이 부족하므로 턴을 넘깁니다.");
									getchar();
									gotoxy(40, 24);
									printf("                                  ");
								}
								else
								{
									build_print(t, x[t] - 3, y[t] + 3, 0);
									build_print(t, x[t], y[t] + 3, 0);
									gotoxy(40, 24);
									printf("건물을 지었습니다.");
									getchar();
									gotoxy(40, 24);
									printf("                      ");
									map_count((t + 1) % NUM, x[t], y[t], 0);
									map_count((t + 2) % NUM, x[t], y[t], 0);
									map_count((t + 3) % NUM, x[t], y[t], 0);
									map_count((t) % NUM, x[t], y[t], 2);
									gotoxy(40, 24);
									printf("턴을 넘깁니다.");
									getchar();
									gotoxy(40, 24);
									printf("                 ");
								}

							}
							else if (Q == 0)
							{
								gotoxy(40, 24);
								printf("턴을 넘깁니다.");
								getchar();
								gotoxy(40, 24);
								printf("                 ");
							}
						}
					}
					else if (Q == 0)
					{
						gotoxy(40, 26);
						printf("                                                   ");
						gotoxy(40, 24);
						printf("턴을 넘깁니다.");
						getchar();
						gotoxy(40, 24);
						printf("                 ");
					}
				}
			}
			else if (map_count((t + 1) % NUM, x[t], y[t], -1) == 2 || map_count((t + 2) % NUM, x[t], y[t], -1) == 2 || map_count((t + 3) % NUM, x[t], y[t], -1) == 2)
			{
				gotoxy(40, 26);
				printf("다른 사람의 건물입니다. 통행료를 지불합니다.");
				if (map_count((t + 1) % NUM, x[t], y[t], -1) == 2)
					Money((t + 1) % NUM, map_money(t, x, y, 2, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 2)
					Money((t + 2) % NUM, map_money(t, x, y, 2, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 2)
					Money((t + 3) % NUM, map_money(t, x, y, 2, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				gotoxy(40, 26);
				printf("                                               ");
				J = Money(t, map_money(t, x, y, 2, 2), 1, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1) //파산
				{
					gotoxy(40, 26);
					printf("파산!");
					Money(t, 0, -1, user, NUM, 1); //돈 관리 함수로 이동
					exit(0);
				}

				gotoxy(40, 26);
				{
					printf("땅과 건물을 인수하시겠습니까?(No는 0, Yes는 1) : ");
					scanf_s("%d", &Q);
				}
				if (Q == 1)
				{
					gotoxy(40, 26);
					printf("                                                     ");
					J = Money(t, map_money(t, x, y, 2, 3), 1, user, NUM, 0); //돈 관리 함수로 이동
					if (J == 1)
					{
						gotoxy(40, 24);
						printf("돈이 부족하므로 턴을 넘깁니다.");
						getchar();
						gotoxy(40, 24);
						printf("                                 ");
					}
					else
					{
						if (map_count((t + 1) % NUM, x[t], y[t], -1) == 2)
							Money((t + 1) % NUM, map_money(t, x, y, 2, 3), 0, user, NUM, 0); //돈 관리 함수로 이동
						else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 2)
							Money((t + 2) % NUM, map_money(t, x, y, 2, 3), 0, user, NUM, 0); //돈 관리 함수로 이동
						else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 2)
							Money((t + 3) % NUM, map_money(t, x, y, 2, 3), 0, user, NUM, 0); //돈 관리 함수로 이동
						gotoxy(40, 26);
						printf("인수값을 지불했습니다.");
						getchar();
						gotoxy(40, 26);
						printf("                         ");
						build_print(t, x[t] - 3, y[t] + 3, 0);
						build_print(t, x[t], y[t] + 3, 0);
						map_count((t + 1) % NUM, x[t], y[t], 0);
						map_count((t + 2) % NUM, x[t], y[t], 0);
						map_count((t + 3) % NUM, x[t], y[t], 0);
						map_count((t) % NUM, x[t], y[t], 2);
						gotoxy(40, 26);
						printf("인수를 완료했습니다.");
						getchar();
						gotoxy(40, 26);
						printf("                       ");
						gotoxy(40, 27);
						{
							printf("랜드마크를 짓겠습니까?(No는 0, Yes는 1) : ");
							scanf_s("%d", &Q);
						}
						getchar();
						gotoxy(40, 27);
						printf("                                                 ");
						if (Q == 1)
						{
							J = Money(t, map_money(t, x, y, 3, 1), 1, user, NUM, 0); //돈 관리 함수로 이동
							if (J == 1)
							{
								gotoxy(40, 24);
								printf("돈이 부족하므로 턴을 넘깁니다.");
								getchar();
								gotoxy(40, 24);
								printf("                                ");
							}
							else
							{
								build_print(t, x[t] - 3, y[t] + 3, 0);
								build_print(t, x[t], y[t] + 3, 0);
								build_print(t, x[t] + 3, y[t] + 3, 0);
								gotoxy(40, 24);
								printf("랜드마크를 지었습니다.");
								getchar();
								gotoxy(40, 24);
								printf("                          ");
								map_count((t + 1) % NUM, x[t], y[t], 0);
								map_count((t + 2) % NUM, x[t], y[t], 0);
								map_count((t + 3) % NUM, x[t], y[t], 0);
								map_count((t) % NUM, x[t], y[t], 3);
								gotoxy(40, 24);
								printf("턴을 넘깁니다.");
								getchar();
								gotoxy(40, 24);
								printf("                 ");
							}

						}
						else if (Q == 0)
						{
							gotoxy(40, 24);
							printf("턴을 넘깁니다.");
							getchar();
							gotoxy(40, 24);
							printf("                 ");
						}
					}
				}
				else if (Q == 0)
				{
					gotoxy(40, 26);
					printf("                                                   ");
					gotoxy(40, 24);
					printf("턴을 넘깁니다.");
					getchar();
					gotoxy(40, 24);
					printf("                 ");
				}
			}
			else if (map_count((t + 1) % NUM, x[t], y[t], -1) == 3 || map_count((t + 2) % NUM, x[t], y[t], -1) == 3 || map_count((t + 3) % NUM, x[t], y[t], -1) == 3)
			{
				gotoxy(40, 26);
				printf("다른 사람의 랜드마크입니다. 통행료를 지불합니다.");
				if (map_count((t + 1) % NUM, x[t], y[t], -1) == 3)
					Money((t + 1) % NUM, map_money(t, x, y, 3, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 3)
					Money((t + 2) % NUM, map_money(t, x, y, 3, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 3)
					Money((t + 3) % NUM, map_money(t, x, y, 3, 2), 0, user, NUM, 0); //돈 관리 함수로 이동
				gotoxy(40, 26);
				printf("                                                    ");
				J = Money(t, map_money(t, x, y, 3, 2), 1, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1) //파산
				{
					gotoxy(40, 26);
					printf("파산!");
					Money(t, 0, -1, user, NUM, 1); //돈 관리 함수로 이동
					exit(0);
				}
				gotoxy(40, 28);
				printf("랜드마크이므로 인수를 할 수 없습니다.");
				getchar();

				gotoxy(40, 28);
				printf("                                      ");
				gotoxy(40, 24);
				printf("턴을 넘깁니다.");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count(t, x[t], y[t], -1) == 0) //땅이 비어있을 때 (땅건설)
		{
			gotoxy(40, 26);
			{
				printf("땅을 사시겠습니까?(No는 0, Yes는 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                              ");
				getchar();
				J = Money(t, map_money(t, x, y, 1, 1), 1, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1)
				{
					gotoxy(40, 24);
					printf("돈이 부족하므로 턴을 넘깁니다.");
					getchar();
					gotoxy(40, 24);
					printf("                                ");
				}
				else
				{
					gotoxy(40, 24);
					printf("땅을 삽니다.");
					build_print(t, x[t] - 3, y[t] + 3, 0);
					getchar();
					gotoxy(40, 24);
					printf("               ");
					map_count((t) % NUM, x[t], y[t], 1);
				}
			}
			else if (Q == 0)
			{
				gotoxy(40, 26);
				printf("                                              ");
				gotoxy(40, 24);
				printf("턴을 넘깁니다.");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count((t) % NUM, x[t], y[t], -1) == 1) //내 땅일 때 (건물건설)
		{
			gotoxy(40, 26);
			{
				printf("건물을 사시겠습니까?(No는 0, Yes는 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                              ");
				getchar();
				J = Money(t, map_money(t, x, y, 2, 1), 1, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1)
				{
					gotoxy(40, 24);
					printf("돈이 부족하므로 턴을 넘깁니다.");
					getchar();
					gotoxy(40, 24);
					printf("                               ");
				}
				else
				{
					gotoxy(40, 24);
					printf("건물을 삽니다.");
					build_print(t, x[t], y[t] + 3, 0);
					getchar();
					gotoxy(40, 24);
					printf("               ");
					map_count((t) % NUM, x[t], y[t], 2);
				}
			}
			else if (Q == 0)
			{
				gotoxy(40, 26);
				printf("                                              ");
				gotoxy(40, 24);
				printf("턴을 넘깁니다.");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count(t, x[t], y[t], -1) == 2) //내 건물일 때 (랜드마크건설)
		{
			gotoxy(40, 26);
			{
				printf("랜드마크를 사시겠습니까?(No는 0, Yes는 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                              ");
				getchar();
				J = Money(t, map_money(t, x, y, 3, 1), 1, user, NUM, 0); //돈 관리 함수로 이동

				if (J == 1)
				{
					gotoxy(40, 24);
					printf("돈이 부족하므로 턴을 넘깁니다.");
					getchar();
					gotoxy(40, 24);
					printf("                                ");
				}
				else
				{
					gotoxy(40, 24);
					printf("랜드마크를 삽니다.");
					build_print(t, x[t] + 3, y[t] + 3, 0);
					getchar();
					gotoxy(40, 24);
					printf("                   ");
					map_count((t) % NUM, x[t], y[t], 3);
				}
			}
			else if (Q == 0)
			{
				gotoxy(40, 26);
				printf("                                              ");
				gotoxy(40, 24);
				printf("턴을 넘깁니다");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count((t) % NUM, x[t], y[t], -1) == 3) //내 랜드마크일 때
		{
			gotoxy(40, 26);
			printf("더이상 지을 수 없습니다. 턴을 넘깁니다.");
			getchar();
			gotoxy(40, 26);
			printf("                                        ");
		}
	}
	else if (x[t] == 8 && y[t] == 53) //출발지
	{
		gotoxy(40, 24);
		printf("%d번째 말이 출발지에 도착했습니다.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                           ");
		Money(t, 1000000, 0, user, NUM, 0); //돈 관리 함수로 이동
		gotoxy(40, 24);
		printf("월급이 지급되었습니다.");
		getchar();
		gotoxy(40, 24);
		printf("                        ");
		gotoxy(40, 24);
		printf("턴을 넘깁니다.");
		getchar();
		gotoxy(40, 24);
		printf("                ");
	}
	else if (x[t] == 106 && y[t] == 53 || x[t] == 106 && y[t] == 4) //쉽터
	{
		gotoxy(40, 24);
		printf("%d번째 말이 쉽터에 도착했습니다.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                          ");
		gotoxy(40, 24);
		printf("턴을 넘깁니다.");
		getchar();
		gotoxy(40, 24);
		printf("                ");
	}
}

int Money(int t, int price, int PM, char user[][5], int NUM, int b)//PM이 1이면 감소 0이면 증가, 돈 관리
{
	static int Money[4] = { 10000000,10000000,10000000,10000000 };
	State(t, user, NUM, Money);
	getchar();
	if (PM == 0) //+돈
	{
		gotoxy(40, 26);
		printf("+%d원                                          ", price);
		Money[t] = Money[t] + price;
		State(t, user, NUM, Money);
		getchar();
		gotoxy(40, 26);
		printf("                                                      ");
		return 0;
	}
	else if (PM == 1) //-돈
	{
		gotoxy(40, 26);
		printf("-%d원                                    ", price);
		if (Money[t] - price<0) //돈이 없을 때
		{
			State(t, user, NUM, Money);
			getchar();
			gotoxy(40, 26);
			printf("                                                 ");
			return 1;
		}
		else //돈이 있을 때
		{
			Money[t] -= price;
			State(t, user, NUM, Money);
			getchar();
			gotoxy(40, 26);
			printf("          ");
			return 0;
		}
	}
	else if (PM == 2) //정신과 시간의 방일 때
	{
		price = Money[t] * price / 100;
		gotoxy(40, 26);
		printf("-%d원", price);
		getchar();
		gotoxy(40, 26);
		printf("           ");
		Money[t] -= price;
		State(t, user, NUM, Money);
		return 0;
	}
	else if (b == 1) //파산한 후 순위출력 함수
	{
		int i, temp1, temp, a[4] = { 0,1,2,3 }, e = 0;
		Money[t] = 0;
		//Money[(t+1)%4]=10,Money[(t+2)%4]=10,Money[(t+3)%4]=10;
		gotoxy(40, 24);
		printf("순위를 출력합니다.");
		getchar();
		gotoxy(40, 24);
		printf("                  ");
		system("cls");
		for (i = 0; i<4; i++)
		{
			for (t = 0; t<4; t++)
			{
				if (Money[t]<Money[(t + 1)])
				{
					temp = Money[t];
					Money[t] = Money[(t + 1)];
					Money[(t + 1)] = temp;
					temp1 = a[t];
					a[t] = a[t + 1];
					a[t + 1] = temp1;
				}
			}
		}
		if (Money[0] == Money[1] && Money[0] == Money[2])//3개가 같은 때
			e = 4;
		else if (Money[1] == Money[2] && Money[1] == Money[3])//3개가 같은 때
			e = 5;
		else if (Money[0] == Money[1])//2개가 같은 때
			e = 1;
		else if (Money[1] == Money[2])//2개가 같은 때
			e = 2;
		else if (Money[2] == Money[3])//2개가 같은 때
			e = 3;
		printf("순위\n");
		if (e>0) //순위 출력
		{
			if (e == 1)
			{
				for (t = 0; t <= 3; t++)
				{
					if (t == 0 || t == 1)
					{
						T_Color(a[t]);
						printf("공동 %d위 : %s %d원\n", 1, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 2 || t == 3)
					{
						T_Color(a[t]);
						printf("%d위 : %s %d원\n", t + 1, user[a[t]], Money[t]);
						Color(15);
					}
				}
			}
			else if (e == 2)
			{
				for (t = 0; t <= 3; t++)
				{
					if (t == 1 || t == 2)
					{
						T_Color(a[t]);
						printf("공동 %d위 : %s %d원\n", 2, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 0 || t == 3)
					{
						T_Color(a[t]);
						printf("%d위 : %s %d원\n", t + 1, user[a[t]], Money[t]);
						Color(15);
					}
				}
			}
			else if (e == 3)
			{
				for (t = 0; t <= 3; t++)
				{
					if (t == 2 || t == 3)
					{
						T_Color(a[t]);
						printf("공동 %d위 : %s %d원\n", 3, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 0 || t == 1)
					{
						T_Color(a[t]);
						printf("%d위 : %s %d원\n", t + 1, user[a[t]], Money[t]);
						Color(15);
					}
				}
			}
			else if (e == 4)
			{
				for (t = 0; t <= 3; t++)
				{
					if (t == 0 || t == 1 || t == 2)
					{
						T_Color(a[t]);
						printf("공동 %d위 : %s %d원\n", 1, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 3)
					{
						T_Color(a[t]);
						printf("%d위 : %s %d원\n", t + 1, user[a[t]], Money[t]);
						Color(15);
					}
				}
			}
			else if (e == 5)
			{
				for (t = 0; t <= 3; t++)
				{
					if (t == 1 || t == 2 || t == 3)
					{
						T_Color(a[t]);
						printf("공동 %d위 : %s %d원\n", 2, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 0)
					{
						T_Color(a[t]);
						printf("%d위 : %s %d원\n", t + 1, user[a[t]], Money[t]);
						Color(15);
					}
				}
			}
		}
		else
		{
			for (t = 0; t<4; t++)
			{
				T_Color(a[t]);
				printf("%d위 : %s %d원\n", t + 1, user[a[t]], Money[t]);
				Color(15);
			}
		}
	}
}
void Icon(int a) //사용자의 말 아이콘
{
	if (a == 0)
	{
		Color(3);
		printf("☆");
		Color(15);
	}
	else if (a == 1)
	{
		Color(6);
		printf("○");
		Color(15);
	}
	else if (a == 2)
	{
		Color(4);
		printf("□");
		Color(15);
	}
	else if (a == 3)
	{
		Color(2);
		printf("◇");
		Color(15);
	}
}
void remove_Icon(int a) //아이콘 지우기
{
	if (a == 0)
	{
		Color(0);
		printf("☆");
		Color(15);
	}
	else if (a == 1)
	{
		Color(0);
		printf("○");
		Color(15);
	}
	else if (a == 2)
	{
		Color(0);
		printf("□");
		Color(15);
	}
	else if (a == 3)
	{
		Color(0);
		printf("◇");
		Color(15);
	}
}
void build_print(int t, int x, int y, int M) //건물 출력
{
	if (M == 0)
	{
		if (t == 0)
		{
			Color(3);
			gotoxy(x, y);
			printf("※");
			Color(15);
		}
		else if (t == 1)
		{
			Color(6);
			gotoxy(x, y);
			printf("※");
			Color(15);
		}
		else if (t == 2)
		{
			Color(4);
			gotoxy(x, y);
			printf("※");
			Color(15);
		}
		else if (t == 3)
		{
			Color(2);
			gotoxy(x, y);
			printf("※");
			Color(15);
		}
	}
	else if (M == 1)
	{
		if (t == 0)
		{
			Color(3);
			gotoxy(x, y);
			printf("▲");
			Color(15);
		}
		else if (t == 1)
		{
			Color(6);
			gotoxy(x, y);
			printf("▲");
			Color(15);
		}
		else if (t == 2)
		{
			Color(4);
			gotoxy(x, y);
			printf("▲");
			Color(15);
		}
		else if (t == 3)
		{
			Color(2);
			gotoxy(x, y);
			printf("▲");
			Color(15);
		}
	}
}

int map_count(int t, int x, int y, int a) //좌표별로 누가 땅의 주인인지 알려줌
{
	if (x == 8 && y == 46) //울산
	{
		static int count_Ulsan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Ulsan[t] += 0;
		else
			count_Ulsan[t] = a;
		return count_Ulsan[t];
	}
	else if (x == 8 && y == 39) //대구
	{
		static int count_Daegu[4] = { 0,0,0,0 };
		if (a == -1)
			count_Daegu[t] += 0;
		else
			count_Daegu[t] = a;
		return count_Daegu[t];
	}
	else if (x == 8 && y == 32) //세종
	{
		static int count_Sejong[4] = { 0,0,0,0 };
		if (a == -1)
			count_Sejong[t] += 0;
		else
			count_Sejong[t] = a;
		return count_Sejong[t];
	}
	else if (x == 8 && y == 18) //인천
	{
		static int count_Incheon[4] = { 0,0,0,0 };
		if (a == -1)
			count_Incheon[t] += 0;
		else
			count_Incheon[t] = a;
		return count_Incheon[t];
	}
	else if (x == 8 && y == 11) //강릉
	{
		static int count_Gangneung[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gangneung[t] += 0;
		else
			count_Gangneung[t] = a;
		return count_Gangneung[t];
	}
	else if (x == 22 && y == 4) //대전
	{
		static int count_Daejeon[4] = { 0,0,0,0 };
		if (a == -1)
			count_Daejeon[t] += 0;
		else
			count_Daejeon[t] = a;
		return count_Daejeon[t];
	}
	else if (x == 36 && y == 4) //광주
	{
		static int count_Gwangju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gwangju[t] += 0;
		else
			count_Gwangju[t] = a;
		return count_Gwangju[t];
	}
	else if (x == 64 && y == 4) //부산
	{
		static int count_Busan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Busan[t] += 0;
		else
			count_Busan[t] = a;
		return count_Busan[t];
	}
	else if (x == 78 && y == 4) //춘천
	{
		static int count_Chuncheon[4] = { 0,0,0,0 };
		if (a == -1)
			count_Chuncheon[t] += 0;
		else
			count_Chuncheon[t] = a;
		return count_Chuncheon[t];
	}
	else if (x == 92 && y == 4) //포항
	{
		static int count_Pohang[4] = { 0,0,0,0 };
		if (a == -1)
			count_Pohang[t] += 0;
		else
			count_Pohang[t] = a;
		return count_Pohang[t];
	}
	else if (x == 106 && y == 11) //목포
	{
		static int count_Mokpo[4] = { 0,0,0,0 };
		if (a == -1)
			count_Mokpo[t] += 0;
		else
			count_Mokpo[t] = a;
		return count_Mokpo[t];
	}
	else if (x == 106 && y == 25) //진주
	{
		static int count_Jinju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Jinju[t] += 0;
		else
			count_Jinju[t] = a;
		return count_Jinju[t];
	}
	else if (x == 106 && y == 32) //광주
	{
		static int count_Gwangju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gwangju[t] += 0;
		else
			count_Gwangju[t] = a;
		return count_Gwangju[t];
	}
	else if (x == 106 && y == 39) //원주
	{
		static int count_Wonju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Wonju[t] += 0;
		else
			count_Wonju[t] = a;
		return count_Wonju[t];
	}
	else if (x == 92 && y == 53) //통영
	{
		static int count_Tongyeong[4] = { 0,0,0,0 };
		if (a == -1)
			count_Tongyeong[t] += 0;
		else
			count_Tongyeong[t] = a;
		return count_Tongyeong[t];
	}
	else if (x == 64 && y == 53) //여수
	{
		static int count_Yeosu[4] = { 0,0,0,0 };
		if (a == -1)
			count_Yeosu[t] += 0;
		else
			count_Yeosu[t] = a;
		return count_Yeosu[t];
	}
	else if (x == 50 && y == 53) //독도
	{
		static int count_Dokdo[4] = { 0,0,0,0 };
		if (a == -1)
			count_Dokdo[t] += 0;
		else
			count_Dokdo[t] = a;
		return count_Dokdo[t];
	}
	else if (x == 22 && y == 53) //서울
	{
		static int count_Seoul[4] = { 0,0,0,0 };
		if (a == -1)
			count_Seoul[t] += 0;
		else
			count_Seoul[t] = a;
		return count_Seoul[t];
	}
	else if (x == 8 && y == 25) //지리산
	{
		static int count_Jirisan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Jirisan[t] += 0;
		else
			count_Jirisan[t] = a;
		return count_Jirisan[t];
	}
	else if (x == 50 && y == 4) //설악산
	{
		static int count_Seoraksan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Seoraksan[t] += 0;
		else
			count_Seoraksan[t] = a;
		return count_Seoraksan[t];
	}
	else if (x == 106 && y == 18) //한라산
	{
		static int count_Hallasan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Hallasan[t] += 0;
		else
			count_Hallasan[t] = a;
		return count_Hallasan[t];
	}
	else if (x == 106 && y == 46) //치악산
	{
		static int count_Chiaksan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Chiaksan[t] += 0;
		else
			count_Chiaksan[t] = a;
		return count_Chiaksan[t];
	}
	else if (x == 78 && y == 53) //관악산
	{
		static int count_Gwanaksan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gwanaksan[t] += 0;
		else
			count_Gwanaksan[t] = a;
		return count_Gwanaksan[t];
	}
	else if (x == 36 && y == 53) //도봉산
	{
		static int count_Dobongsan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Dobongsan[t] += 0;
		else
			count_Dobongsan[t] = a;
		return count_Dobongsan[t];
	}
}

int map_money(int t, int x[], int y[], int i, int j) //땅값을 반환해주는 함수
{
	if (x[t] == 8 && y[t] <= 46 && y[t] >= 11)
	{
		int G = 100000, B = 200000, L = 400000, M = 800000;//땅(G),건물(B),랜드마크(L),관광지(M)
		if (j == 1) //지불
		{
			if (i == 1)
				return G;
			else if (i == 2)
				return B;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M;
		}
		else if (j == 2) //통행료
		{
			if (i == 1)
				return G / 2;
			else if (i == 2)
				return B / 2;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M / 2;
		}
		else if (j == 3) //인수
		{
			if (i == 1)
				return G * 2;
			else if (i == 2)
				return (G + B) * 2;
		}
		else if (i == 0 && j == 0)
		{
			return 0;
		}
		return 0;
	}
	else if (x[t] >= 22 && x[t] <= 92 && y[t] == 4)
	{
		int G = 200000, B = 400000, L = 800000, M = 800000;//땅(G),건물(B),랜드마크(L)
		if (j == 1)
		{
			if (i == 1)
				return G;
			else if (i == 2)
				return B;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M;
		}
		else if (j == 2)
		{
			if (i == 1)
				return G / 2;
			else if (i == 2)
				return B / 2;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M / 2;
		}
		else if (j == 3)
		{
			if (i == 1)
				return G * 2;
			else if (i == 2)
				return (G + B) * 2;
		}
		else if (i == 0 && j == 0)
		{
			return 0;
		}
		return 0;
	}
	else if (x[t] == 106 && y[t] >= 11 && y[t] <= 46)
	{
		int G = 400000, B = 800000, L = 1600000, M = 800000;//땅(G),건물(B),랜드마크(L)
		if (j == 1)
		{
			if (i == 1)
				return G;
			else if (i == 2)
				return B;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M;
		}
		else if (j == 2)
		{
			if (i == 1)
				return G / 2;
			else if (i == 2)
				return B / 2;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M / 2;
		}
		else if (j == 3)
		{
			if (i == 1)
				return G * 2;
			else if (i == 2)
				return (G + B) * 2;
		}
		else if (i == 0 && j == 0)
		{
			return 0;
		}
		return 0;
	}
	else if (x[t] <= 92 && x[t] >= 22 && y[t] == 53)
	{
		int G = 800000, B = 1600000, L = 3200000, M = 800000;//땅(G),건물(B),랜드마크(L)
		if (j == 1)
		{
			if (i == 1)
				return G;
			else if (i == 2)
				return B;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M;
		}
		else if (j == 2)
		{
			if (i == 1)
				return G / 2;
			else if (i == 2)
				return B / 2;
			else if (i == 3)
				return L;
			else if (i == 4)
				return M / 2;
		}
		else if (j == 3)
		{
			if (i == 1)
				return G * 2;
			else if (i == 2)
				return (G + B) * 2;
		}
		else if (i == 0 && j == 0)
		{
			return 0;
		}
		return 0;
	}
}

void T_Color(int t) //사용자의 색
{
	if (t == 0)
	{
		Color(3);
	}
	else if (t == 1)
	{
		Color(6);
	}
	else if (t == 2)
	{
		Color(4);
	}
	else if (t == 3)
	{
		Color(2);
	}
}

void line_cover() //맵 왼쪽에 잘린 부분을 커버해줌
{
	gotoxy(1, 18);
	{
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("├\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("├\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("├\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("├\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("├\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
		printf("│\n");
	}
}