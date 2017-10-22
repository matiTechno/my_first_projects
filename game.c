#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Z CIEKAWOSTEK:: stringi porownuje ze soba przy uzyciu znaku nowej lini,
//bo funkcja fgets() nie zwraca znaku '\0'... niestety...

void drukuj(char tab[][10]);
int porownaj(char *wsk1, char *wsk2);
int poziom_lvl(char *wsk1);

int i, j;

int main(void)
{
	//TABLICE DO FUNKCJI POROWNAJ
	char w[]="w\n";
	char s[]="s\n";
	char a[]="a\n";
	char d[]="d\n";
	char i_i[]="i\n";
	char h[]="h\n";
	char M[]="M\n";
	char o[]="o\n";
	char D[]="D\n";
	char m[]="m\n";
	char ruch[10000];//TABLICA DO WCZYTYWANIA
	
		
	int bomby[][10] =  {{1,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0}};
		
	char plansza[][10] = {{'o','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'},
						  {'*','*','*','*','*','*','*','*','*','*'}};
	int HP = 3, MANA = 6;//WYBOR HP i MANY
	printf("\nMateusz Macieja AiR1, gra w bomby.\n"
			"sterowanie:\n\tWSAD - ruch\n\to - jasnowidz(3 pkt many)\n\tD - destruktor(6 pkt many)\n"
			"dodatkowe opcje:\n\tm - widok planszy\n\ti - info\n"
			"legenda:\n\to - aktualna pozycja\n\t* - nieodkryte pole\n\t. - odkryte pole\n\t@ - bomba\n\tB - wybuch\n"
			"Masz %d HP i %d pkt MANY, dotrzyj w prawy dolny rog!!!\n", HP, MANA);
	for(;;) // BEZPIECZNE ODCZYTYWANIE POZIOMU
	{
		printf("Podaj poziom trudnosci(1-99), polecam 20 :)\n");
		fgets(ruch, 10000, stdin);//cin.getline(ruch, 1000);
		//printf("%d\n", poziom_lvl(ruch));
		if(poziom_lvl(ruch)) break;
	}
	srand(time(NULL)); //ZIARNO
	for(i=0; i<poziom_lvl(ruch);) //ROZSTAWIANIE BOMB , dlugo nad tym myslalem :D
	{
		int losx = rand()%10, losy = rand()%10; //<0, 9> 0 + rand()%(9-0+1)
		if(bomby[losy][losx]==0)
		{
			bomby[losy][losx]=1;
			i += 1;
		}
	} 
	printf("\n");//cout << endl;
	drukuj(plansza); //DRUKUJE PLANSZE PIERWSZY RAZ I WCHODZI DO PETLI
	
	
	int x=0, y=0;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PETLA GRY
	while(x+y!=18)
	{
		if(HP)
		{
			fgets(ruch,10000, stdin);//cin.getline(ruch, 1000);
			
			for(i=0; i<10; i++) //czyszczenie pol z wybuchem po uzyciu destruktora
				{
					for(j=0; j<10; j++)
					{
						if(plansza[i][j]=='B') plansza[i][j]='.';
					}
				}
			plansza[y][x]='o'; //rozwiazanie buga z jasnowidzem i destruktorem, gdy uzylo sie tych umiejetnosc w nastepnej turze po wejsciu
			//na bombe, pozycja gracza 'o' byla czyszczona do '.' i nie widoczna.
			
			//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
			if(porownaj(d, ruch))
			{
				if(x<9)
				{
					if(bomby[y][x+1]==0) // jesli na nastepnym polu nie ma bomby
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							x += 1;
							plansza[y][x] = 'o';
							drukuj(plansza);
						
					}
					else // jesli na nastepnym polu jest bomba
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							x += 1;
							plansza[y][x] = 'B';
							HP -= 1;
							drukuj(plansza);
							printf("####BUM HP: %d\n", HP);//cout << "####BUM HP: " << HP <<"\n";
						}
					}
					else {plansza[y][x] = 'o';drukuj(plansza);}
				
			}
			//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
			else if(porownaj(a, ruch))
			{
				if(x>0)
				{
					if(bomby[y][x-1]==0) // jesli na nastepnym polu nie ma bomby
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							x -= 1;
							plansza[y][x] = 'o';
							drukuj(plansza);
						
					}
					else// jesli na nastepnym polu jest bomba
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							x -= 1;
							plansza[y][x] = 'B';
							HP -= 1;
							drukuj(plansza);
							printf("####BUM HP: %d\n", HP);//cout << "####BUM HP: " << HP << "\n";
						
					}
				}
				else {plansza[y][x] = 'o';drukuj(plansza);}
			}
			//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
			else if(porownaj(w, ruch))
			{
				if(y>0)
				{
					if(bomby[y-1][x]==0) // jesli na nastepnym polu nie ma bomby
					{
							bomby[y][x] = 0;	
							plansza[y][x] = '.';
							y -= 1;
							plansza[y][x] = 'o';
							drukuj(plansza);
						
					}
					else// jesli na nastepnym polu jest bomba
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							y -= 1;
							plansza[y][x] = 'B';
							HP -= 1;
							drukuj(plansza);
							printf("####BUM HP: %d\n", HP);//cout << "####BUM HP: " << HP << "\n";
						
					}
				}
				else {plansza[y][x] = 'o';drukuj(plansza);}
			}
			//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
			else if(porownaj(s, ruch))
			{
				if(y<9)
				{
					if(bomby[y+1][x]==0) // jesli na nastepnym polu nie ma bomby
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							y += 1;
							plansza[y][x] = 'o';
							drukuj(plansza);
						
					}
					else// jesli na nastepnym polu jest bomba
					{
							bomby[y][x] = 0;
							plansza[y][x] = '.';
							y += 1;
							plansza[y][x] = 'B';
							HP -= 1;
							drukuj(plansza);
							printf("####BUM HP: %d\n", HP);//cout << "####BUM HP: " << HP << "\n";
						
					}
				}
				else {plansza[y][x] = 'o';drukuj(plansza);}
			}
			//GOD MODE HP++
			else if(porownaj(h, ruch))
			{
				
				HP+=1;
				
			}
			//OKRYJ WSZYSTKIE BOMBY
			else if(porownaj(M, ruch))
			{
				
				for(i=0; i<10; i++)
				{
					for(j=0; j<10; j++)
					{
						plansza[i][j]='.';
					}
				}
				for(i=0; i<10; i++)
				{
					for(j=0; j<10; j++)
					{
						if(bomby[i][j]==1) plansza[i][j]='@';
					}
				}
				plansza[y][x]='o';
				drukuj(plansza);
			}
			//ODSWIEZ MAPE
			else if(porownaj(m, ruch))
			{
				drukuj(plansza);
			}	
			//INFO
			else if(porownaj(i_i, ruch))
			{
				printf("\t%d HP & %d pkt MANY\n"
				"\tjasnowidz - odkrywa otaczajace pola\n\tdestruktor - nie trzeba tlumaczyc :D\n"
				"\tDLA MODERATORA\n\th - dodaje jedno HP\n\tM - odrywa bomby\n", HP, MANA);
			}
			//jasnowidz
			else if(porownaj(o, ruch))
			{
				if((y<9 && y>0) && (x<9 && x>0))
				{
					if(MANA>2)
					{
						MANA -= 3;
						if(bomby[y][x+1]==1)plansza[y][x+1]='@'; else plansza[y][x+1]='.'; 
						if(bomby[y][x-1]==1)plansza[y][x-1]='@'; else plansza[y][x-1]='.';
						if(bomby[y-1][x]==1)plansza[y-1][x]='@'; else plansza[y-1][x]='.';
						if(bomby[y+1][x]==1)plansza[y+1][x]='@'; else plansza[y+1][x]='.';
						if(bomby[y+1][x+1]==1)plansza[y+1][x+1]='@'; else plansza[y+1][x+1]='.';
						if(bomby[y+1][x-1]==1)plansza[y+1][x-1]='@'; else plansza[y+1][x-1]='.';
						if(bomby[y-1][x-1]==1)plansza[y-1][x-1]='@'; else plansza[y-1][x-1]='.';
						if(bomby[y-1][x+1]==1)plansza[y-1][x+1]='@'; else plansza[y-1][x+1]='.';
						
						drukuj(plansza);
						printf("MASZ %d MANY\n", MANA);//cout <<"MASZ "<< MANA <<" MANY\n";
					}
					else
					{
						printf("Nie masz wystarczajaco many\n");//cout<<"Nie masz wystarczajaco many\n";
					}
				}
				else printf("jasnowidz dziala tylko w polu gry\n");//cout<<"jasnowidz dziala tylko w polu gry\n";
			}
			//destruktor
			else if(porownaj(D, ruch))
			{
				if((y<9 && y>0) && (x<9 && x>0))
				{
					if(MANA==6)
					{	MANA -= 6;
						
						if(bomby[y][x+1]==1)plansza[y][x+1]='B'; else plansza[y][x+1]='.'; //ustawianie symboli w tab plansza
						if(bomby[y][x-1]==1)plansza[y][x-1]='B'; else plansza[y][x-1]='.';
						if(bomby[y-1][x]==1)plansza[y-1][x]='B'; else plansza[y-1][x]='.';
						if(bomby[y+1][x]==1)plansza[y+1][x]='B'; else plansza[y+1][x]='.';
						if(bomby[y+1][x+1]==1)plansza[y+1][x+1]='B'; else plansza[y+1][x+1]='.';
						if(bomby[y+1][x-1]==1)plansza[y+1][x-1]='B'; else plansza[y+1][x-1]='.';
						if(bomby[y-1][x-1]==1)plansza[y-1][x-1]='B'; else plansza[y-1][x-1]='.';
						if(bomby[y-1][x+1]==1)plansza[y-1][x+1]='B'; else plansza[y-1][x+1]='.';
						bomby[y][x+1]=0; //ZEROWANIE BOMB W TAB BOMBA
						bomby[y-1][x]=0;
						bomby[y][x-1]=0;
						bomby[y+1][x]=0;
						bomby[y+1][x+1]=0;
						bomby[y+1][x-1]=0;
						bomby[y-1][x-1]=0;
						bomby[y-1][x+1]=0;
						
						drukuj(plansza);
						printf("MASZ %d MANY\n", MANA);//cout <<"MASZ "<< MANA <<" MANY\n";
					}
					else
					{
						printf("Nie masz wystarczajaco many\n");//cout<<"Nie masz wystarczajaco many\n";
					}
				}
				else printf("destruktor dziala tylko w polu gry\n");//cout<<"destruktor dziala tylko w polu gry\n";
			}
				
			//INNY KLAWISZ NIZ WSAD
			else 
			{
				printf("try again\n");//cout << "try again\n";
			}
		
		
		
		}
		//JESLI HP = 0
		if(HP==0)
		{
			printf("GAME OVER");//cout << "GAME OVER";
			goto koniec;
			
		}
	}
	//JESLI ZNAJDUJESZ SIE NA POLU [9][9]
	printf("U WON!!!!!!!!!!!!!!!!");//cout << "U WON!!!!!!!!!!!!!!!!";
	koniec: printf("\nthx for gaming\n");//cout << "\nthx for gaming\n";
	return 0;
}
//FUNKCJA DO DRUKOWANIA TABLICY 'PLANSZA'
void drukuj(char tab[][10])
{
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			printf("%c ", tab[i][j]);//cout << tab[i][j] << " ";
		}
		printf("\n");//cout <<endl;
	}
}
//funkcja do porownywania c-stringow
int porownaj(char *wsk1, char *wsk2)
{
	while(*wsk1==*wsk2)
	{
		if(*wsk1=='\n' || *wsk2=='\n') break;
		wsk1++;
		wsk2++;
	}
	if(*wsk1=='\n' && *wsk2=='\n') return 1;
	else return 0;
}
//funkcja do porownywania c-stringow dla wczytania poziomu######################################################################
//robiona dluzej niz caly program...
int poziom_lvl(char *wsk1)
{
	if(*(++wsk1)=='\n')
	{
		wsk1--;//powrot wskaznika na pierwsza cyfre
		if(*wsk1 >= 48 && *wsk1 <= 57) return *wsk1 - 48;
		else return 0;
	}
	//###################################
	else if(1)
	{
		if(*(++wsk1)=='\n')//tricky part - nawet jak nie wchodzi w petle to inkrementuje pozycje wskaznika...
		{
			wsk1--;
			if(*wsk1 >= 48 && *wsk1 <= 57)
			{
				wsk1--;
				if(*wsk1 >= 48 && *wsk1 <= 57)
				{
					int lolol = (*wsk1-48)*10; //konwertowanie znakow ASCII na liczby...
					wsk1++;
					int lolol2 = *wsk1-48;
					return lolol+lolol2;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}
