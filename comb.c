#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//--------------------------------------LINKED LIST STUFF-------------------------------------

typedef struct node
{
    char varName;
    int value;
    struct node* next;
} node;

typedef void (*callback)(node* value);

/*
 create a new node
 initialize the value and next field
 return the newly created node
 */
node* create(char varName, int value,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        exit(0);
    }
    new_node->varName = varName;
    new_node->value = value;
    new_node->next = next;
    
    return new_node;
}

/*
 add a new node at the beginning of the list
 */
node* add(node* head,int value, char varName)
{
    node* new_node = create(varName,value,head);
    head = new_node;
    return head;
}

/*
 traverse the linked list
 */
void traverse(node* head,callback f)
{
    node* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}

/*
 display a node
 */
void display(node* n)
{
    if(n != NULL){
        printf("%c ", n->varName);
        printf("%d ", n->value);
    }
}

/*
 Search for a specific node with input value
 
 return the first matched node that stores the input value,
 otherwise return NULL
 */
node* searchNode(node* head,char varName)
{
    
    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->varName == varName)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}


/*
 Search for a specific named node
 
 return the input value of that variable,
 otherwise return -1
 */
int search(node* head, char varName)
{
    
    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->varName == varName)
            return cursor->value;
        cursor = cursor->next;
    }
    return -1;
}

//change the value of a variable
void revalue(node* head, char varName, int newval)
{
    
    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->varName == varName)
            cursor->value = newval;
        cursor = cursor->next;
    }
    return;
}


/*
 remove all element of the list
 */
void dispose(node *head)
{
    node *cursor, *tmp;
    
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}
//-----------------------------------------ALL THE DLD FUNCTIONS----------------------------------//

int bitAND(int value1, int value2){
    if(value1 == 1 && value2 == 1){
        return 1;
    }
    
    return 0;
}

int bitOR(int value1, int value2){
    if(value1 == 1 || value2 == 1){
        return 1;
    }
    return 0;
}

int bitNOT(int value1){
    if(value1 == 1){
        return 0;
    }
    return 1;
}

//spits out answer for inputs and one graycode combination
int bitDECODER(node* head, int numberofinputs, char *decoderinputs, int graycode[50]){
    int decoderfinalvalue = -25;
    int decodertemp;
    int decoderiterator = 0;
    for(decoderiterator=0; decoderiterator<numberofinputs; decoderiterator++){
        //if graycode character is zero, NOT the corresponding input
        if(graycode[decoderiterator]==0){
            decodertemp = bitNOT(search(head, decoderinputs[decoderiterator]));
        }
        else{
            decodertemp = search(head, decoderinputs[decoderiterator]);
        }
        //put answer into decoder value
        //if answer DNE there, just replace
        if(decoderfinalvalue==-25){
            decoderfinalvalue= decodertemp;
        }
        else{
            decoderfinalvalue = bitAND(decodertemp, decoderfinalvalue);
        }
        //otherwise, AND the two and replace
    }
    return decoderfinalvalue;
}

//change to fill array instead of printing
void graycode(int n, int graystring[50][50]){
    int r=pow(2,n);
    int a[10];
    int i;
    int k;
    int j;
    for(i=0; i<r; i++){
        k=i;
        for(j=n-1;j>=0;j--,k/=2){
            a[j]=k%2;}
        k=0;
        for(j=0;j<n;j++){
            if (k==0) {
                if (a[j]==1) {
                    k++;
                }
                //change this to put it in the array at location j
                graystring[i][j]= a[j];
            }
            
            else if(a[j]==a[j-1]){
                // append after previous character
                graystring[i][j]= 0;
            }
            else{
                graystring[i][j]= 1;
            }
        }
    }
    
}

//-----------------------------------------MAIN METHOD- INPUTVAR AND OUTPUTVAR----------------------------------//

