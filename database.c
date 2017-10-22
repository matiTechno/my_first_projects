#include <stdio.h>
#include <stdlib.h>

/// zrobilem liste odwrocona, tzn nie tworze "nastepnych" elementow tylko "poprzednie"... identyfikator listy caly czas wedruje

/// dodawanie, usuwanie, edytowanie rekordow  ####
/// sortowanie ####
/// prezentacja wynikow ####
/// zapisywanie bazy do pliku ####
/// 																				odczyt z pliku format |dane|dane|dane|dane|dane|dane| 
/// czyszczenie bazy ####                                                           pomiedzy | | moga byc biale znaki za wylaczeniem znaku nowej linii
/// podzielic program na pliki !!!													
/// zabezpieczyc program przed podaniem niepoprawnych danych ####
/// 																				dane w polach rekordu musza byc sensowne ???
/// 																				pole gatunek 5 mozliwosci + dodawanie + edycja + usuwanie ???
/// 
///                    znak '~' - nazwa czegokolwiek nie moze byc samym znakiem tyldy
///                    znak '|' - ten znak zarezerwowany jest dla programu
///  program dziala na tablicach 100 elementowych, zatem 99 elementow moze byc wczytanych z funkcji fgets
///                    maksymalna liczba rekordow 999  nazwa nie moze zaczynac sie od innych znakow ascii niz znak widoczny, spacja i nowa linia i '\0'



//moje funkcje zwracaja 1 jako wartosc pozytywna
int compare(char *wsk1, char *wsk2);
void kreator(char *tab_name, char *tab_developer, char *tab_genre, char *tab_memory, char *tab_price, char *tab_platform);
void my_strcpy(char *napis_do, char *napis_z);// ^^^^^^^^^^^^^^^^^^ tab 100
void del_new_line(char *napis);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
int file_name(char *nazwa);
int read_number(char *wsk1);
void clear_tab(char *tab);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
void space_hack(char *tab, int i);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
int check_for_char(char *napis);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
int no_white_char(char *napis);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
void clear_spaces(char *napis);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
int compare2(char *wsk1, const char *wsk2);
int alfabetycznie(char *wsk1, char *wsk2);
void mini_sort(int a);
int count_my_char(char *string);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ tab 100
void strcpy_till_my_char(char *string);
double read_double (char *string);

//funkcje interfejsu
void new();
void ls();
void del();
void edit();
void clear();
void save();
void screen();
void sort();
void set();
void load();

///###################################################################### GLOBAL STUFF
FILE *fp, *fp2; 

int name_spaces = 18,    // ustawienia ekranu
	developer_spaces= 14,
	genre_spaces = 10,
	memory_spaces = 11,
	price_spaces = 5,
	platform_spaces= 8;

char screen_game[100]="G A M E";
char screen_developer[100]="developer";
char screen_genre[100]="genre";
char screen_memory[100]="storage dev";
char screen_price[100]="price";
char screen_platform[100]="platform"; // koniec ustawien ekranu

typedef struct game {
	struct game *previous;
	char name[100];
	char developer[100];
	char genre[100];
	char memory[100];
	char price[100];
	char platform[100];}game;
	
game *last_game;
	
char tab_name[100];
char tab_developer[100];
char tab_genre[100];
char tab_memory[100];
char tab_price[100];
char tab_platform[100];

char command[100];

int quantity;
///#######################################################################

