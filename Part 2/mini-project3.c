#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

struct indexNode{
  char name[8]; //file name
  int size;     // file size (in number of blocks)
  int blockPointers[8]; // block numbers; this*1024 is first byte in file
  int used;     // 0 => inode is free; 1 => in use
};

struct superBlock{
  int8_t freeBlocks[128];
  struct indexNode inodes[16];
};

struct superBlock super;
FILE *input;

void myFileSystem(const char* diskName)
{
   // Open the file with name diskName
   input = fopen(diskName,"r+");
   if(input == NULL){
     printf("Could not find disk '%s'. Please try again\n",diskName);
     exit(-1);
   }
   // Read the first 1KB and parse it to structs/objecs representing the super block
   // 	An easy way to work with the 1KB memory chunk is to move a pointer to a
   //	position where a struct/object begins. You can use the sizeof operator to help
   //	cleanly determine the position. Next, cast the pointer to a pointer of the
   //	struct/object type.
   int8_t freeBlocks[128];
   fread(freeBlocks, sizeof(int8_t), 128, input);
   printf("Free block addresses loaded. Current file point: %d\n",ftell(input));

   struct indexNode inodes[16];
   fread(inodes, sizeof(struct indexNode), 16, input);

   for(int i = 0; i<128; i++){
     super.freeBlocks[i] = freeBlocks[i];
   }
   for(int i = 0; i<16; i++){
     super.inodes[i] = inodes[i];
   }
   // Be sure to close the file in a destructor or otherwise before
   // the process exits.
}


int create(char name[8], int size)
{ //create a file with this name and this size

  // high level pseudo code for creating a new file

  // Step 1: Look for a free inode by searching the collection of objects
  // representing inodes within the super block object.
  // If none exist, then return an error.
  // Also make sure that no other file in use with the same name exists.
  int inodeIndex = -1;
  for(int i = 0; i<16; i++){
    if(inodeIndex == -1 && super.inodes[i].used==0){
      inodeIndex = i;
    }
    if(strcmp(name,super.inodes[i].name)==0){
      printf("Filename '%s' already in use. Please use a different name or delete the offending file.\n",name);
      return -1;
    }
  }

  // Step 2: Look for a number of free blocks equal to the size variable
  // passed to this method. If not enough free blocks exist, then return an error.
  if(size>8){
    printf("The requested space for this file exceed's the system's maximum of eight 1KB blocks");
    return -1;
  }

  int blockIndices[size];
  int foundIndices = 0;
  for(int i = 1; i<128 && foundIndices<size; i++){
    if(super.freeBlocks[i]==0){
      blockIndices[foundIndices] = i;
      foundIndices++;
    }
  }
  if(foundIndices<size){
    printf("There is not enough room on the system for this file.\n");
    return -1;
  }

  // Step 3: Now we know we have an inode and free blocks necessary to
  // create the file. So mark the inode and blocks as used and update the rest of
  // the information in the inode.
  strcpy(super.inodes[inodeIndex].name,name);
  super.inodes[inodeIndex].size = size;
  super.inodes[inodeIndex].used = 1;
  for(int i = 0; i<size; i++){
    super.freeBlocks[blockIndices[i]] = 1;
    super.inodes[inodeIndex].blockPointers[i] = blockIndices[i]; //Holds the block number of this block
  }

  // Step 4: Write the entire super block back to disk.
  //	An easy way to do this is to seek to the beginning of the disk
  //	and write the 1KB memory chunk.
  fseek(input,0,SEEK_SET);
  fwrite(&super,sizeof(struct superBlock),1,input);
} // End Create



int delete(char name[8])
{
  // Delete the file with this name

  // Step 1: Look for an inode that is in use with given name
  // by searching the collection of objects
  // representing inodes within the super block object.
  // If it does not exist, then return an error.
  int inodeIndex = -1;
  for(int i = 0; i<16; i++){
    if(strcmp(name,super.inodes[i].name)==0){
      inodeIndex = i;
      break;
    }
  }
  if(inodeIndex==-1){
    printf("No file with name '%s' exists on the system.",name);
    return -1;
  }

  // Step 2: Free blocks of the file being deleted by updating
  // the object representing the free block list in the super block object.
  for(int i = 0; i<super.inodes[inodeIndex].size; i++){
    super.freeBlocks[super.inodes[inodeIndex].blockPointers[i]] = 0;
  }

  // Step 3: Mark inode as free.
  super.inodes[inodeIndex].used = 0;
  //Free up name
  super.inodes[inodeIndex].name[0] = "\0";

  // Step 4: Write the entire super block back to disk.
  fseek(input,0,SEEK_SET);
  fwrite(&super,sizeof(struct superBlock),1,input);

} // End Delete


int ls(void)
{ 
  // List names of all files on disk

  // Step 1: Print the name and size fields of all used inodes.
  int8_t fileExists = 0;
  for(int i = 0; i<16; i++){
    if(super.inodes[i].used==1){
      // inode in use, print info
      printf("Name: %s\tSize: %d\n",super.inodes[i].name,super.inodes[i].size);
      fileExists = 1;
    }
  }
  if(fileExists == 0){
    printf("File system empty.\n");
  }

} // End ls

int readBlock(char name[8], int blockNum, char buf[1024])
{

   // read this block from this file
   // Return an error if and when appropriate. For instance, make sure
   // blockNum does not exceed size-1.

   // Step 1: Locate the inode for this file as in Step 1 of delete.

   // Step 2: Seek to blockPointers[blockNum] and read the block
   // from disk to buf.

} // End read


int writeBlock(char name[8], int blockNum, char buf[1024])
{

   // write this block to this file
   // Return an error if and when appropriate.

   // Step 1: Locate the inode for this file as in Step 1 of delete.

   // Step 2: Seek to blockPointers[blockNum] and write buf to disk.
   
} // end write

int main(int argc, char *argv[]){
  //TODO read the commands from a file
  const char diskName;
  printf("Enter name of disk to load: ");
  scanf("%s",&diskName);
  myFileSystem(&diskName);
  create("file1",3);
  ls();
  delete("file1");
  ls();
  fclose(input);
	return 0;
}