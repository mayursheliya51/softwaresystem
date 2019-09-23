char *file = "userinfo";

typedef struct user
{
    char name[20];
    char pass[20];
    int type; //1->administrator,2->agent,3->customer
} user;

char* userId;

int isUserExist(char*);
void regUser();
void adminPanel();
void bookTicket(char*);
user login();
void viewPreBookings(char*);
void cancleBookings(char *);

int isUserExist(char name[])
{
    int fd = open(file, O_RDWR);
    user u2;
    if (fd > 0)
    {
        while (read(fd, &u2, sizeof(u2)))
        {
            if (!strcmp(u2.name, name))
            {
                close(fd);
                return 1;
            }
        }
        return 0;
    }
    else
    {
        printf("Error occured while reading file\n");
        return 0;
    }
}

user getUserById(char *userId){
    int fd = open(file, O_RDWR);
    user u2;
    if (fd > 0)
    {
        while (read(fd, &u2, sizeof(u2)))
        {
            if (!strcmp(u2.name, userId))
            {
                close(fd);
                return u2;
            }
        }
    }
   
}

void regUser()
{
    user u;
    int fd = open(file, O_CREAT | O_RDWR, 0700);
    printf("Enter username:\n");
    scanf("%s", u.name);
    printf("Enter password:\n");
    scanf("%s", u.pass);
    printf("Enter user type(Press 2 for agent,Press 3 for customer):\n");
    scanf("%d", &u.type);
    if(u.type !=2 && u.type!=3){
        printf("**Invalid input\n");
        return; 
    }
    lseek(fd, 0L, SEEK_END);
    if (isUserExist(u.name))
    {
        printf("**User Exist....\n");
    }
    else
    {
        if (write(fd, &u, sizeof(u)))
        {
            printf("\n**Registration done successfully..\n");
        }
        else
            printf("**Problem while registering!\n");
    }
    close(fd);
}


user login()
{
    user u1, u2;
    printf("Enter username:\n");
    scanf("%s", u1.name);
    printf("Enter password:\n");
    scanf("%s", u1.pass);
    int fd = open(file, O_RDWR);
    if (fd > 0)
    {
        while (read(fd, &u2, sizeof(u2)))
        {
            if (!strcmp(u2.name, u1.name) && !(strcmp(u2.pass, u1.pass)))
            {
                close(fd);
                return u2;
            }
        }
        printf("**Invalid username or password\n");
    }
    else
    {
        printf("**Error occured while readin file\n");
    }
    close(fd);
}



void updateBooking(){

}


void dashboard(char *userId){
    printf("## 1 Book Ticket\n");
    printf("## 2 View Previous Bookings\n");
    printf("## 3 Cancel Booking\n");
    printf("## 4 Exit\n");
    int choice;
	while(1){
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
            bookTicket(userId);
			break;
		case 2:
			viewPreBookings(userId);
			break;
        case 3:
			cancleBookings(userId);
			break;
        case 4:
			return;
		default:
			printf("Please Enter proper option\n");
			break;
		}
	}
}