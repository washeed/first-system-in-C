#include<stdio.h> /// input and output
#include<string.h> /// string operations
#include<stdlib.h> /// Standard Library
#include<windows.h> /// I use this for positions of Coordinate X and Y
#include<conio.h> ///to run getche();

struct student{ ///Structured Variables for Data of the Student
    char stud_No[15], fname[50], sname[50]; ///string type data
    float grade1, grade2, grade3, grade4; ///float type for grades
};
struct student s; ///Pointer for struct student is letter "s"

///GLOBAL DECLARATIONS
FILE *fprecordsdata, *fptemp, *fpdropped, *fpcomputesummary, *fpgradereport; /// FILE POINTERS
float average;

char choice, ans, temp[50]; ///for Choices in switch selection, answer for Yes and No, and Temporary Variable
char studname[50], searchID[15]; ///For Search in Search bar variable
long int recsize=sizeof(s); /// Record Size (recsize) for all the data per character in the all of the variables in struct
int up=1;

COORD coord = {0,0}; /// Coordinate X and Y = top-left corner of window
void position(int x, int y){
    coord.X = x; //coordinate x
    coord.Y = y; //coordinate y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //code for setting the cursor position
}

void emptyvar(){ /// Clearing Structured Variables
    if(sizeof(s)!=0){
        char stud_No[15] = "NULL";
        char fname[50] = "NULL";
        char sname[50] = "NULL";
        strcpy(s.stud_No, stud_No); //copy string
        strcpy(s.fname, fname);
        strcpy(s.sname, sname);
        s.grade1=0; //replace to 0
        s.grade2=0;
        s.grade3=0;
        s.grade4=0;
    }
}

/// DESIGNS
void Header(){
    position(28, 2); printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**   ");
    position(28, 3); printf("    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=    ");
    position(28, 4); printf("    =       Technological University of the Philippines       =    ");
    position(28, 5); printf("    =            Ayala Blvd. Ermita, Manila 1000              =    ");
    position(28, 6); printf("    =                     www.tup.edu.ph                      =    ");
    position(28, 7); printf("    =                  COLLEGE OF SCIENCES                    =    ");
    position(28, 8); printf("    =   Bachelor of Science in Information System(STEM)   =    ");
    position(28, 8); printf("    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=    ");
    position(28, 9); printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**   ");
}
void LoadingScreen(){ ///Loading Bar
    printf("\n\n\t Loading... Please Wait. ");
    printf("\n\n\t LOADING: ");
    for (int i=1; i<=85; i+=2){
        Sleep(20);
        printf(" %c", 219); //219 is a Bar-like character in ASCII code
    }
}
void LoadingScreen2(){ /// Loading 1 - 100%
    position(16, 5); printf("Loading... Please Wait. ");
    position(16, 7); printf("LOADING: ");

    for(int i=0; i<=100; i+=2){
        Sleep(10);
        position(26, 7); printf("%d%%", i);
    }
}
void Opening(){ /// Title Screen
    Header();
    printf("\n\n");
    printf("\n\t\t\t      %c", 201);
    for(int a=1; a<=60; a++){ printf("%c", 205); }
    printf("%c", 187);
    printf("\n\t\t\t      %c                  G R A D I N G                             %c ", 186, 186);
    printf("\n\t\t\t      %c                                                            %c ", 186, 186);
    printf("\n\t\t\t      %c                             S Y S T E M                    %c ", 186, 186);
    printf("\n\t\t\t      %c", 200);
    for(int a=1; a<=60; a++){ printf("%c", 205); }
    printf("%c",188);
    printf("\n\n");
}
void Border(int y){ /// Border in GenerateGradeSummaryReport
            for(int i=11; i<=105; i++){
                position(i, 14); printf("%c",196);
                position(i, 16); printf("%c",196);
                position(i, y); printf("%c",196);
            }
            for(int j=14; j<=y; j++){
                position(10, j); printf("%c", 179);
                position(106, j); printf("%c", 179);
            }
            position(10, 14); printf("%c", 218);
            position(106, 14); printf("%c", 191);
            position(10, y); printf("%c", 192);
            position(106, y); printf("%c", 217);
}
void Heart(){
    system("cls");

    position(20, 1); printf("                             *  *                    *  *            ");
    position(20, 2); printf("                         *          *             *         *            ");
    position(20, 3); printf("                     *                 *       *                *            ");
    position(20, 4); printf("                  *                       * *                      *             ");
    position(20, 5); printf("                *                          *                          *             ");
    position(20, 6); printf("              *                                                         *            ");
    position(20, 7); printf("            *                                                             *            ");
    position(20, 8); printf("           *                                                               *            ");
    position(20, 9); printf("          *                                                                 *            ");
    position(20, 10);printf("          *                                                                 *            ");
    position(20, 11);printf("          *                                                                 *            ");
    position(20, 12);printf("            *                                                             *            ");
    position(20, 13);printf("              *                                                         *            ");
    position(20, 14);printf("                *                                                     *            ");
    position(20, 15);printf("                  *                                                 *            ");
    position(20, 16);printf("                    *                                             *            ");
    position(20, 17);printf("                       *                                       *             ");
    position(20, 18);printf("                          *                                 *               ");
    position(20, 19);printf("                             *                          *                 ");
    position(20, 20);printf("                                 *                   *                  ");
    position(20, 21);printf("                                     *          *                    ");
    position(20, 22);printf("                                          * *                      ");
    position(40, 10);printf("              T H A N K     Y O U ");
    position(0, 25);
    exit(0);

}

