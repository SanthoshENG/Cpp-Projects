#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

// COIN SORTER SOFTWARE
// This code will help control a Coin Sorter machine



int main()
{

//Variable Declarations and Intializations

ifstream inFile;
string inFileName;
ofstream outFile;
string outFileName;
int numLines = 0;
int currentLine = 0;
int countArray = 0;
int weightSensor[5000] = {0};
int diameterSensor [5000] = {0};
double weight [5000] = {0.0};
double diameter [5000] = {0.0};
string coinConditionSensor[5000];
string imageFaceSensor[5000];
char space;
int count1 = 0;
int count2 = 0;
int count3 = 0;
int numNickels = 0;
int numRollsNickels = 0;
int numDimes = 0;
int numRollsDimes = 0;
int numQuarters = 0;
int numRollsQuarter = 0;
int numLoonies = 0;
int numRollsLoonies = 0; 
int numToonies = 0;
int numRollsToonies = 0;
double weightBentContainer = 0.0;
double totalBentCoinWeight = 0.0;
int numBentContainer = 0;
double weightOtherContainer = 0.0;
int totalOtherCoinsNum = 0;
int numOtherCoinContainer = 0;
int numOtherCoins = 0; 
double totalOtherCoinWeight = 0.0;

//Constants
const int MAXIMUMTRIES = 3;
const int MAXNUMBEROFLINES = 5000;
const int MINNUMBEROFLINES = 0;
const int MAXSENSORVALUE = 255;
const int MINSENSORVALUE = 0;
const double MAXBENTCONTAINERWEIGHT = 100.0;
const double MAXOTHERCONTAINERWEIGHT = 200.0;
const double WEIGHTSENSORSPRING = 1/51;
const int WEIGHTSENSORMULTIPLIER = 2;
const double DIAMETERSENSORSPRING = 2/17;
const int DIAMETERCONSTANT = 10;
//Max and Min Weight of coins
const double MAXWEIGHTNICKEL = 4.30; 
const double MINWEIGHTNICKEL = 3.60;
const double MAXWEIGHTDIME = 2.20;
const double MINWEIGHTDIME = 1.30;
const double MAXWEIGHTQUARTER = 4.80;
const double MINWEIGHTQUARTER = 4.00;
const double MAXWEIGHTLOONIE = 7.50;
const double MINWEIGHTLOONIE = 6.50;
const double MAXWEIGHTTOONIE = 7.85;
const double MINWEIGHTTOONIE = 6.75;
//Max and Min Diameter of coins
const double MAXDIAMETERNICKEL = 21.8;
const double MINDIAMETERNICKEL = 20.3;
const double MAXDIAMETERDIME = 18.7;
const double MINDIAMETERDIME = 17.3;
const double MAXDIAMETERQUARTER = 24.6;
const double MINDIAMETERQUARTER = 22.8;
const double MAXDIAMETERLOONIE = 27.0;
const double MINDIAMETERLOONIE = 25.0;
const double MAXDIAMETERTOONIE = 29.1;
const double MINDIAMETERTOONIE = 26.9;
//Coins per Role
const int NICKELSPERROLE = 40;
const int DIMESPERROLE = 50;
const int QUARTERSPERROLE = 40;
const int LOONIESPERROLE = 25;
const int TOONIESPERROLE = 25;
//Image readings
const string VALUE1 = "Both";
const string VALUE2 = "OneMatch";
const string VALUE3 = "NoMatch";
//Condition readings
const string VALUE4 = "bent";
const string VALUE5 = "usuable";


//Loop to check if input file opened without any errors and reprompts user for maximum of 3 tries
do
{
cout<< "Type the name of the input file containing sensor readings : "<< endl;
cin>> inFileName;
inFile.open(inFileName);
	
	if ( inFile.fail() )
    	{
        	cerr << "ERROR: File "<< inFileName << " could not be opened for input"<< endl;
        
        }
	else { break; } 

	count1++;
	
	if(count1 == MAXIMUMTRIES)
	{
		cerr<< "ERROR: You exceeded maximum number of tries allowed"<< endl;
		cerr<< "while entering the input file name"<< endl;
		inFile.close();
		return 0;
	}
	
}while(count1<=MAXIMUMTRIES);


//Loop to check if output file opened without any errors and reprompts user for maximum of 3 tries

do
{
cout << "Type the name of the output file which will hold the simulation results : " <<endl;
cin>> outFileName;
outFile.open(outFileName, ios::_Nocreate);
    	if ( outFile.fail() )
    	{
        	cerr << "ERROR: File "<< outFileName << " could not be opened for input"<< endl;
        
        	count2++;
   		}
		else {break;}

	
	
	if(count2 == MAXIMUMTRIES)
	{
		cout<< "ERROR: You exceeded maximum number of tries allowed"<< endl;
		cout<< "while entering the output file name"<< endl;
		outFile.close();
		return 2;
	}
	
}while(count2<=MAXIMUMTRIES);

//Reads the number of lines of data in the input file (the first integer in the file, alone on the first line of the file). 1 <= number of lines of data <= 5000


if( !(inFile >> numLines))
{

	if ( inFile.eof() )
	{
		cerr << "ERROR: input file is empty"<< endl;
        inFile.close();
        return 3;
	}
	else 
    {         
       cerr << "ERROR: First piece of data in the file is not an integer " << endl;
       inFile.close();
       return 4;
	}
	

}

if (numLines > MAXNUMBEROFLINES || numLines <= MINNUMBEROFLINES)
{
		cerr << "ERROR: The number of sensor readings is out of range" << endl;
		return 5; 
} 



for (count3 = 0; count3 < numLines; count3++)
{
//	
	currentLine++;
	if(!(inFile >> weightSensor[countArray]))
	{
		if ( inFile.eof() )
		{
			cerr << "ERROR: No more data,"<<endl;
			cerr << "Simulation completed early before line " << numLines << " of input" <<endl;  
            inFile.close();
            break;
		}
		else if(weightSensor[countArray] < MINSENSORVALUE || weightSensor[countArray] > MAXSENSORVALUE)
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << currentLine << " in the input file" <<endl; 
			
			//ignore data
			space = inFile.peek();
			while ( space == '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
						
			continue;
		}
		else 
		{         
			cerr << "ERROR: Weight sensor value read on line " << currentLine << " is not an integer" <<endl;
			cerr << "Simulation terminated early: Please correct your data file" <<endl; 
			inFile.close();
			return 7;
		}
	}
	
	space = inFile.peek();
	
	while (space == ' ' || space == '	')
	{
		space = inFile.get();
		space = inFile.peek();
	}
	
	if( space == '\n') continue;

//

	if(!(inFile >> diameterSensor[countArray]))
	{
		if ( space == '\n')
		{
			cerr << "ERROR: Weight sensor measurement only" <<endl; 
			cerr << "Ignoring line " << currentLine << " of the input file" <<endl;
			
			//ignore data
			space = inFile.peek();
			while ( space == '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
			
			continue;
		}
		else if(diameterSensor[countArray] < MINSENSORVALUE || diameterSensor[countArray] > MAXSENSORVALUE)
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << currentLine << " in the input file" <<endl; 
			//ignore data
			space = inFile.peek();
			while ( space != '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
			
			continue;
		}
		else 
		{         
			cerr << "ERROR: Diameter sensor value read on line " << currentLine << " is not an integer" <<endl;
			cerr << "Simulation terminated early: Please correct your data file" <<endl;
			inFile.close();
			return 8;
		}
	}
	
	space = inFile.peek();
	
	while (space == ' ' || space == '	')
	{
		space = inFile.get();
		space = inFile.peek();
	}
	

	if(!(inFile >> coinConditionSensor[countArray]))
	{
		if ( space == '\n')
		{
			cerr << "ERROR: Weight and diameter sensor measurements only" <<endl;
			cerr << "Ignoring line " << currentLine << " of the input file" <<endl; 			       
            
			//ignore data
			space = inFile.peek();
			while ( space == '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
			
			continue;
		}
		else if (coinConditionSensor[countArray] != VALUE4 && coinConditionSensor[countArray] != VALUE5)
		{         
			cerr << "ERROR: Result of test to determine if coin is bent at line " << currentLine << " is invalid" <<endl;
			cerr << "Ignoring this line of data" <<endl;
			
			//ignore data
			space = inFile.peek();
			while ( space != '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
						
			continue;
		}
	}
	
	space = inFile.peek();
	
	while (space == ' ' || space == '	')
	{
		space = inFile.get();
		space = inFile.peek();
	}
	
	
//
	
	if(!(inFile >> imageFaceSensor[countArray]))
	{
		if(space == '\n')
		{
			cerr << "ERROR: Weight and diameter sensor measurements and bent string only" <<endl;
			cerr << "Ignoring line " << currentLine << " of the input file" <<endl; 
           
			//ignore data
			space = inFile.peek();
			while ( space == '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
			
		continue;
		}
		
		else if ( imageFaceSensor[countArray] != VALUE1 && imageFaceSensor[countArray] != VALUE2 && imageFaceSensor[countArray] != VALUE3)
		{
			cerr << "ERROR: image processing result at line " << currentLine << " is invalid" <<endl;
			cerr << "Ignoring this line of data" <<endl;
			
			//ignore data
          	space = inFile.peek();
			while ( space != '\n')
			{
				space = inFile.get();
				space = inFile.peek();
			}
			continue;
		}
		
	}
	
	space = inFile.peek();
	
	while (space == ' ' || space == '	')
	{
		space = inFile.get();
		space = inFile.peek();
	}

	if( space != '\n') 
	{
		while ( space != '\n')
		{
			space = inFile.get();
			space = inFile.peek();
		}
	cerr << "ERROR: Extra data at line " << currentLine << ".  Ignoring extra data" <<endl;
	
	}
	

cout << currentLine << " " << weightSensor[countArray] << " " << diameterSensor[countArray] << " " << coinConditionSensor[countArray] << " " << imageFaceSensor[countArray] << endl;

	








//Determining Type of coin

// Bent Coins
			
		if(coinConditionSensor[countArray] == VALUE4)
		{
			weight[countArray] = WEIGHTSENSORSPRING * weightSensor[countArray] * WEIGHTSENSORMULTIPLIER;

			weightBentContainer += weight[countArray]; 
			
			totalBentCoinWeight += weight[countArray];
			
			if(weightBentContainer > MAXBENTCONTAINERWEIGHT)
			{
				weightBentContainer = 0;
				weightBentContainer += weight[countArray];
				numBentContainer++;
				
				outFile << "This coin does not fit in the bent coin container" << endl;
				outFile << "The bent coin container has been replaced" << endl;
				outFile << "The coin in the new bent coin container weighs " << weightBentContainer << " grams"<< endl;
			}
			
			outFile << "The Coin Sorter has sent this coin to the bent coin container" << endl;
			outFile << "The coins in the bent coin container now weighs " << weightBentContainer << " grams" << endl; 

			
		}
	
//Usuable but not Canadian // Other Coins

		else if (coinConditionSensor[countArray] == VALUE5)
		{
			weight[countArray] = WEIGHTSENSORSPRING * weightSensor[countArray] * WEIGHTSENSORMULTIPLIER;

			diameter[countArray] = (DIAMETERSENSORSPRING * diameterSensor[countArray]) + DIAMETERCONSTANT;

			if (imageFaceSensor[countArray] == VALUE2 || imageFaceSensor[countArray] == VALUE3)
			{
				totalOtherCoinWeight += weight[countArray];
				totalOtherCoinsNum++;
			
				if(weightOtherContainer > MAXOTHERCONTAINERWEIGHT)
				{
					weightOtherContainer = 0;
					weightOtherContainer += weight[countArray];
					numOtherCoinContainer++;
				
					outFile << "This coin does not fit in the other coin container" << endl;
					outFile << "The other coin container has been replaced" << endl;
					outFile << "The coin in the new other coin container weighs " << weightOtherContainer << " grams"<< endl;
				}	
				else 
				{
					weightOtherContainer += weight[countArray];			
				
				outFile << "The Coin Sorter has sent this coin to the other coin container" << endl;
				outFile << "The coins in the other coin container now weigh " << weightOtherContainer << " grams" << endl; 
				}
			}
							
//Type of Coin

			else if (imageFaceSensor[countArray] == VALUE1)
			{
				weight[countArray] = WEIGHTSENSORSPRING * weightSensor[countArray] * WEIGHTSENSORMULTIPLIER;

				diameter[countArray] = (DIAMETERSENSORSPRING * diameterSensor[countArray]) + DIAMETERCONSTANT;
				
				if(weight[countArray] <= MAXWEIGHTNICKEL && weight[countArray] >= MINWEIGHTNICKEL && diameter[countArray] <= MAXDIAMETERNICKEL && diameter[countArray] >= MINDIAMETERNICKEL)
				{
					numNickels++;
					outFile << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
					if(numNickels == NICKELSPERROLE)
					{
						numRollsNickels++;
						numNickels = 0;

						outFile << "The nickel wrapper is now full" << endl;
						outFile << "The nickel wrapper has now been replaced" << endl;


					}
					else 
					{
						outFile << "There are now " << numNickels << " in the nickels wrapper" << endl;
					}
				
				}
				else if(weight[countArray] <= MAXWEIGHTDIME && weight[countArray] >= MINWEIGHTDIME && diameter[countArray] <= MAXDIAMETERDIME && diameter[countArray] >= MINDIAMETERDIME)
				{
					numDimes++;
					outFile << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
					if(numDimes == DIMESPERROLE)
					{
						numRollsDimes++;
						numDimes = 0;

						outFile << "The dime wrapper is now full" << endl;
						outFile << "The dime wrapper has now been replaced" << endl;


					}
					else 
					{
						outFile << "There are now " << numDimes << " in the dimes wrapper" << endl;
					}
				}
				else if(weight[countArray] <= MAXWEIGHTQUARTER && weight[countArray] >= MINWEIGHTQUARTER && diameter[countArray] <= MAXDIAMETERQUARTER && diameter[countArray] >= MINDIAMETERQUARTER)
				{
					numQuarters++;
					outFile << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
					if(numQuarters == QUARTERSPERROLE)
					{
						numRollsQuarter++;
						numQuarters = 0;

						outFile << "The quarter wrapper is now full" << endl;
						outFile << "The quarter wrapper has now been replaced" << endl;


					}
					else 
					{
						outFile << "There are now " << numQuarters << " in the quarters wrapper" << endl;
					}
				}
				else if(weight[countArray] <= MAXWEIGHTLOONIE && weight[countArray] >= MINWEIGHTLOONIE && diameter[countArray] <= MAXDIAMETERLOONIE && diameter[countArray] >= MINDIAMETERLOONIE)
				{
					numLoonies++;
					outFile << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
					if(numLoonies == LOONIESPERROLE)
					{
						numRollsLoonies++;
						numLoonies = 0;

						outFile << "The loonie wrapper is now full" << endl;
						outFile << "The loonie wrapper has now been replaced" << endl;


					}
					else 
					{
						outFile << "There are now " << numLoonies << " in the loonies wrapper" << endl;
					}
				}
				else if(weight[countArray] <= MAXWEIGHTTOONIE && weight[countArray] >= MINWEIGHTTOONIE && diameter[countArray] <= MAXDIAMETERTOONIE && diameter[countArray] >= MINDIAMETERTOONIE)
				{
					numToonies++;
					outFile << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
					if(numToonies == TOONIESPERROLE)
					{
						numRollsToonies++;
						numToonies = 0;

						outFile << "The toonie wrapper is now full" << endl;
						outFile << "The toonie wrapper has now been replaced" << endl;


					}
					else 
					{
						outFile << "There are now " << numToonies << " in the toonies wrapper" << endl;
					}
				}
				else 
				{
								
				totalOtherCoinWeight += weight[countArray];
				totalOtherCoinsNum++;
			
					if(weightOtherContainer > MAXOTHERCONTAINERWEIGHT)
					{
						weightOtherContainer = 0;
						weightOtherContainer += weight[countArray];
						numOtherCoinContainer++;
				
						outFile << "This coin does not fit in the other coin container" << endl;
						outFile << "The other coin container has been replaced" << endl;
						outFile << "The coin in the new other coin container weighs " << weightOtherContainer << " grams"<< endl;
					}	
					else 
					{
						weightOtherContainer += weight[countArray];			
				
						outFile << "The Coin Sorter has sent this coin to the other coin container" << endl;
						outFile << "The coins in the other coin container now weigh " << weightOtherContainer << " grams" << endl; 
					
					}
				}
			}
						
		}
countArray++;
}



//Prints summary to output File

outFile << "SUMMARY" << endl;

outFile << "The Coin Sorter made " << numRollsNickels << " rolls of nickels." << endl;
outFile << "There are " << numNickels << " nickels in the partially full roll." << endl;

outFile << "The Coin Sorter made " << numRollsDimes << " rolls of dimes." << endl; 
outFile << "There are " << numDimes << " dimes in the partially full roll." << endl;

outFile << "The Coin Sorter made " << numRollsQuarter << " rolls of quarters." << endl;
outFile << "There are " << numQuarters << " quarters in the partially full roll." << endl;

outFile << "The Coin Sorter made " << numRollsLoonies << " rolls of loonies." << endl;
outFile << "There are " << numLoonies << " loonies in the partially full roll." << endl;

outFile << "The Coin Sorter made " << numRollsToonies << " rolls of toonies." << endl;
outFile << "There are " << numToonies << " toonies in the partially full roll." << endl;

outFile << "The Coin Sorter processed " << totalOtherCoinsNum << " other coins." << endl;
outFile << "The other coins completely filled " << numOtherCoinContainer << " containers" << endl;
outFile << "There were " << numOtherCoins << " other coins in the partially full container" << endl; 

outFile << "The total weight of the other coins was " << totalOtherCoinWeight << " grams" << endl;
outFile << "The Coin Sorter processed " << totalBentCoinWeight << " g of bent coins" << endl;

outFile.close();

//Prints summary to Console

cout << endl << endl << endl;
cout << "SUMMARY" << endl;

cout << "The Coin Sorter made " << numRollsNickels << " rolls of nickels." << endl;
cout << "There are " << numNickels << " nickels in the partially full roll." << endl;

cout << "The Coin Sorter made " << numRollsDimes << " rolls of dimes." << endl; 
cout << "There are " << numDimes << " dimes in the partially full roll." << endl;

cout << "The Coin Sorter made " << numRollsQuarter << " rolls of quarters." << endl;
cout << "There are " << numQuarters << " quarters in the partially full roll." << endl;

cout << "The Coin Sorter made " << numRollsLoonies << " rolls of loonies." << endl;
cout << "There are " << numLoonies << " loonies in the partially full roll." << endl;

cout << "The Coin Sorter made " << numRollsToonies << " rolls of toonies." << endl;
cout << "There are " << numToonies << " toonies in the partially full roll." << endl;

cout << "The Coin Sorter processed " << totalOtherCoinsNum << " other coins." << endl;
cout << "The other coins completely filled " << numOtherCoinContainer << " containers" << endl;
cout << "There were " << numOtherCoins << " other coins in the partially full container" << endl; 

cout << "The total weight of the other coins was " << fixed << setprecision(3)  << totalOtherCoinWeight << " grams" << endl;
cout << "The Coin Sorter processed " << fixed << setprecision(4) << totalBentCoinWeight << " g of bent coins" << endl;

	

	








return 0;
}