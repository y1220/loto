#include <stdio.h>
#include <stdlib.h>

int **makemat(int, int);
int **freemat(int **,int );

int main()
{
    int i,j;
    //int n[11][11];
    int **n;
    ///initialization
    n=makemat(11,11);
//    for(i=0;i<11;i++)
//    {
//        for(j=0;j<11;j++)
//        {
//            n[i][j]=0;
//        }
//    }

    ///count how many rows
    FILE *fp;
    fp=fopen("loto.txt","r");
    if(fp==NULL)
    {
        printf("ERROR!FILE OPEN PROBLEM\n");
        exit(0);
    }
    char txt[10];
    int cnt=0;
    while(fgets(txt,10,fp)!=NULL)
    {
        cnt++;
    }
    fclose(fp);

    ///create data box
    //int data[cnt][10];
    int **data;
    data=makemat(cnt,10);
//    for(i=0;i<cnt;i++)
//    {
//        for(j=0;j<10;j++)
//        {
//            data[i][j]=0;
//        }
//    }


    ///count the value
    fp=fopen("loto.txt","r");
    if(fp==NULL)
    {
        printf("ERROR!FILE OPEN PROBLEM\n");
        exit(0);
    }

    fscanf(fp,"%d %d %d %d",&data[0][0],&data[0][1],&data[0][2],&data[0][3]);

    for(i=1;i<cnt;i++)
    {
        fscanf(fp,"%d %d %d %d",&data[i][0],&data[i][1],&data[i][2],&data[i][3]);
        n[data[i][0]][data[i-1][0]]++;
        n[data[i][1]][data[i-1][1]]++;
        n[data[i][2]][data[i-1][2]]++;
        n[data[i][3]][data[i-1][3]]++;
    }
    fclose(fp);

    data=freemat(data,cnt);

    ///transform n[0][j] -> n[10][j]
    ///          n[i][0] -> n[i][10]
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            if(i==0){
                n[10][j]=n[0][j];
            }else if(j==0){
                n[i][10]=n[i][0];
            }
        }
    }





    FILE *fp2;
    fp2=fopen("lotoresult.txt","w");
    if(fp2==NULL)
    {
        printf("ERROR!FILE OPEN PROBLEM\n");
        exit(0);
    }
    ///print the result
    fprintf(fp2,"   ①②③④⑤⑥⑦⑧⑨⓪\n");
    int num;
    for(i=1;i<11;i++)
    {
        num=i;
        if(num==10){
            num=0;
        }
        fprintf(fp2,"%d : ",num);
        for(j=1;j<11;j++)
        {
            fprintf(fp2,"%d ",n[i][j]);
        }
        fprintf(fp2,"\n");
    }


    fclose(fp2);

    n=freemat(n,11);

    printf("Please check inside of the file -> lotoresult.txt\n");

    return 0;
}

/***Dynamic memory allocation***/
int **makemat(int r,int c)
{
    int i;
    int **n;
    n=(int **)malloc(r*sizeof(int *));
    if(n==NULL)
    {
        printf("ERROR!MEMORY ALLOCATION!\n");
        exit(0);
    }
    for(i=0;i<r;i++)
    {
        n[i]=(int *)calloc(c,sizeof(int));
        if(n[i]==NULL)
        {
            printf("ERROR!MEMORY ALLOCATION!\n");
            exit(0);
        }
    }

    return n;
}

/***Free the memory***/
int **freemat(int **n,int r)
{
    int i;
    for(i=0;i<r;i++)
    {
        free(n[i]);
    }
    free(n);

    return n;
}
