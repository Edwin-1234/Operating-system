#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int priority;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int response;
    int waiting;
    int remaining;
    int completed;
}p[10],temp[10],temp_p;

int n,total_burst,slice;
float avg_tt,avg_rt,avg_wt;

void initialize()
{
    int i;
    avg_tt=avg_rt=avg_wt=0;
    total_burst=0;
    for(i=0;i<n;i++)
    {
        p[i].completion=0;
        p[i].turnaround=0;
        p[i].response=0;
        p[i].waiting=0;
        p[i].completed=0;
        temp[i]=p[i];
        total_burst+=p[i].burst;
        p[i].remaining=p[i].burst;
    }
}

void display(struct process* p)
{
    int i;
    printf("PID\t|PRIORITY\t|BURST TIME\t|ARRIVAL TIME\t|COMPLETION TIME\t|TURNAROUND TIME\t|RESPONSE TIME\t|WAITING TIME\t|\n");
    for(i=0;i<n;i++)
    {
        avg_tt+=p[i].turnaround;
        avg_rt+=p[i].response;
        avg_wt+=p[i].waiting;
        printf("%d\t|%d\t\t|%d\t\t|%d\t\t|%d\t\t\t|%d\t\t\t|%d\t\t|%d\t\t|\n",p[i].pid,p[i].priority,p[i].burst,p[i].arrival,p[i].completion,p[i].turnaround,p[i].response,p[i].waiting);
    }
    avg_tt=avg_tt/n;
    avg_wt=avg_wt/n;
    avg_rt=avg_rt/n;
    printf("Average Turnaround Time : %.2f\n",avg_tt);
    printf("Average Response Time : %.2f\n",avg_rt);
    printf("Average Waiting Time : %.2f\n",avg_wt);
}

void fcfs()
{
    initialize();
    int i,j,total;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival > temp[j+1].arrival)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    total=0;
    for(i=0;i<n;i++)
    {
        while(temp[i].arrival > total)
        {
            total++;
        }
        temp[i].completion=temp[i].burst+total;
        temp[i].response=total-temp[i].arrival;
        temp[i].waiting=total-temp[i].arrival;
        temp[i].turnaround=temp[i].completion-temp[i].arrival;
        total+=temp[i].burst;
    }
    display(temp);
}

void sjf()
{
    initialize();
    int completed=0,currenttime=0;
    int i,j;
    int minindex,minimum;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival > temp[j+1].arrival)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival == temp[j+1].arrival && temp[j].burst > temp[j+1].burst)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    while(completed!=n)
    {
        minindex=-1;
        minimum=total_burst;
        for(i=0;i<n;i++)
        {
            if(temp[i].arrival <= currenttime && temp[i].completed == 0)
            {
                if(temp[i].burst < minimum)
                {
                    minimum=temp[i].burst;
                    minindex=i;
                }
                if(temp[i].burst == minimum)
                {
                    if(temp[i].arrival < temp[minindex].arrival)
                    {
                        minindex=i;
                        minimum=temp[i].burst;
                    }
                }
            }
        }
        if(minindex == -1)
        {
            currenttime++;
        }
        else
        {
            temp[minindex].completed=1;
            completed++;
            temp[minindex].completion=temp[minindex].burst+currenttime;
            temp[minindex].response=currenttime-temp[minindex].arrival;
            temp[minindex].waiting=currenttime-temp[minindex].arrival;
            temp[minindex].turnaround=temp[minindex].completion-temp[minindex].arrival;
            currenttime+=temp[minindex].burst;
        }
    }
    display(temp);
}

void priority()
{
    initialize();
    int completed=0,currenttime=0;
    int i,j;
    int minindex,maxpriority;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival > temp[j+1].arrival)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival == temp[j+1].arrival && temp[j].priority > temp[j+1].priority)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    while(completed!=n)
    {
        minindex=-1;
        maxpriority=10000;
        for(i=0;i<n;i++)
        {
            if(temp[i].arrival <= currenttime && temp[i].completed == 0)
            {
                if(temp[i].priority < maxpriority)
                {
                    maxpriority=temp[i].priority;
                    minindex=i;
                }
                if(temp[i].priority == maxpriority)
                {
                    if(temp[i].arrival < temp[minindex].arrival)
                    {
                        minindex=i;
                        maxpriority=temp[i].priority;
                    }
                }
            }
        }
        if(minindex == -1)
        {
            currenttime++;
        }
        else
        {
            temp[minindex].completed=1;
            completed++;
            temp[minindex].completion=temp[minindex].burst+currenttime;
            temp[minindex].response=currenttime-temp[minindex].arrival;
            temp[minindex].waiting=currenttime-temp[minindex].arrival;
            temp[minindex].turnaround=temp[minindex].completion-temp[minindex].arrival;
            currenttime+=temp[minindex].burst;
        }
    }
    display(temp);
}

void roundrobin()
{
    initialize();
    int i,j;
    int remaining=n,time=0,flag=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival > temp[j+1].arrival)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    i=0;
    while(remaining != 0)
    {
        if(temp[i].arrival > time)      
        {
            time++;
            continue;
        }
        if(temp[i].remaining == temp[i].burst)  
        {
            temp[i].response=time-temp[i].arrival;
        }
        if(temp[i].remaining <= slice && temp[i].remaining > 0)
        {
            time+=temp[i].remaining;
            temp[i].remaining=0;
            flag=1;
        }
        else if(temp[i].remaining > 0)
        {
            temp[i].remaining-=slice;
            time+=slice;
        }
        if(temp[i].remaining == 0 && flag == 1)
        {
            remaining--;
            flag=0;
            temp[i].completion=time;
            temp[i].waiting=temp[i].completion-temp[i].arrival-temp[i].burst;
            temp[i].turnaround=temp[i].completion-temp[i].arrival;
            temp[i].completed=1;
        }
        if(i==n-1)
        {
            i=0;
        }
        else if(p[i+1].arrival <= time)
        {
            i++;
        }
        else
        {
            i=0;
        }
    }
    display(temp);
}

void main()
{
    int i;
    printf("How many processes ? : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the process ID : ");
        scanf("%d",&p[i].pid);
        printf("Enter the priority : ");
        scanf("%d",&p[i].priority);
        printf("Enter the arrival time : ");
        scanf("%d",&p[i].arrival);
        printf("Enter the burst time : ");
        scanf("%d",&p[i].burst);
    }
    printf("Enter the time slice : ");
    scanf("%d",&slice);
    printf("\nFIRST COME FIRST SERVE (FCFS)\n");
    fcfs();
    printf("\nSHORTEST JOB FIRST (SJF)\n");
    sjf();
    printf("\nPRIORITY SCHEDULING\n");
    priority();
    printf("\nROUND ROBIN SCHEDULING\n");
    roundrobin();
}
