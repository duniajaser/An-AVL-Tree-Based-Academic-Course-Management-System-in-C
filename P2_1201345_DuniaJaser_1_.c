#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 2000
#define MAX1 1000
//+------------------------------------------------+----------------------------------------------------+
// Dunia Jaser 1201345
// Section 1 - Dr. Ahmed Abusnaina
//+------------------------------------------------+----------------------------------------------------+
typedef struct node_AVL* AVL_pointer;
struct node_AVL{
    int hours;
    char key_code[MAX1];
    char course_name[MAX1];
    char department[MAX1];
    char topics[MAX1][MAX1];
    int Height;
    AVL_pointer left;
    AVL_pointer right;
};
typedef AVL_pointer AVL_Tree;
///+------------------------------------------------+----------------------------------------------------+
//function prototypes
void read_courses_from_file();
void display_menu();
AVL_Tree add_to_AVL_tree(AVL_Tree,AVL_pointer);
int get_height(AVL_pointer);
int max(int, int);
AVL_pointer singleRotateLeft(AVL_pointer);
AVL_pointer singleRotateRight(AVL_pointer);
AVL_pointer doubleRotateLeft(AVL_pointer);
AVL_pointer doubleRotateRight(AVL_pointer);
int get_balance(AVL_pointer);
void preOrder(AVL_pointer);
void inOrder(AVL_pointer);
void insert_a_course_from_user(AVL_Tree);
void find_a_course_and_update(AVL_Tree, char[], int);
AVL_pointer find_Left(AVL_pointer, char[],int);
AVL_pointer find_Right(AVL_pointer, char[],int);
void print_tree_info(AVL_pointer);
void all_topics_given_course(char[],int,AVL_Tree);
void reorder_the_tree_by_names(AVL_pointer);
AVL_pointer copy_tree_info(AVL_pointer);
void all_courses_same_department(AVL_Tree, char[], int);
AVL_Tree add_to_AVL_tree_name(AVL_Tree, AVL_pointer);
AVL_pointer delete_a_node(AVL_Tree, char[],int);
AVL_pointer min_value_node(AVL_pointer node);
void delete_courses_same_first_letter(AVL_pointer , char);
void delete_courses_same_department(AVL_pointer , char[], int);
void write_into_file(AVL_pointer);
void write_into_file1(AVL_pointer,FILE *);

