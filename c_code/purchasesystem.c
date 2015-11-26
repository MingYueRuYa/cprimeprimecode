#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//#include <conio.h>
//#include <windows.h>
void DrawMenu();
void GreateMsg();
void printAll();
void findMsg();
void deleteMsg();
void upDateMsg();
void operation();
void technology();
struct Msg{
	long num;//采购编号
	char name[10];//零部件名称
	char date[15];//采购日期
	char workerName[10];//采购员姓名
	long goodsNum;//采购数量
	float price;//采购单价
	char address[30];//供货单位
}msg[100];
int n=0;
int main()
{
	DrawMenu();
	switch (getchar())
	{
		case '1':GreateMsg();break;
		case '2':findMsg();break;
		case '3':deleteMsg();break;
		case '4':upDateMsg();break;
		case '5':printAll();break;
		case '6':operation();break;
		case '7':technology();break;
		case 'q':
		case 'Q':exit(0);
		default:system("clear");main();
	}
} 
void DrawMenu()
{
	//HANDLE hNewConsole = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ,
	//	0,
	//	NULL, 
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL);
	// SetConsoleTitle("管理系统(Q键退出系统)");
	printf("\n\n\n");
	printf(" ##############################################################################\n");
	printf(" #                           汽车零部件采购管理系统                           #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               1.增加采购信息                               #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               2.查询采购信息                               #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               3.删除采购信息                               #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               4.修改采购信息                               #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               5.查询所有采购信息                           #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               6.系统操作说明                               #\n");
	printf(" #----------------------------------------------------------------------------#\n");
	printf(" #                               7.技术支持                                   #\n");
	printf(" ##############################################################################\n");
}
void GreateMsg()
{
	int isContinue=1;
	while (isContinue==1)
	{
		system("clear");
		printf("采购编号:");
		scanf("%d",&(msg[n].num));
		printf("部件名称:");
		scanf("%s",msg[n].name);
		printf("采购日期:");
		scanf("%s",msg[n].date);
		printf("采购人员:");
		scanf("%s",msg[n].workerName);
		printf("采购数量:");
		scanf("%d",&(msg[n].goodsNum));
		printf("采购单价:");
		scanf("%f",&(msg[n].price));
		printf("供货单位:");
		scanf("%s",msg[n].address);
		n++;
		printf("插入完成是(1)否(0)继续?\n");
		scanf("%d",&isContinue);
	}
	system("clear");
	main();
}
void findMsg()
{
	int num,i;
	system("clear");
	printf("输入你要查询的采购编号:");
	scanf("%d",&num);
	system("clear");
	for (i=0;i<n;i++)
	{
		if(msg[i].num==num)
		{
			printf("----------------------------------财务清单------------------------------------\n");
			printf("##############################################################################\n");
			printf("# 采购编号 | 部件名称 | 采购日期 | 采购人员 | 采购数量 | 采购单价 | 供货单位 #\n");
			printf("#----------------------------------------------------------------------------#\n");
			printf("# %-9d| %-9s| %-9s| %-9s| %-9d| %-9.2f| %-9s #\n",msg[i].num,msg[i].name,msg[i].date,msg[i].workerName,msg[i].goodsNum,msg[i].price,msg[i].address);
			printf("##############################################################################\n");
			break;
		}
	}
	if (i==n-1||n==0)
	{
		printf("未找到该采购单号!按任意键返回主菜单");
	}
	getchar();
	system("clear");
	main();
}
void deleteMsg()
{
	int i;
	char name[20];
	system("clear");
	printf("请输入你要删除的部件名:");
	scanf("%s",name);
	for (i=0;i<n;i++)
	{
		if (strcmp(msg[i].name,name)==0)
		{
			msg[i].goodsNum=0;
			printf("删除成功!按任意键返回主菜单!");
		}
	}
	if (i==n-1||n==0)
	{
		printf("该商品不存在！按任意键返回主菜单!");
	}
	getchar();
	system("clear");
	main();
}
void upDateMsg()
{
	int num,i;
	system("clear");
	printf("请输入你要修改项的采购编号:");
	scanf("%d",&num);
	for (i=0;i<n;i++)
	{
		if (msg[i].num==num)
		{
			system("clear");
			printf("采购编号:");
			scanf("%d",&(msg[i].num));
			printf("部件名称:");
			scanf("%s",msg[i].name);
			printf("采购日期:");
			scanf("%s",msg[i].date);
			printf("采购人员:");
			scanf("%s",msg[i].workerName);
			printf("采购数量:");
			scanf("%d",&(msg[i].goodsNum));
			printf("采购单价:");
			scanf("%f",&(msg[i].price));
			printf("供货单位:");
			scanf("%s",msg[i].address);
			printf("修改已完成，按任意键返回主菜单!");
		}
	}
	if(i==n)
	{
		printf("未找到该采购编号，按任意键返回主菜单!");
	}
	getchar();
	system("clear");
	main();
}
void printAll()
{
	int i;
	system("clear");
	printf("----------------------------------财务清单------------------------------------\n");
	printf("##############################################################################\n");
	printf("# 采购编号 | 部件名称 | 采购日期 | 采购人员 | 采购数量 | 采购单价 | 供货单位 #\n");
	printf("#----------------------------------------------------------------------------#\n");
	for(i=0;i<n;i++)
	{
		if (i!=n-1&&msg[i].goodsNum!=0)
		{
			printf("# %-9d| %-9s| %-9s| %-9s| %-9d| %-9.2f| %-9s #\n",msg[i].num,msg[i].name,msg[i].date,msg[i].workerName,msg[i].goodsNum,msg[i].price,msg[i].address);
			printf("#----------------------------------------------------------------------------#\n");
		}
		else if (i==n-1&&msg[i].goodsNum!=0)
		{
			printf("# %-9d| %-9s| %-9s| %-9s| %-9d| %-9.2f| %-9s #\n",msg[i].num,msg[i].name,msg[i].date,msg[i].workerName,msg[i].goodsNum,msg[i].price,msg[i].address);
			printf("##############################################################################\n");
		}
	}
	printf("按任意键返回主菜单");
	getchar();
	system("clear");
	main();
}
void operation()
{
	system("clear");
	printf("\n\n\n");
	printf("##############################################################################\n");
	printf("#这是一个简版的管理系统，首先进入首页选择菜单前的编号，然后根据进行相关的操作#\n");
	printf("##############################################################################\n");
	getchar();
	system("clear");
	main();
}
void technology()
{
	system("clear");
	printf("\n\n\n");
	printf("##############################################################################\n");
	printf("#本系统使用C语言制作，功能比较简单，但还是要细心才保证不会出现各种故障，本人 #\n");
	printf("#花费了两三个小时时间编写。欢迎各位大牛指点。                                #\n");
	printf("#----------------------------------Made by 废人;QQ:249671015-----------------#\n");
	printf("##############################################################################\n");
	getchar();
	system("clear");
	main();
}
