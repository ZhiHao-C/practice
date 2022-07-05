#include <REGX52.H>
#include "delay.h"
#include "keycode.h"
#include <INTRINS.H>

#define unchar unsigned char
unchar time;
unchar keynum;
unchar dir;
unchar a[]={~0x01,~0x02,~0x04,~0x08,~0x10,~0x20,~0x40,~0x80};
unchar i;
int n;
void init()
{
	TF0=0;//标志位清零
	TMOD=TMOD&0xf0;
	TMOD=TMOD|0x01;//设置定时器0为 0001
	TH0=0x4c;
	TL0=0x00;//初始化使得过50ms中断一次
	EA=ET0=1;//总开关EA，分开关ET0打开
	TR0=1;//开始计时
}
void timing() interrupt 1
{
	TF0=0;
	TH0=0x4c;
	TL0=0x00;//重新填装
	time++;
	if(time>=10)
	{
		time=0;
		if(dir==1)//dir 判断方向：dir为1时向右
		{
			n=n>>1;
			if(n==0)
			{
				n=0x80;
			}
			P2=~n;
		}
		if (dir==0)//dir为0向左
		{
			n=n<<1;
			if(n>0x80)
			{
				n=1;
			}
			P2=~n;
		}
	}
}
void main()
{
	init();
	n=1;
	while(1)
	{
		keynum=key();
		if(keynum==1)
		{
			dir=1;
		}
		else if(keynum==2)
		{
			dir=0;
		}
		
	}
	
}
