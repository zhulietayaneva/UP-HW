#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include "UP-HW.h"
using namespace std;
constexpr int MAX_SIZE = 31;
constexpr int SIZE = 31;
constexpr int MAX_CARDS = 100;
char cards[MAX_CARDS][7]{};
//void OrderSentences()
//{
//	int n;
//	cin >> n;
//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//	char input[MAX_SIZE][MAX_SIZE]{};
//
//	for (size_t i = 0; i < n; i++)
//	{
//		cin.getline(input[i], MAX_SIZE);
//	}
//
//	for (size_t i = 0; i < n; i++)
//	{
//
//		for (size_t j = i + 1; j < n; j++)
//		{
//
//			if (_strcmpi(input[i], input[j])>0)
//			{
//				char temp[MAX_SIZE];
//				strcpy_s(temp, input[i]);
//				strcpy_s(input[i], input[j]);
//				strcpy_s(input[j], temp);
//			}
//		}
//	}
//
//	for (size_t i = 0; i < n; i++)
//	{
//		cout << input[i] << endl;
//	}
//}


int doesOverlap(int nums[]) {

	if (nums[0]<=nums[2] && nums[1]>=nums[3])
	{
		return 1;
	}
	return 0;
}
void Zadacha1()
{
	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	char input[256]{};
	int nums[4]{};
	int count = 0;
	for (size_t i = 0; i < n; i++)
	{
		cin.getline(input, 256);
		stringstream ss(input);

		for (int i = 0; i < 4; i++) {
			ss >> nums[i];
		}

		count += doesOverlap(nums);
	}
	cout << count;
}




char* getCardColor(char num)
{
	/*●	Най-старшата цифра (1 в примера) дава информация за цвета на картата:
	1 - жълт, 2 - зелен, 3 - син, 4 - червен, 5 - черен.
	Всички други стойности на тази позиция са невалидни. */

	char res[15]{};
	switch (num)
	{
	case '1': strcpy_s(res, "YELLOW"); break;
	case '2': strcpy_s(res, "GREEN");  break;
	case '3': strcpy_s(res, "BLUE");   break;
	case '4': strcpy_s(res, "RED");	   break;
	case '5': strcpy_s(res, "BLACK");  break;

	default: strcpy_s(res, "INVALID"); break;
	}
	
	return res;
}
char* getCardValue(char values[], char color)
{
	/*●	Четвъртата и петата цифра (0 и 8 в примера) носят информация за стойността на картата - 
	от 00 до 09 представляват числата от 0 до 9, 
	10 - “+2”,
	11 - обръщане на реда, 
	12 - стоп (валидни стойности само за карти, които не са черни), 
	13 - смяна на цвета, 
	14 - “+4” (валидни стойности само за черни карти). 
	Всички други стойности на тези позиции са невалидни. */

	char res[30]{};

	if (*values == '0' && *(values+1) >= '1' && *(values+1) <= '9')
	{
		res[0] = *(values + 1);		
	}
	else if (*values=='1')
	{
		switch (*(values+1))
		{
		case '0': strcpy_s(res, "+2");										break;
		case '1': strcpy_s(res, "REVERSE");									break;
		case '2': if (strcmp(getCardColor(color), "BLACK") != 0)
				  {
						strcpy_s(res, "STOP");
				  }
				  else
				  {
						strcpy_s(res, "INVALID");
				  }
																			break;
		case '3': strcpy_s(res, "CHANGE COLOR");							break;
		case '4': if (strcmp(getCardColor(color),"BLACK")==0)
				  {
						strcpy_s(res, "+4");
				  }
				  else
				  {
						strcpy_s(res, "INVALID");
				  }
																			break;
		default: strcpy_s(res, "INVALID");									break;
		}
	}
	else
	{
		strcpy_s(res, "INVALID");
	}

	res[29] = '\0';
	return res;
}

void sortCards()
{
	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	char input[6000]{};
	cin.getline(input, 6000);
	
	int count = 0;
	int cardIndex = 0;
	char curr[7]{};
	for (size_t i = 0; i < strlen(input); i++)
	{
		
		if (input[i]!=' ')
		{
			curr[count] = input[i];
			count++;
		}
		else
		{
			char params[2]{ curr[3],curr[4] };
			if (strcmp(getCardColor(curr[0]), "INVALID")==0 || strcmp(getCardValue(params, curr[0]), "INVALID")==0)
			{
				continue;
				curr[0] = { '\0' };
				count = 0;
			}
			strcpy_s(cards[cardIndex], curr);
			curr[0] = {'\0'};
			count = 0;
			cardIndex++;
		}
	}
	strcpy_s(cards[cardIndex], curr);

	for (size_t i = 0; i < n-1; i++)
	{
		for (size_t j=i+1 ; j < n; j++)
		{
			char currI[7]{};
			strcpy_s(currI, cards[i]);

			char currJ[7]{};
			strcpy_s(currJ, cards[j]);

			char paramsI[2]{ currI[3],currI[4] };
			char paramsJ[2]{ currJ[3],currJ[4] };
			if ( stoi(paramsI)>stoi(paramsJ))
			{
				char temp[7]{};
				strcpy_s(temp, cards[i]);
				strcpy_s(cards[i], cards[j]);
				strcpy_s(cards[j], temp);

			}
			else if (stoi(paramsI) == stoi(paramsJ))
			{
				if (currI[0]-'0' < currJ[0]-'0')
				{
					char temp[7]{};
					strcpy_s(temp, cards[i]);
					strcpy_s(cards[i], cards[j]);
					strcpy_s(cards[j], temp);
				}
			}
		}
	}


	for (size_t i = 0; i < n; i++)
	{
		char* print = (getCardColor(cards[i][0]));

		cout << *print << endl;
	}
	for (size_t i = 0; i < n; i++)
	{
		string print1 = (getCardColor(cards[i][0]));
		
		char params[2]{ cards[i][3],cards[i][4] };
		string print2 = (getCardValue(params, cards[i][0]));

		cout << print1<<" "<<print2 << endl;
	}
}

int main()
{	
	sortCards();
}


