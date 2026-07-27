#include <iostream>   // for cout, cin
#include <string>     // for string handling
#include <fstream>    // for file I/O
#include <cstdlib>    // for system, srand, rand
#include <conio.h>    // for _getch() and _kbhit()
#include <ctime>      // for time()
#include <chrono>     // for time measurement (timer)
#include <thread>     // for sleep_for
using namespace std;

// ================== FUNCTION PROTOTYPES ==================
int main_menu();                           // display main menu
int start_quiz();                          // display topic menu
void high_score();                         // show top 5 scores
void difficulty_level();                   // select difficulty
int printquestion(ifstream& fin);          // main quiz function
void reset_lifelines();                     // reset all lifelines
void show_lifelines();                      // display lifelines
char getInputWithTimeout(int time_limit);   // input with timer

// ================== GLOBAL VARIABLES ==================
int n, diff;                // menu choice and difficulty
int score = 0;
int heighst = 0;
int choise, sb;
string name;
int arr;                    // date

// Lifelines
int lifeline_5050 = 1;
int lifeline_skip = 1;
int lifeline_replace = 1;
int lifeline_extraTime = 1;

// ================== LIFELINES FUNCTIONS ==================

// Reset all lifelines to available
void reset_lifelines()
{
    lifeline_5050 = 1;
    lifeline_skip = 1;
    lifeline_replace = 1;
    lifeline_extraTime = 1;
}

// Display available or used lifelines
void show_lifelines()
{
    cout << endl << "====== Lifelines ======" << endl;
    cout << "6. 50/50  (" << (lifeline_5050 ? "Available" : "Used") << ")" << endl;
    cout << "7. Skip Question  (" << (lifeline_skip ? "Available" : "Used") << ")" << endl;
    cout << "8. Replace Question  (" << (lifeline_replace ? "Available" : "Used") << ")" << endl;
    cout << "9. Extra Time +10s  (" << (lifeline_extraTime ? "Available" : "Used") << ")" << endl;
    cout << "========================" << endl;
}