int main(void)
{	
	game *pointer1;
	
	char new_tab[]={'n','e','w','\n'}; //################## command options
	char ls_tab[]={'l','s','\n'};
	char del_tab[]={'d','e','l','\n'};
	char edit_tab[]={'e','d','i','t','\n'};
	char exit_tab[]={'e','x','i','t','\n'};
	char clear_tab_OMG[]={'c','l','e','a','r','\n'};
	char save_tab[]={'s','a','v','e','\n'};
	char screen_tab[]={'s','c','r','e','e','n','\n'};
	
	printf("\n:::\n:::\nGAME manager\noptions:\n\tnew\n\tedit\n\tdel\n\tls\n\tsort\n\tclear\n\tsave\n\tload\n\tset\n\tscreen\n\texit\n\t### help\n");
	///@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if(!(fp=fopen("gamebase_config.txt", "r"))) printf("\n#### no config file ####\n"); /// wczytywanie ustawien ekranu
	else
	{
		
		fgets(command, 100, fp);
		name_spaces = read_number(command);
		
		fgets(command, 100, fp);
		developer_spaces = read_number(command);
		
		fgets(command, 100, fp);
		genre_spaces = read_number(command);
		
		fgets(command, 100, fp);
		memory_spaces = read_number(command);
		
		fgets(command, 100, fp);
		price_spaces = read_number(command);
		
		fgets(command, 100, fp);
		platform_spaces = read_number(command);
		
		fclose(fp);
		printf("\n## config file loaded - for default settings remove file gamebase_config.txt\n");
	}
	///@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if(!(fp2=fopen("gamebase_set.txt", "r"))) printf("#### no database set ####\n"); /// wczytywanie bazy startowej
	else
	{
			fgets(command, 100, fp2);
			
						
						
						if(!(fp=fopen(command, "r"))) printf("file name in database_set.txt is probably misspelled\n");
						else
						{
							printf("adding games...\n");
							fgets(command, 100, fp);
							fgets(command, 100, fp);
							
							for(;;)
							{
								clear_tab(command);
								if(!fgets(command, 100, fp)) break;
								
								else if(count_my_char(command)==7 && no_white_char(command))
								{
									//kreator
									clear_tab(tab_name);
									clear_tab(tab_developer);
									clear_tab(tab_genre);
									clear_tab(tab_memory);
									clear_tab(tab_price);
									clear_tab(tab_platform);
									
									strcpy_till_my_char(command);
									
									space_hack(tab_name, name_spaces);
									space_hack(tab_developer, developer_spaces);
									space_hack(tab_genre, genre_spaces);
									space_hack(tab_memory, memory_spaces);
									space_hack(tab_price, price_spaces);
									space_hack(tab_platform, platform_spaces);
									
									kreator(tab_name, tab_developer, tab_genre, tab_memory, tab_price, tab_platform);
								}
								else printf("\n\tformat invalid\n");
							}
							printf("\n");
							fclose(fp);
						}
		
		fclose(fp2);
	}
	
	space_hack(screen_game, name_spaces); // ustawianie ekranu
	space_hack(screen_developer, developer_spaces);
	space_hack(screen_genre, genre_spaces);
	space_hack(screen_memory, memory_spaces);
	space_hack(screen_price, price_spaces);
	space_hack(screen_platform, platform_spaces);
	
	
	while(1)//########################################################################### program loop
	{
		quantity = 0;
		pointer1 = last_game; //zerowanie moich wskaznikow pomocniczych
		while(pointer1)
		{
			pointer1 = pointer1 -> previous;
			quantity++;
		}
		pointer1 = last_game;
		
		fgets(command, 100, stdin);
		
		//###################################### command execution
		if(compare(command, new_tab)) new();
		else if(compare(command, ls_tab)) ls();
		else if(compare(command, del_tab)) del();
		else if(compare(command, edit_tab)) edit();
		else if(compare(command, exit_tab)) goto koniec;
		else if(compare(command, clear_tab_OMG)) clear();
		else if(compare(command, save_tab)) save();
		else if(compare2(command, "sort\n")) sort();
		else if(compare2(command, "set\n")) set();
		else if(compare2(command, "load\n")) load();
		else if(compare(command, screen_tab)) screen();
		else if(compare2(command, "help\n"))
		printf("\n"
		"This is a user guide.\n"
		"Some basic mechanics are shown.\n"
		"The program cannot handle more than 1000 records and\n"
		"99 characters per string.\n"
		"Ls stands for list and prints all records.\n"
		"Clear deallocates the program's dynamic memory.\n"
		"Screen is a really helpful tool. It allows you to\n"
		"manipulate columns' width so the ls fits.\n"
		"When using save or load remember to put .txt\n"
		"at the end of a file name. Load does not clear records.\n"
		"Input file needs to be formatted in the way in which ls formats,\n"
		"but lines do not have to be numbered.\n"
		"Note that first two lines are always dismissed.\n"
		"Set is used to auto load the database.\n"
		"Sort has two states, normal and reversed.\n"
		"They can be switched into each other by simply reusing the function.\n"
		"Here are some tricks. Type '|' in new or edit functions\n"
		"to stop current process.\n"
		"Every time program requires yes/no or specifed data, type\n"
		"enter to avoid changes.\n\n");
		
		else printf("try again\n");
	}
	koniec:
	printf(":::\n:::\nthank YOU!\n\n"); //### program end
	return 0;
}

