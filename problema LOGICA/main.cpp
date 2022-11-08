#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int verification (char v[300])  //verifies if the proposition is correct
{
    char *p = strtok(v," ");
    int beg=0,fin=0,ok=1,ok2=1,oknot=1,pr1ok=1;

    if(!strcmp(p,"AND") || !strcmp(p,"OR") || !strcmp(p,"IMPLIES") || !strcmp(p,"EQUIVALENT")) //if program starts with connective it is incorrect
    {
        cout<<"Proposition is incorrect.";
        return 0;
    }
    if (v[strlen(v)-1]==')')
        fin++;
    while( p != NULL )
    {
        if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ",p[0])!=0 && p[1]==0)
        {
            ok2=1;
            if(ok==0)
            {
                cout<<"The proposition is incorrect.";  //if between variables there is no connective it is incorrect
                return 0;
            }
            ok=0;
            oknot=1;
            pr1ok=1;
        }
        if(!strcmp(p,"AND") || !strcmp(p,"OR") || !strcmp(p,"IMPLIES") || !strcmp(p,"EQUIVALENT"))
        {
            ok=1;
            if (ok2==0)
            {
                cout<<"The proposition is incorrect."; //if after connective comes another connective it is incorrect
                return 0;
            }
            ok2=0;
            if(oknot==0)    // if after NOT comes a connective it is not correct
            {
                cout<<"The proposition is incorrect.";
                return 0;
            }
            if (pr1ok==0)
            {
                cout<<"The proposition is incorrect."; //if after paranthesis comes a connective it is not correct
                return 0;
            }
        }
        if (!strcmp(p,"NOT"))
        {
            oknot=0;
        }

        if (strchr(")",p[0])!=0)   // if there is no variable between the paranthesis the program is incorrect
        {
            if(pr1ok==0)
            {
                cout<<"Proposition is incorrect.";
                return 0;
            }
            fin++;
        }
        if (strchr("(",p[0])!=0)
        {
            pr1ok=0;
            beg++;
        }

        p=strtok(NULL," ");
    }
    if (ok2==0)
    {
        cout<<"The proposition is incorrect.";   // if proposition ends with a connective it is incorrect
        return 0;
    }
    if(beg!=fin) //if there are not an equal number of open and closed parantheses it is not correct
    {
        cout<<"The proposition is incorrect.";
        return 0;
    }

    return 1;
}

void operations(char c[300],int &cop,int &f)  //makes only the operations between two variables
{
    char c2[300];
    strcpy(c2,c);
    char *p,*copie;
    p=strtok(c2," ");
    while(p!=NULL)
    {   if(!strcmp(p,"NOT"))
         {p=strtok(NULL," ");}
        if(!strcmp(p,"AND"))
        {
            p=strtok(NULL," ");

            cout<<"    "<<copie<<" AND "<<p<<" : ";

            if(f>0 && cop>0 && f==3)
                printf("true ");
            else
                printf("false ");
            break;
        }
        if(!strcmp(p,"OR"))
        {
            p=strtok(NULL," ");
            cout<<"    "<<copie<<" OR "<<p<<" : ";

            if(f==0 && cop==0)
                printf("false ");
            else
                printf("true ");
            break;
        }
        if(!strcmp(p,"IMPLIES"))
        {
            p=strtok(NULL," ");
            cout<<"    "<<copie<<" IMPLIES "<<p<<" : ";

            if(f==2)
                printf("false ");
            else
                printf("true ");
            break;
        }
        if(!strcmp(p,"EQUIVALENT"))
        {
            p=strtok(NULL," ");
            cout<<"    "<<copie<<" EQUIVALENT "<<p<<" : ";

            if(f==cop || (cop>1&&f==3))
                printf("true ");
            else
                printf("false ");
            break;
        }

        strcpy(copie,p);
        p=strtok(NULL," ");
    }

}
void values(char c[300]) //Assigning every existing variable the two values TRUE/FALSE
{
    int val[200]= {0},k=0;
    int arr[200];
    if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ",c[0])!=0 && c[1]==' ')
    {
        cout<<c[0]<<"       ";
        k++;
    }
    for (int i=1; i<strlen(c)-1; i++)  // we search for the variables
    {
        if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ",c[i])!=0 && strchr(" ",c[i+1]) && strchr(" ",c[i-1]))
        {
            cout<<c[i]<<"       ";
            k++;
        }
    }
    if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ",c[strlen(c)-1])!=0 && c[strlen(c)-2]==' ')
    {
        cout<<c[strlen(c)-1]<<"       ";
        k++;
    }
    cout<<endl;
    int m=pow(2,k),cop=0;
    int i,d,f;
    for(i=0; i<m; i++)
        arr[i]=i;
    for(i=0; i<m; i++)
    {
        for (d = k-1; d >= 0; d--)
        {
            f = arr[i] >> d;

            if (f & 1)
            {
                printf("true ");

            }
            else
            {
                printf("false ");

            }
            if(d==0)
            {
                operations(c,cop,f);
                cop=f;
            }
        }
        printf("\n");
    }
}


int main()
{
    char v[300],c[300];
    cin.get(v,300);
    cout<<endl;
    strcpy(c,v);
    if(verification(v))
    {
        cout<<"The proposition is correct."<<endl<<endl<<"Here is the table:"<<endl<<endl;
    }
    else
        return 0;
    values(c);

    return 0;
}
