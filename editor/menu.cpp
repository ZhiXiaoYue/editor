#include<Windows.h>
#include<stdlib.h>
#include"menu.h"
#include<graphics.h>
#include<string.h>
#include"file.h"
FILE *fp;
/*
主菜单函数
*/


void menu() {
	cleardevice();
	xyprintf(0,00,"欢迎使用666画板，请选择你要使用的功能：");
	xyprintf(0,20,"1、清空画板");
	xyprintf(0,40,"2、开始画图");
	xyprintf(0,60,"3、打开之前的刚刚完成的图案");
	xyprintf(0, 80, "4、打开文件");
	xyprintf(0,100,"5、退出程序");
	int func = 0;                                                                                           //选用哪一个功能，设置变量func
	func = getch();
	switch (func)
	{
	case '1': {
		xyprintf(0,120,"正在清空界面");
		Sleep(3000);
		cleardevice();
		xyprintf(0,140,"已成功清空画板(￣▽￣)~*");
		menu();
		break;
	}
	case '2': {
		xyprintf(0,120,"请开始你的表演");
		Sleep(1000);
		startdraw();                       //为以后打开画板程序做入口
		break;
	}
	case '3': {
		xyprintf(0, 140, "还没有画图呢，先画图吧！");
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
		xyprintf(0, 120, "即将退出程序，再见！");
		Sleep(3000);
		exit(0);                                                      //退出程序
		break;
	}
	default:
		xyprintf(0, 150, "请正确输入1~5,按任意键继续.");
		getch();
		cleardevice();
		menu();
	}
}

/*
绘制多变形
*/


void duobianx()
{
	cleardevice();
	char duobianxin[100];
	inputbox_getline("开始输入多边形参数", "边数，颜色（R,G,B)(R红色，G绿色，B蓝色),各个顶点的坐标(之间用逗号隔开。例如：3，r，100,100,200,200,100,200)", duobianxin, 100);
	char *side, *color;//side存边数，color存颜色
	side = strtok(duobianxin, ",");//将第一个逗号前的内容存到side
	color = strtok(NULL, ",");//将第二个逗号前内容存到color
	if (side == NULL) {
		xyprintf(0, 0, "请正确输入！！按任意键继续");
		getch();
		cleardevice();
		duobianx();
	}
	int num = atoi(side);//将side内容装换成数字存入num
	int* where;      //设置int类型的存放坐标的指针
	char *where2;
	where = (int*)malloc(sizeof(int)*(num * 2));//设置动态字符串大小，储存坐标
	int a = 0;
	while (a < num * 2) {
		where2 = strtok(NULL, ",");
		if (where2 == NULL) {
			xyprintf(0, 0, "请输入与边数对应的顶点坐标个数,按任意键继续");
			getch();
			free(where);
			duobianx();
		}                                 //检测是否做标数少于边数对应应有的做标数
		*(where + a) = atoi(where2);
		a++;
	}
	if (color == NULL) {
		cleardevice();
		xyprintf(0, 0, "请正确输入");
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
		xyprintf(0, 20, "请正确输入颜色，是否要重新输入？Y/N");
		char newcolor;
		newcolor = getch();
		if (newcolor == 'y' || newcolor == 'Y')
			duobianx();
		else
			setcolor(GREEN);                       //设置默认颜色
	}//设置颜色
	fillpoly(num, where);
	getch();
	xyprintf(0, 30, "回到菜单or继续画图？（输入数字以选择）");
	xyprintf(0, 50, "1,保存文件?");
	xyprintf(0, 70, "2.继续画图？");
	xyprintf(0, 90, "3.回到菜单？");
	char togo;
	togo = getch();
	Save apicture;
	apicture.color = *color;
	for (int i = 0;i < 100;i++) {
		apicture.coord[i]= *(where+i);
	}//将指针中的数据保存在数组中以储存
	
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
		xyprintf(0, 90, "请正确输入");
	}


	}
}      

/*
设置重载函数用于打开保存文件中的多边形
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
	inputbox_getline("开始输入圆的参数","开始输入圆心横坐标X，纵坐标Y，半径R（之间用逗号隔开）", yuan, 100);
	temp = strtok(yuan, ",");
	if (temp) {
		pos.X = atoi(temp);
	}
	else {
		xyprintf(0, 0, "请正确输入，按任意键继续");
		getch();
		yuanf();
	}
	temp = strtok(NULL, ",");
	if (temp) {
		pos.Y = atoi(temp);
	}
	else {
		xyprintf(0, 0, "请正确输入，按任意键继续");
		getch();
		yuanf();
	}
	temp = strtok(NULL, ",");
	if (temp) {
		radius = atoi(temp);
	}
	else {
		xyprintf(0, 0, "请正确输入，按任意键继续");
		getch();
		yuanf();
	}
	circle(pos.X,pos.Y,radius);
	getch();
	getch();
	xyprintf(0, 30, "回到菜单or继续画图？（输入数字以选择）");
	xyprintf(0, 50, "1,保存文件?");
	xyprintf(0, 70, "2.继续画图？");
	xyprintf(0, 90, "3.回到菜单？");
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
		xyprintf(0, 90, "请正确输入");
	}


	}
}

void startdraw() {
	cleardevice();
	char a;
	xyprintf(0, 0, "请选择你要画的图形");
	xyprintf(0, 20, "1、圆");
	xyprintf(0, 40, "2、多边形");
	a = getch();
	if (a == '1') {
		yuanf();
	}
	else if (a == '2') {
		duobianx();
	}
	else {
		xyprintf(0, 60, "请正确输入，按任意键继续");
		getch();
		startdraw();
	}
}


/*
用于打开之前绘制好的图案
*/
void menu(Save yet) {
	cleardevice();
	xyprintf(0, 00, "欢迎使用666画板，请选择你要使用的功能：");
	xyprintf(0, 20, "1、清空画板");
	xyprintf(0, 40, "2、开始画图");
	xyprintf(0, 60, "3、打开之前的刚刚完成的图案");
	xyprintf(0, 80, "4、打开文件");
	xyprintf(0, 100, "5、退出程序");
	int func = 0;                                                                                           //选用哪一个功能，设置变量func
	func = getch();
	switch (func)
	{
	case '1': {
		xyprintf(0, 120, "正在清空界面");
		Sleep(3000);
		cleardevice();
		xyprintf(0, 140, "已成功清空画板(￣▽￣)~*");
		menu();
		break;
	}
	case '2': {
		xyprintf(0, 120, "请开始你的表演");
		Sleep(1000);
		startdraw();                       //为以后打开画板程序做入口
		break;
	}
	case '3': {
		opyet(yet);
		xyprintf(0, 140, "按任意键返回主菜单");
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
		xyprintf(0, 120, "即将退出程序，再见！");
		Sleep(3000);
		exit(0);                                                                                      //退出程序
		break;
	}
	default:
		xyprintf(0, 150, "请正确输入1~5,按任意键继续.");
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
	xyprintf(0, 30, "回到菜单or继续画图？（输入数字以选择）");
	xyprintf(0, 50, "1,保存文件?");
	xyprintf(0, 70, "2.继续画图？");
	xyprintf(0, 90, "3.回到菜单？");
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
		xyprintf(0, 90, "请正确输入");

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