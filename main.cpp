#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

void citire(char a[][100][100], int &n,int &m, int &si, int sf[],int &k, char cuv[])
{
    int i,q1,q2,j;
    char lit;

    ifstream fin ("automat.in");

    fin>>n;//numarul de stari

    fin>>si;//starea initiala

    fin>>k;//numarul starilor finale
    for(i=1;i<=k;i++)
    fin>>sf[i];//starile finale

    fin>>m; //numarul de muchii
    for(i=1;i<=m;i++)
    {
        fin>>q1>>q2>>lit;
        a[q1][q2][strlen(a[q1][q2])]=lit;
        a[q1][q2][strlen(a[q1][q2])+1]='\0';
    }

    fin>>cuv;//cuvantul care trebuie verificat

}

void afis(char a[][100][100], int n, int si, int sf[],int k, char cuv[])
{
    int i,j;

    ofstream fout ("automat.out");

    fout<<n<<endl;//numarul de stari

    fout<<si<<endl;//starea initiala

    for(i=1;i<=k;i++)
        fout<<sf[i]<<" ";//starile finale

    fout<<endl;

    for(i=0;i<n;i++)
   {
       for(j=0;j<n;j++)
        if(a[i][j][0]==NULL)
            fout<<"- ";
        else
            fout<<a[i][j]<<" ";

        fout<<endl;
   }

    fout<<cuv;
}

int stare_finala(int k, int sf[], int x)
{
    int i;

    for(i=1;i<=k;i++)
        if(sf[i]==x)
        return 1;
    return 0;
}

void verificare_cuvant(int &ok,int p,int n, char cuv[],char a[][100][100],int q,int k, int sf[])
{
    int i,j;
    if(stare_finala(k,sf,q)==1 && cuv[p]=='\0')
        ok=1;

    for(i=0;i<n && cuv[p]!=NULL;i++)
      for(j=0;j<strlen(a[q][i]);j++)
       if(a[q][i][j]==cuv[p])
             verificare_cuvant(ok,p+1,n,cuv,a,i,k,sf);

}

int main()
{
    char a[100][100][100], cuv[100];
    int n,si,sf[100],k,p=0,ok=0,m;

    citire(a,n,m,si,sf,k,cuv);
    afis(a,n,si,sf,k,cuv);

    if(cuv[0]==NULL && stare_finala(k,sf,si)==1)
        cout<<"CUVANT ACCEPTAT";
    else
    {
        verificare_cuvant(ok,p,n,cuv,a,si,k,sf);

        if(ok==1)
            cout<<"CUVANT ACCEPTAT";
        else
            cout<<"CUVANT NEACCEPTAT";

    }


    return 0;
}
