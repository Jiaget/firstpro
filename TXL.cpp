#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

unsigned int key_num;
int length=0;

 struct Node
{
    char name[20],num[19],adr[20],sign;
    struct Node *next;

};

typedef Node *TNode;//关键字为电话号码的线性表
Node *NNode[20];//关键字为名字的线性表

Node **Tel;

void hash_number(char num[19])
{
    int i=1;
    key_num=(int)num[0];
    while(num[i]!='\0')
    {
        key_num+=(int)num[i];
        i++;
    }
    key_num=key_num%20;
}

int ReHarsh(int key,char str[20])//再哈希函数，使用折叠法
{
    int s;
    int num1 = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
    int num2 = (str[4] - '0') * 1000 + (str[5] - '0') * 100 + (str[6] - '0') * 10 + (str[7] - '0');
    int num3 = (str[8] - '0') * 100  + (str[9] - '0') * 10  + (str[10] - '0');
    s=num1+num2+num3;
    s=(s+key)%20;

    return s;
}

void hash_name(Node *N)
//对name的哈希函数，并将信息保存入NNode中，用再哈希法处理冲突
{
    int key_nam=0;
    for(int i=0;N->name[i]!='\0';i++)
        key_nam+=(int)N->name[i];
    key_nam=(key_nam)%20;
    while(NNode[key_nam]->sign=='1')
        key_nam=ReHarsh(key_nam,N->name);

    length++;//计算表长

    strcpy(NNode[key_nam]->name,N->name);
    strcpy(NNode[key_nam]->num,N->num);
    strcpy(NNode[key_nam]->adr,N->adr);
    NNode[key_nam]->sign='1';
}


Node *input()
{
    Node *t;
    t=new Node;
    t->next=NULL;
    cout<<"                                   "<<"请输入姓名:";
    cin>>t->name;
    cout<<"                                   "<<"请输入地址:";
    cin>>t->adr;
    cout<<"                                   "<<"请输入电话号码:";
    cin>>t->num;
    return t;
}

void apend(Node *p)//添加记录，在这里用拉链法处理hash_num的冲突
{
    Node *newtel;
    Node *newname;
    newtel=p;
    newname=newtel;
    newtel->next=NULL;
    newname->next=NULL;
    hash_number(newtel->num);

    newtel->next=Tel[key_num]->next;
    Tel[key_num]->next=newtel;

    hash_name(newname);

}

void creat_Tel()
{
    int i;
    Tel=new TNode[20];
    for(i=0;i<20;i++)
    {
        Tel[i]=new Node;
        Tel[i]->next=NULL;
    }
}

void creat_Nam()
{
   for(int i=0;i<20;i++)
   {
       NNode[i]=new Node;
   }
}

void output_num()
{
    Node *p;
    for(int i=0;i<20;i++)
    {
        p=Tel[i]->next;
        while(p)
        {
            cout.width(15);
            cout<<p->name;

            cout<<' ';
            cout.width(15);
            cout<<p->adr;

            cout<<' ';
            cout.width(15);
            cout<<p->num;
            cout<<endl;
            p=p->next;
        }
    }
}

void search_Tel(char num[19])//以电话号码为关键字查找
{
    int t=0;
    hash_number(num);
    Node *q=Tel[key_num]->next;
    while(q)
    {
        if(strcmp(num,q->num)==0)
            {
                cout<<q->name<<' '<<q->adr<<' '<<q->num<<endl;
                t=1;
            }
        q=q->next;
    }

        if(t==0) cout<<"无记录！"<<endl;
}