// Function to get input with timeout
char getInputWithTimeout(int time_limit)
{
    char choice = '\0';
    time_t startTime = time(0);

    cout << endl << "Choose (1-4) or Lifeline (6-9): ";
    cout.flush();  // Ensure prompt is displayed immediately

    while (true)
    {
        int remaining = time_limit - (time(0) - startTime);

        if (remaining <= 0)
        {
            cout << endl << " Time's up!" << endl;
            return '0';  // Timeout
        }

        // If key is pressed
        if (_kbhit())
        {
            choice = _getch();   // read without waiting for Enter

            // Only echo numeric choices
            if (choice >= '0' && choice <= '9')
            {
                cout << choice << endl;
            }

            return choice;
        }

        // Show timer without clearing screen
        cout << "\rTime left: " << remaining << "s. Choose (1-4) or Lifeline (6-9): ";
        cout.flush();

        // Small delay to prevent CPU overuse
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// ================== MAIN FUNCTION ==================
int main()
{
    cout << "=========Game Start========" << endl;
    cout << "\tLogin The Game" << endl;
    cout << "==============================" << endl;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter Date (number): ";
    cin >> arr;
    while (!(arr > 0))
    {
        cout << "Invalid date. Enter again: ";
        cin >> arr;
    }

    cout << "==============================" << endl;
    cout << "Press any key to continue...";
    _getch();     // pause until key press
    system("cls"); // clear screen

    while (true)
    {
        bool f = false;
        bool flag = false;
        n = 0, diff = 0;
        choise = 0, sb = 0;

        reset_lifelines();  // lifelines available at start

        main_menu();
        cin >> n;

        while (!f)
        {
            system("cls");

            switch (n)
            {
            case 1:
            {
                start_quiz();
                f = true;

                while (!flag)
                {
                    cin >> choise;

                    if (choise >= 1 && choise <= 5)
                    {
                        difficulty_level();
                        cin >> diff;

                        while (!(diff == 1 || diff == 2 || diff == 3))
                        {
                            cout << "Invalid! Enter difficulty level again: ";
                            cin >> diff;
                        }

                        system("cls");
                        flag = true;
                    }
                    else
                    {
                        cout << "Wrong choice! Enter again: ";
                        cin >> choise;
                    }
                }
                break;
            }

            case 2:
                f = true;
                high_score();
                break;

            case 3:
                return 0;

            default:
                cout << "Invalid menu option! Enter again: ";
                cin >> n;
            }
        }

        // Load question file based on topic + difficulty
        string file = "";

        if (choise == 1)
        {
            if (diff == 1)
                file = "science_easy.txt";
            if (diff == 2)
                file = "science_medium.txt";
            if (diff == 3)
                file = "science_hard.txt";
        }

        if (choise == 2)
        {
            if (diff == 1)
                file = "sports_easy.txt";
            if (diff == 2)
                file = "sports_medium.txt";
            if (diff == 3)
                file = "sports_hard.txt";
        }

        if (choise == 3)
        {
            if (diff == 1)
                file = "history_easy.txt";
            if (diff == 2)
                file = "history_medium.txt";
            if (diff == 3)
                file = "history_hard.txt";
        }

        if (choise == 4)
        {
            if (diff == 1)
                file = "computer_easy.txt";
            if (diff == 2)
                file = "computer_medium.txt";
            if (diff == 3)
                file = "computer_hard.txt";
        }

        if (choise == 5)
        {
            if (diff == 1)
                file = "iq_easy.txt";
            if (diff == 2)
                file = "iq_medium.txt";
            if (diff == 3)
                file = "iq_hard.txt";
        }

        ifstream fin;
        fin.open(file.c_str());
        if (!fin)
        {
            cout << "File not found!" << endl;
        }
        else
        {
            printquestion(fin);
        }
        fin.close();
    }

    return 0;
}

// ================== MENU FUNCTIONS ==================
int main_menu()
{
    cout << "==============Game Start============" << endl;
    cout << "\t  Main Menu " << endl;
    cout << "\t1. Start Quiz" << endl;
    cout << "\t2. View High Scores" << endl;
    cout << "\t3. Exit Game" << endl;
    cout << "Enter your choice: ";
    return 0;
}

int start_quiz()
{
    cout << "==========================" << endl;
    cout << "\t Choose the Topic" << endl;
    cout << "\t1. Science" << endl;
    cout << "\t2. Sports" << endl;
    cout << "\t3. History" << endl;
    cout << "\t4. Computer" << endl;
    cout << "\t5. IQ/Logical Question" << endl;
    cout << "==========================" << endl;
    cout << " Enter Number: ";
    return 0;
}

void high_score()
{
    ifstream fin4("player_record.txt");  // text file containing previous scores
    string pname;
    int pdate;
    int pscore;

    int top_scores[5] = { 0 };
    string top_players[5] = { " " };

    while (fin4 >> pname >> pdate >> pscore)
    {
        for (int i = 0; i < 5; i++)
        {
            if (pscore > top_scores[i])
            {
                for (int j = 4; j > i; j--)
                {
                    top_scores[j] = top_scores[j - 1];
                    top_players[j] = top_players[j - 1];
                }

                top_scores[i] = pscore;
                top_players[i] = pname;
                break;
            }
        }
    }

    fin4.close();

    if (top_scores[0] == 0)
    {
        cout << "No high scores yet!" << endl;
    }
    else
    {
        cout << "==========HIGH SCORES==========" << endl;
        for (int i = 0; i < 5; i++)
        {
            if (top_scores[i] != 0)
                cout << i + 1 << ". " << top_players[i] << "  " << top_scores[i] << endl;
        }
        cout << "==============================" << endl;
    }

    cout << "Press any key to return to menu...";
    _getch();
    system("cls");
}

void difficulty_level()
{
    cout << "====================" << endl;
    cout << "\tChoose Difficulty level" << endl;
    cout << "\t1. Easy" << endl;
    cout << "\t2. Medium" << endl;
    cout << "\t3. Hard" << endl;
    cout << "====================" << endl;
}
int printquestion(ifstream& fin)
{
    int correct = 0;
    int wrong = 0;
    int bonus = 0;
    int negative = 0;
    int streak = 0;

    srand(time(0));

    for (int r = 0; r < 10; r++)
    {
        // Load random question
        int q = rand() % 40;
        fin.clear();
        fin.seekg(0);

        int skipLines = q * 6;
        string line;

        for (int i = 0; i < skipLines; i++)
        {
            getline(fin, line);
        }

        cout << "============================" << endl;
        cout << "QUESTION " << r + 1 << "/10" << endl;
        cout << "============================" << endl;

        // Read question and options
        string question[5];
        for (int i = 0; i < 5; i++)
        {
            getline(fin, question[i]);
            cout << question[i] << endl;
        }

        // Read correct answer
        getline(fin, line);
        char correctAns = line[18];   // Answer is at 18th position in file line

        // Show available lifelines
        show_lifelines();

        // Timer and lifeline input
        int time_limit = 10;
        char choice;
        bool replaceQuestion = false;
        bool skipQuestion = false;

        choice = getInputWithTimeout(time_limit);

        // Lifeline handling
        while (choice == '6' || choice == '7' || choice == '8' || choice == '9')
        {
            // 50/50
            if (choice == '6' && lifeline_5050)
            {
                lifeline_5050 = 0;
                cout << "50/50 used — Two wrong options removed." << endl;
                cout << "Choose your answer (1-4): ";
                choice = getInputWithTimeout(time_limit);
                continue;
            }

            // Skip question
            if (choice == '7' && lifeline_skip)
            {
                lifeline_skip = 0;
                cout << "Question skipped." << endl;
                skipQuestion = true;
                break;
            }

            // Replace question
            if (choice == '8' && lifeline_replace)
            {
                lifeline_replace = 0;
                cout << "Replacing question..." << endl;
                replaceQuestion = true;
                break;
            }

            // Extra time
            if (choice == '9' && lifeline_extraTime)
            {
                lifeline_extraTime = 0;
                time_limit += 10;
                cout << "+10 seconds added! New time: " << time_limit << "s" << endl;
                choice = getInputWithTimeout(time_limit);
                continue;
            }

            cout << "Lifeline already used or invalid!" << endl;
            choice = getInputWithTimeout(time_limit);
        }

        if (replaceQuestion)
        {
            system("cls");
            r--;  // repeat question
            continue;
        }

        if (skipQuestion)
        {
            system("cls");
            continue;
        }

        system("cls");

        // Check answer
        if (choice == correctAns)
        {
            correct++;
            streak++;

            if (streak == 3)
            {
                bonus += 5;
                cout << "=============================" << endl;
                cout << "You get +5 Bonus" << endl;
                cout << "=============================" << endl;
            }

            if (streak == 5)
            {
                bonus += 15;
                cout << "=============================" << endl;
                cout << "You get +15 Bonus" << endl;
                cout << "=============================" << endl;
            }

            cout << "=============================" << endl;
            cout << "Correct!" << endl;
            cout << "=============================" << endl;
        }
        else if (choice == '0')  // Timeout
        {
            wrong++;
            streak = 0;
            cout << "Time's up! Correct answer was: " << correctAns << endl;
        }
        else
        {
            wrong++;
            streak = 0;

            // Negative marking based on difficulty
            if (diff == 1)
            {
                negative -= 2;
                cout << "============================" << endl;
                cout << "Your 2 points deducted" << endl;
                cout << "============================" << endl;
            }
            else if (diff == 2)
            {
                negative -= 3;
                cout << "============================" << endl;
                cout << "Your 3 points deducted" << endl;
                cout << "============================" << endl;
            }
            else if (diff == 3)
            {
                negative -= 5;
                cout << "============================" << endl;
                cout << "Your 5 points deducted" << endl;
                cout << "============================" << endl;
            }

            cout << "Wrong! Correct answer was: " << correctAns << endl;
        }

        _getch();
        system("cls");
    }

    // Final score calculation
    int finalScore = negative - bonus;

    cout << "==========Result=========" << endl;
    cout << "Correct: " << correct << endl;
    cout << "Wrong: " << wrong << endl;
    cout << "Bonus Points: " << bonus << endl;
    cout << "Final Score: " << finalScore << endl;
    cout << "=============================" << endl;

    // Save score to file
    ofstream fout("player_record.txt", ios::app);
    fout << name << " " << arr << " " << finalScore << endl;
    fout.close();

    cout << "Press any key to return...";
    _getch();
    system("cls");

    return finalScore;
}
