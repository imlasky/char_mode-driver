#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
#define BUFFER_LENGTH 1050               ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM
 
int main(){
	int ret, fd, readLength;
	char stringToSend[BUFFER_LENGTH];
	printf("Starting device test code example...\n");
	fd = open("/dev/testdev", O_RDWR);             // Open the device with read/write access
	if (fd < 0){
		perror("Failed to open the device...");
		return errno;
	}
	
	int selection = 0; 
	int len; // length of input to kernel module 
	do 
	{
	    printf("Enter a number to make a selection\n");  
	    printf("1- Send/write string to kernel module\n");
	    printf("2- Read string from kernel module\n"); 
	    printf("0- Exit program\n"); 
	    scanf("%d%*c", &selection); 
	    if (selection == 1)
	    {
		printf("Type in a short string to send to the kernel module:\n");
		//scanf("%[^\n]*c", stringToSend);                // Read in a string (with spaces)
		fgets(stringToSend, sizeof stringToSend, stdin);
		len = strlen(stringToSend);
		if (len > 0 && stringToSend[len-1] == '\n')
		    stringToSend[--len] = '\0'; // remove trailing new line character 
		printf("Writing message to the device [%s].\n", stringToSend);
		ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
		if (ret < 0){
			perror("Failed to write the message to the device.");
			return errno;
		}
	    }
	    else if(selection == 2)
	    {
		printf("How many bytes would you like to read back?\n");
		scanf("%d%*c",&readLength);
		if(readLength > BUFFER_LENGTH)
		{
			readLength = BUFFER_LENGTH;
		}
		printf("Reading from the device...\n");
		ret = read(fd, receive, readLength);        // Read the response from the LKM
		if (ret < 0){
			perror("Failed to read the message from the device.");
			return errno;
		}
		printf("The received message is: [%s]\n", receive);
	    }
	    else
	    {
		selection = 0; 
	    }
	} while (selection > 0);

	printf("End of the program\n");
	return 0;
}
