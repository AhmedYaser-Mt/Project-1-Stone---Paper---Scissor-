#include<iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

short RandomNumber(short From, short To)
{
    short RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone","Paper","Scissor" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1","Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    }

    return enWinner::Player1;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (Player1WinTimes < ComputerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (short i = 1;i <= NumberOfTabs;i++)
    {
        t += "\t";
        cout << t;
    }

    return t;
}

enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;

    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor? ";
        cin >> Choice;

    } while (Choice < 1 || Choice >3);

    return enGameChoice(Choice);
}

enGameChoice GetComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How many Rounds 1 to 10 ?\n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds>10);

    return GameRounds;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F");
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n\n____________________ Round [" << RoundInfo.RoundNumber << "] __________________\n\n";
    cout << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
    cout << "_________________________________________________\n\n";

    SetWinnerScreenColor(RoundInfo.RoundWinner);
}

void PrintGameOverScreen()
{
    cout << Tabs(1) << "_____________________________________________________________________\n";
    cout << Tabs(1) << "                        +++ G a m e  O v e r +++\n";
    cout << Tabs(1) << "_____________________________________________________________________\n\n";
}

void PrintFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(1) << "__________________________ [Game Results] ___________________________\n\n";
    cout << Tabs(1) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(1) << "Player1 win times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(1) << "Computer win times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(1) << "Draw Times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(1) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(1) << "_____________________________________________________________________\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        PrintGameOverScreen();
        PrintFinalGameResults(GameResults);

        cout << Tabs(1) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}