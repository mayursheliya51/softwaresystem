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
		int choice;
		user u;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			u=login();
			if(u.type==1){
				system("clear");
				printf("**Logged in..\n\n");
				adminPanel();
			}else if(u.type==3){
				system("clear");
				printf("**Logged in..\n\n");
				dashboard(u.name);
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
