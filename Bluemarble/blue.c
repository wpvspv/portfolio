#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void map(); //����� �Լ�
void gotoxy(int x, int y); //��ǥ�Լ�
void Random_Dice(); //�ֻ��� ������ �Լ�
void Move(); //�� �����̱� �Լ�
void Desert_island(); //���� 2���� �� ���Ű� �ð��� �� �Լ�
void build(); //��ǥ���� �ǹ� �Ǽ� �Լ�
void State(); //����� ���� �Լ�
void Icon(); //������� �� ������ �Լ�
void Color(); //�� �Լ�
int Money(); //�� ���� �Լ�
void build_print(); //�ǹ� ��� �Լ�
void remove_Icon(); //������ ����� �Լ�
int map_count(); //��ǥ���� ���� ���� �������� �˷��ִ� �Լ�
void T_Color(); //������� �� �Լ�
void Rank(); //���� �Լ�
void line_cover(); //�� ���ʿ� �߸� �κ��� Ŀ�����ִ� �Լ�
int map_money(); //������ ��ȯ���ִ� �Լ�

int main()
{
	char user[4][5]; //�ִ� ������� �̸� �迭 ����
	int NUM, i;

	printf("��� ���� �־��ּ���(2��~4��) : ");
	scanf("%d", &NUM);

	for (i = 0; i<NUM; i++) //�̸� �Է�
	{
		getchar();
		printf("%d��° ����� �г����� �־��ּ���(����3���� �ѱ� 2����)", i + 1);
		scanf("%s", user[i]);//�̸� ����
	}

	getchar();
	system("cls");

	map(); //�� ���
	for (i = 0; i<NUM; i++) //����� ���� ���� ���
	{
		gotoxy(120, 8 + i * 14);
		{
			T_Color(i);
			printf("%s", user[i]);
			Color(15);
		}
	}
	for (i = 0; i<NUM; i++) //�������� �� ���
	{
		if (i == 0)
		{
			Color(3);
			gotoxy(6, 52);
			printf("��");
			Color(15);
		}
		else if (i == 1)
		{
			Color(6);
			gotoxy(10, 52);
			printf("��");
			Color(15);
		}
		else if (i == 2)
		{
			Color(4);
			gotoxy(6, 54);
			printf("��");
			Color(15);
		}
		else if (i == 3)
		{
			Color(2);
			gotoxy(10, 54);
			printf("��");
			Color(15);
		}
	}
	getchar();
	for (i = 0;; i++)
	{
		static int x[4] = { 8,8,8,8 }, y[4] = { 53,53,53,53 }; //ó�� ��ǥ
		gotoxy(50, 42);
		printf("%d��° ���� �ϴ� ��\n", i%NUM + 1);

		Random_Dice(i%NUM, user, NUM, 0, x, y); //�ֻ��� ������ 
		line_cover();//�� ���ʿ� �߸� �κ��� Ŀ��
	}
	return 0;
}

void State(int t, char p[][5], int NUM, int Money[]) //���� ����(�г��� �ڻ�) ���
{
	int i;
	Color(0); //��µȰ� �����ش�
	for (i = 0; i<NUM; i++)
	{
		gotoxy(120, 8 + i * 14);
		{
			if (t == 0)
			{
				printf("%s �����ڻ� : %d��          ", p[i], Money[i]);
			}
		}
	}
	for (i = 0; i<NUM; i++)
	{
		gotoxy(120, 8 + i * 14);
		{
			T_Color(i);
			printf("%s �����ڻ� : %d��", p[i], Money[i]);
			Color(15);
		}
	}
}

