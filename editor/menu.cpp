#include<Windows.h>
#include<stdlib.h>
#include"menu.h"
#include<graphics.h>
#include<string.h>
#include"file.h"
FILE *fp;
/*
���˵�����
*/


void menu() {
	cleardevice();
	xyprintf(0,00,"��ӭʹ��666���壬��ѡ����Ҫʹ�õĹ��ܣ�");
	xyprintf(0,20,"1����ջ���");
	xyprintf(0,40,"2����ʼ��ͼ");
	xyprintf(0,60,"3����֮ǰ�ĸո���ɵ�ͼ��");
	xyprintf(0, 80, "4�����ļ�");
	xyprintf(0,100,"5���˳�����");
	int func = 0;                                                                                           //ѡ����һ�����ܣ����ñ���func
	func = getch();
	switch (func)
	{
	case '1': {
		xyprintf(0,120,"������ս���");
		Sleep(3000);
		cleardevice();
		xyprintf(0,140,"�ѳɹ���ջ���(������)~*");
		menu();
		break;
	}
	case '2': {
		xyprintf(0,120,"�뿪ʼ��ı���");
		Sleep(1000);
		startdraw();                       //Ϊ�Ժ�򿪻�����������
		break;
	}
	case '3': {
		xyprintf(0, 140, "��û�л�ͼ�أ��Ȼ�ͼ�ɣ�");
		getch();
		menu();
		break;
	}
	
	case '4': {
		Save anew;
		anew = openfile();
		if (anew.radius != 0) {
			yuanf(anew);
		}
		else {
			duobianx(anew);
		}
		cleardevice();
		break;
	}
		
	case '5': {
		xyprintf(0, 120, "�����˳������ټ���");
		Sleep(3000);
		exit(0);                                                      //�˳�����
		break;
	}
	default:
		xyprintf(0, 150, "����ȷ����1~5,�����������.");
		getch();
		cleardevice();
		menu();
	}
}

/*
���ƶ����
*/


void duobianx()
{
	cleardevice();
	char duobianxin[100];
	inputbox_getline("��ʼ�������β���", "��������ɫ��R,G,B)(R��ɫ��G��ɫ��B��ɫ),�������������(֮���ö��Ÿ��������磺3��r��100,100,200,200,100,200)", duobianxin, 100);
	char *side, *color;//side�������color����ɫ
	side = strtok(duobianxin, ",");//����һ������ǰ�����ݴ浽side
	color = strtok(NULL, ",");//���ڶ�������ǰ���ݴ浽color
	if (side == NULL) {
		xyprintf(0, 0, "����ȷ���룡�������������");
		getch();
		cleardevice();
		duobianx();
	}
	int num = atoi(side);//��side����װ�������ִ���num
	int* where;      //����int���͵Ĵ�������ָ��
	char *where2;
	where = (int*)malloc(sizeof(int)*(num * 2));//���ö�̬�ַ�����С����������
	int a = 0;
	while (a < num * 2) {
		where2 = strtok(NULL, ",");
		if (where2 == NULL) {
			xyprintf(0, 0, "�������������Ӧ�Ķ����������,�����������");
			getch();
			free(where);
			duobianx();
		}                                 //����Ƿ����������ڱ�����ӦӦ�е�������
		*(where + a) = atoi(where2);
		a++;
	}
	if (color == NULL) {
		cleardevice();
		xyprintf(0, 0, "����ȷ����");
		duobianx();
	}
	if (*color == 'g' || *color == 'G')
		setcolor(GREEN);
	else if (*color == 'r' || *color == 'R')
	{
		setcolor(RED);
	}
	else if (*color == 'Y' || *color == 'y')
	{
		setcolor(YELLOW);
	}
	else {
		xyprintf(0, 20, "����ȷ������ɫ���Ƿ�Ҫ�������룿Y/N");
		char newcolor;
		newcolor = getch();
		if (newcolor == 'y' || newcolor == 'Y')
			duobianx();
		else
			setcolor(GREEN);                       //����Ĭ����ɫ
	}//������ɫ
	fillpoly(num, where);
	getch();
	xyprintf(0, 30, "�ص��˵�or������ͼ��������������ѡ��");
	xyprintf(0, 50, "1,�����ļ�?");
	xyprintf(0, 70, "2.������ͼ��");
	xyprintf(0, 90, "3.�ص��˵���");
	char togo;
	togo = getch();
	Save apicture;
	apicture.color = *color;
	for (int i = 0;i < 100;i++) {
		apicture.coord[i]= *(where+i);
	}//��ָ���е����ݱ������������Դ���
	
	apicture.side = num;
	switch (togo) {
	case '1': {
		savefile(apicture);

	}
	case '2': {
		cleardevice();
		duobianx();
		break;
	}
	case '3': {
		menu(apicture);
	}
	default: {
		xyprintf(0, 90, "����ȷ����");
	}


	}
}      

/*
�������غ������ڴ򿪱����ļ��еĶ����
*/

void duobianx(Save anew) {
	cleardevice();
	char color;
	int *where;
	color = anew.color;
	where = anew.coord;
	/*if (color == 'g' || color == 'G')
		setcolor(GREEN);
	else if (color == 'r' || color == 'R')
	{
		setcolor(RED);
	}
	else if (color == 'Y' || color == 'y')
	{
		setcolor(YELLOW);
	}*/
	fillpoly(anew.side, where);
	getch();
	menu(anew);
}

