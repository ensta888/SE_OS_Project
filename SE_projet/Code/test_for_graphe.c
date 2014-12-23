#include <math.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
//#include <graphics.h>

int main()
{
 int GraphDriver;
 int GraphMode;
 int i, x, y;
 char buffer[5];
 int data[]={7,3,12,6,9,5,8,11};

 GraphDriver = DETECT;      /*自动检测图形设备*/
 initgraph(&GraphDriver, &GraphMode, ""); /*初始化图形设备*/

 setcolor(15);    /*设置前景色，白色*/
 moveto(635, 461);   /*移动画笔至点(635,461)*/
 lineto(20, 461);   /*从当前画线至(20,461)，并移画笔到(20,461)，画x轴*/
 lineto(20, 20);   /*从当前画线至(20,20)，并移画笔到(20,20)，画y轴*/

 setcolor(15);    /*设置前景色，白色*/
 for (i = 1 ; i < 13; i++)
  {
   itoa(i, buffer, 10);  /*将i以十进制形式转换成字符串，保存在buffer*/
   outtextxy(20 - textwidth(buffer), 456 - i * 36, buffer); /*在适当位置输出y轴的刻度对应的标签*/
   moveto(20, 460 - i * 36); /*画笔移至y轴刻度起点*/
   lineto(23, 460 - i * 36); /*画y轴刻度*/
  }
 setfillstyle(SOLID_FILL, 1); /*设置填充模式（配合直方图）*/
 for (i = 0 ; i < 8; i++)
  {
   moveto(i * 50 + 49, 461); /*移动画笔至x刻度处*/
   lineto(i * 50 + 49, 465); /*画x刻度*/
   outtextxy(i * 50 + 51, 463, itoa(i + 1, buffer, 10));   /*输出x轴刻度*/
   bar(i * 50 + 35, 460 - data[i] * 36, i * 50 + 65, 460); /*画直方图*/
  }

 getch();   /*等待一个按键*/

 closegraph();  /*关闭图形模式*/
}
