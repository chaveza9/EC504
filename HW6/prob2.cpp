#include <cstdio>
#include <algorithm>


using namespace std;


struct Job {
   int V;
   int T;
};

struct JobComparator {
   bool operator() (const Job & i, const Job & j) {
       return ( i.V >= j.V );
   }
} JobComparatorObject;


double maxValue(struct Job sortedJobs[], int T) {
   int T_remain = T;
   double total_value = 0.0;
   for(int i=0; i < 10; ++i) {
       if(T_remain < sortedJobs[i].T) {
           total_value += (sortedJobs[i].V * ((double)T_remain) / sortedJobs[i].T);
           break;
       }
       else {
           total_value += sortedJobs[i].V;
           T_remain -= sortedJobs[i].T;
       }
   }
   return total_value;
}


int main() {
    FILE *fpout;
    int V[] = { 6, 25, 4, 1, 7, 3, 12, 1, 1, 8 };
    int T[] = { 2, 5, 1, 4, 4, 9, 1, 5, 3, 16 }; 

    struct Job Jobs[10];

    for(int i=0; i<10; ++i) {
        Jobs[i].V = V[i];
        Jobs[i].T = T[i];
    }

    // sort Jobs by value (highest Value is first)
    sort(Jobs, Jobs + 10, JobComparatorObject);

    // now we totally consume Jobs with higher values before moving on to lower value Jobs
    fpout = fopen("out6.dat","w");
    //fprintf (fpout,"Time \t Value \n");
    fprintf (fpout,"Time \t Value \n");
    for(int t = 1; t <= 50; ++t) {
        fprintf(fpout, "%d\t %f\n", t, maxValue(Jobs, t));
    }
    fclose(fpout);
    return 0;
}