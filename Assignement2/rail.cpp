#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<math.h> 
#define key 3 

char* encryptedMessage(char*); 
char* decryptedMessage(char*); 
char *cipher; 
int main() 
{ 
	FILE *fp; 
	fp= fopen("rail_input.txt","r"); 
	FILE *fpOut; 
	fpOut = fopen("rail_output.txt", "w"); 
	if(!fpOut || !fp) 
	{ 
		printf("File does not exist"); 
		exit(0); 
	} 
	char partOfLine[128];
	size_t len = sizeof(partOfLine); 
	char *line = (char *)malloc(len); 
	line[0] = '\0'; 
	while(fgets(partOfLine, sizeof(partOfLine), fp) != NULL)  { 
		size_t len_used = strlen(line); 
		size_t chunk_used = strlen(partOfLine); 
		if(len - len_used < chunk_used)  
		{ 
			len *= 2; 
			if((line = (char *)realloc(line, len)) == NULL) 
			{ 
				perror("Unable to reallocate memory for the line buffer."); 
				free(line); 
				exit(1); 
			} 
		} 
		strncpy(line + len_used, partOfLine, len - len_used); 
		len_used += chunk_used; 
		if(line[len_used - 1] == '\n')  
		{ 
			char *message = (char*)malloc(len_used+1); 
			printf("Plain text message-> "); 
			puts(line); 
			message = encryptedMessage(line);
			fputs(message, fpOut); 
			message = decryptedMessage(message); 
			fputs(message, fpOut); 
		} 
	} 
	fclose(fp); 
	free(line); 
} 

char* encryptedMessage(char *msg){
    int msgLen = strlen(msg), i, j, k = -1, row = 0, col = 0;
    char *encrypt =(char*)malloc(strlen(msg)+1);
    
    char railMatrix[key][msgLen];
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < msgLen; ++i){
        railMatrix[row][col++] = msg[i];
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
 	
    printf("\nEncrypted Message: ");
 	int m = 0;
    for(i = 0; i < key; ++i){
        for(j = 0; j < msgLen; ++j){
        	if(railMatrix[i][j] != '\n'){
            	printf("%c", railMatrix[i][j]);
            	if(railMatrix[i][j] != '*'){
            		encrypt[m] = railMatrix[i][j];
            		m += 1;
				}
			}
		}
	}
	encrypt[m] = '\0';
	return encrypt;	              
}
 
char* decryptedMessage(char* msg){
    int msgLen = strlen(msg), i, j, k = -1, row = 0, col = 0, m = 0;
    char *decrypt =(char*)malloc(strlen(msg)+1);
    
    char railMatrix[key][msgLen];
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < msgLen; ++i){
        railMatrix[row][col++] = '*';
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < msgLen; ++j)
            if(railMatrix[i][j] == '*'){
            	railMatrix[i][j] = msg[m++];
			}
                
 
    row = col = 0;
    k = -1;
 	m = 0;
    printf("\nDecrypted Message: ");
 
    for(i = 0; i < msgLen; ++i){
    	msg[m] = railMatrix[row][col];
    	m += 1;
        printf("%c", railMatrix[row][col]);
 		col += 1;
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
    decrypt[m] = '\0';
 	return decrypt;
}
 
