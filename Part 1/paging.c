// Part 1: Memory managment - paging
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    String inputFileName;

    //Grabbing file name
    printf("Input file name: ")
    scanf("%d", &inputFileName)

    // For loop through each line of the file
    int number; 
 
    FILE* inputFile= fopen(inputFileName, "r"); // read only  
         
    if (! in_file ){  
        printf("Error the file does not exist\n"); 
        exit(-1); 
    } 
 
    // attempt to read the next line and store 
    // the value in the "input" variable 
    int count = 1;
    int n;  // The n lowest significant bits that represent the offset
    int m;  // The next m bits that represent the page number, assume n+m id always 16

    while(fscanf(file, "%d", & input ) == 1){
        if(count = 1){
            n = input;
        }elif(count = 2){
            m = input;
        }else{
            // Each line going forward is a virtual address
            unsigned int v = input;  // Virutal Address(')
            int p = pageNumberCalculation(); //page number
            int d = offsetCalculation(v, n); //Offset
            print("virtual addressed v"+count+" is in page number "+p+" and offsetd"+d);

        }
        count++;
    }
    // Close I/O file stream
    fclose(inputFile);
}

// Page number calculation
// v DIV 2^n
// DIV == bitwise >>
int pageNumberCalculation(v, n){
    int p = v >> 2^n
    return p;
}

// Offset Calculation
// v MOD 2^n 
// MOD == bitwise AND
int offsetCalculation(v, n){
    int d = v & 2^n;
    return d;
}

//Testing methods
int testPageNumberCalculation(v, n){
    int p = v/2^n;
    return p;
}

int testOffsetCalculation(v, n){
    int d = v%2*n;
    return d;
}

// Understanding bitwise operations
// https://mziccard.me/2015/05/08/modulo-and-division-vs-bitwise-operations/
