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
    double score[5];//���ſγɼ�
    double total;
    double avg;
}STU;
void display(void);                     //��ʾ���˵�
void load(STU stu[],int *nPtr);//��ѧ����Ϣ���ص��ڴ�
void save(STU stu[],int n);//�����ݱ��浽����
void sort(STU stu[],int n);//����
void InputRecord(STU stu[],int i);//����һ����¼
void find(STU stu[],int n);//����
void del(STU stu[],int *nPtr);//ɾ��
void add(STU stu[],int *nPtr);//���һ����¼
void edit(STU stu[],int n);//�޸�һ����¼
void DeleteAll(STU stu[],int *nPtr);//ɾ�����м�¼
void DeleteRecord(STU stu[],int *nPtr);//ɾ��һ����¼
int FindByNum(STU stu[],int n,char *str);//��ѧ�Ų���
void output(STU stu[],int n);//���������Ϣ
void PrintRecord(STU *nPtr);//���һ����¼
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
                add(stu,&n);break;//���
            case 2:
                edit(stu,n);break;//�޸�
            case 3:
                sort(stu,n);break;//����
            case 4:
                find(stu,n);break;//����
            case 5:
                del(stu,&n);break;//ɾ��
            case 6:
                output(stu,n);break;//���
            case 7:
                return 0;//�˳�
        }
    }
}
void display(void)
{
    system("cls");
    printf("��ӭʹ�ñ�ѧ���ɼ�����ϵͳ\n");
    printf("˵�����ڱ�ϵͳ����ִ��ĳ�����������Ӧ������\n");
    printf("1 ���\n");
    printf("2 �޸�\n");
    printf("3 ����\n");
    printf("4 ����\n");
    printf("5 ɾ��\n");
    printf("6 ���\n");
    printf("7 �˳�\n");
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
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    fwrite(stu,n * sizeof(stu[0]),1,fp);
    fclose(fp);
}
void output(STU stu[],int n)
{
    int i;
    /*��ӡ��ͷ*/
    printf("%8s%8s%4s%8s%8s%8s%8s%8s%8s%8s\n","ID","NAME","SEX",
           "SCORE1","SCORE2","SCORE3","SCORE4","SCORE5","total","avg");
    /*��ӡ���м�¼*/
    for(i=0;i<n;i++)
        PrintRecord(&stu[i]);
    system("pause");
}
void PrintRecord(STU *sPtr)//���ָ��sPtr��ָ��¼������
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
    //int i=0;//û��
    char sel = 'y';
    while(sel=='y')
    {
        InputRecord(stu,(*sPtr)++);
        printf("�Ƿ�������(yes--y,no--others)\n");
        scanf(" %c",&sel);
    }
    save(stu,*sPtr);
}
void InputRecord(STU stu[],int i)//����һ��ѧ������Ϣ����������Ԫ��stu[i].
{
    int j;
    //i=i-1;
    /*����ѧ�ţ�����֤�Ϸ���*/
    printf("�������%d��ѧ����Ϣ\n",i+1);
    printf("������ѧ��ѧ��(ѧ��С��9λ�������)\n");
    scanf("%s",stu[i].id);
    printf("������ѧ������\n");
    scanf(" %s",stu[i].name);
    printf("������ѧ���Ա�f��m f����Ů�� m�������ԣ�\n");
    scanf(" %c",&stu[i].sex);
    printf("���������ſγɼ���0~100��\n");
    stu[i].total = 0;
    for(j=0;j<5;j++)
    {
        scanf(" %lf",&stu[i].score[j]);
        stu[i].total+=stu[i].score[j];
    }
    stu[i].avg = stu[i].total/5;
}
int FindByNum(STU stu[],int n,char *str)//��ѧ�Ų�����Ҫ�޸ĵļ�¼�������±ꡣ
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
    printf("������ѧ�ţ�\n");
    scanf("%s",str);
    index=FindByNum(stu, n, str);//���ú���FindByNum()�ҵ�Ҫ�޸ĵļ�¼��
    if(index<0)
    {
        printf("��ѧ����Ϣ������\n");
        return ;
    }
    printf("�޸�ǰ��ԭ��¼���£�\n");
    PrintRecord(&stu[index]);//����PrintRecord()������ʾ�ü�¼������

    printf("�Ƿ��޸�������������y or n:\n");
    scanf(" %c",&sel);
    if(sel=='y')
    {
        printf("������������\n");
        scanf("%s",stu[index].name);
    }
    printf("�Ƿ��޸��Ա�������y or n:\n");
    scanf(" %s",&sel);
    if(sel=='y')
    {
        printf("������ f or m:\n");
        scanf(" %c",&stu[index].sex);
    }
    printf("�Ƿ��޸ĳɼ���input y or n:\n");
    scanf(" %c",&sel);
    if(sel=='y')
    {
        stu[index].total = 0;
        printf("������5��ѧ�Ƴɼ���\n");
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
    int (*cmp)(STU a,STU b);//����ָ��
    int ScoreAsc(STU a,STU b);//��������
    int ScoreDes(STU a,STU b);//��������
    int NameAsc(STU a,STU b);//����������
    printf("1 ���ܷ���������\n");
    printf("2 ���ֽܷ�������\n");
    printf("3 ����������\n");
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
    printf("������ѧ�ţ�\n");
    scanf("%s",str);
    index = FindByNum(stu,n,str);
    if(index>=0)
        PrintRecord(&stu[index]);
    else
        printf("��ѧ����Ϣ������\n");
    system("pause");
}
void del(STU stu[],int *nPtr)
{
    int i,index;
    char str[20];
    printf("������ѧ�ţ�\n");
    scanf("%s",str);
    index=FindByNum(stu,*nPtr,str);
    if(index<0)
    {
        printf("\n��ѧ����Ϣ������\n");
        return ;
    }
    for(i=index;i<*nPtr-1;i++)
    {
        stu[i] = stu[i+1];
    }
    (*nPtr)--;
    printf("\n ɾ���ɹ�\n");
    save(stu,*nPtr);
}
