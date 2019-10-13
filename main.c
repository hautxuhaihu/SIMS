#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 10000
typedef struct student
{
    char id[10];
    char name[20];
    char sex;
    double score[5];//五门课成绩
    double total;
    double avg;
}STU;
void display(void);                     //显示主菜单
void load(STU stu[],int *nPtr);//把学生信息加载到内存
void save(STU stu[],int n);//将数据保存到磁盘
void sort(STU stu[],int n);//排序
void InputRecord(STU stu[],int i);//输入一条记录
void find(STU stu[],int n);//查找
void del(STU stu[],int *nPtr);//删除
void add(STU stu[],int *nPtr);//添加一条记录
void edit(STU stu[],int n);//修改一条记录
void DeleteAll(STU stu[],int *nPtr);//删除所有记录
void DeleteRecord(STU stu[],int *nPtr);//删除一条记录
int FindByNum(STU stu[],int n,char *str);//按学号查找
void output(STU stu[],int n);//输出所有信息
void PrintRecord(STU *nPtr);//输出一条记录
int main()
{
    STU stu[N];
    int n;
    int select ;
    load(stu,&n);
    while(1)
    {
        //load(stu,&n);
        display();
        scanf("%d",&select);
        switch(select)
        {
            case 1:
                add(stu,&n);break;//添加
            case 2:
                edit(stu,n);break;//修改
            case 3:
                sort(stu,n);break;//排序
            case 4:
                find(stu,n);break;//查找
            case 5:
                del(stu,&n);break;//删除
            case 6:
                output(stu,n);break;//输出
            case 7:
                return 0;//退出
        }
    }
}
void display(void)
{
    system("cls");
    printf("欢迎使用本学生成绩管理系统\n");
    printf("说明：在本系统中欲执行某功能请输出相应的数字\n");
    printf("1 添加\n");
    printf("2 修改\n");
    printf("3 排序\n");
    printf("4 查找\n");
    printf("5 删除\n");
    printf("6 输出\n");
    printf("7 退出\n");
}
void load(STU stu[],int *nPtr)
{
    FILE *fp;
    int i;
    if((fp=fopen("d:\\student.dat","r"))==NULL)
    {
        *nPtr = 0;
        return;
    }
    for (i=0;fread(&stu[i],sizeof(STU),1,fp)!=0;i++)
        *nPtr=i+1;
    fclose(fp);
}
void save(STU stu[],int n)
{
    FILE *fp;
    if((fp = fopen("d:\\student.dat","w"))==NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    fwrite(stu,n * sizeof(stu[0]),1,fp);
    fclose(fp);
}
void output(STU stu[],int n)
{
    int i;
    /*打印表头*/
    printf("%8s%8s%4s%8s%8s%8s%8s%8s%8s%8s\n","ID","NAME","SEX",
           "SCORE1","SCORE2","SCORE3","SCORE4","SCORE5","total","avg");
    /*打印所有记录*/
    for(i=0;i<n;i++)
        PrintRecord(&stu[i]);
    system("pause");
}
void PrintRecord(STU *sPtr)//输出指针sPtr所指记录的内容
{
    int i;
    printf("%8s%8s%4c",sPtr->id,sPtr->name,sPtr->sex);
    for(i=0;i<5;i++)
    {
        printf("%8.2f",sPtr->score[i]);
    }
    printf("%8.2f%8.2f",sPtr->total,sPtr->avg);
    printf("\n");
}
void add(STU stu[],int *sPtr)
{
    //int i=0;//没用
    char sel = 'y';
    while(sel=='y')
    {
        InputRecord(stu,(*sPtr)++);
        printf("是否继续添加(yes--y,no--others)\n");
        scanf(" %c",&sel);
    }
    save(stu,*sPtr);
}
void InputRecord(STU stu[],int i)//读入一个学生的信息，存入数组元素stu[i].
{
    int j;
    //i=i-1;
    /*输入学号，并验证合法性*/
    printf("请输入第%d个学生信息\n",i+1);
    printf("请输入学生学号(学号小于9位数字组成)\n");
    scanf("%s",stu[i].id);
    printf("请输入学生姓名\n");
    scanf(" %s",stu[i].name);
    printf("请输入学生性别（f或m f代表女性 m代表男性）\n");
    scanf(" %c",&stu[i].sex);
    printf("请输入五门课成绩（0~100）\n");
    stu[i].total = 0;
    for(j=0;j<5;j++)
    {
        scanf(" %lf",&stu[i].score[j]);
        stu[i].total+=stu[i].score[j];
    }
    stu[i].avg = stu[i].total/5;
}
int FindByNum(STU stu[],int n,char *str)//按学号查找需要修改的记录，返回下标。
{
    int i;
    for(i=0;i<n;i++){
        if(strcmp(stu[i].id,str)==0)
            return i;}
    return -1;
}
void edit(STU stu[],int n)
{
    int i,index;
    char sel;
    char str[20];
    printf("请输入学号：\n");
    scanf("%s",str);
    index=FindByNum(stu, n, str);//调用函数FindByNum()找到要修改的记录。
    if(index<0)
    {
        printf("该学生信息不存在\n");
        return ;
    }
    printf("修改前的原记录如下：\n");
    PrintRecord(&stu[index]);//调用PrintRecord()函数显示该记录的内容

    printf("是否修改姓名？请输入y or n:\n");
    scanf(" %c",&sel);
    if(sel=='y')
    {
        printf("请输入姓名：\n");
        scanf("%s",stu[index].name);
    }
    printf("是否修改性别？请输入y or n:\n");
    scanf(" %s",&sel);
    if(sel=='y')
    {
        printf("请输入 f or m:\n");
        scanf(" %c",&stu[index].sex);
    }
    printf("是否修改成绩？input y or n:\n");
    scanf(" %c",&sel);
    if(sel=='y')
    {
        stu[index].total = 0;
        printf("请输入5门学科成绩：\n");
        for(i=0;i<5;i++)
        {
            scanf("%lf",&stu[index].score[i]);
            stu[index].total=stu[index].total+stu[index].score[i];
        }
        stu[index].avg=stu[index].total/5;
    }
    save(stu,n);
}
void sort(STU stu[],int n)
{
    int select,i,j;
    int (*cmp)(STU a,STU b);//函数指针
    int ScoreAsc(STU a,STU b);//升序排序
    int ScoreDes(STU a,STU b);//降序排序
    int NameAsc(STU a,STU b);//按姓名排序
    printf("1 按总分升序排列\n");
    printf("2 按总分降序排列\n");
    printf("3 按姓名排列\n");
    scanf("%d",&select);
    switch(select)
    {
        case 1:cmp = ScoreAsc;break;
        case 2:cmp = ScoreDes;break;
        case 3:cmp = NameAsc;break;
        default: return;
    }
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if((*cmp)(stu[i],stu[j])>0)
            {
                STU temp;
                temp=stu[i];
                stu[i]=stu[j];
                stu[j]=temp;
            }
    output(stu,n);
}
int ScoreAsc(STU a,STU b)
{
    return a.total > b.total ? 1:-1;
}
int ScoreDes(STU a,STU b)
{
    return a.total < b.total ? 1:-1;
}
int NameAsc(STU a,STU b)
{
    return strcmp(a.name,b.name);
}
void find(STU stu[],int n)
{
    int index;
    char str[20];
    printf("请输入学号：\n");
    scanf("%s",str);
    index = FindByNum(stu,n,str);
    if(index>=0)
        PrintRecord(&stu[index]);
    else
        printf("该学生信息不存在\n");
    system("pause");
}
void del(STU stu[],int *nPtr)
{
    int i,index;
    char str[20];
    printf("请输入学号：\n");
    scanf("%s",str);
    index=FindByNum(stu,*nPtr,str);
    if(index<0)
    {
        printf("\n该学生信息不存在\n");
        return ;
    }
    for(i=index;i<*nPtr-1;i++)
    {
        stu[i] = stu[i+1];
    }
    (*nPtr)--;
    printf("\n 删除成功\n");
    save(stu,*nPtr);
}
