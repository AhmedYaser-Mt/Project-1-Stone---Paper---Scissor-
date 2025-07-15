#include <iostream>
using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner { Computer = 1, User = 2, NoWinner = 3 };

struct stUserVariables
{
    short UserChoice;
    enChoice enUserChoice;
    string UserChoiceInWord;
    short UserRounds;
    short UserWinningTimes;
};

struct stComputerVariables
{
    enChoice enComputerChoice;
    string ComputerChoiceInWord;
    short ComputerWinningTimes;
};

struct stGameVariables
{
    stUserVariables UserVariables;
    stComputerVariables ComputerVariables;
    enWinner enGameWinner;
    string GameWinnerInWord;
    short DrawTimes;
    enWinner enFinalWinner;
    string FinalWinnerInWord;
    char RepeatingQuestion;
};

bool ValidateNumberinRange(short Number, short From, short To)
{
    return (Number >= From && Number <= To);
}

short ReadPositiveNumber(string Message)
{
    short Number = 0;

    do
    {
        cout << Message << endl;
        cin >> Number;

    } while (Number <= 0);

    return Number;
}

char ReadCharacter(string Message)
{
    char Character = 'n';

    do
    {
        cout << Message << endl << "\t\t\t";
        cin >> Character;

    } while (!(Character == 'Y' || Character == 'y' || Character == 'N' || Character == 'n'));

    return Character;
}

