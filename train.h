
typedef struct train
{
    char name[100];
    char number[20];
    int seats; //1->administrator,2->agent,3->customer
} train;

char *file1 = "railinfo";


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

void updateTrain(){
    char number[20];
    train t,t1;
    printf("Enetr train number:\n");
    scanf("%s",number);
    printf("Enetr new train number:\n");
    scanf("%s",t1.number);
    printf("Enetr new train name:\n");
    scanf("%s",t1.name);
    printf("Enetr train seats:\n");
    scanf("%d",&t1.seats);
    int fd = open(file1,O_RDWR);
    while(read(fd,&t,sizeof(t))){
        lseek(fd,-sizeof(t),SEEK_CUR);
        if(!strcmp(t.number,number)){
            write(fd,&t1,sizeof(t1));
        }else
        {
            lseek(fd,sizeof(t),SEEK_CUR);   
        }  
    }
    close(fd);
}

void deleteTrain(){
    char number[20];
    train t;
    int p = sizeof(t);
    printf("Enetr train number:\n");
    scanf("%s",number);
    int fd = open(file1,O_RDWR);
    while(read(fd,&t,sizeof(t))){
        lseek(fd,-p,SEEK_CUR);
        if(strcmp(t.number,number)){
            lseek(fd,p,SEEK_CUR);
        }else
        {
          lseek(fd,p,SEEK_CUR);
          break;
        //   if(!read(fd,&t,p)){
        //      ftruncate(fd,p); 
        //      return;
        //   }else{
        //     lseek(fd,-p,SEEK_CUR);
        //     p = 2*p;
        //     break;
        //   }  
        }   
    }
    while(read(fd,&t,sizeof(t))){
         lseek(fd,-p,SEEK_CUR);
         write(fd,&t,p);
         lseek(fd,p/2,SEEK_CUR);
    }
    ftruncate(fd,p/2);
    close(fd);
}

void adminPanel(){
    system("clear");
    printf("\n\t\t\t\t\t\tADMIN PANEL\n\n");
    train t1,t2;
    int fd = open(file1,O_CREAT|O_RDWR,0700);
    printf("\t\tTrain No\t\tTrain Name\t\t\tSeats Avai.\n");
    while(read(fd,&t1,sizeof(t1))){
        printf("\t\t%s\t\t\t%s\t\t\t\t\t%d\n",t1.number,t1.name,t1.seats);
    }

    printf("\n\n\n");
    printf("## 1 Add\n");
    printf("## 2 Update\n");
    printf("## 3 Delete\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            addTrain();
            adminPanel();
            break;
        case 2:
            updateTrain();
            adminPanel();
            break;
        case 3:
            deleteTrain();
            adminPanel();
            break;
        default:
            printf("Please Enter proper option\n");
            break;
	}
}

