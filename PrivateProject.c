//---------------------------------------------------------------------------
// Author: Vamsi Reddy Ayyappaneni
//---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
// The class has the tools for the DNA program
struct molecule{
    char mol1;
    char mol2;
    struct molecule* next;
};typedef struct molecule molecule;
//---------------------------------------------------------------------------
// The variable helps to store the molecule information
molecule* moleculeStore[500];
// The variable acts as a counter
int count;
//---------------------------------------------------------------------------
// This is changes the structure the DNA structure
// Passed a parameter moleculeType which has the information
char Chain(char moleculeType)
{
    if (moleculeType == 'C')
    {
        return 'G';
    }
    if (moleculeType == 'T')
    {
        return 'A';
    }
    if (moleculeType == 'G')
    {
        return 'C';
    }
    if (moleculeType == 'A')
    {
        return 'T';
    }
}
//---------------------------------------------------------------------------
// This function stores the string of the array and even checks even
// Passed a parameter string which stores the information of the DNA
void CreateMolecule(char string[])
{
    int len = strlen(string);
    for (int i = 0; i < len; i++) {
        if ((string[i]!='A') && (string[i]!='G') && (string[i]!='T') && (string[i]!='C'))
        {
            printf("Invalid string\n");
            return;
        }
    }
    molecule* size = (molecule*)malloc(sizeof(molecule)); // The dynamic allocation for the memory
    molecule* store = size;
    moleculeStore[count++] = size;
    store -> mol1 = string[0];
    store -> mol2 = Chain(string[0]);
    store -> next = NULL;

    for (int i = 1; i < len; i++) {
        store -> next = (molecule*)malloc(sizeof(molecule)); // The dynamic allocation for the memory
        store = store -> next;
        store -> mol1 = string[i];
        store -> mol2 = Chain(string[i]);
    }
    store -> next = NULL;
}
//---------------------------------------------------------------------------
// The function is used to insert the molecule
// Passed a parameter molType which stores molecule ID,
// chainType which information about chain ID,
// positionToInsert is for the position of the nucleotide,
// nucleotide has the information of nucleotide.
void insert(int molType, int chainType, char nucleotide, int positionToInsert)
{
    if (molType > count){
        printf("Invalid molecule ID!!\n");
        return;
    }

    if (chainType != 1 && chainType != 2){
        printf("Invalid chain ID!!\n");
        return;
    }

    molecule* temp = moleculeStore[molType - 1];
    molecule* temp2 = (molecule*)malloc(sizeof(molecule));
    molecule* temp1 = moleculeStore[molType - 1];
    int position = 1;
    if (positionToInsert == 1)
    {
        if (chainType == 1)
        {
            temp2 -> mol1 = nucleotide;
            temp2 -> mol2 = Chain(nucleotide);
        }
        else
        {
            temp2 -> mol2 = nucleotide;
            temp2 -> mol1 = Chain(nucleotide);
        }
        temp2 -> next = temp;
        moleculeStore[molType - 1] = temp2;
        return;
    }
    while (temp != NULL)
    {
        if (position == positionToInsert - 1)
        {
            temp1 = temp;
        }

        else if (position == positionToInsert)
        {
            temp1 -> next = temp2;
            if (chainType == 1){
                temp2 -> mol1 = nucleotide;
                temp2 -> mol2 = Chain(nucleotide);
            }
            else
            {
                temp2 -> mol2 = nucleotide;
                temp2 -> mol1 = Chain(nucleotide);
            }
            temp2 -> next = temp;
            break;
        }
        temp = temp -> next;
        position++;
    }
    if(temp == NULL)
        printf("Invalid position\n");
    return;
}
//---------------------------------------------------------------------------
// The function helps the delete the molecules
// Passed a parameter molType which stores molecule ID,
// positionToDelete which helps to delete the molecule in that position
void delete(int molType, int positionToDelete)
{
    if (molType > count)
    {
        printf("Invalid molecule ID.......\n");
        exit(-1);
    }
    molecule* temp = moleculeStore[molType - 1];
    molecule* temp1 = temp;
    int position = 1;

    if (positionToDelete == 1)
    {
        if (temp -> next == NULL)
        {
            count--;
            printf("A molecule is deleted.......\n");
        }
        moleculeStore[molType - 1] = temp -> next;
    }

    while (temp != NULL) {
        if (position == positionToDelete - 1)
        {
            temp1 = temp;
        }

        else if (position == positionToDelete)
        {
            temp1 -> next = temp -> next;
            break;
        }
        temp = temp -> next;
        position++;
    }
    if (temp == NULL)
        printf("Invalid position\n");
}
//---------------------------------------------------------------------------
// This splits the structure the DNA structure
// Passed a parameter molType which has the information
void split(int molType)
{
    char string[500];
    int len=0;
    molecule* temp = moleculeStore[molType - 1];
    while (temp != NULL)
    {
        string[len++] = temp -> mol2;
        temp = temp -> next;
    }
    string[len] = '\0';
    CreateMolecule(string);
}
//---------------------------------------------------------------------------
// This prints the structure the DNA structure
// Passed a parameter molType which has the information
void PrintChain(int molType)
{
    if (molType > count){
        printf("Invalid molecule ID!!\n");
        return;
    }

    molecule* temp = moleculeStore[molType - 1];
    int count_nucleotide = 0;
    printf("\n");
    while (temp -> next!= NULL) {
        printf("%c-", temp -> mol1);
        temp = temp -> next;
        count_nucleotide++;
    }
    printf("%c", temp -> mol1);
    count_nucleotide++;

    printf("\n");

    for (int i = 0; i < count_nucleotide; i++)
        printf("| ");

    printf("\n");

    temp = moleculeStore[molType - 1];
    while(temp -> next != NULL) {
        printf("%c-", temp -> mol2);
        temp = temp -> next;
    }
    printf("%c", temp -> mol2);
    printf("\n\n");
    return;
}
//---------------------------------------------------------------------------
// Prints all the chains
void PrintAllChains()
{
    if (count == 0){
        printf("No chains to print\n");
        return;
    }

    for (int i = 1; i <= count; i++) {
        PrintChain(i);
        printf("\n");
    }
    return;
}
//---------------------------------------------------------------------------
int main() {
    printf("\n");
    printf("\tWelome to Assignment - 1\n");
    printf("\tWhich is about DNA.\n");
    printf("\n");
    // The while loop helps in running the program
    // until the user selects exit
    while(1)
    {
        // Display menu and handle menu options
        printf("Choose an Option from the menu:\n");
        printf(" 1. CreateMolecule\n 2. Insert\n 3. Delete\n 4. Split\n 5. PrintChain(Molecule ID)\n 6. PrintAllChains\n 7. Quit\n");
        int menuOption;
        printf("Your choice:");
        scanf("%d", &menuOption);

        if (menuOption == 1)
        {
            char string[100000];
            printf("Enter a string:\n");
            scanf("%s", string);

            CreateMolecule(string);
        }
        else if (menuOption == 2)
        {
            int mol_ID, chain_ID, pos;
            char nucleotide;
            printf("Enter DNA Molecule ID:\n");
            scanf("%d", &mol_ID);
            printf("Enter chain ID:\n");
            scanf("%d", &chain_ID);
            printf("Enter the position to insert nucleotide at:\n");
            scanf("%d", &pos);
            printf("Enter nucleotide to be inserted:\n");
            scanf(" %c", &nucleotide);

            insert(mol_ID, chain_ID, nucleotide, pos);

        }
        else if (menuOption == 3)
        {
            int mol_ID, pos;
            printf("Enter DNA Molecule ID:\n");
            scanf("%d", &mol_ID);
            printf("Enter the position of nucleotide to be deleted\n");
            scanf("%d", &pos);
            delete(mol_ID, pos);
        }

        else if (menuOption == 4)
        {
            int mol_ID;
            printf("Enter DNA Molecule ID:\n");
            scanf("%d", &mol_ID);
            split(mol_ID);

        }

        else if (menuOption == 5)
        {
            int mol_ID;
            printf("Enter DNA Molecule ID:\n");
            scanf("%d", &mol_ID);
            PrintChain(mol_ID);
        }

        else if (menuOption == 6)
        {
            PrintAllChains();
        }

        else if (menuOption == 7)
        {
            printf("Exiting the Program..........\n");
            exit(-1);
        }
        else
        {
            printf("Invalid option: (Please enter a valid input from 1 to 7)\n");
        }
    }
    return 0;
}
//---------------------------------------------------------------------------