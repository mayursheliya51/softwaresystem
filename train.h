typedef struct train
{
    char name[100];
    char number[20];
    int seats; //1->administrator,2->agent,3->customer
} train;

typedef struct bookingInfo
{
    char userId[100];
    char tno[20];
} bookingInfo;

char *file1 = "railinfo";
char *file_book = "bookinginfo";
char *tmp ="tmp";
int norm_user = 1;
int admin = 0;


user getUserById(char*);

int isTrainExist(char number[])
{
    int fd = open(file1, O_RDWR); //write(fd,&t,sizeof(t));
    train t;
    if (fd > 0)
    {
        while (read(fd, &t, sizeof(t)))
        {
            if (!strcmp(t.number, number))
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

void addTrain()
{
    train t;
    int fd = open(file1, O_CREAT | O_RDWR, 0700);
    printf("Enter train name:\n");
    scanf("%s",t.name);
    printf("Enter train number:\n");
    scanf("%s",t.number);
    getchar();
    printf("Enter seats:\n");
    scanf("%d", &t.seats);
    lseek(fd, 0L, SEEK_END);
    if (isTrainExist(t.number))
    {
        printf("**Train Exist....\n");
    }
    else
    {
        if (write(fd, &t, sizeof(t)))
        {
            printf("\n**Train Added successfully..\n");
        }
        else
            printf("**Problem while adding train!\n");
    }
    close(fd);
}

void updateTrain(char *number,int usr,int val){
    train t,t1;
    int fd = open(file1,O_RDWR);
    if(usr == admin){
        printf("Enetr new train number:\n");
        scanf("%s",t1.number);
        printf("Enetr new train name:\n");
        scanf("%s",t1.name);
        printf("Enetr train seats:\n");
        scanf("%d",&t1.seats);
        while(read(fd,&t,sizeof(t))){
            lseek(fd,-sizeof(t),SEEK_CUR);
            if(!strcmp(t.number,number)){
                write(fd,&t1,sizeof(t1));
            }else
            {
                lseek(fd,sizeof(t),SEEK_CUR);   
            }  
    }
    }else{
        while(read(fd,&t,sizeof(t))){
            lseek(fd,-sizeof(t),SEEK_CUR);
            if(!strcmp(t.number,number)){
                t.seats+=val;
                write(fd,&t,sizeof(t));
            }else
            {
                lseek(fd,sizeof(t),SEEK_CUR);   
            }  
        }
    }
    
    close(fd);
}

train getTrainById(char* tno){
    int fd = open(file1, O_RDWR); //write(fd,&t,sizeof(t));
    train t;
    if (fd > 0)
    {
        while (read(fd, &t, sizeof(t)))
        {
            if (!strcmp(t.number, tno))
            {
                close(fd);
                return t;
            }
        }
    }
}

void deleteTrain(){
    char number[20];
    train t;
    int p = sizeof(t);
    printf("Enetr train number:\n");
    scanf("%s",number);
    int fd = open(file1,O_RDWR);
    int tmpFd = open("tmp",O_CREAT|O_RDWR,0700);
    while(read(fd,&t,sizeof(t))){
        lseek(fd,-p,SEEK_CUR);
        if(strcmp(t.number,number)){
            write(tmpFd,&t,sizeof(t));
            lseek(fd,p,SEEK_CUR);
        }else
        {
           lseek(fd,p,SEEK_CUR);
        }   
    }
    remove(file1);
    rename(tmp,file1);
    close(fd);
    close(tmpFd);
}

void addBookingInfo(char* tno,char* userId){
    int fd = open(file_book, O_CREAT | O_RDWR, 0700);
    bookingInfo b;
    strcpy(b.userId,userId);
    strcpy(b.tno ,tno);
    lseek(fd,0,SEEK_END);
    if(write(fd,&b,sizeof(b))){
        user u = getUserById(userId);
        train t = getTrainById(tno);
        printf("\n\nBooking Successfull...\n");
        printf("Below is your booking details\n");
        printf("Pessenger name:%s\n",u.name);
        printf("Train name:%s\n",t.name);
        printf("Train number:%s\n",t.number);

    }

}

void trainList(){
    train t1,t2;
    int fd = open(file1,O_CREAT|O_RDWR,0700);
    printf("\t\tTrain No\t\tTrain Name\t\t\tSeats Avai.\n");
    while(read(fd,&t1,sizeof(t1))){
        printf("\t\t%s\t\t\t%s\t\t\t\t\t%d\n",t1.number,t1.name,t1.seats);
    }
}

void bookTicket(char *userId){
    trainList();
    printf("\nEnter train number to book ticket:\n");
    char tno[20];
    scanf("%s",tno);
    if(isTrainExist(tno)){
        updateTrain(tno,norm_user,-1);
        addBookingInfo(tno,userId);
    }else{
        printf("Train does not exist..\n");
    }
}

void viewPreBookings(char *userId){
    bookingInfo b;
    train t;
    int fd = open(file_book,O_RDONLY);
    printf("\t\tTrain No\t\tTrain Name\n");
    while(read(fd,&b,sizeof(b))){
        if(!strcmp(b.userId, userId)){
            t= getTrainById(b.tno);
            printf("\t\t%s\t\t\t%s\n",t.number,t.name);
        }
    }
}


void cancleBookings(char *userId){
    printf("\n Previous bookings by %s\n",userId);
    viewPreBookings(userId);
    char tno[20];
    printf("Enter train no to cancel booking \n ");
    scanf("%s",tno);
    int fd = open(file_book, O_RDWR);
    int tmpFd = open("tmp",O_CREAT|O_RDWR,0700);
    bookingInfo b;
    int p = sizeof(b);
    while(read(fd,&b,sizeof(b))){
        lseek(fd,-p,SEEK_CUR);
        if(!strcmp(b.tno,tno) && !strcmp(b.userId,userId)){
            lseek(fd,p,SEEK_CUR);
        }else
        {
            write(tmpFd,&b,sizeof(b));
            lseek(fd,p,SEEK_CUR);
        }   
    }
    remove(file_book);
    rename(tmp,file_book);
    close(fd);
    close(tmpFd);
    updateTrain(tno,norm_user,1);
}

void adminPanel(){
    system("clear");
    printf("\n\t\t\t\t\t\tADMIN PANEL\n\n");
    trainList();
    printf("\n\n\n");
    printf("## 1 Add\n");
    printf("## 2 Update\n");
    printf("## 3 Delete\n");
    printf("## 4 Exit\n");
    int choice;
    char *tno;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            addTrain();
            adminPanel();
            break;
        case 2:
            printf("Enetr train number:\n");
            scanf("%s",tno);
            updateTrain(tno,admin,0);
            adminPanel();
            break;
        case 3:
            deleteTrain();
            adminPanel();
            break;
        case 4:
            return;
        default:
            printf("Please Enter proper option\n");
            break;
	}
}

