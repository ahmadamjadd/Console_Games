#include <iostream>
#include<windows.h>
#include <conio.h>

using namespace std;

//Forward Declaration
struct Car;

//Structure of scoreboard declared to us it inside Car structure to demonstrate concept of nested structures
struct scoreboard
{
    int scores;
    void printscore(Car &a, Car &b);
};

//structure of Car
struct Car
{
    int position;
    int points;

    void CarPosition(Car &a, Car &b,char c);
    void DisplayCar(Car &a, Car &b);
    scoreboard s;//nested structure

};


int main()
{
    //using car datatype
    Car a, b;

    //initializing variables to zero;
    a.position = 0;
    b.position = 0;
    a.s.scores = 0;
    b.s.scores = 0;
    char control = '\0';

    //Printing Main Menu Interface of Game
    cout<<"=======================\n";
    cout<<"Welcome to Racing Game!\n";
    cout<<"=======================\n";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Track:\n";
    cout<<"+-------------------------------+\n";
    cout<<"_________________________________\n";
    cout<<endl;
    cout<<"Car1\n";
    cout<<endl;
    cout<<"Car2\n";
    cout<<"_________________________________\n";
    cout<<endl;
    cout<<"+-------------------------------+\n";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;

    cout<<"=========\n";
    cout<<"Controls: \n";
    cout<<"=========\n";
    cout<<"+-----------------------------+\n";
    cout<<"- Car1: 'a' (left), 'd' (right)\n";
    cout<<"- Car2: 'j' (left), 'l' (right)\n";
    cout<<"- Quit: 'q'\n";
    cout<<"+-----------------------------+\n";

    //using windows.h functions to escape from main manu and start playing
    system("pause");
    Sleep(500);
    system("cls");

    cout<<"Start Playing!\n";

    //While loop to continue playing until user enters 'q' tp exit game
    while (control != 'q')
    {
        //using _kbhit and _getch functions so user do not have to press enter after pressing control keys
        if (_kbhit())
        {
            control = _getch();

            if (control != 'd' && control != 'a' && control != 'l' && control != 'j')
            {
                Beep(500, 500);//Sound of wrong key entered
                cout<<"Enter valid control!\n";
            }
            else
            {
                if (control == 'd' || control == 'a')
                {
                    a.CarPosition(a, b, control);
                    Beep(750, 100);//Sound of CAR1 moving
                }
                else if (control == 'l' || control == 'j')
                {
                    b.CarPosition(a, b, control);
                    Beep(600, 100);//sound of CAR2 moving
                }

                while (_kbhit())//using this function to continue pressing control keys without pressing enter key
                    _getch();

                system("cls");

                a.DisplayCar(a, b);

                if (a.position == 30)
                {
                    cout<<"CAR1 won!";
                    break;
                }
                else if (b.position == 30)
                {
                    cout<<"CAR2 won!";
                    break;
                }

                cout<<"Press Controls to continue:\n";
            }
        }
    }

    return 0;
}

//function declaration
void Car :: CarPosition(Car &a, Car &b, char c)
    {
        // Position of Car1
        if (c == 'd')
        {
            if (a.position < 31)
            {
                a.position++;
                a.s.scores++;
            }
            else
            {
                cout<<"You cannot move further!\n";
            }
        }
        else if (c == 'a')
        {
            if (a.position <= 0)
            {
                cout<<"You are at starting point!\n";
            }
            else
            {
                a.position--;
                a.s.scores--;
            }
        }

        // Position of Car2
        if (c == 'l')
        {
            if (b.position < 31)
            {
                b.position++;
                b.s.scores++;
            }
            else
            {
                cout<<"You cannot move further!\n";
            }
        }
        else if (c == 'j')
        {
            if (b.position <= 0)
            {
                cout<<"You are at starting point!\n";
            }
            else
            {
                b.position--;
                b.s.scores--;
            }
        }
    }


    //function declaration
    void Car :: DisplayCar(Car &a, Car &b)
    {
        a.s.printscore(a,b);
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"+--------------------------------+\n";
        cout<<"__________________________________\n";
        cout<<endl;
        for(int i = 0; i<a.position; i++)
        {
            cout<<" ";
        }
        cout<<"CAR1"<<endl;
        cout<<endl;
        for(int i = 0; i<b.position; i++)
        {
            cout<<" ";
        }
        cout<<"CAR2"<<endl;
        cout<<"__________________________________\n";
        cout<<endl;
        cout<<"+--------------------------------+\n";
    }

    //function declaration
    void scoreboard :: printscore(Car &a, Car &b)
    {
        cout<<"+---------------------+\n";
        cout<<"===========\n";
        cout<<"SCOREBOARD\n";
        cout<<"===========\n";
        cout<<endl;
        cout<<"CAR1: "<<a.s.scores<<endl;
        cout<<endl;
        cout<<"CAR2: "<<b.s.scores<<endl;
        cout<<endl;
        cout<<"+---------------------+\n";
    }