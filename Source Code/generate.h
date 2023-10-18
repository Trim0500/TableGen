#ifndef GENERATE_H_
#define GENERATE_H_

struct TableRow {
    int UserId;
    char *FirstName;
    char *LastName;
    char *Country;
    char *PhoneNum;
    char *Email;
    int SIN;
    char *Password;
};

void SortStructs(struct TableRow*, int, int);
char* ToLowerString(char*);
struct TableRow* BuildStructs(int*, int, int, char**, char**, char**, char**);
void BuildCSVOutputAndWriteToFile(int, int, int*, struct TableRow*, char*);
void InitColumnOptionsMenu();
void InitTableGenMenu();

#endif