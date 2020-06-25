#include "Cli.h"
#include <windows.h>
#define MAX_PATH_SIZE 10000
#define MAX_C_FILE_NAME 1000

void changeConsoleColor(int colorCode) {
    // color code between 0 to 255
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);

}

struct InputData{
    String cFileName;
    String cFilePath;
    String yourInputsPath;
    String yourOutputsPath;
    String testCasesDirectoryPath;

};

int main(){

    char choose;
    String yourDirectoryPath;
    struct InputData input;
    struct ResultData *result;

    yourDirectoryPath = (String) malloc(sizeof(char) * MAX_PATH_SIZE);
    input.testCasesDirectoryPath = (String) malloc(sizeof(char) * MAX_PATH_SIZE);
    input.cFileName = (String) malloc(sizeof(char) * MAX_C_FILE_NAME);
    input.cFilePath = (String) malloc(sizeof(char) * MAX_PATH_SIZE);
    input.yourInputsPath = (String) malloc(sizeof(char) * MAX_PATH_SIZE);
    input.yourOutputsPath = (String) malloc(sizeof(char) * MAX_PATH_SIZE);
    // free them at last


    print("**** Hi! Welcome to the");

    changeConsoleColor(COLOR_YELLOW);
    print("judge program ****\n");

    changeConsoleColor(COLOR_WHITE);
    print("In this program,");

    changeConsoleColor(COLOR_YELLOW);
    print("a C file that contains your codes and");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("some test cases in txt format");

    changeConsoleColor(COLOR_WHITE);
    print("are given to judge and it generates");

    changeConsoleColor(COLOR_BLOCK_GREEN);
    print("the outputs");

    changeConsoleColor(COLOR_WHITE);
    print("based on the inputs\n");
    print("and check the answers.\n\n");

    print("So... Please enter your C file name (name.c) : ");
    scanf("%s", input.cFileName);

    print("Where is your C file? Enter the path: ");
    scanf("%s", input.cFilePath);

    print("Now, please enter\n");

    changeConsoleColor(COLOR_YELLOW);
    print("your directory name that contains \"in\" and \"out\" directories which contains your inputs and outputs /n");

    changeConsoleColor(COLOR_LIGHT_BLUE);
    print("and the directory that the test cases outputs will place in there.\n");

    changeConsoleColor(COLOR_BLOCK_YELLOW);
    print("pay attention that split your address with '\\'!");

    changeConsoleColor(COLOR_RED);
    print("Otherwise I stop here and you will be sad\n");
    // maybe cli needs to work with makeDirectories for more options

    changeConsoleColor(COLOR_WHITE);
    print("Your in/out directory: ");
    scanf("%s", yourDirectoryPath);

    print("Test cases directory: ");
    scanf("%s", input.testCasesDirectoryPath);

    print("Ok. Now I am adjusting your input and output address...\n");
    input.yourInputsPath = strcat("\\in", yourDirectoryPath);
    input.yourOutputsPath = strcat("\\out", yourDirectoryPath);
    free(yourDirectoryPath);


    print("Generating test cases...\n");
    if (generate(input.cFilePath, input.cFileName, input.yourInputsPath, input.testCasesDirectoryPath) ){
        changeConsoleColor(COLOR_BLOCK_RED);
        print("Warning! judging causes all your file in your output directory and in test case directory being erased.\n");
        print("But in order to see the proper result, you should proceed.\n");
        print("However, do you wanna proceed?(y/n) ");

        choose = getchar();

        if (choose != 'y' && choose != 'n'){
            while (choose != 'y' && choose != 'n'){
                print("Hey! Enter the proper letter, yes or no? (y/n) ");
                choose = getchar();

            }
        }
        if (choose == 'n'){
            print("bye!");
            return 1;

        } else {
            result = judgeAll(input.yourOutputsPath, input.testCasesDirectoryPath, input.cFilePath, input.cFileName);

            print("judging...");

            if(result == NULL){
                changeConsoleColor(COLOR_BLOCK_RED);
                print(" ...So, the program stops here.");
                changeConsoleColor(COLOR_WHITE);
                return 1;
            } else{

                changeConsoleColor(COLOR_LIGHT_BLUE);
                print("Your C file is: %s\nIn the path: %s\nIn %s\n", result->fileName, result->path, result->date);
                print("The message from judge: %s\n", result->message);

                changeConsoleColor(COLOR_WHITE);
                print("Take a look at it and see if everything is good.\n");
                system("pause");

                print("Now let's check the answer...\n\n");

                loop(currentTestCase, result->testCaseNumber){
                    print("Status of testCase #%d: ", result->testCases[currentTestCase].testCaseNumber);
                    if(result->testCases[currentTestCase].isPass){
                        changeConsoleColor(COLOR_BLOCK_GREEN);
                        print("%s\n", result->testCases[currentTestCase].message);
                        changeConsoleColor(COLOR_WHITE);

                    } else{
                        changeConsoleColor(COLOR_RED);
                        print("%s\n", result->testCases[currentTestCase].message);
                        changeConsoleColor(COLOR_WHITE);
                    }

                }

                changeConsoleColor(COLOR_BLOCK_YELLOW);
                print("Your overall score is %s .\n", result->score);
                changeConsoleColor(COLOR_WHITE);

                print("Check judge message in calm... then press a key\n");
                system("pause");

                print("Thanks for using our program\nHave a nice day :)\n");
            }
        }

    } else {
        changeConsoleColor(COLOR_BLOCK_RED);
        print(" ...the program stops here.");
        changeConsoleColor(COLOR_WHITE);
        return 1;
    }

    return 0;
}
