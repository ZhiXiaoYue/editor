#include<Windows.h>
#include<stdlib.h>
#include<graphics.h>
#include<direct.h>
#include"menu.h"
#include"file.h"
void file() {
	xyprintf(0,0,"欢迎使用画板程序,是否打开之前保存的文件？ヽ(￣▽￣)ﾉ<Y/N>");
	char opfile;                                                                         //变量oplile用于储存是否打开文件的指令
	opfile = getch();
	Save anew;
	char opanther;
	if (opfile == 'y' || opfile == 'Y')
	{
		
		anew=openfile();
		if (anew.radius != 0) {
			yuanf(anew);
		}
		else {
			duobianx(anew);
		}
		
		/*yprintf(0, 20, "打开文件成功,是否继续打开文件?<Y/N>");
		opanther = getch();
		if (opanther == 'Y' || opanther == 'y') {
			duobianx(openfile());
		}
		else {
			menu();
		}*/
		
	}
	else if (opfile == 'n' || opfile == 'N')
	{
		xyprintf(0,50,"未打开文件( ﾟ∀ﾟ)");
		menu();
	}
	else {
		xyprintf(0,40,"请正确输入Y/N,注意将输入法切换成英文");
		file();                                                                                       //如果输入y\n以外的字母时回到之前重新输入
	}
}

/*
*该函数用于保存文件
*/
void savefile(Save apicture) {
	FILE *fp;
	FILE *older;
	char path[100];                                         //用来存文件路径
	char name[100];                                         //用来存文件名
	inputbox_getline("保存文件", "请输入你要保存的地址(eg.C\\:User\\Adminastrition\\Desktop)",path,100);
	if ((_mkdir(path))) {               //如果路径不存在,则创建该文件夹
		lable:
		inputbox_getline("保存文件", "请输入文件名", name, 100);
		sprintf(path, "%s\\%s%s", path,name, ".draw");
		if ((older = fopen(path, "r+"))) {
			xyprintf(0, 0, "该文件已存在，继续保存将覆盖。是否继续？1.是    2.否");
			if (getch() == 2) {
				cleardevice();
				savefile(apicture);
			}
			else {
				cleardevice();
			}
		}
		if (!(fp = fopen(path, "w+"))) {
			xyprintf(0, 0, "文件保存失败");
			getch();
		}
		else {
			if (fwrite(&apicture, sizeof(apicture), 1, fp)) {
				xyprintf(0, 0, "保存文件成功,按任意键继续");
				fclose(fp);
				getch();
				menu(apicture);
			}
			else {
				xyprintf(0, 0, "保存失败");
				getch();
			}
		}
	}
	else {
		xyprintf(0, 0, "不存在该路径,已创建文件夹");
		goto lable;
	}
}


/*
*该函数用于打开保存的文件
*/
Save openfile() {
	Save anew;
	FILE *fp;
	cleardevice();
	char  ifff;//判断是否继续打开文件
	char filename[60], path[60];
	char buffer[120];
	xyprintf(0, 20, "请输入文件地址：");
	inputbox_getline("文件地址", " ", path, 60);                                                                               //存储文件路径
	xyprintf(0, 40, "请输入文件名：");
	inputbox_getline("文件名", " ", filename, 60);                                                    //存储文件名
	sprintf(buffer, "%s\\%s.draw", path, filename);                                           //文件路径和文件名合一
	if ((fp = fopen(buffer, "r"))) {                                                //打开文件
		fread(&anew, sizeof(anew), 1, fp);                              //读取文件
		fclose(fp);                                          //关闭文件
		return anew;                               //返回所读取的信息
	}
	else {
		xyprintf(0, 0, "未找到文件,按任意键重新输入,按0放弃打开文件");
		ifff = getch();
		if (ifff == '0') {
			cleardevice();
			menu();
		}
		else
		openfile();
	}                                          //防止打不开文件导致的死循环

}//