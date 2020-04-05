// Part 1: Memory managment - paging
#include <stdio.h>
#include <stdlib.h>

// Page number calculation
// v DIV 2^n
// DIV == bitwise >>
unsigned int pageNumberCalculation(v, n){
    unsigned int p = v >> 2^n;
    return p;
}

// Offset Calculation
// v MOD 2^n 
// MOD == bitwise AND
unsigned int offsetCalculation(v, n){
    unsigned int d = v & 2^n;
    return d;
}

//Testing methods
unsigned int testPageNumberCalculation(v, n){
    unsigned int p = v/2^n;
    return p;
}

unsigned int testOffsetCalculation(v, n){
    unsigned int d = v%2*n;
    return d;
}

// Understanding bitwise operations
// https://mziccard.me/2015/05/08/modulo-and-division-vs-bitwise-operations/


int main (int argc, char *argv[]){
    char inputFileName[15];

    //Grabbing file name
    printf("Input file name: ");
    scanf("%s", &inputFileName);
    
    printf("%s", inputFileName);
    FILE* inputFile= fopen(inputFileName, "r"); // read only  
         
    if (inputFile == NULL ){  
        printf("Error the file does not exist\n"); 
        exit(-1); 
    } 
 
    // attempt to read the next line and store 
    // the value in the "input" variable 
    int count = 1;
    unsigned int n;  // The n lowest significant bits that represent the offset
    unsigned int m;  // The next m bits that represent the page number, assume n+m id always 16
    unsigned int input;

    while(fscanf(inputFile, "%d", & input ) == 1){
        if(count = 1){
            n = input;
        }else if(count = 2){
            m = input;
        }else{
            // Each line going forward is a virtual address
            unsigned int v = input;  // Virutal Address(')
            unsigned int p = pageNumberCalculation(v, n); //page number
            unsigned int d = offsetCalculation(v, n); //Offset
            printf("virtual addressed v %d is in page number %d offset %d", count, p, d);

        }
        count++;
    }
    // Close I/O file stream
    fclose(inputFile);
}