int main(int argc, char *argv[])
{
    FILE *circuit;
    FILE *input;
    int gcodes[50][50];
    char outputs[100] = "";
    int outputIterator = 0;
    //circuit = fopen(argv[1], "r");
    //input = fopen(argv[2], "r");
    circuit = fopen("circuit.txt", "r");
    input = fopen("input.txt", "r");
    int numVar = 0;
    int LLexists = 0;
    int CHECKINPUTREAD =0;
    
    
    char circuitReader[100], inputReader[100];
    char *circuitToken, *inputToken = NULL;
    char *saveCircuitPTR, *saveInputPTR = NULL;
    
    //set up parameters to read files
    const char delimiter[2]= " ";
    
    //loops through input.txt until all the inputs have been considered
    do {
        memset(&outputs[0], 0, sizeof(outputs));
        memset(&inputReader[0], 0, sizeof(inputReader));
        fgets(inputReader, 100, input);
        if(inputReader[0] == '\n'){
            break;
        }
        if(inputReader[0] == '\0'){
            break;
        }
        node* head = NULL;
        
        //loops through circuit.txt to execute operations
        
        
        //get first line of both files
        memset(&circuitReader[0], 0, sizeof(circuitReader));
        fgets(circuitReader, 100, circuit);
        
        
        //read "INPUTVAR"
        circuitToken = strtok_r(circuitReader, delimiter, &saveCircuitPTR);
        
        if(strcmp (circuitToken,"INPUTVAR") == 0){
            circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
            numVar = atoi(&circuitToken[0]);
            circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
            inputToken = strtok_r(inputReader, delimiter, &saveInputPTR);
        }
        
        //create a new linked list for the circuit elements.
        int i;
        
        
        if(CHECKINPUTREAD == 0){
            
            
            for (i = 0; i < numVar; i++){
                CHECKINPUTREAD=1;
                //if head equals null, then fill that in with the first variable's data
                if(LLexists == 0){
                    //make the value = the value in input file
                    //make the varname = name of variable
                    //make the next node = NULL
                    
                    //fscanf(circuit, " %c ", &tempvarname);
                    //fscanf(input, "%d", &tempvalue);
                    
                    if (inputToken== NULL) {
                        break;
                    }
                    
                    head = create(circuitToken[0], atoi(&inputToken[0]), NULL);
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                    inputToken = strtok_r(NULL, delimiter, &saveInputPTR);
                    if(circuitToken==NULL){
                        break;
                    }
                    LLexists = 1;
                    
                }
                //else, put in the next variable's data into a new node and put it at front, making it the new head
                //use add(node* head,int value, char varName)
                else{
                    head = add(head, atoi(&inputToken[0]), circuitToken[0]);
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                    inputToken = strtok_r(NULL, delimiter, &saveInputPTR);
                    if(circuitToken==NULL){
                        break;
                    }
                }
            }
        }
        //-----------finished reading inputvar and storing in linked list
        
        
        
        //-------OUTPUTVAR FUNCTION-----------//
        
        while(!feof(circuit)){
            memset(&circuitReader[0], 0, sizeof(circuitReader));
            fgets(circuitReader, 100, circuit);
            circuitToken = strtok_r(circuitReader, delimiter, &saveCircuitPTR);
            
            if (circuitToken==NULL) {
                break;
            }
            
            if(strcmp (circuitToken,"OUTPUTVAR") == 0){
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                while(circuitToken != NULL){
                    outputs[outputIterator] = circuitToken[0];
                    outputIterator++;
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                }
                memset(&circuitReader[0], 0, sizeof(circuitReader));
                fgets(circuitReader, 100, circuit);
                circuitToken = strtok_r(circuitReader, delimiter, &saveCircuitPTR);
            }
            
            
            //-------NOT FUNCTION-----------//
            
            if(strcmp (circuitToken,"NOT") == 0){
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char notvar1 = circuitToken[0];
                if(search(head, notvar1) == -1){
                    head = add(head, -1, notvar1);
                }
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char notvar2 = circuitToken[0];
                if(search(head, notvar2) == -1){
                    head = add(head, -1, notvar2);
                }
                int notvar1value;
                int notanswer;
                //search for their values in the linked list
                notvar1value = search(head, notvar1);
                notanswer = bitNOT(notvar1value);
                //printf("notvar1value: %d notanswer: %d\n",notvar1value,notanswer);
                revalue(head, notvar2, notanswer);
            }
            
            //-------OR FUNCTION-----------//
            
            else if(strcmp (circuitToken,"OR") == 0){
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char orvar1 = circuitToken[0];
                if(search(head, orvar1) == -1){
                    head = add(head, -1, orvar1);
                }
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char orvar2 = circuitToken[0];
                if(search(head, orvar2) == -1){
                    head = add(head, -1, orvar2);
                }
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char orvar3 = circuitToken[0];
                if(search(head, orvar3) == -1){
                    head = add(head, -1, orvar3);
                }
                int orvar1value, orvar2value;
                int oranswer;
                //search for their values in the linked list
                orvar1value = search(head, orvar1);
                orvar2value = search(head, orvar2);
                oranswer = bitOR(orvar1value, orvar2value);
                //printf("orvar1value: %d orvar2value: %d oranswer: %d\n",orvar1value, orvar2value, oranswer);
                revalue(head, orvar3, oranswer);
                
            }
            
            //-------AND FUNCTION-----------//
            
            else if(strcmp (circuitToken,"AND") == 0){
                //read in the variables that need to be used
                
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char andvar1 = circuitToken[0];
                if(search(head, andvar1) == -1){
                    head = add(head, -1, andvar1);
                }
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char andvar2 = circuitToken[0];
                if(search(head, andvar2) == -1){
                    head = add(head, -1, andvar2);
                }
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char andvar3 = circuitToken[0];
                if(search(head, andvar3) == -1){
                    head = add(head, -1, andvar3);
                }
                int andvar1value, andvar2value;
                int andanswer;
                //search fand their values in the linked list
                andvar1value = search(head, andvar1);
                andvar2value = search(head, andvar2);
                andanswer = bitAND(andvar1value, andvar2value);
                //printf("andvar1value: %d andvar2value: %d andanswer: %d\n",andvar1value, andvar2value, andanswer);
                revalue(head, andvar3, andanswer);
            }
            
            //-------MULTIPLEXER FUNCTION-----------//
            
            else if(strcmp (circuitToken,"MULTIPLEXER") == 0){
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                int muxInputNumber = atoi(&circuitToken[0]);
                //read same number of inputs as decinputnumber
                
                char muxInputs[100];
                memset(&muxInputs[0], 0, sizeof(muxInputs));
                int muxinputiterator = 0;
                for (muxinputiterator=0; muxinputiterator<muxInputNumber; muxinputiterator++) {
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                    muxInputs[muxinputiterator]= circuitToken[0];
                }
                
                int muxSelectorIterator=0;
                
                
                //y = pow (x, 1.0 / 5);
                //x = pow(y, 5);
                
                int muxSelectorNumber= (int)log2(muxInputNumber*1.0);
                
                //fill in 2^n Selectors
                char muxSelectors[100];
                memset(&muxSelectors[0], 0, sizeof(muxSelectors));
                for (muxSelectorIterator=0; muxSelectorIterator<muxSelectorNumber; muxSelectorIterator++) {
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                    muxSelectors[muxSelectorIterator]= circuitToken[0];
                    
                    
                }
                memset(&gcodes[0], 0, sizeof(gcodes));
                graycode(muxSelectorNumber, gcodes);
                //get the Selector value
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                char muxOutput= circuitToken[0];
                
                //the character array we're looking for
                int muxSelectorCodes[10];
                memset(&muxSelectorCodes[0], 0, sizeof(muxSelectorCodes));
                for (muxSelectorIterator=0; muxSelectorIterator<muxSelectorNumber; muxSelectorIterator++) {
                    muxSelectorCodes[muxSelectorIterator]=search(head, muxSelectors[muxSelectorIterator]);
                }
                
                //to find the output,search through the gray codes to see which number gray code it is
                int muxOutputEntry = 0;
                int muxrow;
                for (muxrow=0; muxrow<muxInputNumber; muxrow++) {
                    if (memcmp(muxSelectorCodes, gcodes[muxrow], 4*muxSelectorNumber)==0)
                    {
                        muxOutputEntry=muxrow;
                    }
                    
                }
                
                char muxFinalValue = muxInputs[muxOutputEntry];
                //muxOutput needs to equal this value;
                
                //if the input is a number, output equals the number
                if (isdigit(muxFinalValue)) {
                    if(search(head, muxOutput) == -1){
                        head = add(head, atoi(&muxFinalValue), muxOutput);
                    }
                    else{
                        revalue(head, muxOutput, atoi(&muxFinalValue));
                    }
                    
                }
                else{
                    //if the input is a variable, output equals the searched value of that variable
                    if(search(head, muxOutput) == -1){
                        head = add(head, search(head, muxFinalValue), muxOutput);
                    }
                    else{
                        revalue(head, muxOutput, search(head, atoi(&muxFinalValue)));
                    }
                    
                }
                
                
                
            }
            
            
            //-------DECODER FUNCTION-----------//
            //int bitDECODER(node* head, int numberofinputs, char *decoderinputs, char graycode[]){
            
            
            else if(strcmp (circuitToken,"DECODER") == 0){
                circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                int decInputNumber = atoi(&circuitToken[0]);
                memset(&gcodes[0], 0, sizeof(gcodes));
                graycode(decInputNumber, gcodes);
                //read same number of inputs as decinputnumber
                char decoderInputs[100];
                memset(&decoderInputs[0], 0, sizeof(decoderInputs));
                int decinputiterator = 0;
                for (decinputiterator=0; decinputiterator<decInputNumber; decinputiterator++) {
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                    decoderInputs[decinputiterator]= circuitToken[0];
                }
                int decoderOutputIterator=0;
                
                //fill in 2^n outputs
                char decoderOutputs[100];
                for (decoderOutputIterator=0; decoderOutputIterator<(int)pow(2,decInputNumber); decoderOutputIterator++) {
                    circuitToken = strtok_r(NULL, delimiter, &saveCircuitPTR);
                    decoderOutputs[decoderOutputIterator]= circuitToken[0];
                }
                
                //for 2^n outputs, use a for loop and put them into the LL if they dont exist, and then
                // output= bitDECODER(head,decInputNumber, decoderInputs, gcodes[decoderOutputIterator]);
                for (decoderOutputIterator=0; decoderOutputIterator<(int)pow(2,decInputNumber); decoderOutputIterator++) {
                    int tempdecodervalue;
                    tempdecodervalue = bitDECODER(head,decInputNumber, decoderInputs, gcodes[decoderOutputIterator]);
                    if(search(head, decoderOutputs[decoderOutputIterator]) == -1){
                        head = add(head, tempdecodervalue, decoderOutputs[decoderOutputIterator]);
                    }
                    else{
                        revalue(head, decoderOutputs[decoderOutputIterator], tempdecodervalue);
                    }
                    
                }
                
                
                
            }
            
            //-----------------------------------------------------------------
            
            
            if(feof(circuit)){
                break;
            }
            
            
            
            
        }
        //end of circuit while loop
        
        //print out outputs
        int finalPrintIterator =0;
        for (finalPrintIterator=0; finalPrintIterator<outputIterator; finalPrintIterator++) {
            printf("%d",search(head,outputs[finalPrintIterator]));
            if (finalPrintIterator != outputIterator-1) {
                printf("%c",' ');
            }
            if (finalPrintIterator == outputIterator-1) {
                printf("\n");
            }
            
        }
        outputIterator = 0;
        
        //deletes linked list so we can make a new one for new input values.
        dispose(head);
        LLexists = 0;
        CHECKINPUTREAD=0;
        
        if(feof(input)){
            break;
        }
        else{
            fclose(circuit);
            circuit = fopen("circuit.txt", "r");
            //circuit = fopen(argv[1], "r");
        }
        
    } while(!feof(input));
    fclose(circuit);
    fclose(input);
    return 0;
}



