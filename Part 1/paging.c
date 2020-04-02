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
    int n;
    int m;

    while(fscanf(file, "%d", & input ) == 1){
        if(count = 1){
            n = input;
        }elif(count = 2){
            m = input;
        }else{
            // Each line going forward is a virtual address
            unsigned int v = input;  // Virutal Address
            

        }
        count++;
    }
    fclose(inputFile);
}