/// DATA CHECKS AND CREATE REPORT FUNCTION
void DataChecking(){
    fprecordsdata = fopen("Classrecordsdata.txt", "rb+"); // opening file

    if(fprecordsdata==NULL){ // Checking if it is NULL
        fprecordsdata = fopen("Classrecordsdata.txt", "wb+"); //creating a file
        if(fprecordsdata==NULL){ //Checks if it is NULL
            printf("Cannot Open File");
            exit(101); // Exit Program
        }
    }
    fclose(fprecordsdata); // close the file
}
void CreatingGradeReport(){
    char studno[15], fname[50], sname[50], remarks[10]; //Declare Variables
    float passed=0, failed=0, numOfStud=0;;
    float grade, rpassed, rfailed;
    fpcomputesummary = fopen("Compute Summary.txt", "r");

    if(fpcomputesummary != NULL){
        fpgradereport = fopen("TUP Summary of Grade Report.txt", "w");
        system("cls");
        LoadingScreen();

            fprintf(fpgradereport, "\n");
            fprintf(fpgradereport, "\n\t\t\t             Technological University of the Philippines        ");
            fprintf(fpgradereport, "\n\t\t\t                    Ayala Blvd. Ermita, Manila 1000             ");
            fprintf(fpgradereport, "\n\t\t\t                             www.tup.edu.ph                     ");
            fprintf(fpgradereport, "\n\t\t\t                          COLLEGE OF SCIENCES                   ");
            fprintf(fpgradereport, "\n\t\t\t          Bachelor of Science in Information System(STEM)   ");
            fprintf(fpgradereport, "\n");
            fprintf(fpgradereport, "\n\t\t Student No: \t Name: \t\t\t\t\t Grade: \t Remarks");
            while(fscanf(fpcomputesummary, "%s %s %s %f %s",  studno, fname, sname, &grade, remarks)!=EOF){
                fprintf(fpgradereport, "\n\t\t %s \t %s %s \t\t\t  %.2f%% \t %s", studno, fname, sname, grade, remarks);
                    if(grade>=90.00){
                        passed++;
                    }
                    else if(grade>=81.00 && grade<90){
                        passed++;
                    }
                    else if(grade>=75.00 && grade<81){
                        passed++;
                    }
                    else if(grade<75){
                        failed++;
                    }
                numOfStud++;
            }
            rpassed=(passed/numOfStud)*100; //rate for passed
            rfailed=(failed/numOfStud)*100; //rate for failed
            fprintf(fpgradereport, "\n\n\n\t\t  Total Number of Students: %.0f", numOfStud);
            fprintf(fpgradereport, "\n\n\t\t  Total Passed: %.1f%%", rpassed);
            fprintf(fpgradereport, "\n\t\t  Total Failed: %.1f%%", rfailed);
            fprintf(fpgradereport, "\n\t\t\t\t\t\t\t                      MAY GARCIA");
            fprintf(fpgradereport, "\n\t\t\t\t\t\t\t                <Name of the Faculty>");
        fclose(fpgradereport);
        printf("\n\n\t\t\t                File Created: TUP Summary of Grade Report.txt");
    }
    fclose(fpcomputesummary);
    getche();
    return;
}


/// TITLE BANNERS
void AddStudentBanner(){
        system("cls"); //Clear Screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /             ADD NEW STUDENT            /");
        position(35, 7); printf("   / /________________________________________/");
}
void EditStudentBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /              EDIT STUDENT              /");
        position(35, 7); printf("   / /________________________________________/");
}
void DeleteStudentBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /             DELETE STUDENT             /");
        position(35, 7); printf("   / /________________________________________/");
}
void DisplayStudentBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /            DISPLAY STUDENT             /");
        position(35, 7); printf("   / /________________________________________/");
}
void DisplayAllBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /              DISPLAY ALL              /");
        position(35, 7); printf("   / /________________________________________/");
}
void DisplayAllStudentsBanner(){
        system("cls");
        position(35, 1); printf("      ___________________________________________");
        position(35, 2); printf("     / _________________________________________");
        position(35, 3); printf("    / /          DISPLAY ALL STUDENTS          /");
        position(35, 4); printf("   / /________________________________________/");
}
void DisplayDropBanner(){
        system("cls");
        position(35, 1); printf("      ___________________________________________");
        position(35, 2); printf("     / _________________________________________");
        position(35, 3); printf("    / /         DISPLAY DROP STUDENTS          /");
        position(35, 4); printf("   / /________________________________________/");
}
void ComputeGradeBanner(){
        system("cls");
        position(35, 1); printf("      ___________________________________________");
        position(35, 2); printf("     / _________________________________________");
        position(35, 3); printf("    / /              COMPUTE GRADE             /");
        position(35, 4); printf("   / /________________________________________/");

}
void ResetAllBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /             RESET ALL DATA             /");
        position(35, 7); printf("   / /________________________________________/");
}
void ExitProgramBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /              EXIT PROGRAM              /");
        position(35, 7); printf("   / /________________________________________/");
}
void ResetBanner(){
        system("cls"); // clear screen
        position(35, 4); printf("      ___________________________________________");
        position(35, 5); printf("     / _________________________________________");
        position(35, 6); printf("    / /             RESET ALL DATA             /");
        position(35, 7); printf("   / /________________________________________/");
}