void yuanf() {
	cleardevice();
	char yuan[100];
	COORD pos;
	char *temp;
	int radius;
	inputbox_getline("��ʼ����Բ�Ĳ���","��ʼ����Բ�ĺ�����X��������Y���뾶R��֮���ö��Ÿ�����", yuan, 100);
	temp = strtok(yuan, ",");
	if (temp) {
		pos.X = atoi(temp);
	}
	else {
		xyprintf(0, 0, "����ȷ���룬�����������");
		getch();
		yuanf();
	}
	temp = strtok(NULL, ",");
	if (temp) {
		pos.Y = atoi(temp);
	}
	else {
		xyprintf(0, 0, "����ȷ���룬�����������");
		getch();
		yuanf();
	}
	temp = strtok(NULL, ",");
	if (temp) {
		radius = atoi(temp);
	}
	else {
		xyprintf(0, 0, "����ȷ���룬�����������");
		getch();
		yuanf();
	}
	circle(pos.X,pos.Y,radius);
	getch();
	getch();
	xyprintf(0, 30, "�ص��˵�or������ͼ��������������ѡ��");
	xyprintf(0, 50, "1,�����ļ�?");
	xyprintf(0, 70, "2.������ͼ��");
	xyprintf(0, 90, "3.�ص��˵���");
	char togo;
	togo = getch();
	Save apicture;
	apicture.pos.X = pos.X;
	apicture.pos.Y = pos.Y;
	apicture.radius = radius;

	switch (togo) {
	case '1': {
		savefile(apicture);

	}
	case '2': {
		cleardevice();
		yuanf();
		break;
	}
	case '3': {
		cleardevice();
		menu(apicture);
		break;
	}
	default: {
		xyprintf(0, 90, "����ȷ����");
	}


	}
}

void startdraw() {
	cleardevice();
	char a;
	xyprintf(0, 0, "��ѡ����Ҫ����ͼ��");
	xyprintf(0, 20, "1��Բ");
	xyprintf(0, 40, "2�������");
	a = getch();
	if (a == '1') {
		yuanf();
	}
	else if (a == '2') {
		duobianx();
	}
	else {
		xyprintf(0, 60, "����ȷ���룬�����������");
		getch();
		startdraw();
	}
}


/*
���ڴ�֮ǰ���ƺõ�ͼ��
*/
void menu(Save yet) {
	cleardevice();
	xyprintf(0, 00, "��ӭʹ��666���壬��ѡ����Ҫʹ�õĹ��ܣ�");
	xyprintf(0, 20, "1����ջ���");
	xyprintf(0, 40, "2����ʼ��ͼ");
	xyprintf(0, 60, "3����֮ǰ�ĸո���ɵ�ͼ��");
	xyprintf(0, 80, "4�����ļ�");
	xyprintf(0, 100, "5���˳�����");
	int func = 0;                                                                                           //ѡ����һ�����ܣ����ñ���func
	func = getch();
	switch (func)
	{
	case '1': {
		xyprintf(0, 120, "������ս���");
		Sleep(3000);
		cleardevice();
		xyprintf(0, 140, "�ѳɹ���ջ���(������)~*");
		menu();
		break;
	}
	case '2': {
		xyprintf(0, 120, "�뿪ʼ��ı���");
		Sleep(1000);
		startdraw();                       //Ϊ�Ժ�򿪻�����������
		break;
	}
	case '3': {
		opyet(yet);
		xyprintf(0, 140, "��������������˵�");
		getch();
		menu(yet);
		break;
	}

	case '4': {
		cleardevice();
		openfile();
		break;
	}

	case '5': {
		xyprintf(0, 120, "�����˳������ټ���");
		Sleep(3000);
		exit(0);                                                                                      //�˳�����
		break;
	}
	default:
		xyprintf(0, 150, "����ȷ����1~5,�����������.");
		getch();
		cleardevice();
		menu();
	}
}

void yuanf(Save yet) {
	cleardevice();
	COORD pos;
	int radius;
	pos.X = yet.pos.X;
	pos.Y = yet.pos.Y;
	radius = yet.radius;

	circle(pos.X, pos.Y, radius);
	getch();
	getch();
	xyprintf(0, 30, "�ص��˵�or������ͼ��������������ѡ��");
	xyprintf(0, 50, "1,�����ļ�?");
	xyprintf(0, 70, "2.������ͼ��");
	xyprintf(0, 90, "3.�ص��˵���");
	char togo;
	Save apicture;
	apicture.pos.X = pos.X;
	apicture.pos.Y = pos.Y;
	apicture.radius = radius;

	togo = getch();
	switch (togo) {
	case '1': {
		
		savefile(apicture);
	}
	case '2': {
		cleardevice();
		yuanf();
		break;
	}
	case '3': {
		cleardevice();
		menu(apicture);
		break;
	}
	default: {
		xyprintf(0, 90, "����ȷ����");

	}


	}
}

void opyet(Save yet) {
	if (yet.radius == 0) {
		duobianx(yet);
		getch();
	}
	else {
		yuanf(yet);
	}
}