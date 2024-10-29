#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user{
    char phone[50];
    char ac[50];
    char password[50];
    char homeadd[200];
    char nid[20];
    char Fathername[30];
    char mothername[30];
    char nomine[30];
    char nomineeadd[100];
    char nomineenid[20];
    char nomineemobile[20];
    float balance;
};

int main(){
    struct user usr,usr1;

    FILE *fp;
    char filename[50];
    char phone[50];
    char pword[50];

    int opt,choice;
    char cont='y';
    float amount;

    printf("\n\033[1;32mWhat do you want to do?\033[0m\n"); 
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);

    if(opt==1){
        // create new account:
        system("cls"); // Clear the screen

        printf("Enter your account number:\t");
        scanf("%s",usr.ac);
        printf("Enter your phone number:\t");
        scanf("%s",usr.phone);
        printf("Enter your new password:\t");
        scanf("%s",usr.password);
        printf("Enter your home address:\t");
        scanf("%s",usr.homeadd);
        printf("Enter your NID card number:\t");
        scanf("%s",usr.nid);
        printf("Enter your Father's name:\t");
        scanf("%s",usr.Fathername);
        printf("Enter your Mother's name:\t");
        scanf("%s",usr.mothername);
        printf("Enter your Nominee name:\t");
        scanf("%s",usr.nomine);
        printf("Enter your Nominee Address:\t");
        scanf("%s",usr.nomineeadd);
        
        printf("Enter your Nominee Phone:\t");
        scanf("%s",usr.nomineemobile);

        // initial account create korar somoy balance 0
        usr.balance=0;

        strcpy(filename,usr.phone);
        fp=fopen(strcat(filename,".txt"),"w");
        fwrite(&usr,sizeof(struct user),1,fp);
        if(fwrite!=0){ 
            printf("\n\nAccount successfully registered");
        }
        else{
            printf("\n\nSomething went wrong, Please try again");
        }
        fclose(fp);
    }
    if(opt==2){
        // Login to account
        system("cls");

        printf("\nPhone number:\t");
        scanf("%s",phone);
        printf("Password:\t");
        scanf("%s",pword);
        strcpy(filename,phone);
        fp=fopen(strcat(filename,".txt"),"r");
        if(fp==NULL)
        {
            printf("\nAccount number is not registered");
        }
        else{
            fread(&usr,sizeof(struct user),1,fp);
            fclose(fp);
            if(!strcmp(pword,usr.password)){
                //Password matched
                while(cont=='y'){
                    system("cls");
                    printf("\033[1;34m"); // set green color
                    printf("+-------------------------------------+\n");
                    printf("|              MAIN MENU              |\n");
                    printf("+-------------------------------------+\n");
                    printf("| 1. Balance Inquiry.                 |\n");
                    printf("| 2. Depositing Cash.                 |\n");
                    printf("| 3. Cash Withdrawl.                  |\n");
                    printf("| 4. Online Transfer.                 |\n");
                    printf("| 5. Password Change.                 |\n");
                    printf("+-------------------------------------+\n");
                    printf("\033[0m");
                    printf("\n\nYour choice:\t");
                    scanf(" %d",&choice);
                    
                    switch(choice){
                        case 1:
                            printf("\nYour current balance is Tk. %.2f",usr.balance);
                            break;
                        case 2:
                            printf("\nEnter the amount:\t");
                            scanf("%f",&amount);
                            usr.balance+=amount;
                            fp=fopen(filename,"w"); // Again concate .txt korte hobe na karon agei ekbar koresi
                            fwrite(&usr,sizeof(struct user),1,fp);
                            if(fwrite!=NULL) printf("\nSuccessfully deposited");
                            fclose(fp);
                            break;
                        case 3:
                            printf("\nEnter the amount:\t");
                            scanf("%f",&amount);
                            if(amount>usr.balance){
                                printf("\nInsufficient balance");
                                break;
                            } 
                            else{
                                usr.balance-=amount;
                                fp=fopen(filename,"w"); // Again concate .txt korte hobe na karon agei ekbar koresi
                                fwrite(&usr,sizeof(struct user),1,fp);
                                if(fwrite!=NULL) printf("\nYou have withdrawn Tk. %.2f",amount);
                                fclose(fp);
                                break;

                            }
                        case 4:
                            printf("\nPlease enter the phone number to transfer the balance:\t");
                            scanf("%s",phone);
                            printf("\nPlease enter the amount to transfer:\t");
                            scanf("%f",&amount);
                            if(amount>usr.balance) printf("\nInsufficient balance");
                            else{
                                strcpy(filename,phone);
                                fp=fopen(strcat(filename,".txt"),"r"); // We open this account where I send money
                               
                                fread(&usr1,sizeof(struct user),1,fp);
                                fclose(fp);
                                fp=fopen(filename,"w");
                                usr1.balance+=amount;
                                fwrite(&usr1,sizeof(struct user),1,fp);
                                fclose(fp);
                                if(fwrite!=NULL){
                                    printf("\nYou have successfully transfered Tk. %.2f to %s",amount,phone);
                                    strcpy(filename,usr.phone);
                                    fp=fopen(strcat(filename,".txt"),"w");
                                    usr.balance-=amount;
                                    fwrite(&usr,sizeof(struct user),1,fp);
                                    fclose(fp);

                                }
                            }
                        

                    }

                    printf("\n\nDo you want to continiue the transaction [y/n]");
                    scanf("%s",&cont);
                }
            }
            else{
                printf("\nInvalid password");
            }
        }

    }

    return 0;
}