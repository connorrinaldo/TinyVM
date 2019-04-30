//Connor Rinaldo

#include <stdio.h>
#include <stdlib.h>

typedef struct {
		int opCode;
    int Address;
	} Instruction;

void linePrint(int pc, int ac, int *dm){//Prints the current state
	printf("PC = %d | AC = %d | DM = [", pc, ac);
	for(int i = 0; i < 9; i++){
		printf("%d, ", dm[i]);
		}
	printf("%d]\n\n", dm[9]);//Makes it look nice
}

int main(int argc, char *argv[])
{
FILE *file;
int i = 0;

Instruction *IR = malloc(sizeof(Instruction));
Instruction *MDR1 = malloc(sizeof(Instruction));
Instruction *IM = malloc(sizeof(Instruction)*100);

int *DM = calloc(10, sizeof(int));
int MDR2 = 0;
int MAR1 = 0;
int MAR2 = 0;
int AC = NULL;
int PC = 0;
int run = 1;

file=fopen(argv[1],"r");

//this while loop is to read your file line by line until it reaches the file end
//fscanf( your file variable, your target text, the variables that will get the text)
printf("Assembling Program...\nProgram Assembled.\n\nRun.\n");

linePrint(PC, AC, DM);

while (fscanf(file, "%d %d",&IM[i].opCode, &IM[i].Address) != EOF && run == 1)
{
	MAR1 = PC;//Fetch
	MDR1[0] = IM[MAR1];
	PC++;
	IR = MDR1;

    switch(IM[i].opCode){
      case 1:
        MAR2 = IM[i].Address;
        MDR2 = DM[MAR2];
        AC = MDR2;
				printf("/* loading from memory loaction %d */\n", MAR2);
				linePrint(PC, AC, DM);
        break;
      case 2:
        MAR2 = IM[i].Address;
        MDR2 = DM[MAR2];
        AC = AC + MDR2;
				printf("/* adding accumulator and memory location %d */\n", MAR2);
				linePrint(PC, AC, DM);
        break;
      case 3:
        MAR2 = IM[i].Address;
        MDR2 = AC;
        DM[MAR2] = MDR2;
				printf("/* storing accumulator to memory location %d */\n", MAR2);
				linePrint(PC, AC, DM);
        break;
      case 4:
        MAR2 = IM[i].Address;
        MDR2 = DM[MAR2];
        AC = AC - MDR2;
				printf("/* subtracting accumulator and memory location %d */\n", MAR2);
				linePrint(PC, AC, DM);
        break;
      case 5:
				printf("/* input value */\n");
        scanf("%d", &AC);
				linePrint(PC, AC, DM);
        break;
      case 6:
        printf("/* outputting accumulator to screen */\n%d\n", AC);
				linePrint(PC, AC, DM);
        break;
      case 7:
        run = 0;
				printf("/* Program Complete, last state */\n");
				linePrint(PC, AC, DM);
        break;
      case 8://Clsoes the file and reopens it to the jump line
      	PC = IM[i].Address;
				printf("/* jumping to line %d */\n", PC);
				fclose(file);
				file=fopen(argv[1],"r");
				for(int i = 0; i < PC; i++)//Goes to the new line
					fscanf(file, "%d %d",&IM[i].opCode, &IM[i].Address) != EOF;
				linePrint(PC, AC, DM);
        break;
      case 9:
        if(AC == 0){
					printf("/* skipping next line */\n");+
					fscanf(file, "%d %d",&IM[i].opCode, &IM[i].Address) != EOF;//Skips a single line
					linePrint(PC, AC, DM);
				}
        break;
    }
   i++;
}
fclose(file);
}
