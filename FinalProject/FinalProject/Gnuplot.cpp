#include"Gnuplot.hpp"


// Generate a matrix to store results for all 3 groups as required
vector<Matrix> get_computation_result(vector<Stock*> stocks,const StockPrice& benchmark, const int n){
   
   vector<Matrix> res;
   for(int i=0;i<3;i++){
     res.push_back(call_bootstrap(stocks,benchmark,n)) 
   }
    return res;
}

void Gnuplot_CAAR(vector<Matrix> computation_result){
    Vector caar_group1 = computation_result[0][2];
    Vector caar_group2 = computation_result[1][2];
    Vector caar_group3 = computation_result[2][2];
    
    
    int dataSize = caar_group1.size();
	int N = dataSize / 2;
	FILE* gnuplotPipe, **tempDataFile;
	const char* tempDataFileName1 = "BEAT";
	const char* tempDataFileName2 = "MEET";
	const char* tempDataFileName3 = "MISS";
	double x, y, x2, y2, x3, y3;
	int i;
    
    gnuplotPipe = popen("/opt/local/bin/gnuplot","w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines\n",tempDataFileName1, tempDataFileName2);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i <= dataSize; i++) {
            x = i - N;
            y = caar_group1[i];
            fprintf(tempDataFile,"%lf %lf\n",x,y);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i <= dataSize; i++) {
            x2 = 1 - N;
            y2 = caar_group2[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
         tempDataFile = fopen(tempDataFileName3,"w");
        for (i=0; i <= dataSize; i++) {
            x = i - N;
            y = caar_group3[i];
            fprintf(tempDataFile,"%lf %lf\n",x,y);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
    } else {        
        printf("gnuplot not found...");    
    }

	
}

