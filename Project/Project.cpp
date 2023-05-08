/*
Project for CS 230
Menu with 4 options for Boston Red Sox

Licensed under the GNU public license open source agreement.
@author George Garopoulos 20200017@student.act.edu
 */

#include <iostream>
#include <iomanip>	
#include <fstream>
#include <limits> 	
#include <string> 	

using namespace std;

struct red_sox//stuct for the first file
{
   string p_name; 
   int p_games;  
   int p_home_runs;
   int p_strike_outs;		
};

struct red_sox_new//struct for the file for option 3
{
   string p_name; 
   int p_games;  
   int p_home_runs;
   int p_strike_outs;
   double p_home_runs_per_g;
   double p_strike_outs_per_g;
};
//Bellow are the methods
void Menu_display();
void display(int i);
void display_new(int i);
bool read_data(int temp);
void ascending(int temp);
void descending(int temp);
void sort(red_sox_new*, red_sox_new*);

//both structs are here in order to make the methods easier
red_sox player[12];
red_sox_new player_new[12];

int main()
{
    int option = 0;  
    double  temp(0);
    bool first_run = false;//flag for the first option
    bool run_option_three = false;//flag for the third option
    
	cout << "=======================================================" << endl << endl;
	cout << "Major League Baseball statistics for the Boston Red Sox" << endl << endl;
    cout << "=======================================================" << endl << endl << endl;
  
  //the begining of the menu
  
  do		   				
 { 		
    Menu_display();
        
	cin >> option;  
    
	cout << endl;
    
	cin.sync(); 			
    
	while(cin.fail())//check for false input
	{
		cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        cout << "Invalid entry. Please enter a number of the option you want to select: ";
        cin >> option;
        cin.sync(); 	
    } 
      
    if(option == 1) 
	{
		first_run = read_data(1);//chnage the first run to true
		char answer = ' ';
		
		if(run_option_three)//only works if we run option 3
		{
			cout << "Do you want to display the new file? (y/n)" << endl;
			cin >> answer;
		}
		
		for(int i = 0; i < 12; i++) 
		{
			if (answer == 'y' || answer == 'Y')
			{
				display_new(i);
			}
			else
			{
				display(i);	
			}
			cout << endl;
		}
    }
    else if(option == 2 && first_run) 
    {
    	temp = 0;
    	cout << "Please enter a Limit for the Home Runs" << endl;
    	cin >> temp;
    
    	for(int i = 0; i < 12; i++) 
		{
			if(player[i].p_home_runs >= temp)
			{
				display(i);
				cout << endl;
			}
		}
    }
    else if(option == 3 && first_run)
    {
    	temp = 0;
    	double  temp1(0), temp2(0);
		ofstream new_file;
		
		cout << setprecision(2) << fixed;
		new_file << setprecision(2) << fixed;
		
		new_file.open("Garopoulos_red_sox_stats.txt");//opens the new file
		
		for(int i = 0; i < 12; i++) //imports the data
		{
			new_file << player[i].p_name << "\t";
			new_file << player[i].p_games << "\t";
			temp = player[i].p_games;
			new_file << player[i].p_home_runs << "\t";
			temp1 = player[i].p_home_runs;
			new_file << player[i].p_strike_outs << "\t";
			temp2 = player[i].p_strike_outs;
			new_file << float(temp1/temp) << "\t";
			new_file << float(temp2/temp) << "\n";
		}
		
		new_file.close();
		
		run_option_three = read_data(2);//we chnage the flag and write the data into the struct
		
		for(int i = 0; i < 12; i++) 
		{
			display_new(i);
		}
	}
    else if(option == 4 && first_run) 
    {
    	if(run_option_three)
    	{
    		string temp_text;
	    	temp = 0;
	    	int temp1(0);
	    	
			cout << "Please enter a field to sort by: " << endl;
			do//simplifies the field to sort by  
			{
				cout << "Fields: Name(N), Game(G), Home Run(HR), Strike Out(SO), Home Run Per Game(HRP), Strike Out Per Game(SOG) " << endl;
	    		cin >> temp_text;
	    	
	    		if(temp_text == "Name" || temp_text == "name" || temp_text == "N" || temp_text == "n")
	    		{
	    			temp = 1;
				}
				else if(temp_text == "Game" || temp_text == "game" || temp_text == "G" || temp_text == "g")
				{
					temp = 2;
				}
				else if(temp_text == "Home Run" || temp_text == "home run" || temp_text == "HR" || temp_text == "hr")
				{
					temp = 3;
				}
				else if(temp_text == "Strike Out" || temp_text == "strike out" || temp_text == "SO" || temp_text == "so")
				{
					temp = 4;
				}
				else if(temp_text == "Home Run Per Game" || temp_text == "home run per game" || temp_text == "HRG" || temp_text == "hrg")
				{
					temp = 5;
				}
				else if(temp_text == "Strike Out Per Game" || temp_text == "strike out per game" || temp_text == "SOG" || temp_text == "sog")
				{
					temp = 6;
				}
			}while(temp == 0);//runs untill a valid input has been given
			
			do
			{
				cout << "Please enter 1 for Ascending or 2 for Descending" << endl;
				cin >> temp1;
			}while(temp1 != 1 && temp1 != 2);//runs untill either 1 or 2 has been given
			
			for(int i = 0; i < 12; i++) 
			{
				//calls either asceding or descending and passes the field we selected
				if(temp1 == 1)
				{
					ascending(temp);
				}
				else
				{
					descending(temp);
				}
			}
			
			for(int i = 0; i < 12; i++) 
			{
				display_new(i);
				cout << endl;
			}
		}
		else
		{
			cout << "Please run option 3 first. \n" << endl;	//if option 3 has not been run we display a message
		}		
    }
    else if(option == 5)
    {
    	cout << endl << "Thank you for using this program! " << endl << endl;//closes the program
    } 
    else 		
    {
    	if(!first_run)
    	{
    		cout << "Please be sure to run option 1 first in order to input the data!" << endl << endl;
		}
		else
		{
			cout << "Invalid entry. Please enter \"1\" , \"2\" or \"3\" " << endl << endl;
		}
    }
     
 } while(option != 5); 
   
   return 0;
}