/// MAIN FUNCTIONS
void AddStudent(){ ///Switch 1
    char stud_No[50];
    int exist;
    while(1){ // Infinite Loop for Selection Screen
        AddStudentBanner();
        position(46, 11); printf("       >> S E L E C T <<\n");
        position(46, 14); printf("  | 1 | Add New Student Record");
        position(46, 15); printf("  | 0 | Back to MAIN MENU");
        position(46, 17); printf("    %c%c Select Number: ", 175,175);
        choice = getche(); // get any char and stores to choice

        switch(choice){
        case '1': //Input data for Adding Student
            emptyvar(); //Clearing Variables
            fprecordsdata = fopen("Classrecordsdata.txt", "rb+"); // Opening a file with the mode read and write

            AddStudentBanner();
            exist=0;
            position(30, 11); printf("      >>  A D D   N E W  S T U D E N T  R E C O R D  <<");
            position(30, 13); printf("      SCHOOL ID [Example TUPM-XX-XXXX] "); //School ID
            position(30, 14); printf("         Enter Student No.: "); scanf("%s",searchID);

                    ///checks if Student NO is already taken.
                    rewind(fprecordsdata);
                    while(fread(&s,recsize,1,fprecordsdata)==1){
                        if(strcmp(s.stud_No, searchID)==0){
                            exist=1;
                            position(30, 16); printf("         Student ID %s is already exist!!", searchID);
                            position(30, 17); printf("         Returning To Main Menu ");
                            fclose(fprecordsdata);
                            getche();
                            return;
                        break;
                        }
                    }


            position(30, 16); printf("      NOTE: [Use underscore for 2 names Example: 'Dela_Cruz' 'John_Paul']");
            position(30, 17); printf("      NAME OF THE STUDENT"); //Name of the Student
            position(30, 18); printf("         Enter First Name: "); scanf("%s",s.fname);
            position(30, 19); printf("         Enter  Last Name: "); scanf("%s",s.sname);

            position(30, 21); printf("      GRADES [1st to 4th Grading]");// Grades of the student
            position(30, 22); printf("         Enter 1st Grading: "); scanf("%f", &s.grade1);
            position(30, 23); printf("         Enter 2nd Grading: "); scanf("%f", &s.grade2);
            position(30, 24); printf("         Enter 3rd Grading: "); scanf("%f", &s.grade3);
            position(30, 25); printf("         Enter 4th Grading: "); scanf("%f", &s.grade4);

            strcpy(s.stud_No, searchID);
            rewind(fprecordsdata);
            while(1){ // Infinite Loop for Summary Screen
            AddStudentBanner();

            position(37, 11); printf("              >>  S U M M A R Y  <<");

            position(37, 13); printf("     >> Student ID: %s  ", s.stud_No);
            position(37, 14); printf("     >> Name: %s, %s",s.sname, s.fname);

            position(37, 16); printf("     >> Grades:                               ");
            position(37, 17); printf("             1st Grading: %.2f              ", s.grade1);
            position(37, 18); printf("             2nd Grading: %.2f              ", s.grade2);
            position(37, 19); printf("             3rd Grading: %.2f              ", s.grade3);
            position(37, 20); printf("             4th Grading: %.2f              ", s.grade4);

            position(37, 22); printf("          Save this record?        ");
            position(37, 23); printf("             [Y] Yes         [N] No    ");
            position(37, 24); printf("          Answer: ");

            ans = getche(); // Get any character and store to variable ans

            if(ans=='y' || ans=='Y'){ // if it yes, it will write the data to a file/database

                    up=1;
                    fseek(fprecordsdata, 0, SEEK_END); //Seeks to the end of file
                    fwrite(&s, recsize, 1, fprecordsdata); //fwrite (write to file) writes all the data using structured variables.
                    position(37, 26); printf("          %s Saved Successfully...    ", s.stud_No);
                    position(37, 27); printf("          Press Any Key To Continue  ");

                    getche(); // Get any character and store to variable ans

                break; // Breaking the Loop
            }else if(ans=='n'||ans=='N'){ // If No
                position(37, 26); printf("           %s did not saved...    ", s.stud_No);
                position(37, 27); printf("           Press Any Key To Continue  ");

                getche();// Get any char
                break; // Breaking the Loop For Summary Screen
            }
            }
            fclose(fprecordsdata); // Close the file
        break;
        case '0':
            return; // Return back to the Main Program (Main Menu)
        break;
        }
    }
}