short RandomNumber(short From, short To)
{
    short RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

void ReadUserRounds(stGameVariables& GameVariables)
{
    do
    {
        GameVariables.UserVariables.UserRounds = ReadPositiveNumber("How many rounds 1 to 10 ?");
    } while (!ValidateNumberinRange(GameVariables.UserVariables.UserRounds, 1, 10));
}

void ReadUserChoice(stGameVariables& GameVariables)
{
    do
    {
        GameVariables.UserVariables.UserChoice = ReadPositiveNumber("\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor ?");
    } while (!ValidateNumberinRange(GameVariables.UserVariables.UserChoice, 1, 3));

    GameVariables.UserVariables.enUserChoice = enChoice(GameVariables.UserVariables.UserChoice);
}

void GetComputerRandomChoice(stGameVariables& GameVariables)
{
    GameVariables.ComputerVariables.enComputerChoice = enChoice(RandomNumber(1, 3));
}

string GetChoiceInWord(enChoice Choice)
{
    switch (Choice)
    {
    case enChoice::Paper:
        return "Paper";
    case enChoice::Scissor:
        return "Scissor";
    case enChoice::Stone:
        return "Stone";
    }
}

void AssignChoiceInWord(stGameVariables& GameVariables)
{
    GameVariables.ComputerVariables.ComputerChoiceInWord = GetChoiceInWord(GameVariables.ComputerVariables.enComputerChoice);
    GameVariables.UserVariables.UserChoiceInWord = GetChoiceInWord(GameVariables.UserVariables.enUserChoice);
}

void InitializingVariables(stGameVariables& GameVariables)
{
    GameVariables.ComputerVariables.ComputerWinningTimes = 0;
    GameVariables.UserVariables.UserWinningTimes = 0;
    GameVariables.DrawTimes = 0;
}

void GetWinner(stGameVariables& GameVariables)
{
    if (GameVariables.UserVariables.enUserChoice == GameVariables.ComputerVariables.enComputerChoice)
    {
        GameVariables.enGameWinner = enWinner::NoWinner;
    }
    else if (GameVariables.UserVariables.enUserChoice == enChoice::Paper && GameVariables.ComputerVariables.enComputerChoice == enChoice::Stone)
    {
        GameVariables.enGameWinner = enWinner::User;
    }
    else if (GameVariables.UserVariables.enUserChoice == enChoice::Stone && GameVariables.ComputerVariables.enComputerChoice == enChoice::Scissor)
    {
        GameVariables.enGameWinner = enWinner::User;
    }
    else if (GameVariables.UserVariables.enUserChoice == enChoice::Scissor && GameVariables.ComputerVariables.enComputerChoice == enChoice::Paper)
    {
        GameVariables.enGameWinner = enWinner::User;
    }
    else
    {
        GameVariables.enGameWinner = enWinner::Computer;
    }
}

void AssignWinnerInWord(stGameVariables& GameVariables)
{
    switch (GameVariables.enGameWinner)
    {
    case enWinner::Computer:
        GameVariables.GameWinnerInWord = "Computer";
        break;
    case enWinner::User:
        GameVariables.GameWinnerInWord = "User";
        break;
    case enWinner::NoWinner:
        GameVariables.GameWinnerInWord = "No Winner";
        break;
    }
}

void ChangeScreenColor(stGameVariables& GameVariables)
{
    switch (GameVariables.enGameWinner)
    {
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::User:
        system("color 2F");
        break;
    case enWinner::NoWinner:
        system("color 6F");
        break;
    }
}

void PrintRoundInfo(short RoundNumber, stGameVariables& GameVariables)
{
    cout << "\n_______________Round [" << RoundNumber << "]_______________\n\n";
    cout << "Player1  Choice: " << GameVariables.UserVariables.UserChoiceInWord << endl;
    cout << "Computer Choice: " << GameVariables.ComputerVariables.ComputerChoiceInWord << endl;
    cout << "Round Winner   : [" << GameVariables.GameWinnerInWord << "]\n";
    cout << "________________________________________\n\n";
}

void CountWinningTimes(stGameVariables& GameVariables)
{
    switch (GameVariables.enGameWinner)
    {
    case enWinner::Computer:
        GameVariables.ComputerVariables.ComputerWinningTimes++;
        break;
    case enWinner::User:
        GameVariables.UserVariables.UserWinningTimes++;
        break;
    case enWinner::NoWinner:
        GameVariables.DrawTimes++;
        break;
    }
}

void GetFinalWinner(stGameVariables& GameVariables)
{
    if (GameVariables.UserVariables.UserWinningTimes > GameVariables.ComputerVariables.ComputerWinningTimes)
        GameVariables.FinalWinnerInWord = "User";
    else if (GameVariables.UserVariables.UserWinningTimes < GameVariables.ComputerVariables.ComputerWinningTimes)
        GameVariables.FinalWinnerInWord = "Computer";
    else
        GameVariables.FinalWinnerInWord = "No Winner";
}

void AssignFinalWinnerInWord(stGameVariables& GameVariables)
{
    switch (GameVariables.enFinalWinner)
    {
    case enWinner::Computer:
        GameVariables.FinalWinnerInWord = "Computer";
        break;
    case enWinner::User:
        GameVariables.FinalWinnerInWord = "User";
        break;
    case enWinner::NoWinner:
        GameVariables.FinalWinnerInWord = "NoWinner";
        break;
    }
}

void PrintFinalResults(stGameVariables& GameVariables)
{
    cout << "\t\t\t_______________________________________________________________\n\n";
    cout << "\t\t\t                +++ G a m e  O v e r +++ \n";
    cout << "\t\t\t_______________________________________________________________\n\n";
    cout << "\t\t\t_____________________ [Game Resulst ] _________________________\n\n";
    cout << "\t\t\tGame Rounds        : " << GameVariables.UserVariables.UserRounds << endl;
    cout << "\t\t\tPlayer1 won times  : " << GameVariables.UserVariables.UserWinningTimes << endl;
    cout << "\t\t\tComputer won times : " << GameVariables.ComputerVariables.ComputerWinningTimes << endl;
    cout << "\t\t\tDraw times         : " << GameVariables.DrawTimes << endl;
    cout << "\t\t\tFinal Winner       : " << GameVariables.FinalWinnerInWord << endl;
    cout << "\t\t\t_______________________________________________________________\n\n";
}

void AskingForRepatingGame(stGameVariables& GameVariables)
{
    GameVariables.RepeatingQuestion = ReadCharacter("\t\t\tDo you want to play again? Y/N?");
}

void StartGame(stGameVariables& GameVariables)
{
    ReadUserRounds(GameVariables);

    InitializingVariables(GameVariables);

    for (short i = 0;i < GameVariables.UserVariables.UserRounds;i++)
    {
        cout << "\nRound [" << i + 1 << "] begins:\n";
        ReadUserChoice(GameVariables);
        GetComputerRandomChoice(GameVariables);
        AssignChoiceInWord(GameVariables);
        GetWinner(GameVariables);
        AssignWinnerInWord(GameVariables);
        ChangeScreenColor(GameVariables);
        PrintRoundInfo(i + 1, GameVariables);
        CountWinningTimes(GameVariables);
    }
}

void EndGame(stGameVariables& GameVariables)
{
    GetFinalWinner(GameVariables);
    PrintFinalResults(GameVariables);
}

void FullGame(stGameVariables& GameVariables)
{
    do
    {
        system("cls");
        system("color 0F");
        StartGame(GameVariables);
        EndGame(GameVariables);
        AskingForRepatingGame(GameVariables);

    } while (GameVariables.RepeatingQuestion == 'Y' || GameVariables.RepeatingQuestion == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    stGameVariables GameVariables;

    FullGame(GameVariables);

    return 0;
}