void Menu_display()//the display menu options, runs after option
{
	cout << "1) Read and Display the stats for the 12 players" << endl;
    cout << "2) Display players who have hit a number of home runs" << endl;
    cout << "3) Calculate the number of Home Runs and Strike Outs per Game and make a new file" << endl;
    cout << "4) Sort the new file made in option 3 " << endl;
    cout << "5) Exit this program" << endl << endl;
    cout << "Please select an option: ";
}

bool read_data(int temp)//the population of the structs, takes a int to determine which struct to populate
{
	if(temp == 1)
	{
		int counter(0);
		ifstream file;
		
		file.open("Garopoulos_red_sox.txt");
		
		if(file.fail())
		{
			cerr << "Error opening input file\n";
	 		exit(1);
	 	}
	    
	    while ( !file.eof() )
		{
			file >> player[counter].p_name;
			file >> player[counter].p_games;
			file >> player[counter].p_home_runs;
			file >> player[counter].p_strike_outs;
			counter++;
		}
		
		file.close();
	}
	else
	{
		int counter(0);
		ifstream file;
	
		file.open("Garopoulos_red_sox_stats.txt");
		
		if(file.fail())
		{
			cerr << "Error opening input file\n";
	 		exit(1);
	 	}
	 	
	 	while ( !file.eof() )
		{
			file >> player_new[counter].p_name;
			file >> player_new[counter].p_games;
			file >> player_new[counter].p_home_runs;
			file >> player_new[counter].p_strike_outs;
			file >> player_new[counter].p_home_runs_per_g;
			file >> player_new[counter].p_strike_outs_per_g;
			counter++;
		}
		file.close();
	}
	
	return true;
}

void display(int i)//display struct 1
{	
	cout << "Player's Name': " << player[i].p_name << endl;
	cout << "Games played: " << player[i].p_games << endl;
	cout << "Home runs: " << player[i].p_home_runs << endl;
	cout << "Strike outs: " << player[i].p_strike_outs << endl;
}

void display_new(int i)//display struct from option 3
{	
	cout << "Player's Name': " << player_new[i].p_name << endl;
	cout << "Games played: " << player_new[i].p_games << endl;
	cout << "Home runs: " << player_new[i].p_home_runs << endl;
	cout << "Strike outs: " << player_new[i].p_strike_outs << endl;
	cout << "Home runs per Game: " << player_new[i].p_home_runs_per_g << endl;
	cout << "Strike outs per Game: " << player_new[i].p_strike_outs_per_g << endl << endl;
}

//both ascending and descending call sort to swap


void ascending(int temp)
{
	for(int i = 0; i < 12; i++) 
	{
		if(temp == 1 && (player_new[i].p_name > player_new[i+1].p_name))
		{
			sort(&player_new[i], &player_new[i+1]);
		}
		if(temp == 2 && (player_new[i].p_games > player_new[i+1].p_games))
		{
			sort(&player_new[i], &player_new[i+1]);
		}
		if(temp == 3 && (player_new[i].p_home_runs > player_new[i+1].p_home_runs))
		{
			sort(&player_new[i], &player_new[i+1]);
		}
		if(temp == 4 && (player_new[i].p_strike_outs > player_new[i+1].p_strike_outs))
		{
			sort(&player_new[i], &player_new[i+1]);
		}
		if(temp == 5 && (player_new[i].p_home_runs_per_g > player_new[i+1].p_home_runs_per_g))
		{
			sort(&player_new[i], &player_new[i+1]);
		}
		if(temp == 6 && (player_new[i].p_strike_outs_per_g > player_new[i+1].p_strike_outs_per_g))
		{
			sort(&player_new[i], &player_new[i+1]);
		}
	}
}

void descending(int temp)
{
	for(int i = 12; i > 0; i--) 
	{
		if(temp == 1 && (player_new[i].p_name > player_new[i-1].p_name))
		{
			sort(&player_new[i], &player_new[i-1]);
		}
		if(temp == 2 && (player_new[i].p_games > player_new[i-1].p_games))
		{
			sort(&player_new[i], &player_new[i-1]);
		}
		if(temp == 3 && (player_new[i].p_home_runs > player_new[i-1].p_home_runs))
		{
			sort(&player_new[i], &player_new[i-1]);
		}
		if(temp == 4 && (player_new[i].p_strike_outs > player_new[i-1].p_strike_outs))
		{
			sort(&player_new[i], &player_new[i-1]);
		}
		if(temp == 5 && (player_new[i].p_home_runs_per_g > player_new[i-1].p_home_runs_per_g))
		{
			sort(&player_new[i], &player_new[i-1]);
		}
		if(temp == 6 && (player_new[i].p_strike_outs_per_g > player_new[i-1].p_strike_outs_per_g))
		{
			sort(&player_new[i], &player_new[i-1]);
		}
	}
}


void sort(red_sox_new* i, red_sox_new* j) //sort takes the adress of the items instead of taking every variable and changing them which makes sorting faster.
{
   red_sox_new temp = *i;
  *i = *j;
  *j = temp;
}