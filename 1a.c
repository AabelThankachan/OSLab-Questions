#include<stdio.h>
typedef struct{
   int name;
   int arrival;
   int burst;
   int completion;
   int waiting;
   int turnaround;
}Process;

void main(){
   int n;
   printf("Enter number of processes: ");
   scanf("%d",&n);
   
   Process processes[n];
   
   for (int i=0;i<n;i++)
   {
     printf("Enter details for Process %d: \n",i+1);
     processes[i].name=i+1;
     printf("Arrival time:");
     scanf("%d",&processes[i].arrival);
     printf("Burst time:");
     scanf("%d",&processes[i].burst);
   }
   
   
   Process temp;
   for (int i=0;i<n;i++){
      for (int j=0;j<n-i-1;j++){
         if(processes[j].arrival>processes[j+1].arrival){
             temp=processes[j];
             processes[j]=processes[j+1];
             processes[j+1]=temp;
         }
      }
   }          
   
   
   int currenttime=0;
   printf("Process | Time\n");
   
   for (int i=0;i<n;i++){
      int execution_time=processes[i].burst;
      currenttime+=execution_time;
      printf("P%d | %d\n",processes[i].name,currenttime);
      processes[i].completion=currenttime;
      processes[i].turnaround=processes[i].completion-processes[i].arrival;
      processes[i].waiting=processes[i].turnaround-processes[i].burst;
   }
   
   
   Process temp1;
   for (int i=0;i<n;i++){
      for (int j=0;j<n-i-1;j++){
         if(processes[j].name>processes[j+1].name){
             temp1=processes[j];
             processes[j]=processes[j+1];
             processes[j+1]=temp1;
         }
      }
   }      
   
   float avg_wt=0.0;
   float avg_tat=0.0;
   printf("Process  AT  BT  CT  TAT  WT\n");
   
   for (int i=0;i<n;i++)
   {
      printf("P%d \t %d  %d  %d  %d  %d\n",processes[i].name,processes[i].arrival,processes[i].burst,processes[i].completion,processes[i].turnaround,processes[i].waiting);
      avg_wt+=processes[i].waiting;
      avg_tat+=processes[i].turnaround;
   }
   
   printf("Average Waiting Time= %f\n",avg_wt/n);
   printf("Average Turnaround Time= %f\n",avg_tat/n);        
}      
      
     
      
      
        