///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
int numberOfReadings = 0;// to let the user read from the file only one time.
int exist_department = 0 ;//to know if the department is exist in the tree or not.
int deleted = 0; // to know if the node is deleted or not
AVL_Tree courses_AVL ;
AVL_Tree courses_AVL_order_names ;//if we want to reorder the tree by names not codes
AVL_Tree courses_in_same_department ;
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
int main()
{
    display_menu();
    return 0;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void display_menu(){
    printf("\n------------------------------ MENU ---------------------------------\n");
    printf("Choose one of these options:\n");
    printf("1) Read the courses file and create the tree.\n");
    printf("2) Insert a new course from the user with all its associated data.\n");
    printf("3) Find a course and support updating of its information.\n");
    printf("4) List courses in lexicographic order with their associated information.\n");// in order
    printf("5) List all topics associated with a given course.\n");
    printf("6) List all courses in lexicographic order that belong to the same department.\n");
    printf("7) Delete a course.\n");
    printf("8) Delete all courses that start with a specific letter.\n");
    printf("9) Delete all courses belong to a given department.\n");
    printf("10) Save all words in file offered_courses.txt.\n");
    printf("11) Exit the program.\n");
    int choice;
    scanf("%d",&choice);
    if (choice == 1){
        printf("+----------------+-----------------------------+--------------------+\n");
        if(numberOfReadings == 0 ){
            numberOfReadings++;
            read_courses_from_file();
            printf("The operation done sucessfully!\n");
            display_menu();
        }else{
            printf("You had chosen it before!\n");
            display_menu();
        }
        printf("+----------------+-----------------------------+--------------------+\n");

    }
    else if (choice == 2 ){
            insert_a_course_from_user(courses_AVL);

    }
    else if (choice == 3 ){
        if(numberOfReadings != 0 )
         {
              printf("+----------------+-----------------------------+--------------------+\n");
        printf("Enter the code that you would to update its its information:\n");
        char key[MAX1];
        scanf("%s",key);
        find_a_course_and_update(courses_AVL,key,MAX1);

         }else{
            printf("You have to load the courses information before by choosing 1 from the menu! \n ");
            display_menu();
         }


    }
    else if (choice == 4 ){
        if(numberOfReadings != 0 ){
          //   courses_AVL_order_names= NULL;
         // reorder_the_tree_by_names(courses_AVL);
        printf("+----------------+-----------------------------+--------------------+\n");
        printf("Courses in lexicographic order:\n");
      // print_tree_info(courses_AVL_order_names);
     print_tree_info(courses_AVL);
       printf("+----------------+-----------------------------+--------------------+\n");
         }else{
                printf("You have to load the courses information before by choosing 1 from the menu! \n ");
         }
        display_menu();
    }
    else if (choice == 5 ){
            if(numberOfReadings != 0 )
         {
             printf("+----------------+-----------------------------+--------------------+\n");
        printf("Enter the code that you would to display its topic information:\n");
        char key[MAX1];
        scanf("%s",key);
        all_topics_given_course(key,MAX1,courses_AVL);
         }else{
            printf("You have to load the courses information before by choosing 1 from the menu! \n ");
            display_menu();
         }

    }
    else if (choice == 6 ){
        if(numberOfReadings == 0 ){
            printf("You have to choose 1 before choosing the other choices!\n");
            display_menu();
        }
        else{
        exist_department = 0;
        printf("+----------------+-----------------------------+--------------------+\n");
        printf("Enter the department you want to display its courses:\n");
        char dep[MAX1];
        fflush(stdin);// because it takes \n as a choice for the menu.
        gets(dep);
        all_courses_same_department(courses_AVL,dep,MAX1);
        if(exist_department == 0){
            printf("The department you are searching for is not found!!\n");
            fflush(stdin);//to avoid infinite loop during the runtime because it takes \n as a choice for the menu.
            printf("+----------------+-----------------------------+--------------------+\n");
           courses_in_same_department = NULL; // if the user chose the choice 6 for many times so the tree is updated with the new information without affecting the previous tree.
            display_menu();
        }else{
            printf("\nCourses in the same department in lexicographic order:\n");
            print_tree_info(courses_in_same_department);
            printf("+----------------+-----------------------------+--------------------+\n");
            fflush(stdin);//to avoid infinite loop during the runtime because it takes \n as a choice for the menu.
           courses_in_same_department = NULL;// if the user chose the choice 6 for many times so the tree is updated with the new information without affecting the previous tree.
            display_menu();
        }
    }
    }
    else if (choice == 7 ){
        if(numberOfReadings == 0 ){
            printf("You have to choose 1 before choosing the other choices!\n");
            display_menu();
        }
        deleted = 0;
        printf("+----------------+-----------------------------+--------------------+\n");
        printf("Enter the course's code you want to delete it:\n");
        char key1[MAX1];
        scanf("%s",key1);
        delete_a_node(courses_AVL,key1,MAX1);
        if(deleted == 1){
             printf("Tree after deletion\n");
        inOrder(courses_AVL);
        }else{
            printf("The course you want to delete does not exist in the tree!\n");

        }


        display_menu();

    }

    else if (choice == 8){
            if(numberOfReadings == 0 ){
            printf("You have to choose 1 before choosing the other choices!\n");
            display_menu();
        }
        printf("+----------------+-----------------------------+--------------------+\n");
        printf("Enter the first letter of the code of courses you would like to delete:\n");
        char c;
        scanf(" %c",&c);
        deleted = 0;
        delete_courses_same_first_letter(courses_AVL,c);
        printf("+----------------+-----------------------------+--------------------+\n");
        if(deleted == 1){
             printf("Tree after deletion:\n");
            inOrder(courses_AVL);

        }else{
            printf("The letter you want to delete does not exist in the tree!\n");
        }
        display_menu();
    }
     else if(choice == 9){
         if(numberOfReadings == 0 ){
            printf("You have to choose 1 before choosing the other choices!\n");
            display_menu();
        }
         printf("+----------------+-----------------------------+--------------------+\n");
        printf("Enter the department you would like to delete its courses:\n");
        char dep[MAX1];
        fflush(stdin);// because it takes \n as a choice for the menu.
        gets(dep);
        delete_courses_same_department(courses_AVL,dep,MAX1);
        printf("+----------------+-----------------------------+--------------------+\n");
         if(deleted == 1){
             printf("Tree after deletion\n");
            inOrder(courses_AVL);
        }else{
            printf("The department's courses you want to delete do not exist in the tree!\n");
        }

        display_menu();
    }
    else if(choice == 10){
        if(numberOfReadings == 0 ){
            printf("You have to choose 1 before choosing the other choices!\n");
            display_menu();
        }
        if(courses_AVL != NULL){
                write_into_file(courses_AVL);
            printf("+----------------+-----------------------------+--------------------+\n");
            printf("The operation done successfully!\n");
        }else{
            printf("The courses tree is empty!\n");
        }

        display_menu();
    }
    else if (choice == 11 ){//exit from the program.
        printf("+----------------+-----------------------------+--------------------+\n");
        printf("Hope you enjoy trying this program ^_^\n");
        exit(0);
    }
    else {
        printf("Not a valid choice. \n");
        display_menu();
    }

}

///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void all_courses_same_department(AVL_Tree courses_tree, char departmentt[], int sizee){
 if(courses_tree != NULL)
    {

        all_courses_same_department(courses_tree->left,departmentt,sizee);
          AVL_pointer temp = courses_tree;
        if(strcmp(temp->department, departmentt) == 0){
            AVL_pointer neww = copy_tree_info(temp);
            exist_department += 1;
         //  courses_in_same_department = add_to_AVL_tree_name(courses_in_same_department,neww);
          courses_in_same_department = add_to_AVL_tree(courses_in_same_department,neww);
        }
        all_courses_same_department(courses_tree->right,departmentt,sizee);
    }
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void read_courses_from_file(){
    FILE *in = fopen("courses.txt","r");
    if(in == NULL){
            printf("The courses file not found!\n");
            exit(0);
        }
    int lines_count = 0;
    char c;
    for( c = fgetc(in); c != EOF ; c = fgetc(in) ){
            if( c == '\n')
                lines_count += 1;
    }
    fclose(in);
    FILE *input = fopen("courses.txt","r");
    int times = 0;
    char *token;
    AVL_pointer temp;
    while(input != NULL){
        times++;
        if(times == lines_count+1)
            break;
        temp = (AVL_pointer)malloc(sizeof(struct node_AVL));
        char line[MAX_LINE];
        fgets(line,sizeof(line),input);
        token = strtok(line,":");//course name
        strcpy(temp->course_name,token);
      //  printf("%s\n",temp->course_name);

        token = strtok(NULL,"#");//course hours
        temp->hours = atoi(token);
      //  printf("%d\n",temp->hours);

        token = strtok(NULL,"#");//course code
        strcpy(temp->key_code,token);
       // printf("%s\n",temp->key_code);

        token = strtok(NULL,"/");//department
        strcpy(temp->department,token);
     //   printf("%s\n",temp->department);

        int i = 0;
        while(token != NULL){
            token = strtok(NULL,", ");
            strcpy(temp->topics[i],token);
         //  printf("%s\n",temp->topics[i]);
            int lengthString = strlen(token);
            if(temp->topics[i][lengthString-1] == '\n'){
                temp->topics[i][lengthString-1] = '\0';
                break;
            }

            i++;
        }

        if(i == 0 ){
            printf("The topics should be one or more!\n");
        }
        else{
            temp->Height=0;
            courses_AVL = add_to_AVL_tree(courses_AVL,temp);
        }
    }
    fclose(input);
    printf("+----------------+-----------------------------+--------------------+\n");
   // inOrder(courses_AVL);
    display_menu();
}

///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
int get_height(AVL_pointer N){
    if (N == NULL)
        return 0;
    return 1 + max(get_height(N->left), get_height(N->right));
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
int max(int a, int b){
    return (a > b)? a : b;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
int get_balance(AVL_pointer N){
    if (N == NULL)
        return 0;
    return get_height(N->left) - get_height(N->right);
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_Tree add_to_AVL_tree(AVL_Tree tree ,AVL_pointer temp){
    if(tree == NULL){
        tree = (AVL_Tree)malloc(sizeof(struct node_AVL));
        temp->left = temp->right = NULL;
        temp->Height = 0;
        tree=temp;
    }
    else if((strcmp(tree->key_code,temp->key_code) < 0 )&& (tree->right == NULL)){
        tree->right = temp;
        if(get_height(tree->left) - get_height(tree->right) >= 2){
            if(strcmp(temp->key_code,tree->key_code) > 0)
                tree =singleRotateRight(tree);
            else
                tree =doubleRotateLeft(tree);
        }

        }else if((strcmp(tree->key_code,temp->key_code) < 0 ) && (tree->right != NULL)){
          tree->right =  add_to_AVL_tree(tree->right,temp);
        }

        else if((strcmp(tree->key_code,temp->key_code) > 0 ) && (tree->left == NULL)){
            tree->left=temp;

            if(get_height(tree->right) - get_height(tree->left) >= 2){
            if(strcmp(temp->key_code, tree->key_code) < 0)
                tree =singleRotateLeft(tree);
            else
                tree =doubleRotateRight(tree);
        }

        }
        else if((strcmp(tree->key_code,temp->key_code) > 0 ) && (tree->left != NULL)){
            tree->left =add_to_AVL_tree(tree->left,temp);

        }
        else if(strcmp(tree->key_code,temp->key_code) == 0  && strcmp(tree->course_name,temp->course_name) == 0 && strcmp(tree->department,temp->department) == 0){
            printf("You can not add %s %s because you added it before!\n",temp->key_code,temp->course_name);

        }else if(strcmp(tree->key_code,temp->key_code) == 0 ){
            printf("You can not add %s %s because the code is not unique!\n",temp->key_code,temp->course_name);
        }
    return tree;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void preOrder(AVL_pointer root) // root - left - right
{
    if(root != NULL)
    {
        printf("%s %s \n", root->key_code,root->course_name);
        preOrder(root->left);
        preOrder(root->right);
    }
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void inOrder(AVL_pointer root) // left - root - right
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("%s \n", root->key_code);
        inOrder(root->right);
    }
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer singleRotateLeft(AVL_pointer x) {
    AVL_pointer y;
    y = x->right;
    x->right  = y->left;
    y->left = x;

    x->Height = 1 + max(get_height(x->left) , get_height(x->right));
    y->Height = 1 + max(get_height(x) , get_height(y->right));

    return y;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer singleRotateRight(AVL_pointer y) {
    AVL_pointer x;
    x = y->left;
    y->left  = x->right;
    x->right = y;

    y->Height = 1 + max(get_height(y->right) , get_height(y->left));
    x->Height = 1 + max(get_height(y) , get_height(x->left));

    return x;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer doubleRotateLeft(AVL_pointer K3) {
    K3->left  = singleRotateLeft(K3->left);
    return singleRotateRight(K3);
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer doubleRotateRight(AVL_pointer K3) {
    K3->right  = singleRotateRight(K3->right);
    return singleRotateLeft(K3);
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void insert_a_course_from_user(AVL_Tree coursess){
    printf("+----------------+-----------------------------+--------------------+\n");
    AVL_pointer temp = (AVL_pointer)malloc(sizeof(struct node_AVL));
    printf("Enter the course code:\n");
    scanf("%s",temp->key_code);
    printf("Enter the course name:\n");
    fflush(stdin);// because it takes \n as a choice for the menu.
    gets(temp->course_name);
    scanf("%s",temp->course_name);
    printf("Enter the department:\n");
    fflush(stdin);// because it takes \n as a choice for the menu.
    gets(temp->department);
    printf("Enter the course hours:\n");
    scanf("%d",&temp->hours);
    int numberOfTopics;
    printf("Enter the number of topics(the number should be 1 or more):\n");
    scanf("%d",&numberOfTopics);
    if(numberOfTopics >=1 ){
        for(int i = 0 ; i < numberOfTopics ; i++){
        printf("Enter topic #%d:\n",(i+1));
        scanf("%s",temp->topics[i]);
    }
    }else{
        printf("The number should be more than 1!\n");
        while(numberOfTopics < 1){
             printf("Enter the number of topics(the number should be 1 or more):\n");
            scanf("%d",&numberOfTopics);
            if(numberOfTopics >=1 ){
            for(int i = 0 ; i < numberOfTopics ; i++){
            printf("Enter topic #%d:\n",(i+1));
            scanf("%s",temp->topics[i]);
            }
        }
    }
    }
    printf("+----------------+-----------------------------+--------------------+\n");
    coursess = add_to_AVL_tree(coursess,temp);
    preOrder(coursess);
    display_menu();
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void find_a_course_and_update(AVL_Tree coursess, char code[],int size){
    AVL_pointer temp = coursess;
    if(coursess == NULL){
        printf("The course you are trying to reach is not found!!\n");
    }else if(strcmp(temp->key_code,code) == 0){
        printf("Code: %s | Name: %s | Hours: %d | Department: %s | topics:\n--->",temp->key_code,temp->course_name,temp->hours,temp->department);
        for(int i = 0 ; i<sizeof(temp->topics); i++){
              if(strcmp(temp->topics[i],"")== 0){
                    printf("\n");
                    break;
              }
            printf("%s | ",temp->topics[i]);

        }
        printf("+----------------+-----------------------------+--------------------+\n");
        printf("What value would you update?\n");
        printf("Please choose the number:\n");
        printf("1)Name.\n2)Course hours.\n3)Department.\n4)topics.\n");
        int choice;
        scanf("%d",&choice);
        if( choice == 1){
            printf("Enter the updated name of the course:\n");
            fflush(stdin);// because it takes \n as a choice for the menu.
            gets(temp->course_name);
        } else if( choice == 2){
            printf("Enter the updated number of hours of the course:\n");
            scanf("%d",&temp->hours);
        } else if( choice == 3){
            printf("Enter the updated department of the course:\n");
            fflush(stdin);// because it takes \n as a choice for the menu.
            gets(temp->department);
        } else if( choice == 4 ){
            for(int i = 0 ; i<sizeof(temp->topics); i++){
                if(strcmp(temp->topics[i],"") != 0)
                    strcpy(temp->topics[i],"");
                else
                    break;

            }
             printf("Enter the updated number of topics of the course:\n");
             int new_size;
            scanf("%d",&new_size);
            for(int i = 0 ; i<new_size; i++){
                printf("Enter the updated topic %d of the course:\n",(i+1));
                fflush(stdin);// because it takes \n as a choice for the menu.
                gets(temp->topics[i]);
                }
        }
        printf("The course after updating:\n");
        printf("Code: %s | Name: %s | Hours: %d | Department: %s | topics:\n--->",temp->key_code,temp->course_name,temp->hours,temp->department);
        for(int i = 0 ; i<sizeof(temp->topics); i++){
              if(strcmp(temp->topics[i],"")== 0){
                    printf("\n");
                    break;
              }
            printf("%s | ",temp->topics[i]);

        }
        display_menu();
    }else if(strcmp(temp->key_code,code) > 0){
        temp = find_Left(temp,code,size);
        find_a_course_and_update(temp,code,size);
    }
    else if(strcmp(temp->key_code,code) < 0){
        temp = find_Right(temp,code,size);
        find_a_course_and_update(temp,code,size);
    }
    printf("+----------------+-----------------------------+--------------------+\n");
    display_menu();
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer find_Left(AVL_pointer coursess, char code[],int size){
    return coursess->left;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer find_Right(AVL_pointer coursess, char code[],int size){
        return coursess->right;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
/*/// if the user want to list the tree according to names
void reorder_the_tree_by_names(AVL_pointer current){
    if(current != NULL)
    {
        reorder_the_tree_by_names(current->left);
        courses_AVL_order_names = add_to_AVL_tree_name(courses_AVL_order_names,copy_tree_info(current));
        reorder_the_tree_by_names(current->right);
    }
}

/// if the user want to list the tree according to names
AVL_Tree add_to_AVL_tree_name(AVL_Tree tree ,AVL_pointer temp){ // Rearrangement the tree by the name of course for lexicographic order.
   if(tree == NULL){
        tree = (AVL_Tree)malloc(sizeof(struct node_AVL));
        temp->left = temp->right = NULL;
        temp->Height = 0;
        tree=temp;
    }
    else if((strcmp(tree->course_name,temp->course_name) <= 0 )&& (tree->right == NULL)){// if they have the same name with different codes (=)
        tree->right = temp;
        if(get_height(tree->left) - get_height(tree->right) >= 2){
            if(strcmp(temp->course_name,tree->course_name) > 0)
                tree =singleRotateRight(tree);
            else
                tree =doubleRotateLeft(tree);
        }

        }else if((strcmp(tree->course_name,temp->course_name) <= 0 ) && (tree->right != NULL)){
          tree->right =  add_to_AVL_tree_name(tree->right,temp);
        }

        else if((strcmp(tree->course_name,temp->course_name) > 0 ) && (tree->left == NULL)){
            tree->left=temp;

            if(get_height(tree->right) - get_height(tree->left) >= 2){
            if(strcmp(temp->course_name, tree->course_name) < 0)
                tree =singleRotateLeft(tree);
            else
                tree =doubleRotateRight(tree);
        }

        }
        else if((strcmp(tree->key_code,temp->key_code) > 0 ) && (tree->left != NULL)){
            tree->left =add_to_AVL_tree_name(tree->left,temp);

        }
    return tree;

}
*/

AVL_pointer copy_tree_info(AVL_pointer temp){
    AVL_pointer new1 = (AVL_pointer)malloc(sizeof(struct node_AVL));
    strcpy(new1->course_name,temp->course_name);
    strcpy(new1->key_code,temp->key_code);
    strcpy(new1->department,temp->department);
    new1->hours = temp->hours;
    new1->Height= 0;
    for(int i = 0 ; i<sizeof(temp->topics); i++){
            if(strcmp(temp->topics[i],"")== 0)
                break;
            strcpy(new1->topics[i],temp->topics[i]);
        }

    return new1;
}
void print_tree_info(AVL_pointer coursesss){ /// in order
    if(coursesss != NULL){
        print_tree_info(coursesss->left);
        printf("Code: %s | Name: %s | Hours: %d | Department: %s | topics:\n--->",coursesss->key_code,coursesss->course_name,coursesss->hours,coursesss->department);
        for(int i = 0 ; i<sizeof(coursesss->topics); i++){
              if(strcmp(coursesss->topics[i],"")== 0){
                    printf("\n");
                    break;
              }
            printf("%s | ",coursesss->topics[i]);

        }
        printf("      ---------------------      \n");
        print_tree_info(coursesss->right);

    }

}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void all_topics_given_course(char code[],int size,AVL_Tree coursess){
    AVL_pointer temp = coursess;
    if(coursess == NULL){
        printf("The course you are trying to reach is not found!\n");
    }else if(strcmp(temp->key_code,code) == 0){
        printf("Topics for course |%s|%s: --->\n",temp->course_name,temp->key_code);
        for(int i = 0 ; i<sizeof(temp->topics); i++){
              if(strcmp(temp->topics[i],"")== 0){
                    printf("\n");
                    break;
              }
            printf("%s | ",temp->topics[i]);

        }
         fflush(stdin);//to avoid infinite loop during the runtime because it takes \n as a choice for the menu.
        display_menu();
    }else if(strcmp(temp->key_code,code) > 0){
        temp = find_Left(temp,code,size);
        all_topics_given_course(code,size,temp);
    }
    else if(strcmp(temp->key_code,code) < 0){
        temp = find_Right(temp,code,size);
        all_topics_given_course(code,size,temp);
    }
    printf("+----------------+-----------------------------+--------------------+\n");
    fflush(stdin);//to avoid infinite loop during the runtime because it takes \n as a choice for the menu.
    display_menu();
}

///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer delete_a_node(AVL_Tree root, char key[],int size){

    if (root == NULL)
        return root;

    if ( strcmp(key ,root->key_code) < 0 )
        root->left = delete_a_node(root->left, key, size);

    else if(strcmp(key, root->key_code) >0 )
        root->right = delete_a_node(root->right, key, size);
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            AVL_pointer temp = root->left ? root->left : root->right;

            // no child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // one child case
              {
                  *root = *temp; // Copy the contents of
                            // the non-empty child
              }

            free(temp);
            deleted = 1;
        }
        else
        {
            // node with two children
            AVL_pointer temp = min_value_node(root->right);// the smallest node in the right sub-tree
            // copy the smallest node's data to this node
            strcpy(root->key_code, temp->key_code);
            strcpy(root->course_name,temp->course_name);
            strcpy(root->department,temp->department);
            root->hours = temp->hours;
            root->Height= 0;
            for(int i = 0 ; i<sizeof(temp->topics); i++){
                if(strcmp(temp->topics[i],"")== 0)
                    break;
                strcpy(root->topics[i],temp->topics[i]);
            }
            // delete the target
            root->right = delete_a_node(root->right, temp->key_code,size);
            deleted = 1;
        }
    }

    // if the tree had only one node then return
    if (root == NULL){
          return root;
    }


    // check whether this node became unbalanced
    int balance = get_balance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && get_balance(root->left) >= 0)
        return singleRotateRight(root);

    // Left Right Case
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left =  singleRotateLeft(root->left);
        return singleRotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && get_balance(root->right) <= 0)
        return singleRotateLeft(root);

    // Right Left Case
    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = singleRotateRight(root->right);
        return singleRotateLeft(root);
    }


    return root;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
AVL_pointer min_value_node(AVL_pointer node)
{
    AVL_pointer current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void delete_courses_same_first_letter(AVL_pointer tree, char letter){
    if(tree != NULL){
        if(tree->key_code[0] == letter){
            courses_AVL = delete_a_node(courses_AVL,tree->key_code,MAX1);
            }
        delete_courses_same_first_letter(tree->left,letter);

        if(tree->key_code[0] == letter){
            courses_AVL = delete_a_node(courses_AVL,tree->key_code,MAX1);
        }

    delete_courses_same_first_letter(tree->right,letter);
    if(tree->key_code[0] == letter){
        courses_AVL = delete_a_node(courses_AVL,tree->key_code,MAX1);
    }

    }
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void delete_courses_same_department(AVL_pointer tree, char department[], int size){
    if(tree != NULL){
    delete_courses_same_department(tree->left,department,size);

    if(strcmp(tree->department,department)== 0 ){
        courses_AVL = delete_a_node(courses_AVL,tree->key_code,MAX1);
    }

    delete_courses_same_department(tree->right,department,size);
    if(strcmp(tree->department,department)== 0 ){
        courses_AVL = delete_a_node(courses_AVL,tree->key_code,MAX1);
    }

    }
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void write_into_file(AVL_pointer tree){
     FILE *out;
    out = fopen("offered_courses.txt","w");
    write_into_file1(courses_AVL, out);
    fclose(out) ;
}
///^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^
void write_into_file1(AVL_pointer tree,FILE *out){
    if(tree != NULL){

        write_into_file1(tree->left,out);

        fprintf(out,"%s:%d#%s#%s/",tree->course_name,tree->hours,tree->key_code,tree->department);
        printf("%s:%d#%s#%s/\n",tree->course_name,tree->hours,tree->key_code,tree->department);

        fprintf(out,"%s",tree->topics[0]);
        for(int i = 1 ; i<sizeof(tree->topics); i++){
              if(strcmp(tree->topics[i],"")== 0){
                    fprintf(out,"\n");
                    break;
              }
            fprintf(out,", %s",tree->topics[i]);

            }
        write_into_file1(tree->right,out);

      }

}
