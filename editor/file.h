#pragma once
typedef struct {
	int side=0;
	char color=0;
	int coord[100];
	int line_width=0;
	COORD pos = { 0,0 };
	int radius=0;
}Save;
void file();
void savefile(Save apicture);
Save openfile();
void main();