///                                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ F U N K C J E
//################################## compare
int compare(char *wsk1, char *wsk2)
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
//################################## kreator
void kreator(char *tab_name, char *tab_developer, char *tab_genre, char *tab_memory, char *tab_price, char *tab_platform)
{
	game *pointer1= malloc(sizeof(game));
	
	if(pointer1)
	{	
		my_strcpy(pointer1 -> name, tab_name);
		my_strcpy(pointer1 -> developer, tab_developer);
		my_strcpy(pointer1 -> genre, tab_genre);
		my_strcpy(pointer1 -> memory, tab_memory);
		my_strcpy(pointer1 -> price, tab_price);
		my_strcpy(pointer1 -> platform, tab_platform);
		pointer1 -> previous = last_game; //lista
		last_game = pointer1;//             lista
		printf("\t*");
	}
	else printf("not enough memory\n");
}
//#################################### strcpy
void my_strcpy(char *napis_do, char *napis_z)
{
	int i;
	for(i=0;i<100;i++)
	{
		*(napis_do++)=*(napis_z++);
	}
}
//#################################### del_new_line
void del_new_line(char *napis)
{
	int i = 0;
	while((*(napis) != '\n') && (i < 100)) 
	{
		napis++;
		i++;
	}
	if(*napis=='\n') *napis=0;
}	
//#################################### file_name	
int file_name(char *nazwa)
{
	while(*nazwa != 0) nazwa++;
	if(*(--nazwa) == 't')
	{
		if(*(--nazwa) == 'x')
		{
			if(*(--nazwa) == 't')
			{
				if(*(--nazwa) == '.') return 1;
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}
//##################################### read_number
int read_number(char *wsk1)
{
	
	int part100, part10, part1;
	
	if(*(++wsk1)=='\n')
	{ 
		wsk1--;
		if(*wsk1 >= 48 && *wsk1 <= 57) return *wsk1 - 48;
		else return 0;
	}
	else if(*(++wsk1)=='\n')
	{
		wsk1--;
		if(*wsk1 >= 48 && *wsk1 <= 57)
		{
			wsk1--;
			if(*wsk1 >= 48 && *wsk1 <= 57)
			{
				part10 = (*wsk1-48)*10; 
				wsk1++;
				part1 = *wsk1-48;
				return part10+part1;
			}
			else return 0;
		}
		else return 0;
	}
	else if(*(++wsk1)=='\n')
	{	
		wsk1--;
		if(*wsk1 >= 48 && *wsk1 <= 57)
		{
			wsk1--;
			if(*wsk1 >= 48 && *wsk1 <= 57)
			{
				wsk1--;
				if(*wsk1 >= 48 && *wsk1 <= 57)
				{
					part100 = (*wsk1-48)*100; 
					wsk1++;
					part10 = (*wsk1-48)*10;
					wsk1++;
					part1 = *wsk1-48;
					return part100+part10+part1;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}
//################################################## new 
void new()
{
	clear_tab(tab_name);
	clear_tab(tab_developer);
	clear_tab(tab_genre);
	clear_tab(tab_memory);
	clear_tab(tab_price);
	clear_tab(tab_platform);
	
	printf("game\n");
	fgets(tab_name, 100, stdin);
	if(no_white_char(tab_name)==0){printf("invalid string\n"); return;}
	if(check_for_char(tab_name)==0){printf("\t'|' can't be used\n"); return;}
	
	printf("developer\n");
	fgets(tab_developer, 100, stdin);
	if(no_white_char(tab_developer)==0){printf("invalid string\n"); return;}
	if(check_for_char(tab_developer)==0){printf("\t'|' can't be used\n"); return;}
	
	printf("genre\n");
	fgets(tab_genre, 100, stdin);
	if(no_white_char(tab_genre)==0){printf("invalid string\n"); return;}
	if(check_for_char(tab_genre)==0){printf("\t'|' can't be used\n"); return;}
	
	printf("storage device\n");
	fgets(tab_memory, 100, stdin);
	if(no_white_char(tab_memory)==0){printf("invalid string\n"); return;}
	if(check_for_char(tab_memory)==0){printf("\t'|' can't be used\n"); return;}
	
	printf("price\n");
	fgets(tab_price, 100, stdin);
	if(no_white_char(tab_price)==0){printf("invalid string\n"); return;}
	if(check_for_char(tab_price)==0){printf("\t'|' can't be used\n"); return;}
	
	printf("platform\n");
	fgets(tab_platform, 100, stdin);
	if(no_white_char(tab_platform)==0){printf("invalid string\n"); return;}
	if(check_for_char(tab_platform)==0){printf("\t'|' can't be used\n"); return;}
	
	del_new_line(tab_name);	
	del_new_line(tab_developer);
	del_new_line(tab_genre);
	del_new_line(tab_memory);
	del_new_line(tab_price);
	del_new_line(tab_platform);
	
	space_hack(tab_name, name_spaces);
	space_hack(tab_developer, developer_spaces);
	space_hack(tab_genre, genre_spaces);
	space_hack(tab_memory, memory_spaces);
	space_hack(tab_price, price_spaces);
	space_hack(tab_platform, platform_spaces);
	
	kreator(tab_name, tab_developer, tab_genre, tab_memory, tab_price, tab_platform);
	printf("\ndone\n");
}
//################################################## ls
void ls()
{	
	int i = 1;
	game *pointer1 = last_game;
	printf("     |%s|%s|%s|%s|%s|%s|\n\n", screen_game, screen_developer, screen_genre, screen_memory, screen_price, screen_platform);
	while(pointer1)
	{
		if(i<10) printf("%d    ", i++);

		else if(i<100) printf("%d   ", i++);
		
		else printf("%d  ", i++); 
		printf("|%s|%s|%s|%s|%s|%s|\n", pointer1->name, pointer1->developer, pointer1->genre,
		pointer1->memory, pointer1->price, pointer1->platform);
		
		
		pointer1 = pointer1 -> previous;
	}
	//char tab_test[100];
	//my_strcpy(tab_test, last_game -> name);                                                do debugowania
	//for(i=0;i<100;i++) printf("%d    %d\n", tab_test[i], tab_name[i]);///test
}
//################################################## del
void del()
{
	int game_no, i;
	char yes[]={'y','e','s','\n'};
	game *pointer1 = last_game, *pointer2 = last_game, *pointer3 = last_game;
	
	printf("game number\n");
	fgets(command, 100, stdin);
	game_no = read_number(command);
	
	if(!game_no || game_no > quantity) printf("no such game\n");
	
	else
	{	
		printf("delete game %d? yes/no\n", game_no);
		fgets(command, 100, stdin);
		
		
		if(compare(command, yes))
		{	
			
			if(quantity==1)
			{
				free(last_game);
				last_game = 0;
			}
			else if(game_no==quantity)
			{
				for(i=1; i<game_no; i++)
				{
					pointer2 = pointer2 -> previous; // wskaznik na usuwany rekord
				}
				for(i=2; i<game_no; i++)
				{
					pointer1 = pointer1 -> previous; // wskaznik na o jeden nowszy rekord
				}
				pointer1 -> previous = 0;
				free(pointer2);
			}
			else if(game_no==1)
			{
				for(i=1; i<game_no; i++)
				{
					pointer2 = pointer2 -> previous; // wskaznik na usuwany rekord
				}
				for(i=0; i<game_no; i++)
				{
					pointer3 = pointer3 -> previous; // wskaznik na o jeden starszy rekord
				}
				last_game = pointer3; 
				free(pointer2);
			}
			else
			{
				for(i=1; i<game_no; i++)
				{
					pointer2 = pointer2 -> previous; // wskaznik na usuwany rekord
				}
				for(i=2; i<game_no; i++)
				{
					pointer1 = pointer1 -> previous; // wskaznik na o jeden nowszy rekord
				}
				for(i=0; i<game_no; i++)
				{
					pointer3 = pointer3 -> previous; // wskaznik na o jeden starszy rekord
				}
				pointer1 -> previous = pointer3;
				free(pointer2);
			}
			printf("done\n");	
		}
		else
		{
			printf("abandoned\n");
		}	
	}	
}
//################################################## edit
void edit()
{
	int game_no, i;
	char tilde[]={'~','\n'};
	game *pointer1 = last_game;
	
	printf("game number\n");
	fgets(command, 100, stdin);
	game_no = read_number(command);
	
	if(!game_no || game_no > quantity) printf("no such game\n");
	
	else
	{
		clear_tab(tab_name);
		clear_tab(tab_developer);
		clear_tab(tab_genre);
		clear_tab(tab_memory);
		clear_tab(tab_price);
		clear_tab(tab_platform);
		
	
		for(i=1; i<game_no; i++)
		{
			pointer1 = pointer1 -> previous; // wskaznik na edytowany rekord
		}
		printf("enter new data or type ~ to leave untouched\n");
		
		printf("game\n");
		fgets(tab_name, 100, stdin);
		if(no_white_char(tab_name)==0){printf("invalid string\n"); return;}
		if(check_for_char(tab_name)==0){printf("\t'|' can't be used\n"); return;}
		
		printf("developer\n");
		fgets(tab_developer, 100, stdin);
		if(no_white_char(tab_developer)==0){printf("invalid string\n"); return;}
		if(check_for_char(tab_developer)==0){printf("\t'|' can't be used\n"); return;}
		
		printf("genre\n");
		fgets(tab_genre, 100, stdin);
		if(no_white_char(tab_genre)==0){printf("invalid string\n"); return;}
		if(check_for_char(tab_genre)==0){printf("\t'|' can't be used\n"); return;}
		
		printf("storage device\n");
		fgets(tab_memory, 100, stdin);
		if(no_white_char(tab_memory)==0){printf("invalid string\n"); return;}
		if(check_for_char(tab_memory)==0){printf("\t'|' can't be used\n"); return;}
		
		printf("price\n");
		fgets(tab_price, 100, stdin);
		if(no_white_char(tab_price)==0){printf("invalid string\n"); return;}
		if(check_for_char(tab_price)==0){printf("\t'|' can't be used\n"); return;}
		
		printf("platform\n");
		fgets(tab_platform, 100, stdin);
		if(no_white_char(tab_platform)==0){printf("invalid string\n"); return;}
		if(check_for_char(tab_platform)==0){printf("\t'|' can't be used\n"); return;}
		
		if(!compare(tab_name, tilde))
		{
			del_new_line(tab_name);
			space_hack(tab_name, name_spaces);
			my_strcpy(pointer1 -> name, tab_name);
		}
		if(!compare(tab_developer, tilde))
		{
			del_new_line(tab_developer);
			space_hack(tab_developer, developer_spaces);
			my_strcpy(pointer1 -> developer, tab_developer);
		}
		if(!compare(tab_genre, tilde))
		{
			del_new_line(tab_genre);
			space_hack(tab_genre, genre_spaces);
			my_strcpy(pointer1 -> genre, tab_genre);
		}
		if(!compare(tab_memory, tilde))
		{
			del_new_line(tab_memory);
			space_hack(tab_memory, memory_spaces);
			my_strcpy(pointer1 -> memory, tab_memory);
		}
		if(!compare(tab_price, tilde))
		{
			del_new_line(tab_price);
			space_hack(tab_price, price_spaces);
			my_strcpy(pointer1 -> price, tab_price);
		}
		if(!compare(tab_platform, tilde))
		{
			del_new_line(tab_platform);
			space_hack(tab_platform, platform_spaces);
			my_strcpy(pointer1 -> platform, tab_platform);
		}
		printf("changes saved\n");
	}
}
//################################################## clear
void clear()
{
	game *pointer1;
	
	printf("double check yes/no\n");
	fgets(command, 100, stdin);
		
		
	if(compare2(command, "yes\n"))
	{
		while(last_game)
		{
			pointer1 = last_game;
			last_game = last_game -> previous;
			free(pointer1);
			printf("\t*");
		}
		printf("\ncleared\n");
	}
	else printf("abandoned\n");
}
//################################################# save
void save()
{
	printf("file name\n");
	fgets(command, 100, stdin);
	del_new_line(command);
	
	if(!file_name(command)) printf("invalid name\n");
	else if(!(fp=fopen(command, "w"))) printf("no permission\n");
	else
	{
		int i = 1;
		game *pointer1 = last_game;
		fprintf(fp, "     |%s|%s|%s|%s|%s|%s|\n\n", screen_game, screen_developer, screen_genre, screen_memory, screen_price, screen_platform);
		while(pointer1)
		{
			if(i<10) fprintf(fp, "%d    ", i++);

			else if(i<100) fprintf(fp, "%d   ", i++);
			
			else fprintf(fp, "%d  ", i++); 
			fprintf(fp, "|%s|%s|%s|%s|%s|%s|\n", pointer1->name, pointer1->developer, pointer1->genre,
			pointer1->memory, pointer1->price, pointer1->platform);
		
		
			pointer1 = pointer1 -> previous;
		}
		
		fclose(fp);
		printf("data saved\n");
	}
}
//################################################# space_hack
void space_hack(char *tab, int i)
{
	int j;
	char *wsk = tab;
	for(j=0;j<i;j++)// sprawdza czy przypadkiem w tablicy nie ma samych zer
	{
		if(*(wsk++)) break;
	}
	if(*(--wsk))// jesli nie to uzupelnia spacjami od gory ...10, 9, 8, ...
	{
		tab = tab + i - 1;
		while(!*tab)
		{
			*(tab--)=' ';
		}
	}
	else// jesli sa tylko zera to cala tablice wypelnia spacjami od dolu ...0, 1, 2, ...
	{
		for(j=0;j<i;j++)
		{
			*(tab++)=' ';
		}
	}
}
//################################################# clear_tab
void clear_tab(char *tab)
{
	int i;
	for(i=0; i<100; i++)
	{
		*(tab++)=0;
	}
}
//################################################# check_for_char
int check_for_char(char *napis)
{
	int i = 0;
	while((*(napis) != '|') && (i < 100)) 
	{
		napis++;
		i++;
	}
	if(*napis=='|') return 0;
	else return 1;
}
//################################################# no_white_char
int no_white_char(char *napis)
{
	//od 32 do 126 (*napis >= 32 && *napis <= 126)
	int i;
	for(i=0; i<100; i++)
	{	
		if(!(*napis >= 32 && *napis <= 126) && !(*napis==10) && !(*napis==0)) return 0;
		napis++;
	}
	return 1;
}
//################################################## screen
void screen()
{
	char tab7[]={'y','e','s','\n'};
	
	printf("video settings\n\tgame width: %d\n\tdeveloper width: %d\n\tgenre width: %d\n\tmemory dev width: %d\n\t"
	"price width: %d\n\tplatform width: %d\ntype new values\n", name_spaces, developer_spaces, genre_spaces, memory_spaces,
	price_spaces, platform_spaces);
	
	printf("game width\n");
	fgets(command, 100, stdin);
	if(read_number(command)) name_spaces = read_number(command);
	else printf("\twrong data\n");
	
	printf("developer width\n");
	fgets(command, 100, stdin);
	if(read_number(command)) developer_spaces = read_number(command);
	else printf("\twrong data\n");
	
	printf("genre width\n");
	fgets(command, 100, stdin);
	if(read_number(command)) genre_spaces = read_number(command);
	else printf("\twrong data\n");
	
	printf("memory dev width\n");
	fgets(command, 100, stdin);
	if(read_number(command)) memory_spaces = read_number(command);
	else printf("\twrong data\n");
	
	printf("price width\n");
	fgets(command, 100, stdin);
	if(read_number(command)) price_spaces = read_number(command);
	else printf("\twrong data\n");
	
	printf("platform width\n");
	fgets(command, 100, stdin);
	if(read_number(command)) platform_spaces = read_number(command);
	else printf("\twrong data\n");
	
	printf("save to config file? yes/no\n");
	fgets(command, 100, stdin);
	if(compare(command, tab7))
	{
		if(!(fp=fopen("gamebase_config.txt", "w"))) printf("no permission\n");
		else 
		{
			fprintf(fp, "%d\n%d\n%d\n%d\n%d\n%d\n", name_spaces, developer_spaces, genre_spaces, 
			memory_spaces, price_spaces, platform_spaces);
			fclose(fp);
			printf("saved\n");
		}
	}
	else printf("unsaved\n");
	
	clear_spaces(screen_game);
	clear_spaces(screen_developer);
	clear_spaces(screen_genre);
	clear_spaces(screen_memory);
	clear_spaces(screen_price);
	clear_spaces(screen_platform);
	
	space_hack(screen_game, name_spaces);
	space_hack(screen_developer, developer_spaces);
	space_hack(screen_genre, genre_spaces);
	space_hack(screen_memory, memory_spaces);
	space_hack(screen_price, price_spaces);
	space_hack(screen_platform, platform_spaces);
	
	game *pointer1 = last_game;
	
	while(pointer1)
	{	
		clear_spaces(pointer1 -> name);
		clear_spaces(pointer1 -> developer);
		clear_spaces(pointer1 -> genre);
		clear_spaces(pointer1 -> memory);
		clear_spaces(pointer1 -> price);
		clear_spaces(pointer1 -> platform);
		
		space_hack(pointer1 -> name, name_spaces);
		space_hack(pointer1 -> developer, developer_spaces);
		space_hack(pointer1 -> genre, genre_spaces);
		space_hack(pointer1 -> memory, memory_spaces);
		space_hack(pointer1 -> price, price_spaces);
		space_hack(pointer1 -> platform, platform_spaces);
		
		pointer1 = pointer1 -> previous;
	}
}
//###################################################### clear_spaces
void clear_spaces(char *napis)
{
	napis = napis + 99;
	int i=0;
	while(i<100 && (*napis==0 || *napis==32))
	{
		if(*napis==' ') *napis = 0;
		napis--;
		i++;
	}
}
//###################################################### sort
void sort()
{
	printf("sort by <name, developer, genre, storage dev, price, platform>\n");
	fgets(command, 100, stdin);
	if(compare2(command, "name\n"))// G A M E
	{
		mini_sort(1);
		printf("\tdone\n");
	}
	else if(compare2(command, "developer\n")) // D E V E L O P E R
	{
		mini_sort(2);
		printf("\tdone\n");
	}
	else if(compare2(command, "genre\n")) // G E N R E
	{
		mini_sort(3);
		printf("\tdone\n");
	}
	else if(compare2(command, "storage dev\n")) // S T O R A G E  D E V
	{
		mini_sort(4);
		printf("\tdone\n");
	}
	else if(compare2(command, "price\n"))  // P R I C E
	{
		mini_sort(5);
		printf("\tdone\n");
		
	}
	else if(compare2(command, "platform\n")) // P L A T F O R M
	{
		mini_sort(6);
		printf("\tdone\n");
	}
	else printf("\tinvalid phrase\n");
}
//###################################################### compare 2
int compare2(char *wsk1, const char *wsk2)
{
	while(*wsk1==*wsk2)
	{
		if(*wsk1 == 0 || *wsk2 == 0) break;
		wsk1++;
		wsk2++;
	}
	if(*wsk1==0 && *wsk2==0) return 1;
	else return 0;
}
//####################################################### alfabetycznie
int alfabetycznie(char *wsk1, char *wsk2)
{
	int i=0;
	
	while(*wsk1 == *wsk2 && i < 100)
	{
		if(*wsk1 != *wsk2) break;
		wsk1++;
		wsk2++;
		i++;
	}
	if(*wsk1 < *wsk2) return 1; // jesli wsk1 jest mniejsze od wsk2 zwroc 1
	else return 0;
}
//######################################################## mini_sort@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
void mini_sort(int a)
{
	game *pointer, *help1, *help2;
	int i, j, co_zmienic;
	static int state = 1;
				
				if(state==1) // a, b, c, d
				{
					for(i=0; i<quantity-1; i++) //sortowanie babelkowe
					{
						pointer = last_game; // po kazdym przebiegu petli ze zmienna j wskaznik pomocniczy wraca na ostatni element
						
						for(j=0; j<quantity-1; j++)
						{
									if(a==1) co_zmienic = alfabetycznie(pointer -> name, pointer -> previous ->name);
									else if(a==2) co_zmienic = alfabetycznie(pointer -> developer, pointer -> previous ->developer);
									else if(a==3) co_zmienic = alfabetycznie(pointer -> genre, pointer -> previous ->genre);
									else if(a==4) co_zmienic = alfabetycznie(pointer -> memory, pointer -> previous ->memory);
									else if(a==5) co_zmienic = read_double(pointer -> price) <=  read_double(pointer -> previous ->price);
									else co_zmienic = alfabetycznie(pointer -> platform, pointer -> previous ->platform);		
							
							if(!co_zmienic)
							{																
								if(pointer==last_game)
								{
									help1 = pointer ->previous;
									pointer -> previous = pointer -> previous -> previous;
									help1 -> previous = pointer;
									last_game = help1;
									pointer = last_game; // zeby potem pod koniec petli for bylo dobre przejscie na previousa
									
								}
								else
								{	///             {pointer -> previous -> previous} <----- help1 <-------- pointer <------- help 2  < ------- LAST
									help1 = pointer ->previous;
									help2 -> previous = help1;
									pointer -> previous = pointer -> previous -> previous;
									help1 -> previous = pointer;
									pointer = help1; // zeby potem pod koniec petli for bylo dobre przejscie na previousa
								}
							}
							help2 = pointer;
							pointer = pointer -> previous;
						}
					}	
				}
				else // d, c, b, a @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				{
					for(i=0; i<quantity-1; i++) //sortowanie babelkowe
					{
						pointer = last_game; // po kazdym przebiegu petli ze zmienna j wskaznik pomocniczy wraca na ostatni element
						
						for(j=0; j<quantity-1; j++)
						{
									if(a==1) co_zmienic = alfabetycznie(pointer -> name, pointer -> previous ->name);
									else if(a==2) co_zmienic = alfabetycznie(pointer -> developer, pointer -> previous ->developer);
									else if(a==3) co_zmienic = alfabetycznie(pointer -> genre, pointer -> previous ->genre);
									else if(a==4) co_zmienic = alfabetycznie(pointer -> memory, pointer -> previous ->memory);
									else if(a==5) co_zmienic = read_double(pointer -> price) <=  read_double(pointer -> previous ->price);
									else co_zmienic = alfabetycznie(pointer -> platform, pointer -> previous ->platform);		
							
							if(co_zmienic)
							{																
								if(pointer==last_game)
								{
									help1 = pointer ->previous;
									pointer -> previous = pointer -> previous -> previous;
									help1 -> previous = pointer;
									last_game = help1;
									pointer = last_game; // zeby potem pod koniec petli for bylo dobre przejscie na previousa
									
								}
								else
								{	///             {pointer -> previous -> previous} <----- help1 <-------- pointer <------- help 2  < ------- LAST
									help1 = pointer ->previous;
									help2 -> previous = help1;
									pointer -> previous = pointer -> previous -> previous;
									help1 -> previous = pointer;
									pointer = help1; // zeby potem pod koniec petli for bylo dobre przejscie na previousa
								}
							}
							help2 = pointer;
							pointer = pointer -> previous;		
						}
					}
				}
	state *= -1;
}
//#################################################### load
void load()
{
	printf("file name\n");
	fgets(command, 100, stdin);
	del_new_line(command);
	
	
	if(!(fp=fopen(command, "r"))) printf("couldn't open\n");
	else
	{
		fgets(command, 100, fp);
		fgets(command, 100, fp);
		
		for(;;)
		{
			clear_tab(command);
			if(!fgets(command, 100, fp)) break;
			
			else if(count_my_char(command)==7 && no_white_char(command))
			{
				//kreator
				clear_tab(tab_name);
				clear_tab(tab_developer);
				clear_tab(tab_genre);
				clear_tab(tab_memory);
				clear_tab(tab_price);
				clear_tab(tab_platform);
				
				strcpy_till_my_char(command);
				
				space_hack(tab_name, name_spaces);
				space_hack(tab_developer, developer_spaces);
				space_hack(tab_genre, genre_spaces);
				space_hack(tab_memory, memory_spaces);
				space_hack(tab_price, price_spaces);
				space_hack(tab_platform, platform_spaces);
				
				kreator(tab_name, tab_developer, tab_genre, tab_memory, tab_price, tab_platform);
			}
			else printf("\n\tformat invalid\n");
		}
		
		fclose(fp);
		printf("\ndata loaded\n");
	}
}
//#################################################### set
void set()
{
	printf("file name\n");
	fgets(command, 100, stdin);
	del_new_line(command);
	
	if(!file_name(command)) printf("invalid name\n");
	
	else if(!(fp=fopen("gamebase_set.txt", "w"))) printf("no permission\n");
	else 
	{
		fprintf(fp, "%s", command);
		fclose(fp);
		printf("saved\n");
	}
}
//#################################################### count_my_char
int count_my_char(char *string)
{
	int i, ile=0;
	for(i=0; i<100; i++)
	{
		if(*string=='|') ile++;
		string++;
	}
	return ile;
}
//##################################################### strcpy_till_my_char
void strcpy_till_my_char(char *string)
{
	char *tab_name1 = tab_name,
	 *tab_developer1 = tab_developer, 
	 *tab_genre1 = tab_genre, 
	 *tab_memory1 = tab_memory,
	*tab_price1 = tab_price,
	 *tab_platform1 = tab_platform;
	while(*string != '|') string++;
	string++;
	while(*string != '|') 
	{
		*tab_name1 = *string;
		tab_name1++;
		string++;
	}
	string++;
	while(*string != '|') 
	{
		*tab_developer1 = *string;
		tab_developer1++;
		string++;
	}
	string++;
	while(*string != '|') 
	{
		*tab_genre1 = *string;
		tab_genre1++;
		string++;
	}
	string++;
	while(*string != '|') 
	{
		*tab_memory1 = *string;
		tab_memory1++;
		string++;
	}
	string++;
	while(*string != '|') 
	{
		*tab_price1 = *string;
		tab_price1++;
		string++;
	}
	string++;
	while(*string != '|') 
	{
		*tab_platform1 = *string;
		tab_platform1++;
		string++;
	}
}
///############################## read_double
double read_double (char *string)
{
	int help = 0;
	char *head = string;
	
	while(*string == 46 || (*string >= 48 && *string <= 57))
	{
		if(*string == 46) help++;
		if(help == 2) return 0;
		string++;
	}
	if(head == string) return 0;
	if(*string == 0 || *string == ' ')
	{
		double a;
		sscanf(head, "%lf", &a);
		return a;
	}
	else return 0;
}
///                                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ K O N I E C

