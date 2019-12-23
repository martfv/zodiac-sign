#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct login_page {
    char nickname[20];
    char password[20];
};

struct new_user{
    char username[20];
    char password[20];
};

void comments(){
    char line[1000];
    char comments[12][9999];
    
    FILE *fComments = fopen("comments.txt", "r");
    
    int i = 0;
    while (fgets(line, sizeof(line), fComments)) {
        char *sign = strtok(line, "!");
        strcpy(comments[i], strtok(NULL, "!"));
        i++;
    }
    fclose(fComments);
    
    printf("Your comment: %s", comments[rand() % 11]);
}

void lucky_number() {
    char line[128];
    int numbers[100];
    int i = 0;
    
    FILE *fNumbers = fopen("lucky_numbers.txt", "r");
    
    while (fgets(line, sizeof(line), fNumbers)) {
        numbers[i] = atoi(line);
        i++;
    }
    
    fclose(fNumbers);
    
    printf("Your lucky number: %i", numbers[rand() % 100]);
}

void lucky_color() {
    char line[128];
    char colors[75][128];
    int i = 0;
    
    FILE *fColors = fopen("colors.txt", "r");
    
    while (fgets(line, sizeof(line), fColors)){
        strcpy(colors[i], line);
        i++;
    }
    
    fclose(fColors);

    printf("Your lucky color: %s", colors[rand() % 75]);
}

void sign_tree(){
    int d, m;
    
    printf("Enter date (1-31): ");
    scanf("%d", &d);
    
    printf("Enter month (1-12): ");
    scanf("%d", &m);
    
    if((m==12&&d>=22)||(m==1&&d<=19))
        printf("\nYour Zodiac Sign is Capricorn.\n");
    else if((m==1&&d>=20)||(m==2&&d<=17))
        printf("\nYour Zodiac Sign is Aquarius.\n");
    else if((m==2&&d>=18)||(m==3&&d<=19))
        printf("\nYour Zodiac Sign is Pisces.\n");
    else if((m==3&&d>=20)||(m==4&&d<=19))
        printf("\nYour Zodiac Sign is Aries.\n");
    else if((m==4&&d>=20)||(m==5&&d<=20))
        printf("\nYour Zodiac Sign is Taurus.\n");
    else if((m==5&&d>=21)||(m==6&&d<=20))
        printf("\nYour Zodiac Sign is Gemini.\n");
    else if((m==6&&d>=21)||(m==7&&d<=22))
        printf("\nYour Zodiac Sign is Cancer.\n");
    else if((m==7&&d>=23)||(m==8&&d<=22))
        printf("\nYour Zodiac Sign is Leo.\n");
    else if((m==8&&d>=23)||(m==9&&d<=22))
        printf("\nYour Zodiac Sign is Virgo.\n");
    else if((m==9&&d>=23)||(m==10&&d<=22))
        printf("\nYour Zodiac Sign is Libra.\n");
    else if((m==10&&d>=23)||(m==11&&d<=21))
        printf("\nYour Zodiac Sign is Scorpio.\n");
    else if((m==11&&d>=20)||(m==12&&d<=17))
        printf("\nYour Zodiac Sign is Sagittarius.\n");
    else
        printf("\nYou Typed Wrongly.\n");
    
}

void main_menu(){
    int selection;
    
    do {
        printf("\n");
        printf("1) Zodiac Sign of Yours\n");
        printf("2) Lucky Color of The Day\n");
        printf("3) Lucky Number of Your Sign\n");
        printf("4) Personality Traits of Your Zodiac Sign\n");
        printf("Which feature do you want to choose: ");
        
        do {
            scanf("%i", &selection);
        } while( selection == '\n' );
        
        switch (selection) {
            case 1:
                sign_tree();
                break;
            case 2:
                lucky_color();
                break;
            case 3:
                lucky_number();
                break;
            case 4:
                comments();
                break;
                
            default:
                printf("Write something between 1 and 4. \n");
                break;
        }
    } while(selection >= 1 && selection <= 4);
}

int authenticate(struct login_page *user) {
    FILE *ptr = fopen("users.txt", "r");
    char line[1000];
    
    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        char *fUsername = strtok(line, ",");
        char *fPassword = strtok(NULL, ",\n");
        
        if(strcmp(user->nickname, fUsername) == 0 && strcmp(user->password, fPassword) == 0) {
            return 1;
            break;
        }
    }
    
    fclose(ptr);
    
    return 0;
}

void login_page(){
    struct login_page *user = (struct login_page*)malloc(sizeof(struct login_page));
    
    printf("Please enter your nickname: ");
    scanf("%s", user ->nickname);
    
    printf("Please enter your password: ");
    scanf("%s", user ->password);
    
    int result = authenticate(user);
    
    if (result > 0) {
        printf("Welcome %s!", user->nickname);
        main_menu();
    }
    else {
        printf("No user found. \n");
    }
}

void createUser() {
    struct new_user *new = (struct new_user *)malloc(sizeof(struct new_user));
    
    
    printf("username: ");
    scanf("%s", new->username);
    printf("password: ");
    scanf("%s", new ->password);
    
    FILE *user = fopen("users.txt", "a");

    fprintf(user, "%s,%s\n", new->username, new->password);
    
    fclose(user);
    
    printf("Your account has been created. You can use your credentials above. \n");
    
    login_page();
}

int main(){
    srand(getpid());
    
    int op;
    
    printf("\t\t\t\tWELCOME TO ZODIAC SIGN FINDER\n\n");
    printf("1)LOG IN\n");
    printf("2)NEW USER (Create an account)\n");
    printf("Please make your decision: ");
    scanf("%d", &op);
    
    switch (op) {
        case 1:
            login_page();
            break;
        case 2:
            createUser();
            break;
    }
    
    return 0;
}
