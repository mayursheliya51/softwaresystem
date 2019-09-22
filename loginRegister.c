#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "train.h"

int main()
{
	while(1){
		system("clear");
		printf("\n\t\t\tWELCOME TO RAILWAY TICKET RESERVATION SYSTEM\n");
		printf("Please choose one option below\n");
		printf("# Press 1 for Login\n");
		printf("# Press 2 for Register\n");
		int choice,l;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			l=login();
			if(l==1){
				system("clear");
				printf("**Logged in..\n\n");
				adminPanel();
			}else if(l==3){
				system("clear");
				printf("**Logged in..\n\n");
				dashboard();
			}
			break;
		case 2:
			regUser();
			break;
		default:
			printf("Please Enter proper option\n");
			break;
		}
	}
}
