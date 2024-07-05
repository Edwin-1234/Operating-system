#include<stdio.h>
void main()
{
    int avail[25],max[25][25],alloc[25][25],need[25][25];
    int work[25],fin[25];
    int i,j,y,n,m,flag,s=0,k;
    int safeseq[10],safeflag=1;
    printf("Enter how many process:");
    scanf("%d",&n);
    printf("Enter how many resourcse:");
    scanf("%d",&m);
    printf("enter the max matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("enter the alloc matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("Enter the available matrix\n");
    for(i=0;i<m;i++)
    {
        scanf("%d",&avail[i]);
    }
    for(i=0;i<m;i++)
    {
        work[i]=avail[i];
    }
    printf("Need matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<n;i++)
    {
        fin[i]=0;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(fin[j]==0)
            {
                flag=1;
                for(k=0;k<m;k++)
                {
                    if(need[j][k]>work[k])
                    {
                        flag=0;
                        break;
                    }
                }
                if(flag)
                {
                    safeseq[s++]=j;
                    fin[j]=1;
                    for(y=0;y<m;y++)
                    {
                        work[y]+=alloc[j][y];
                    }
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(fin[i]==0)
        {
            safeflag=0;
            break; 
        }
    }
    if(safeflag)
    {
        printf("SAFE SEQUENCE : ");
        for(i=0;i<n;i++)
        {
            printf("P%d ",safeseq[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Unsafe");
    }
}