void search_Nam(char name[20])//以姓名为关键字查找
{
    int key=0;
    for(int i=0;name[i]!='\0';i++)
    {
        key+=(int)name[i];
    }
    key=(key)%20;
    int j=1;
    while((NNode[key]->sign=='1')&&(strcmp(name,NNode[key]->name)!=0))
        {
            key=ReHarsh(key,name);
            j++;
           /* if(j>=length)
            {
                key=-1;
                break;
            }*/
        }
    if(NNode[key]->sign!='1') cout<<"无记录!"<<endl;
    else
      {
        for(unsigned int i=0; NNode[key]->name[i]!='\0'; i++)
        {
            cout << NNode[key]->name[i];
        }

        for(unsigned int i=0; i<10; i++)
        {
            cout << " ";
        }

        cout << NNode[key]->adr;

        for(int i=0; i<10; i++)
        {
            cout << " ";
        }

        cout << NNode[key]->num << endl;
    }

}
Node read() //读取文件
{
	ifstream read("data.dat",ios::in);
	read.seekg(ios::beg);
	char name[20],num[19],adr[20];
	int count=0;
	char c;
	c=read.get();
	while(c!='*')
    {
        if(c=='\n') count++;
        c=read.get();
    }
    read.seekg(ios::beg);

    for(int i=0;i<count;i++)
    {
        Node *q;
        q=new Node;
    read.getline(name,20,'-');
    strcpy(q->name,name);
    memset(name,0,20);
	read.getline(adr,20,'-');
	strcpy(q->adr,adr);
	memset(adr,0,20);
	read.getline(num,19,'\n');
	strcpy(q->num,num);
	memset(num,0,19);
    apend(q);
    }
    read.close();

}

void save()  //将数据保存在文件中
{
    ofstream out("data.dat",ios::out);
    Node *p;
    for(int i=0;i<20;i++)
    {
        p=Tel[i]->next;
        while(p)
        {
            out<<p->name<<"-"<<p->adr<<"-"<<p->num<<'\n';
            p=p->next;
        }
    }
    out<<'*';
    out.close();
}

void menu()
{
    cout<<"                                   "<<"电话号码查询系统"<<endl;
    cout<<"                                   "<<"***************"<<endl;
    cout<<"                                     "<<"1.添加记录"<<endl<<endl;
    cout<<"                                     "<<"2.查找记录"<<endl<<endl;
    cout<<"                                     "<<"3.显示记录"<<endl<<endl;
    cout<<"                                     "<<"4.清空记录"<<endl<<endl;
    cout<<"                                     "<<"5.退出系统"<<endl;
    cout<<"                                   "<<"***************"<<endl;
}

int main()
{
    char num[19];
    char name[20];
    creat_Nam();
    creat_Tel();
    read();
    int sel;
    while(1)
    {
    menu();
    cin>>sel;
    if(sel==2)
    {
        cout<<endl;
        cout<<"                                   "<<"6.姓名查询" <<endl;
        cout<<"                                   "<<"7.号码查询"<<endl;
        cout<<"                                   "<<"输入其他返回上一级"<<endl;
        int b;
        cin>>b;
        if(b==7)
        {
            cout<<endl;
            cout<<"                                   "<<"请输入电话号码: ";
            cin >>num;
            cout<<"                                   "<<"输出查找的信息: "<<endl;
            search_Tel(num);
            system("PAUSE");
        }
        else if(b==6)
        {
            cout<<endl;
            cout<<"                                   "<<"请输入姓名:";
            cin >>name;
            cout<<"                                   "<<"输出查找的信息: "<<endl;
            search_Nam(name);
            system("PAUSE");
        }
        else
        {
            system("cls");
        }
        system("cls");
        }


    if(sel==1)
        {
            cout<<endl;
            cout<<"                                   "<<"请输入要添加的内容:"<<endl;
            apend(input());
            save();
            cout<<"                                   "<<"信息添加成功！"<<endl;
            system("PAUSE");
        }
    if(sel==3)
        {
            cout<<endl;
            cout<<"                                   "<<"记录显示结果:"<<endl;
            output_num();
            cout<<endl;
            cout<<"                                   "<<"继续(1)或者退出程序(2)？"<<endl;
            int a;
            cin>>a;
            if(a==1) system("cls");
            else if(a==2) return 0;
        }
    if(sel==4)
        {
            cout<<"列表已清空:"<<endl;
            creat_Tel();creat_Nam();
            system("PAUSE");
        }

    if(sel==5) return 0;
          system("cls");
    }

return 0;

}