void EditStudent(){ ///Switch 2
    char tempID[50], tempSn[50], tempFn[50]; //temporary strings
    float tempD; // temporary digits
    int flag=0; // Flag for searching found or not.
    int exist;

    while(1){
        EditStudentBanner();
        position(46, 11); printf("       >> S E L E C T <<\n");
        position(46, 14); printf("  | 1 | Search Student to Edit");
        position(46, 15); printf("  | 0 | Back to MAIN MENU");
        position(46, 17); printf("    %c%c Select Number: ", 175,175);
        choice = getche(); // get char to store in choice variable

        switch(choice){
        case '1':
            flag=0;
            fprecordsdata = fopen("Classrecordsdata.txt", "rb+"); // open file with mode read and write

            EditStudentBanner();

            position(35, 9); printf("         Search Student ID: ");
            scanf("%s", searchID);
            rewind(fprecordsdata); // puts the pointer to the starting point of the file
            while(fread(&s,recsize,1,fprecordsdata)==1){ //fetch all the records from file. and stores it in the structured variable up above. it is equal to 1 data then its true
                if(strcmp(s.stud_No, searchID)==0){
                    flag=1;
                    break;
                }
            }
            while(1){
                if(flag==1){
                    EditStudentBanner();

                    position(30, 11); printf("          Search Found: %s\n", s.stud_No);
                    position(30, 13); printf("          Select To Edit");
                    position(30, 15); printf("              | 1 | Student No.: %s", s.stud_No);
                    position(30, 16); printf("              | 2 | Name: %s, %s", s.sname, s.fname);
                    position(30, 17); printf("              | 3 | 1st Grading: %.2f", s.grade1);
                    position(30, 18); printf("              | 4 | 2nd Grading: %.2f", s.grade2);
                    position(30, 19); printf("              | 5 | 3rd Grading: %.2f", s.grade3);
                    position(30, 20); printf("              | 6 | 4th Grading: %.2f", s.grade4);
                    position(30, 21); printf("              | 0 | Back");
                    position(30, 23); printf("                %c%c Select Number: ", 175,175);

                    choice = getche();
                    if(choice == '1'){
                        exist=0;
                        EditStudentBanner();

                        position(30, 11); printf("                   >>  S T U D E N T   I D  <<");

                        position(30, 13); printf("              School Student No.: %s", s.stud_No);
                        position(30, 15); printf("              Enter New Student No: ");
                        scanf("%s", tempID); // input to temporary variable


                        position(30, 17); printf("              Update and save this record?");
                        position(30, 18); printf("                  [Y] Yes         [N] No    ");

                        while(1){
                        position(30, 20); printf("                 Answer:   ");
                        position(55, 20); ans = getche(); // Get any character and store to variable ans
                        if(ans=='y' || ans=='Y'){
                            up=1;
                            strcpy(s.stud_No, tempID); //copy string to stud_no from tempID
                            fseek(fprecordsdata,-recsize,SEEK_CUR); //seeks and move the cursor and step back to current position depends of the size of the record
                            fwrite(&s,recsize,1,fprecordsdata); // override the record
                            position(30, 24); printf("              Update Record Successfully... ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }else if(ans=='n' || ans=='N'){
                            position(30, 24); printf("              Edit Student Cancelled. ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }
                        }
                    }
                    else if(choice == '2'){
                        EditStudentBanner();

                        position(30, 11); printf("                 >>  S T U D E N T  N A M E  <<");

                        position(30, 13); printf("NOTE: [Use underscore for 2 names Example: 'Dela_Cruz' 'John_Paul']");
                        position(30, 14); printf("              School Student Name: %s %s", s.sname, s.fname);
                        position(30, 15); printf("              Enter New First Name: ");
                        scanf("%s", tempFn); // input to temporary variable
                        position(30, 16); printf("              Enter New  Last Name: ");
                        scanf("%s", tempSn); // input to temporary variable

                        position(30, 18); printf("              Update and save this record?");
                        position(30, 19); printf("                  [Y] Yes         [N] No    ");

                        while(1){
                        position(30, 21); printf("                 Answer:   ");
                        position(55, 21); ans = getche(); // Get any character and store to variable ans
                        if(ans=='y' || ans=='Y'){
                            up=1;
                            strcpy(s.fname, tempFn); //copy string to stud_no from tempID
                            strcpy(s.sname, tempSn);
                            fseek(fprecordsdata,-recsize,SEEK_CUR); //seeks and move the cursor and step back to current position depends of the size of the record
                            fwrite(&s,recsize,1,fprecordsdata); // override the record
                            position(30, 24); printf("              Update Record Successfully... ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }else if(ans=='n' || ans=='N'){
                            position(30, 24); printf("              Edit Name Cancelled. ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }
                        }
                    }
                    else if(choice == '3'){
                        EditStudentBanner();
                        position(30, 11); printf("            >>  1 S T  G R A D I N G  G R A D E  <<");
                        position(30, 13); printf("              1st Grading Grade: %.2f", s.grade1);
                        position(30, 15); printf("              Enter New 1st Grade: ");
                        scanf("%f", &tempD); // input to temporary variable

                        position(30, 17); printf("              Update and save this record?");
                        position(30, 18); printf("                  [Y] Yes         [N] No    ");

                        while(1){
                        position(30, 20); printf("                 Answer:   ");
                        position(55, 20); ans = getche(); // Get any character and store to variable ans
                        if(ans=='y' || ans=='Y'){
                            up=1;
                            s.grade1 = tempD;
                            fseek(fprecordsdata,-recsize,SEEK_CUR); //seeks and move the cursor and step back to current position depends of the size of the record
                            fwrite(&s,recsize,1,fprecordsdata); // override the record
                            position(30, 24); printf("              Update Record Successfully... ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }else if(ans=='n' || ans=='N'){
                            position(30, 24); printf("              Edit 1st Grading Grade Cancelled. ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }
                        }

                    }
                    else if(choice == '4'){
                        EditStudentBanner();

                        position(30, 11); printf("            >>  2 N D  G R A D I N G  G R A D E  <<");
                        position(30, 13); printf("              2nd Grading Grade: %.2f", s.grade2);
                        position(30, 14); printf("              Enter New 2nd Grade: ");
                        scanf("%f", &tempD); // input to temporary variable

                        position(30, 17); printf("              Update and save this record?");
                        position(30, 18); printf("                  [Y] Yes         [N] No    ");

                        while(1){
                        position(30, 20); printf("                 Answer:   ");
                        position(55, 20); ans = getche(); // Get any character and store to variable ans
                        if(ans=='y' || ans=='Y'){
                            up=1;
                            s.grade2 = tempD;
                            fseek(fprecordsdata,-recsize,SEEK_CUR); //seeks and move the cursor and step back to current position depends of the size of the record
                            fwrite(&s,recsize,1,fprecordsdata); // override the record
                            position(30, 24); printf("              Update Record Successfully... ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }else if(ans=='n' || ans=='N'){
                            position(30, 24); printf("              Edit 2nd Grading Grade Cancelled. ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }
                        }
                    }
                    else if(choice == '5'){
                        EditStudentBanner();

                        position(30, 11); printf("            >>  3 R D  G R A D I N G  G R A D E  <<");

                        position(30, 13); printf("              3rd Grading Grade: %.2f", s.grade3);
                        position(30, 14); printf("              Enter New 3rd Grade: ");
                        scanf("%f", &tempD); // input to temporary variable

                        position(30, 17); printf("              Update and save this record?");
                        position(30, 18); printf("                  [Y] Yes         [N] No    ");

                        while(1){
                        position(30, 20); printf("                 Answer:   ");
                        position(55, 20); ans = getche();
                        if(ans=='y' || ans=='Y'){
                            up=1;
                            s.grade3 = tempD;
                            fseek(fprecordsdata,-recsize,SEEK_CUR); //seeks and move the cursor and step back to current position depends of the size of the record
                            fwrite(&s,recsize,1,fprecordsdata); // override the record
                            position(30, 24); printf("              Update Record Successfully... ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }else if(ans=='n' || ans=='N'){
                            position(30, 24); printf("              Edit 3rd Grading Grade Cancelled. ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }
                        }
                    }
                    else if(choice == '6'){
                        EditStudentBanner();
                        position(30, 11); printf("            >>  4 T H  G R A D I N G  G R A D E  <<");

                        position(30, 13); printf("              4th Grading Grade: %.2f", s.grade4);
                        position(30, 14); printf("              Enter New 4th Grade: ");
                        scanf("%f", &tempD); // input to temporary variable

                        position(30, 17); printf("              Update and save this record?");
                        position(30, 18); printf("                  [Y] Yes         [N] No    ");

                        while(1){
                        position(30, 20); printf("                 Answer:   ");
                        position(55, 20); ans = getche();
                        if(ans=='y' || ans=='Y'){
                            up=1;
                            s.grade4 = tempD;
                            fseek(fprecordsdata,-recsize,SEEK_CUR); //seeks and move the cursor and step back to current position depends of the size of the record
                            fwrite(&s,recsize,1,fprecordsdata); // override the record
                            position(30, 24); printf("              Update Record Successfully... ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }else if(ans=='n' || ans=='N'){
                            position(30, 24); printf("              Edit 4th Grading Grade Cancelled. ");
                            position(30, 25); printf("              Press Any Key To Continue ");
                            getche(); //enter to continue
                            break;
                        }
                        }
                    }
                    else if(choice == '0'){
                        break;
                    }
                }
                else if(flag==0){
                    position(35, 11); printf("         ID: %s not found", searchID);
                    position(35, 13); printf("         Press Any Key To Continue");
                    getche();
                    break;
                }
            }

            fclose(fprecordsdata);
        break;
        case '0':
            return;
        break;
        }
    }
}

void DeleteStudent(){ ///Switch 3
    int flag;
    while(1){ // infinite loop for delete student screen
        flag=0;
        DeleteStudentBanner();
        position(46, 11); printf("       >> S E L E C T <<\n");
        position(46, 14); printf("  | 1 | Search Student to Delete");
        position(46, 15); printf("  | 0 | Back to MAIN MENU");
        position(46, 17); printf("    %c%c Select Number: ", 175,175);

        choice = getche(); // get char to store in choice variable

        switch(choice){
            case '1':
                fprecordsdata = fopen("Classrecordsdata.txt", "rb+");
                DeleteStudentBanner();

                position(40, 9); printf("    Search Student ID: ");
                scanf("%s", searchID);

                rewind(fprecordsdata); // puts the pointer to the starting point of the file
                while(fread(&s,recsize,1,fprecordsdata)==1){ //fetch all the records from file. and stores it in the structured variable up above. it is equal to 1 data then its true
                    if(strcmp(s.stud_No, searchID)==0){
                        flag=1;
                        DeleteStudentBanner();

                        position(35, 11); printf("             Search Found: %s\n", s.stud_No);

                        position(35, 13); printf("             Student No.: %s", s.stud_No);
                        position(35, 14); printf("             Name: %s %s", s.fname, s.sname);
                        position(35, 15); printf("                 1st Grading: %.2f", s.grade1);
                        position(35, 16); printf("                 2nd Grading: %.2f", s.grade2);
                        position(35, 17); printf("                 3rd Grading: %.2f", s.grade3);
                        position(35, 18); printf("                 4th Grading: %.2f", s.grade4);
                        position(35, 20); printf("             Do You Want To Delete This Student?");
                        position(35, 21); printf("                  [Y] Yes          [N] No");

                        while(1){ // infinite loop for are you sure
                            position(35, 23); printf("                 Answer:      ");
                            position(60, 23);ans = getche(); // Get any character and store to variable ans
                            if(ans=='Y' || ans=='y'){
                                up=1;
                                fptemp = fopen("temp.txt", "wb"); //creates a temporary file
                                fpdropped = fopen("DroppedStudentsData.txt", "rb+"); //creates file for drop students

                                if(fpdropped==NULL){ //checks if null
                                    fpdropped = fopen("DroppedStudentsData.txt", "wb+");
                                }

                                fwrite(&s, recsize, 1, fpdropped); //write the current data to drop file
                                fclose(fpdropped); //closes the drop file

                                rewind(fprecordsdata); //puts the pointer to the start of the file
                                while(fread(&s,recsize,1,fprecordsdata)==1){ // read all the data
                                    if(strcmp(s.stud_No, searchID)!=0){ //checks if it is NOT the same with the searched that you want to delete
                                        fwrite(&s, recsize, 1, fptemp); // if it is true, then it will write all the data to temp file
                                    }                                   // if it is not same then it will skip that data then enter to the same loop
                                }
                                // once done, close all the files
                                fclose(fprecordsdata);
                                fclose(fptemp);

                                if(remove("Classrecordsdata.txt")==0){ //remove the original file
                                    rename("temp.txt", "Classrecordsdata.txt"); //rename the temp file to become the original file
                                    fprecordsdata=fopen("Classrecordsdata.txt", "rb+"); //reopen the file
                                }
                                    position(35, 26); printf("             Deleted Successfully");
                                    break; //break the loop
                            }
                            else if(ans=='n' || ans=='N'){
                                break;
                            }
                        }
                    }
                }
            if(flag==0){
                position(35, 11); printf("             %s not found", searchID);
            }
            fclose(fprecordsdata); // close the file
            position(35, 27); printf("             Press Any Key To Continue");
            fflush(stdin);
            getche();
            break;
            case '0':
                return; // Return back to the Main Program (Main Menu)
            break;
        }
    }
}

void DisplayStudent(){ ///Switch 4
    int flag=0, y, found;
     while(1){ // infinite loop for display student screen
        DisplayStudentBanner();
        position(46, 11); printf("       >> S E L E C T <<");
        position(46, 14); printf("  | 1 | Search To Display Student");
        position(46, 15); printf("  | 0 | Back to MAIN MENU");
        //printf("\n [D] Display All Dropped");
        position(46, 17); printf("    %c%c Select Number: ", 175,175);

        choice = getche(); // get char to store in choice variable
        switch(choice){
        case '1': // Display Student
            fprecordsdata = fopen("Classrecordsdata.txt", "r"); // open file with mode read
            DisplayStudentBanner();
            flag=0;

            position(40, 9); printf("    Search Student Name: ");
            scanf("%s", studname);
            y=14; //Y-Coordinate Position
            found=0; //Show number of search found
            rewind(fprecordsdata); // puts the pointer to the starting point of the file
            while(fread(&s,recsize,1,fprecordsdata)==1){ //reads all the data and print it to screen

                if(strstr(s.fname, studname)){ //checks if it is the same searched name and fname
                    found++;
                    position(20, 11); printf("STUDENT ID      NAMES                                           GRADES");
                    position(70, 12); printf("   1st     2nd     3rd     4th   ");
                    position(20, 10); printf("Search Found: %d", found);
                    position(20, y); printf("%s",s.stud_No);
                    position(36, y); printf("%s, %s",s.sname, s.fname);
                    position(72, y); printf("%.2f   %.2f   %.2f   %.2f", s.grade1, s.grade2, s.grade3, s.grade4);
                    y++;
                    flag=1; //flags if found a data
                }else if(strstr(s.sname, studname)){ //else if checks it the same searched name and sname
                    found++;
                    position(20, 11); printf("STUDENT ID      NAMES                                           GRADES");
                    position(70, 12); printf("   1st     2nd     3rd     4th   ");
                    position(20, 10); printf("Search Found: %d", found);
                    position(20, y); printf("%s",s.stud_No);
                    position(36, y); printf("%s, %s",s.sname, s.fname);
                    position(72, y); printf("%.2f   %.2f   %.2f   %.2f", s.grade1, s.grade2, s.grade3, s.grade4);
                    y++;
                    flag=1;
                }
            }
            if(flag==0){ // flags 0 if not found any data
                position(45, 11); printf("  %s not found", studname);
                position(45, 12); printf("  Press Any Key To Continue");
            }
            fclose(fprecordsdata); // Close the file

            getche();
        break;
        case '0':
            return; // Return back to the Main Program (Main Menu)
        break;
        }
     }
}

void DisplayAllStudents(){ ///Display All Switch 1
        int y;
        fprecordsdata = fopen("Classrecordsdata.txt", "r"); // open file with mode read and write
        system("cls"); // clear screen
        LoadingScreen2();
        printf("\n\n\t        Press Any Key To Continue");
        getche();
        DisplayAllStudentsBanner();
            if(fread(&s,recsize,1,fprecordsdata)==0){
                position(50, 15); printf(" E M P T Y     L I S T");

            }else{
            rewind(fprecordsdata);
            y=10;
            while(fread(&s,recsize,1,fprecordsdata)==1){ //reads all the records
                    position(20, 7); printf("STUDENT ID      NAMES                                           GRADES");
                    position(70, 8); printf("   1st     2nd     3rd     4th   ");
                    position(20, y); printf("%s",s.stud_No);
                    position(36, y); printf("%s, %s",s.sname, s.fname);
                    position(72, y); printf("%.2f   %.2f   %.2f   %.2f", s.grade1, s.grade2, s.grade3, s.grade4);
                    y++;
            }
            }
        fclose(fprecordsdata); // Close the file
        printf("\n\n\n\t\t\t\t\t    Press any key to RETURN to MAIN MENU ");
        getche();
}

void DisplayDropped(){ ///Display All Switch 2
        fpdropped = fopen("DroppedStudentsData.txt", "r"); // open file with mode read and write
        system("cls");
        LoadingScreen2();
        printf("\n\n\t        Press Any Key To Continue");
        getche();
        DisplayDropBanner();
            if(fread(&s,recsize,1,fpdropped)==0){
                position(50, 15); printf(" E M P T Y     L I S T");
            }else{
            rewind(fpdropped);
            int y=10;
            while(fread(&s,recsize,1,fprecordsdata)==1){ //reads all the records
                    position(20, 7); printf("STUDENT ID      NAMES                                           GRADES");
                    position(70, 8); printf("   1st     2nd     3rd     4th   ");
                    position(20, y); printf("%s",s.stud_No);
                    position(36, y); printf("%s, %s",s.sname, s.fname);
                    position(72, y); printf("%.2f   %.2f   %.2f   %.2f", s.grade1, s.grade2, s.grade3, s.grade4);
                    y++;
            }
            }
        fclose(fpdropped); // Close the file
        printf("\n\n\n\t\t\t\t\t    Press any key to RETURN to MAIN MENU ");
        getche();
}

void DisplayAll(){ ///Switch 5
    int flag=0, y, found;
     while(1){ // infinite loop for display student screen
        DisplayAllBanner();
        position(46, 11); printf("       >> S E L E C T <<");
        position(44, 14); printf("  | 1 | Display All Current Student");
        position(44, 15); printf("  | 2 | Display All Dropped Student");
        position(44, 16); printf("  | 0 | Back to MAIN MENU");
        //printf("\n [D] Display All Dropped");
        position(44, 18); printf("    %c%c Select Number: ", 175,175);

        choice = getche(); // get char to store in choice variable
        switch(choice){
        case '1': DisplayAllStudents();
        break;
        case '2': DisplayDropped();
        break;
        case '0':
            return; // Return back to the Main Program (Main Menu)
        break;
        }
     }
}

void ComputeGrade(){ ///Switch 6
up=0;

float numOfStud=0;
float passed=0, failed=0;
float rpassed, rfailed;
int y;

        fprecordsdata = fopen("Classrecordsdata.txt", "r"); // open file with mode read and write
        fpcomputesummary = fopen("Compute Summary.txt", "w");
        system("cls"); // clear screen
        LoadingScreen2();

            printf("\n\n\t\tPress ENTER Key To Display");
            ans = getche();

        ComputeGradeBanner();

            position(30, 6); printf("                    SUMMARY OF GRADE REPORT \n");
            position(30, 8); printf("NAMES                            Average       Letter Grade");

            if(fread(&s,recsize,1,fprecordsdata)==0){ //checks if it don't have any record in a file.
                position(50, 15); printf(" E M P T Y     L I S T");
            }
            else{ //else, read all the records
                rewind(fprecordsdata); //puts the pointer in the starting point of a file
                y=10;
                while(fread(&s,recsize,1,fprecordsdata)==1){ // reads each data
                    Sleep(50);
                    average=(s.grade1+s.grade2+s.grade3+s.grade4)/4;

                    position(30, y); printf("%s, %s", s.sname, s.fname);
                    position(64, y); printf("%.2f", average);

                    fprintf(fpcomputesummary, "%s %s %s %.2f ", s.stud_No, s.sname, s.fname, average);
                    if(average>=90.00){ passed++;
                        position(77, y); printf("A");
                        fprintf(fpcomputesummary, "Passed\n");
                    }else if(average>=81.00 && average<90){ passed++;
                        position(77, y); printf("B");
                        fprintf(fpcomputesummary, "Passed\n");
                    }else if(average>=75.00 && average<81){ passed++;
                        position(77, y); printf("C");
                        fprintf(fpcomputesummary, "Passed\n");
                    }else if(average<75){ failed++;
                        position(77, y); printf("F");
                        fprintf(fpcomputesummary, "Failed\n");
                    }

                    y++; numOfStud++;
                }
                rpassed=(passed/numOfStud)*100; //rate for passed
                rfailed=(failed/numOfStud)*100; //rate for failed
                printf("\n\n");
                printf("\n\t\t\t\t\t   Total Passed: %.0f             Rate: %.1f%%", passed, rpassed);
                printf("\n\t\t\t\t\t   Total Failed: %.0f             Rate: %.1f%%", failed, rfailed);

            }
        fclose(fpcomputesummary);
        fclose(fprecordsdata); // Close the file
        printf("\n\n\n\t\t\t\t\t    Press any key to RETURN to MAIN MENU ");
        getche();
        return;
}

void GenerateGradeSummaryReport(){ /// Switch 7
    char studno[15], fname[50], sname[50], Lgrade, remarks[10]; //Declare Variables
    float passed, failed, numOfStud;
    float grade, rpassed, rfailed;
    int y, i ,j;

    fpcomputesummary = fopen("Compute Summary.txt", "r");
    system("cls");
    LoadingScreen2();
    if(fpcomputesummary==NULL){
        printf("\n\n\t\t      You Have Not Compute All Your Records Yet");
        printf("\n\t\t      Press any key to RETURN to MAIN MENU ");
        getche();

    }else{
        if(up == 1){
            printf("\n\n\t\t      Grade Summary Report is out of date");
            printf("\n\t\t      You Might Not Compute All Your Records Yet.");
            printf("\n\t\t      Press any key to RETURN to MAIN MENU ");
            getche();
        }
        else{
            while(1){
                    passed=0; failed=0; numOfStud=0;
            system("cls");

            position(30, 1); printf("          Technological University of the Philippines       ");
            position(30, 2); printf("                Ayala Blvd. Ermita, Manila 1000             ");
            position(30, 3); printf("                        www.tup.edu.ph                      ");
            position(30, 4); printf("                      COLLEGE OF SCIENCES                   ");
            position(30, 5); printf("      Bachelor of Science in Information System(NON-STEM)   ");

            position(30, 7); printf("                       SUMMARY OF GRADE                     ");

            position(10, 10); printf("Subject Code: CC131                                           Day/Time: Tue: 7am-10am / Thu: 1pm-3pm");
            position(10, 11); printf("Subject Description: Computer Programming 2                   Room: ");
            position(10, 12); printf("Semester: First Semester                                      S.Y.: 2020-2021");

            position(12, 15); printf("STUDENT NUMBER \t\t NAME \t\t\t\t\t  GWA \t\t REMARKS");
            y=17;
            rewind(fpcomputesummary);
            while(fscanf(fpcomputesummary, "%s %s %s %f %s",  studno, sname, fname, &grade, remarks)!=EOF){
                position(12, y); printf("%s", studno);
                position(41, y); printf("%s, %s", sname, fname);
                position(82, y); printf("%.2f          %s", grade, remarks);

                    if(grade>=90.00){
                        passed++;
                    }
                    else if(grade>=81.00 && grade<90){
                        passed++;
                    }
                    else if(grade>=75.00 && grade<81){
                        passed++;
                    }
                    else if(grade<75){
                        failed++;
                    }
                numOfStud++; y++;
            }

            Border(y);


            printf("\n\n\n");
            printf("\n\t  Total Students: %.0f", numOfStud);
            printf("\n\t  Total   Passed: %.0f", passed);
            printf("\n\t  Total   Failed: %.0f", failed);
            position(70, y+5); printf("\t         MAY  GARCIA");
            position(70, y+6); printf("\t    <Name of the Faculty>");
            position(70, y+7); printf("\t                         ");


                ans = getche();
                if(ans=='P'){
                    CreatingGradeReport();
                    break;
                }else{
                    break;
                }
            }

        }

    }
    fclose(fpcomputesummary);
}

void ExitProgram(){ /// Switch 8
    while(1){ //Infinite Loop
            ExitProgramBanner();
            printf("\n\n");
            printf("\n\t\t\t\t         Are You Sure?\n");
            printf("\n\t\t\t\t                  [N] No             [Y] Yes\n\n\n\n");
            printf("\n\t\t\t\t         %c%c Answer: ", 175,175);
            ans = getche(); // stores any character inputed to ans
            if(ans=='Y' || ans=='y'){ //checks if inputs y or Y
                system("cls");
        printf("\n\t\t\t      %c", 201);
        for(int a=1; a<=60; a++){ printf("%c", 205); }
        printf("%c", 187);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c        Technological University of the Philippines         %c ", 186, 186);
        printf("\n\t\t\t      %c               Ayala Blvd. Ermita, Manila 1000              %c ", 186, 186);
        printf("\n\t\t\t      %c                     www.tup.edu.ph                         %c ", 186, 186);
        printf("\n\t\t\t      %c                   COLLEGE OF SCIENCES                      %c ", 186, 186);
        printf("\n\t\t\t      %c     Bachelor of Science in Information System(STEM)    %c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c____________________________________________________________%c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c                G R A D I N G   S Y S T E M                 %c ", 186, 186);
        printf("\n\t\t\t      %c          C O M P U T E R  P R O G R A M M I N G  1         %c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c____________________________________________________________%c ", 186, 186);
        printf("\n\t\t\t      %c                                                            %c ", 186, 186);
        printf("\n\t\t\t      %c", 200);
        for(int a=1; a<=60; a++){ printf("%c", 205); }
        printf("%c",188);
        getche();
        Heart();
            }
            else if(ans=='n' || ans=='N'){
                return;
            }
    }
}

void ResetAll(){ /// Switch R Hidden Function in the screen system
    while(1){
        ResetBanner();
        printf("\n\n\t\t\t\t         Warning: ");
        printf("\n\n\t\t\t\t            This will reset all your records.");
        printf("\n\n\t\t\t\t            Including: ");
        printf("\n\t\t\t\t                   Classrecordsdata.txt");
        printf("\n\t\t\t\t                   DroppedStudentsData.txt");
        printf("\n\t\t\t\t                   Compute Summary.txt \n");
        printf("\n\n\t\t\t\t         Do you want to delete all??\n");
        printf("\n\t\t\t\t                  [N] No             [Y] Yes\n");
        printf("\n\t\t\t\t         %c%c Answer: ", 175,175);
        ans = getche(); // stores any character inputed to ans
        if(ans=='n' || ans=='N'){
            return;
        }
        else if(ans=='y' || ans=='Y'){ //else if Yes, then remove all the data you have
            LoadingScreen();
            remove("Classrecordsdata.txt");
            remove("DroppedStudentsData.txt");
            remove("Compute Summary.txt");
            return;
        }
    }
}



/// MAIN PROGRAM
int main(){
    system ("color 4E");
    Opening(); //Opening
    LoadingScreen(); //Loading Screen
    printf("\n\n\t Press Any Key To Continue ");
    getche();
    while(1){ //Infinite Loop. If it does not entering the right choice, it will just loop.
        system("cls"); // Clear Screen
        DataChecking(); //For File Checking
        Header();
        position(50,13); printf("%c  M A I N   M E N U  %c", 177, 177);
        position(50,15); printf("| 1 | Add New Student");
        position(50,16); printf("| 2 | Edit Student");
        position(50,17); printf("| 3 | Delete Student");
        position(50,18); printf("| 4 | Display Student");
        position(50,19); printf("| 5 | Display All");
        position(50,20); printf("| 6 | Compute Grade");
        position(50,21); printf("| 7 | Generate Grade Summary");
        position(50,22); printf("| 8 | Exit");

        position(50,24); printf(" %c%c Select Number:       ", 175, 175);
        position(69,24); choice = getche(); // Getting any character to store in variable Choice

        switch (choice){
        case '1': AddStudent(); // Adding Student
        break;
        case '2': EditStudent(); // Editing Student
        break;
        case '3': DeleteStudent(); // Deleting Student
        break;
        case '4': DisplayStudent(); // Displaying Student
        break;
        case '5': DisplayAll(); // Display All
        break;
        case '6': ComputeGrade(); // Computing of Grades
        break;
        case '7': GenerateGradeSummaryReport(); // Summary
        break;
        case '8': ExitProgram();// Exiting the Program
        break;
        case 'R': ResetAll();
        break;
        }

        }


    return 0;
}