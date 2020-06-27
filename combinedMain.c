//#include<stdio.h>
#include "myheader.h"

int main()
{


   int choice = 0;
   int start , end , weight,co;
   int cyc;
   int source , target ,djDis;
   printf("before file\n");
   listfromfile();
   printf("after file\n");
   while(choice != -1)
   {

   printf("------------------------------");
       printf("\n-1 - to EXIT\n\n");
       printf("\n1 - add Nodes\n");
       printf("\n2 - add Edge\n");
       printf("\n3 - display GRAPH\n");
       printf("\n4 - delete Edge\n");
       printf("\n5 - delete Node\n");
       printf("\n6 - DIJKSTRA alog\n");
       printf("\n7 - Change weight\n");
    //   printf("\n6 - DFT\n");
    //   printf("\n7 - BFT\n");
    //   printf("\n8 - Detect CYCLE\n");
    //  printf("\n9 - Minimum Spanning TREE\n");

       printf("\nEnter the choice\n");

       printf("=============================");
       fflush(stdin);
       scanf("%d",&choice);
       switch(choice)
       {
       case 1 :
        addNode();
        break;

       case 2 :
            printf("add edge from:- \n");
            scanf("%d",&start);
            printf("to:-\n");
            scanf("%d",&end); //end edge is here;
            printf("\n weight on edge\n");
            scanf("%d",&weight);

        addEdge(start , end , weight , vptr);
        addEdge(end , start , weight , vptr);
        break;

       case 3 :
           printf("GRAPH IS:-\n");
        display(vptr);
        break;

        case 4:
           printf("which edge to delete??\n");
            printf("starts from:\n");
            scanf("%d",&start);
            printf("ends on\n");
            scanf("%d",&end);

            deleteEdge(start,end);
            deleteEdge(end,start);
        break;

        case 5 :
        vptr = deleteNode();
        break;

        case 6 :
            printf("\nEnter the source:");
            scanf("%d", &source);
            printf("\nEnter the target");
            scanf("%d", &target);
            djDis = dijkstra(source,target);
        break;

        case 7 :
            printf("change weight from:- \n");
            scanf("%d",&start);
            printf("to:-\n");
            scanf("%d",&end); //end edge is here;
            printf("\n weight on edge\n");
            scanf("%d",&weight);

        changeWeight(start , end , weight , vptr);
        changeWeight(end , start , weight , vptr);
        printf("Weight has been updated to %d\n",weight);
        break;


       }
   }
   writeINfile();
    return 0;
}