void map() //�����
{
	// ���� : �� �� �� �� �� �� �� �� �� �� ��
	printf("������������������������������������������������������������������������������������������������������������������\n");
	printf("��   ���Ű�   ��    ����    ��    ����    ��  �㼳�ǻ�  ��    �λ�    ��    ��õ    ��    ����    ��   �ͽ���   ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��  �ð��ǹ�  ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("������������������������������������������������������������������������������������������������������������������\n");
	printf("��    ����    ��                                                                                  ��    ����    ��\n");
	printf("��            ��                                                                                  ��	        ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("����������������                                                                                  ����������������\n");
	printf("��    ��õ    ��                                                                                  ��  ���Ѷ��  ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("����������������                                                                                  ����������������\n");
	printf("��  ��������  ��                                                                                  ��    ����    ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("����������������                                                                                  ����������������\n");
	printf("��    ����    ��                                                                                  ��    ����    ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("����������������                                                                                  ����������������\n");
	printf("��    �뱸    ��                                                                                  ��    ����    ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("����������������                                                                                  ����������������\n");
	printf("��    ���    ��                                                                                  ��  ��ġ�ǻ�  ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("��            ��                                                                                  ��            ��\n");
	printf("������������������������������������������������������������������������������������������������������������������\n");
	printf("��    ����    ��    ����    ��  �㵵����  ��    ����    ��    ����    ��  ����ǻ�  ��    �뿵    ��   �ͽ���   ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("��            ��            ��            ��            ��            ��            ��            ��            ��\n");
	printf("������������������������������������������������������������������������������������������������������������������\n");
}

void gotoxy(int x, int y) //��ǥ
{
	COORD pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Color(int a) //��
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void Move(int a, int t, char user[][5], int NUM, int c, int x[], int y[]) //�� �̵�
{
	int s;
	//gotoxy(x[t],y[t]);
	//Icon(t);
	getchar();
	Color(0);
	gotoxy(50, 14); //�ֻ��� ��� ����
	printf("������    ������\n");
	gotoxy(50, 15);
	printf("��%2d��    ��%2d��\n");
	gotoxy(50, 16);
	printf("������    ������\n");
	Color(15);


	if (t == 0) //�ֻ��� �������� ��ǥ�� �ִ� �� ����
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
	for (; a>0;) //�� �̵��Ұ� �������� ��
	{
		if (x[t] == 8 && y[t] - 7 * a<4 && y[t] != 4)
		{


			s = (y[t] - 4) / 7; //�̵��Ÿ�

								//gotoxy(x,y-7*s);
								//printf("��");
			y[t] = y[t] - 7 * s;
			a = a - s;


		}
		else if (x[t] + 14 * a>106 && x[t] != 106 && y[t] == 4)
		{


			s = (106 - x[t]) / 14;

			//gotoxy(x+14*s,y);
			//printf("��");
			x[t] = x[t] + 14 * s;
			a = a - s;


		}

		else if (x[t] == 106 && y[t] + 7 * a>53 && y[t] != 53)
		{


			s = (53 - y[t]) / 7;

			//gotoxy(x,y+7*s);
			//printf("��");
			y[t] = y[t] + 7 * s;
			a = a - s;


		}
		else if (x[t] - 14 * a<8 && x[t] != 8 && y[t] == 53)
		{


			s = (x[t] - 8) / 14;

			//gotoxy(x-14*s,y);
			//printf("��");
			x[t] = x[t] - 14 * s;
			a = a - s;


		}
		else //�� ��� �κ�
		{
			if (x[t] == 8 && y[t] <= 53 && y[t] >= 11) //����
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
			else if (x[t] <= 92 && x[t] >= 8 && y[t] == 4) //����
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
			else if (x[t] == 106 && y[t] >= 4 && y[t] <= 46) //������
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
			else if (x[t] <= 106 && x[t] >= 22 && y[t] == 53) //�Ʒ���
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

void Random_Dice(int t, char user[][5], int NUM, int c, int x[], int y[]) //�ֻ��� ������
{
	int sum = 0, i = 0, j = 0;
	//static int count[t]={0,0,0,0};
	srand(time(NULL)); //�ֻ��� �� ����
	getchar();
	i = rand() % 6 + 1;
	j = rand() % 6 + 1;

	gotoxy(50, 14); //�ֻ��� ���
	printf("������    ������\n");
	gotoxy(50, 15);
	printf("��%2d��    ��%2d��\n", i, j);
	gotoxy(50, 16);
	printf("������    ������\n");

	sum = i + j;//�ֻ����� ��
	if (i == j) //�ѹ� ������ ��
	{
		gotoxy(52, 17);
		printf("����");
		gotoxy(55, 20);
		printf("�� : %d", sum); //�� ���
		getchar();
		gotoxy(52, 17);
		printf("     ");
		gotoxy(55, 20);
		printf("            ");
		Move(sum, t, user, NUM, c, x, y); //�� �̵� �Լ��� �̵�


		Color(15); //�ѹ��� �ֻ��� ���
		i = rand() % 6 + 1;
		j = rand() % 6 + 1;
		getchar();
		gotoxy(50, 14);
		printf("������    ������\n");
		gotoxy(50, 15);
		printf("��%2d��    ��%2d��\n", i, j);
		gotoxy(50, 16);
		printf("������    ������\n");

		sum = i + j;//�ֻ����� ��

		if (i == j) //2�� ������ �� ���Ű� �ð��� ������ ��
		{
			gotoxy(52, 17);
			printf("����");
			getchar();
			gotoxy(52, 17);
			printf("     ");
			gotoxy(45, 20);
			printf("���Ű� �ð��� ������ ������");
			if (t == 0) //���� �ִ� �� ����
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
			Desert_island(t, user, NUM, x, y); //���ε� �Լ��� �̵�

			Color(0);
			gotoxy(45, 20);
			printf("���Ű� �ð��� ������ ������");

			Color(15);
		}
		else
		{
			gotoxy(52, 17);
			printf("     ");
			gotoxy(55, 20);
			printf("�� : %d", sum); //�� ���
			Move(sum, t, user, NUM, c, x, y); //�� �̵� �Լ��� �̵�
			getchar();
			Color(0);
			gotoxy(55, 20);
			printf("�� : %d", sum);

			Color(15);
		}
	}
	else
	{
		gotoxy(55, 20);
		printf("�� : %d", sum); //�� ���
		Move(sum, t, user, NUM, c, x, y); //�� �̵� �Լ��� �̵�
		getchar();
		Color(0);
		gotoxy(55, 20);
		printf("�� : %d", sum);

		Color(15);
	}
}

void Desert_island(int t, char user[][5], int NUM, int x[], int y[]) //���Ű� �ð��� ��
{
	getchar();
	Color(0); //�ֻ��� ��� ���� 
	gotoxy(50, 14);
	printf("������    ������\n");
	gotoxy(50, 15);
	printf("��%2d��    ��%2d��\n");
	gotoxy(50, 16);
	printf("������    ������\n");
	Color(15);
	x[t] = 8, y[t] = 4;//���Ű� �ð��� ������ ����
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
	build(t, x, y, user, NUM); //��ǥ���� �ǹ� �Ǽ� �Լ��� �̵�
}

void build(int t, int x[], int y[], char user[][5], int NUM) //��ǥ���� �ǹ� �Ǽ�
{
	int Q, J;//Q�� yes or no, J�� ���� �Ǵ�
	if (x[t] == 8 && y[t] == 4) //���Ű� �ð��� ���� ��
	{
		int i;
		gotoxy(40, 24);
		printf("%d��° ���� ������ �ð��� �濡 �����߽��ϴ�.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                                  ");
		gotoxy(40, 24);
		printf("����� ���� 5~10�ۼ�Ʈ�� �ҽ��ϴ�.(�ڿ���)             ");//5,6,7,8,9,10%�߿� �������� ���� ���δ�
		srand(time(NULL));
		i = rand() % 6 + 5;
		Money(t, i, 2, user, NUM, 0); //�� ���� �Լ��� �̵�
		gotoxy(40, 24);
		printf("                                                   ");
		getchar();
		if (x[t] == 8)
		{
			getchar();
			gotoxy(40, 24);
			printf("���� �ѱ�ϴ�.");
			getchar();
			gotoxy(40, 24);
			printf("                ");
		}
		/*
		static int count[4]={0,0,0,0};
		if(count[t]==0)
		{
		gotoxy(40,24);
		printf("2�� ����");
		getchar();
		gotoxy(40,24);
		printf("���� �ѱ�ϴ�.");
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
		printf("1�� ����");
		getchar();
		gotoxy(40,24);
		printf("���� �ѱ�ϴ�.");
		getchar();
		gotoxy(40,24);
		printf("                ");
		count[t]++;
		}
		else if(count[t]==2)
		{
		gotoxy(40,24);
		printf("Ż��!");
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
		printf("Ż��!");
		getchar();
		gotoxy(36,24);
		printf("      ");
		getchar();
		count[t]=0;
		Random_Dice(t,user,NUM,-3);
		gotoxy(36,24);
		printf("�ֻ��� ����");
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
	printf("%d�� ����",count_t[t]+2);
	getchar();
	gotoxy(36,24);
	printf("���� �ѱ�ϴ�.");
	getchar();
	gotoxy(36,24);
	printf("                 ");
	count_t[t]=-1;
	}
	else if(count_t[t]==-1)
	{
	gotoxy(36,24);
	printf("%d�� ����",count_t[t]+2);
	getchar();
	gotoxy(36,24);
	printf("���� �ѱ�ϴ�.");
	getchar();
	gotoxy(36,24);
	printf("                 ");
	count_t[t]=-2;
	}
	else if(count_t[t]==-2)
	{
	gotoxy(36,24);
	printf("Ż��!");
	getchar();
	gotoxy(36,24);
	printf("        ");
	getchar();
	count_t[t]=0;
	Random_Dice(t,user,NUM,-2);
	gotoxy(36,24);
	printf("�ֻ��� ����");
	}
	}
	*/
	else if (x[t] == 8 && y[t] == 25 || x[t] == 50 && y[t] == 4 || x[t] == 106 && y[t] == 18 || x[t] == 106 && y[t] == 46 || x[t] == 78 && y[t] == 53 || x[t] == 36 && y[t] == 53) //������ �� ��
	{
		gotoxy(40, 24);
		printf("%d��° ���� �����߽��ϴ�.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                    ");
		if (map_count((t + 1) % NUM, x[t], y[t], -1)>0 || map_count((t + 2) % NUM, x[t], y[t], -1)>0 || map_count((t + 3) % NUM, x[t], y[t], -1)>0) //������ ���� ��
		{
			gotoxy(40, 26);
			printf("�ٸ� ����� �������Դϴ�. ����Ḧ �����մϴ�.");
			getchar();
			gotoxy(40, 26);
			printf("                                                 ");
			J = Money(t, map_money(t, x, y, 4, 2), 1, user, NUM, 0); //�� ���� �Լ��� �̵�
			if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1)
				Money((t + 1) % NUM, map_money(t, x, y, 4, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
			else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 1)
				Money((t + 2) % NUM, map_money(t, x, y, 4, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
			else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
				Money((t + 3) % NUM, map_money(t, x, y, 4, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�

			if (J == 1) //�Ļ�
			{
				gotoxy(40, 26);
				printf("�Ļ�!");
				Money(t, 0, -1, user, NUM, 1); //���� 0����
				exit(0);
			}
			else
			{
				gotoxy(40, 24);
				printf("���� �ѱ�ϴ�.");
				getchar();
				gotoxy(40, 24);
				printf("                 ");
			}
		}
		else if (map_count(t, x[t], y[t], -1) == 1) //�ڽ��� �������� ��
		{
			gotoxy(40, 26);
			printf("�ڽ��� �������̹Ƿ� ���� �ѱ�ϴ�.");
			getchar();
			gotoxy(40, 26);
			printf("                                            ");
		}
		else //������ ���� ��
		{
			gotoxy(40, 26);
			{
				printf("�������� ��ðڽ��ϱ�?(No�� 0, Yes�� 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                                 ");
				getchar();
				J = Money(t, map_money(t, x, y, 4, 1), 1, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1) //���� ���� ��
				{
					gotoxy(40, 24);
					printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
					getchar();
					gotoxy(40, 24);
					printf("                                 ");
				}
				else
				{
					gotoxy(40, 24);
					printf("�������� ��ϴ�.");
					build_print(t, x[t], y[t] + 3, 1); //�ǹ� ���
					getchar();
					gotoxy(40, 24);
					printf("                     ");
					map_count((t) % NUM, x[t], y[t], 1); //��ǥ���� ���� ���� �������� �˷��ִ� �Լ��� �̵�
					gotoxy(40, 24);
					printf("���� �ѱ�ϴ�.");
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
				printf("���� �ѱ�ϴ�.");
				getchar();
				gotoxy(40, 24);
				printf("                 ");
			}
		}

	}
	else if (x[t] == 8 && y[t] <= 46 && y[t] >= 11 && y[t] != 25 || x[t] >= 22 && x[t] <= 92 && x[t] != 50 && y[t] == 4 || x[t] == 106 && y[t] >= 11 && y[t] <= 39 && y[t] != 18 || x[t] <= 92 && x[t] >= 22 && x[t] != 78 && x[t] != 36) //���� �� �� �������� ��
	{
		gotoxy(40, 24);
		printf("%d��° ���� �����߽��ϴ�.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                    ");
		if (map_count((t + 1) % NUM, x[t], y[t], -1)>0 || map_count((t + 2) % NUM, x[t], y[t], -1)>0 || map_count((t + 3) % NUM, x[t], y[t], -1)>0) //�ٸ� ����� ���� ��
		{
			if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1 || map_count((t + 2) % NUM, x[t], y[t], -1) == 1 || map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
			{
				gotoxy(40, 26);
				printf("�ٸ� ����� ���Դϴ�. ����Ḧ �����մϴ�.");
				getchar();
				gotoxy(40, 26);
				printf("                                              ");
				J = Money(t, map_money(t, x, y, 1, 2), 1, user, NUM, 0);  //�� ���� �Լ��� �̵�

				if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1)
					Money((t + 1) % NUM, map_money(t, x, y, 1, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 1)
					Money((t + 2) % NUM, map_money(t, x, y, 1, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
					Money((t + 3) % NUM, map_money(t, x, y, 1, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1) //�Ļ�
				{
					gotoxy(40, 26);
					printf("�Ļ�!");
					Money(t, 0, -1, user, NUM, 1); //�� ���� �Լ��� �̵�
					exit(0);
				}
				else
				{
					gotoxy(40, 26);
					{
						printf("���� �μ��Ͻðڽ��ϱ�?(No�� 0, Yes�� 1) : ");
						scanf_s("%d", &Q);
					}
					if (Q == 1)
					{
						gotoxy(40, 26);
						printf("                                                   ");
						J = Money(t, map_money(t, x, y, 1, 3), 1, user, NUM, 0); //�� ���� �Լ��� �̵�
						if (J == 1)
						{
							gotoxy(40, 24);
							printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
							getchar();
							gotoxy(40, 24);
							printf("                                  ");
						}
						else
						{
							if (map_count((t + 1) % NUM, x[t], y[t], -1) == 1)
								Money((t + 1) % NUM, map_money(t, x, y, 1, 3), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
							else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 1)
								Money((t + 2) % NUM, map_money(t, x, y, 1, 3), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
							else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 1)
								Money((t + 3) % NUM, map_money(t, x, y, 1, 3), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
							gotoxy(40, 26);
							printf("�μ����� �����߽��ϴ�.");
							getchar();
							gotoxy(40, 26);
							printf("                          ");
							build_print(t, x[t] - 3, y[t] + 3, 0);
							map_count((t + 1) % NUM, x[t], y[t], 0);
							map_count((t + 2) % NUM, x[t], y[t], 0);
							map_count((t + 3) % NUM, x[t], y[t], 0);
							map_count((t) % NUM, x[t], y[t], 1);
							gotoxy(40, 26);
							printf("�μ��� �Ϸ��߽��ϴ�.");
							getchar();
							gotoxy(40, 26);
							printf("                        ");
							gotoxy(40, 27);
							{
								printf("�ǹ��� ���ڽ��ϱ�?(No�� 0, Yes�� 1) : ");
								scanf_s("%d", &Q);
							}
							getchar();
							gotoxy(40, 27);
							printf("                                              ");
							if (Q == 1)
							{
								J = Money(t, map_money(t, x, y, 2, 1), 1, user, NUM, 0); //�� ���� �Լ��� �̵�
								if (J == 1)
								{
									gotoxy(40, 24);
									printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
									getchar();
									gotoxy(40, 24);
									printf("                                  ");
								}
								else
								{
									build_print(t, x[t] - 3, y[t] + 3, 0);
									build_print(t, x[t], y[t] + 3, 0);
									gotoxy(40, 24);
									printf("�ǹ��� �������ϴ�.");
									getchar();
									gotoxy(40, 24);
									printf("                      ");
									map_count((t + 1) % NUM, x[t], y[t], 0);
									map_count((t + 2) % NUM, x[t], y[t], 0);
									map_count((t + 3) % NUM, x[t], y[t], 0);
									map_count((t) % NUM, x[t], y[t], 2);
									gotoxy(40, 24);
									printf("���� �ѱ�ϴ�.");
									getchar();
									gotoxy(40, 24);
									printf("                 ");
								}

							}
							else if (Q == 0)
							{
								gotoxy(40, 24);
								printf("���� �ѱ�ϴ�.");
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
						printf("���� �ѱ�ϴ�.");
						getchar();
						gotoxy(40, 24);
						printf("                 ");
					}
				}
			}
			else if (map_count((t + 1) % NUM, x[t], y[t], -1) == 2 || map_count((t + 2) % NUM, x[t], y[t], -1) == 2 || map_count((t + 3) % NUM, x[t], y[t], -1) == 2)
			{
				gotoxy(40, 26);
				printf("�ٸ� ����� �ǹ��Դϴ�. ����Ḧ �����մϴ�.");
				if (map_count((t + 1) % NUM, x[t], y[t], -1) == 2)
					Money((t + 1) % NUM, map_money(t, x, y, 2, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 2)
					Money((t + 2) % NUM, map_money(t, x, y, 2, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 2)
					Money((t + 3) % NUM, map_money(t, x, y, 2, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				gotoxy(40, 26);
				printf("                                               ");
				J = Money(t, map_money(t, x, y, 2, 2), 1, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1) //�Ļ�
				{
					gotoxy(40, 26);
					printf("�Ļ�!");
					Money(t, 0, -1, user, NUM, 1); //�� ���� �Լ��� �̵�
					exit(0);
				}

				gotoxy(40, 26);
				{
					printf("���� �ǹ��� �μ��Ͻðڽ��ϱ�?(No�� 0, Yes�� 1) : ");
					scanf_s("%d", &Q);
				}
				if (Q == 1)
				{
					gotoxy(40, 26);
					printf("                                                     ");
					J = Money(t, map_money(t, x, y, 2, 3), 1, user, NUM, 0); //�� ���� �Լ��� �̵�
					if (J == 1)
					{
						gotoxy(40, 24);
						printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
						getchar();
						gotoxy(40, 24);
						printf("                                 ");
					}
					else
					{
						if (map_count((t + 1) % NUM, x[t], y[t], -1) == 2)
							Money((t + 1) % NUM, map_money(t, x, y, 2, 3), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
						else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 2)
							Money((t + 2) % NUM, map_money(t, x, y, 2, 3), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
						else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 2)
							Money((t + 3) % NUM, map_money(t, x, y, 2, 3), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
						gotoxy(40, 26);
						printf("�μ����� �����߽��ϴ�.");
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
						printf("�μ��� �Ϸ��߽��ϴ�.");
						getchar();
						gotoxy(40, 26);
						printf("                       ");
						gotoxy(40, 27);
						{
							printf("���帶ũ�� ���ڽ��ϱ�?(No�� 0, Yes�� 1) : ");
							scanf_s("%d", &Q);
						}
						getchar();
						gotoxy(40, 27);
						printf("                                                 ");
						if (Q == 1)
						{
							J = Money(t, map_money(t, x, y, 3, 1), 1, user, NUM, 0); //�� ���� �Լ��� �̵�
							if (J == 1)
							{
								gotoxy(40, 24);
								printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
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
								printf("���帶ũ�� �������ϴ�.");
								getchar();
								gotoxy(40, 24);
								printf("                          ");
								map_count((t + 1) % NUM, x[t], y[t], 0);
								map_count((t + 2) % NUM, x[t], y[t], 0);
								map_count((t + 3) % NUM, x[t], y[t], 0);
								map_count((t) % NUM, x[t], y[t], 3);
								gotoxy(40, 24);
								printf("���� �ѱ�ϴ�.");
								getchar();
								gotoxy(40, 24);
								printf("                 ");
							}

						}
						else if (Q == 0)
						{
							gotoxy(40, 24);
							printf("���� �ѱ�ϴ�.");
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
					printf("���� �ѱ�ϴ�.");
					getchar();
					gotoxy(40, 24);
					printf("                 ");
				}
			}
			else if (map_count((t + 1) % NUM, x[t], y[t], -1) == 3 || map_count((t + 2) % NUM, x[t], y[t], -1) == 3 || map_count((t + 3) % NUM, x[t], y[t], -1) == 3)
			{
				gotoxy(40, 26);
				printf("�ٸ� ����� ���帶ũ�Դϴ�. ����Ḧ �����մϴ�.");
				if (map_count((t + 1) % NUM, x[t], y[t], -1) == 3)
					Money((t + 1) % NUM, map_money(t, x, y, 3, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				else if (map_count((t + 2) % NUM, x[t], y[t], -1) == 3)
					Money((t + 2) % NUM, map_money(t, x, y, 3, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				else if (map_count((t + 3) % NUM, x[t], y[t], -1) == 3)
					Money((t + 3) % NUM, map_money(t, x, y, 3, 2), 0, user, NUM, 0); //�� ���� �Լ��� �̵�
				gotoxy(40, 26);
				printf("                                                    ");
				J = Money(t, map_money(t, x, y, 3, 2), 1, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1) //�Ļ�
				{
					gotoxy(40, 26);
					printf("�Ļ�!");
					Money(t, 0, -1, user, NUM, 1); //�� ���� �Լ��� �̵�
					exit(0);
				}
				gotoxy(40, 28);
				printf("���帶ũ�̹Ƿ� �μ��� �� �� �����ϴ�.");
				getchar();

				gotoxy(40, 28);
				printf("                                      ");
				gotoxy(40, 24);
				printf("���� �ѱ�ϴ�.");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count(t, x[t], y[t], -1) == 0) //���� ������� �� (���Ǽ�)
		{
			gotoxy(40, 26);
			{
				printf("���� ��ðڽ��ϱ�?(No�� 0, Yes�� 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                              ");
				getchar();
				J = Money(t, map_money(t, x, y, 1, 1), 1, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1)
				{
					gotoxy(40, 24);
					printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
					getchar();
					gotoxy(40, 24);
					printf("                                ");
				}
				else
				{
					gotoxy(40, 24);
					printf("���� ��ϴ�.");
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
				printf("���� �ѱ�ϴ�.");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count((t) % NUM, x[t], y[t], -1) == 1) //�� ���� �� (�ǹ��Ǽ�)
		{
			gotoxy(40, 26);
			{
				printf("�ǹ��� ��ðڽ��ϱ�?(No�� 0, Yes�� 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                              ");
				getchar();
				J = Money(t, map_money(t, x, y, 2, 1), 1, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1)
				{
					gotoxy(40, 24);
					printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
					getchar();
					gotoxy(40, 24);
					printf("                               ");
				}
				else
				{
					gotoxy(40, 24);
					printf("�ǹ��� ��ϴ�.");
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
				printf("���� �ѱ�ϴ�.");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count(t, x[t], y[t], -1) == 2) //�� �ǹ��� �� (���帶ũ�Ǽ�)
		{
			gotoxy(40, 26);
			{
				printf("���帶ũ�� ��ðڽ��ϱ�?(No�� 0, Yes�� 1) : ");
				scanf_s("%d", &Q);
			}
			if (Q == 1)
			{
				gotoxy(40, 26);
				printf("                                              ");
				getchar();
				J = Money(t, map_money(t, x, y, 3, 1), 1, user, NUM, 0); //�� ���� �Լ��� �̵�

				if (J == 1)
				{
					gotoxy(40, 24);
					printf("���� �����ϹǷ� ���� �ѱ�ϴ�.");
					getchar();
					gotoxy(40, 24);
					printf("                                ");
				}
				else
				{
					gotoxy(40, 24);
					printf("���帶ũ�� ��ϴ�.");
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
				printf("���� �ѱ�ϴ�");
				getchar();
				gotoxy(40, 24);
				printf("               ");
			}
		}
		else if (map_count((t) % NUM, x[t], y[t], -1) == 3) //�� ���帶ũ�� ��
		{
			gotoxy(40, 26);
			printf("���̻� ���� �� �����ϴ�. ���� �ѱ�ϴ�.");
			getchar();
			gotoxy(40, 26);
			printf("                                        ");
		}
	}
	else if (x[t] == 8 && y[t] == 53) //�����
	{
		gotoxy(40, 24);
		printf("%d��° ���� ������� �����߽��ϴ�.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                           ");
		Money(t, 1000000, 0, user, NUM, 0); //�� ���� �Լ��� �̵�
		gotoxy(40, 24);
		printf("������ ���޵Ǿ����ϴ�.");
		getchar();
		gotoxy(40, 24);
		printf("                        ");
		gotoxy(40, 24);
		printf("���� �ѱ�ϴ�.");
		getchar();
		gotoxy(40, 24);
		printf("                ");
	}
	else if (x[t] == 106 && y[t] == 53 || x[t] == 106 && y[t] == 4) //����
	{
		gotoxy(40, 24);
		printf("%d��° ���� ���Ϳ� �����߽��ϴ�.\n", t + 1);
		getchar();
		gotoxy(40, 24);
		printf("                                          ");
		gotoxy(40, 24);
		printf("���� �ѱ�ϴ�.");
		getchar();
		gotoxy(40, 24);
		printf("                ");
	}
}

int Money(int t, int price, int PM, char user[][5], int NUM, int b)//PM�� 1�̸� ���� 0�̸� ����, �� ����
{
	static int Money[4] = { 10000000,10000000,10000000,10000000 };
	State(t, user, NUM, Money);
	getchar();
	if (PM == 0) //+��
	{
		gotoxy(40, 26);
		printf("+%d��                                          ", price);
		Money[t] = Money[t] + price;
		State(t, user, NUM, Money);
		getchar();
		gotoxy(40, 26);
		printf("                                                      ");
		return 0;
	}
	else if (PM == 1) //-��
	{
		gotoxy(40, 26);
		printf("-%d��                                    ", price);
		if (Money[t] - price<0) //���� ���� ��
		{
			State(t, user, NUM, Money);
			getchar();
			gotoxy(40, 26);
			printf("                                                 ");
			return 1;
		}
		else //���� ���� ��
		{
			Money[t] -= price;
			State(t, user, NUM, Money);
			getchar();
			gotoxy(40, 26);
			printf("          ");
			return 0;
		}
	}
	else if (PM == 2) //���Ű� �ð��� ���� ��
	{
		price = Money[t] * price / 100;
		gotoxy(40, 26);
		printf("-%d��", price);
		getchar();
		gotoxy(40, 26);
		printf("           ");
		Money[t] -= price;
		State(t, user, NUM, Money);
		return 0;
	}
	else if (b == 1) //�Ļ��� �� ������� �Լ�
	{
		int i, temp1, temp, a[4] = { 0,1,2,3 }, e = 0;
		Money[t] = 0;
		//Money[(t+1)%4]=10,Money[(t+2)%4]=10,Money[(t+3)%4]=10;
		gotoxy(40, 24);
		printf("������ ����մϴ�.");
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
		if (Money[0] == Money[1] && Money[0] == Money[2])//3���� ���� ��
			e = 4;
		else if (Money[1] == Money[2] && Money[1] == Money[3])//3���� ���� ��
			e = 5;
		else if (Money[0] == Money[1])//2���� ���� ��
			e = 1;
		else if (Money[1] == Money[2])//2���� ���� ��
			e = 2;
		else if (Money[2] == Money[3])//2���� ���� ��
			e = 3;
		printf("����\n");
		if (e>0) //���� ���
		{
			if (e == 1)
			{
				for (t = 0; t <= 3; t++)
				{
					if (t == 0 || t == 1)
					{
						T_Color(a[t]);
						printf("���� %d�� : %s %d��\n", 1, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 2 || t == 3)
					{
						T_Color(a[t]);
						printf("%d�� : %s %d��\n", t + 1, user[a[t]], Money[t]);
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
						printf("���� %d�� : %s %d��\n", 2, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 0 || t == 3)
					{
						T_Color(a[t]);
						printf("%d�� : %s %d��\n", t + 1, user[a[t]], Money[t]);
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
						printf("���� %d�� : %s %d��\n", 3, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 0 || t == 1)
					{
						T_Color(a[t]);
						printf("%d�� : %s %d��\n", t + 1, user[a[t]], Money[t]);
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
						printf("���� %d�� : %s %d��\n", 1, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 3)
					{
						T_Color(a[t]);
						printf("%d�� : %s %d��\n", t + 1, user[a[t]], Money[t]);
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
						printf("���� %d�� : %s %d��\n", 2, user[a[t]], Money[t]);
						Color(15);
					}
					else if (t == 0)
					{
						T_Color(a[t]);
						printf("%d�� : %s %d��\n", t + 1, user[a[t]], Money[t]);
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
				printf("%d�� : %s %d��\n", t + 1, user[a[t]], Money[t]);
				Color(15);
			}
		}
	}
}
void Icon(int a) //������� �� ������
{
	if (a == 0)
	{
		Color(3);
		printf("��");
		Color(15);
	}
	else if (a == 1)
	{
		Color(6);
		printf("��");
		Color(15);
	}
	else if (a == 2)
	{
		Color(4);
		printf("��");
		Color(15);
	}
	else if (a == 3)
	{
		Color(2);
		printf("��");
		Color(15);
	}
}
void remove_Icon(int a) //������ �����
{
	if (a == 0)
	{
		Color(0);
		printf("��");
		Color(15);
	}
	else if (a == 1)
	{
		Color(0);
		printf("��");
		Color(15);
	}
	else if (a == 2)
	{
		Color(0);
		printf("��");
		Color(15);
	}
	else if (a == 3)
	{
		Color(0);
		printf("��");
		Color(15);
	}
}
void build_print(int t, int x, int y, int M) //�ǹ� ���
{
	if (M == 0)
	{
		if (t == 0)
		{
			Color(3);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
		else if (t == 1)
		{
			Color(6);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
		else if (t == 2)
		{
			Color(4);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
		else if (t == 3)
		{
			Color(2);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
	}
	else if (M == 1)
	{
		if (t == 0)
		{
			Color(3);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
		else if (t == 1)
		{
			Color(6);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
		else if (t == 2)
		{
			Color(4);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
		else if (t == 3)
		{
			Color(2);
			gotoxy(x, y);
			printf("��");
			Color(15);
		}
	}
}

int map_count(int t, int x, int y, int a) //��ǥ���� ���� ���� �������� �˷���
{
	if (x == 8 && y == 46) //���
	{
		static int count_Ulsan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Ulsan[t] += 0;
		else
			count_Ulsan[t] = a;
		return count_Ulsan[t];
	}
	else if (x == 8 && y == 39) //�뱸
	{
		static int count_Daegu[4] = { 0,0,0,0 };
		if (a == -1)
			count_Daegu[t] += 0;
		else
			count_Daegu[t] = a;
		return count_Daegu[t];
	}
	else if (x == 8 && y == 32) //����
	{
		static int count_Sejong[4] = { 0,0,0,0 };
		if (a == -1)
			count_Sejong[t] += 0;
		else
			count_Sejong[t] = a;
		return count_Sejong[t];
	}
	else if (x == 8 && y == 18) //��õ
	{
		static int count_Incheon[4] = { 0,0,0,0 };
		if (a == -1)
			count_Incheon[t] += 0;
		else
			count_Incheon[t] = a;
		return count_Incheon[t];
	}
	else if (x == 8 && y == 11) //����
	{
		static int count_Gangneung[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gangneung[t] += 0;
		else
			count_Gangneung[t] = a;
		return count_Gangneung[t];
	}
	else if (x == 22 && y == 4) //����
	{
		static int count_Daejeon[4] = { 0,0,0,0 };
		if (a == -1)
			count_Daejeon[t] += 0;
		else
			count_Daejeon[t] = a;
		return count_Daejeon[t];
	}
	else if (x == 36 && y == 4) //����
	{
		static int count_Gwangju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gwangju[t] += 0;
		else
			count_Gwangju[t] = a;
		return count_Gwangju[t];
	}
	else if (x == 64 && y == 4) //�λ�
	{
		static int count_Busan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Busan[t] += 0;
		else
			count_Busan[t] = a;
		return count_Busan[t];
	}
	else if (x == 78 && y == 4) //��õ
	{
		static int count_Chuncheon[4] = { 0,0,0,0 };
		if (a == -1)
			count_Chuncheon[t] += 0;
		else
			count_Chuncheon[t] = a;
		return count_Chuncheon[t];
	}
	else if (x == 92 && y == 4) //����
	{
		static int count_Pohang[4] = { 0,0,0,0 };
		if (a == -1)
			count_Pohang[t] += 0;
		else
			count_Pohang[t] = a;
		return count_Pohang[t];
	}
	else if (x == 106 && y == 11) //����
	{
		static int count_Mokpo[4] = { 0,0,0,0 };
		if (a == -1)
			count_Mokpo[t] += 0;
		else
			count_Mokpo[t] = a;
		return count_Mokpo[t];
	}
	else if (x == 106 && y == 25) //����
	{
		static int count_Jinju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Jinju[t] += 0;
		else
			count_Jinju[t] = a;
		return count_Jinju[t];
	}
	else if (x == 106 && y == 32) //����
	{
		static int count_Gwangju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gwangju[t] += 0;
		else
			count_Gwangju[t] = a;
		return count_Gwangju[t];
	}
	else if (x == 106 && y == 39) //����
	{
		static int count_Wonju[4] = { 0,0,0,0 };
		if (a == -1)
			count_Wonju[t] += 0;
		else
			count_Wonju[t] = a;
		return count_Wonju[t];
	}
	else if (x == 92 && y == 53) //�뿵
	{
		static int count_Tongyeong[4] = { 0,0,0,0 };
		if (a == -1)
			count_Tongyeong[t] += 0;
		else
			count_Tongyeong[t] = a;
		return count_Tongyeong[t];
	}
	else if (x == 64 && y == 53) //����
	{
		static int count_Yeosu[4] = { 0,0,0,0 };
		if (a == -1)
			count_Yeosu[t] += 0;
		else
			count_Yeosu[t] = a;
		return count_Yeosu[t];
	}
	else if (x == 50 && y == 53) //����
	{
		static int count_Dokdo[4] = { 0,0,0,0 };
		if (a == -1)
			count_Dokdo[t] += 0;
		else
			count_Dokdo[t] = a;
		return count_Dokdo[t];
	}
	else if (x == 22 && y == 53) //����
	{
		static int count_Seoul[4] = { 0,0,0,0 };
		if (a == -1)
			count_Seoul[t] += 0;
		else
			count_Seoul[t] = a;
		return count_Seoul[t];
	}
	else if (x == 8 && y == 25) //������
	{
		static int count_Jirisan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Jirisan[t] += 0;
		else
			count_Jirisan[t] = a;
		return count_Jirisan[t];
	}
	else if (x == 50 && y == 4) //���ǻ�
	{
		static int count_Seoraksan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Seoraksan[t] += 0;
		else
			count_Seoraksan[t] = a;
		return count_Seoraksan[t];
	}
	else if (x == 106 && y == 18) //�Ѷ��
	{
		static int count_Hallasan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Hallasan[t] += 0;
		else
			count_Hallasan[t] = a;
		return count_Hallasan[t];
	}
	else if (x == 106 && y == 46) //ġ�ǻ�
	{
		static int count_Chiaksan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Chiaksan[t] += 0;
		else
			count_Chiaksan[t] = a;
		return count_Chiaksan[t];
	}
	else if (x == 78 && y == 53) //���ǻ�
	{
		static int count_Gwanaksan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Gwanaksan[t] += 0;
		else
			count_Gwanaksan[t] = a;
		return count_Gwanaksan[t];
	}
	else if (x == 36 && y == 53) //������
	{
		static int count_Dobongsan[4] = { 0,0,0,0 };
		if (a == -1)
			count_Dobongsan[t] += 0;
		else
			count_Dobongsan[t] = a;
		return count_Dobongsan[t];
	}
}

int map_money(int t, int x[], int y[], int i, int j) //������ ��ȯ���ִ� �Լ�
{
	if (x[t] == 8 && y[t] <= 46 && y[t] >= 11)
	{
		int G = 100000, B = 200000, L = 400000, M = 800000;//��(G),�ǹ�(B),���帶ũ(L),������(M)
		if (j == 1) //����
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
		else if (j == 2) //�����
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
		else if (j == 3) //�μ�
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
		int G = 200000, B = 400000, L = 800000, M = 800000;//��(G),�ǹ�(B),���帶ũ(L)
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
		int G = 400000, B = 800000, L = 1600000, M = 800000;//��(G),�ǹ�(B),���帶ũ(L)
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
		int G = 800000, B = 1600000, L = 3200000, M = 800000;//��(G),�ǹ�(B),���帶ũ(L)
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

void T_Color(int t) //������� ��
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

void line_cover() //�� ���ʿ� �߸� �κ��� Ŀ������
{
	gotoxy(1, 18);
	{
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
		printf("��\n");
	}
}