#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<fstream>
#include<Windows.h>
using namespace std;
///HIPERPARAMETRY
//#define max_am_of_gen 100

#define population 100
//#define starting_bg 133//modifible
//#define wanted_bg 233//modifible
 int starting_bg;
 int wanted_bg;
///nie zmieniac!
#define attributes 4
#define numbers 0
#define evaluation 1
#define fitness 2
#define places 3
//#define mutarate 1
 int mutarate;
 void evaluation_input(double tab[attributes][population]);//ewaluacja kazdego osobnika wlozenie wartosci do atrybutu ewaluacja
 void fitness_count(double tab_fit[attributes][population]);//liczenie fitnessu kazdego osobnika wlozenie do atrybutu fitness
 void places_to_give(double tab_place[attributes][population], int *plac);//wlozenie miejsc do atrybutu miejsca
 void sort(double tab_place[attributes][population]);//sortowanie wg miejsca
 void equal_places(double tab_place_eq[attributes][population], int *plac_eq);//wyrowanie miejsc
 void agamic_replication(double tab_place_rep[attributes][population]);//replikacja agamiczna
 void mutation(double tab_place_mut[attributes][population]);//mutacja osobnikow
 void centerstring(char* s);//centrowanie tekstu
 void reverse_name(char buffer[], string name); 
 string get_directory();//znalezienie bazy danych

int main() {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char* hello_program = "Rodzina mrowek w obliczu zmian...";
	centerstring(hello_program);
	SetConsoleTextAttribute(hConsole, 12);
	cout << hello_program << endl;
	
	SetConsoleTextAttribute(hConsole, 15);
	cout << " Pewne stado 100 mrowek zyje sobie w dosyc zanieczyszczonym srodowisku." << endl;
	cout << " Specyfika owego srodowiska jest fakt, iz jego pogoda drastycznie sie zmienia co 25 pokolen." << endl;
	cout << " Deszcze, zanieczyszczone powietrze, oraz promieniowanie, ma wplyw na zdrowie mrowek." << endl;
	cout << " W skutek czego sa one zmuszone do czestych zmian genetycznych." << endl;
	cout << " Program ilustruje w jaki sposob rodzina mrowek radzi sobie z nieprzewidywalnymi zmianami w srodowisku naturalnym." << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 14);
	cout << " Zakres wartosci genetycznych jest od 0 - 255" << endl;
	cout << " Uzytkownik ma wplyw, na wstepne okreslenie wartosci genetycznej mrowek, oraz docelowej w pierwszych 25 pokoleniach. " << endl;
	cout << " Poczatkowa mutacja na 25 pokolen tak samo jest okreslana manualnie." << endl;
	cout << " Po kazdym przekroczeniu 25 nastepnych pokolen, jest losowana randomowa wielkosc mutacji w zakresie 0-10, oraz najlepsza wartosc genetyczna dla danej sytuacji pogodowej." << endl; 
	cout << endl;
	SetConsoleTextAttribute(hConsole, 13);
	cout << " Owy problem wykorzystuje algorytm genetyczny, ktory optymalizuje na przestrzeni 25 pokolen, wartosci 100 osobnikow do danej najlepszej wartosci genetycznej." << endl;
	cout << " Wyniki zostana zachowane w bazie Access, a ich wizualizacja pokazana w PowerBI." << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;



	int max_am_of_gen;
	cout << " Wpisz startowa wartosc genetyczna dla wszystkich mrowek" << endl;
	cin >> starting_bg;
	cout << " Wpisz docelowa wartosc w pierwszych 25 pokoleniach" << endl;
	cin >> wanted_bg;
	cout << " Wpisz ile procent jest na mozliwosc mutacji, (najbardziej optymalne jest miedzy 1-3)" << endl;
	cin >> mutarate;
	cout << " Wpisz ilosc pokolen jakie maja nastapic: " << endl;
	cin >> max_am_of_gen;

	int id_osobnika = 0;

	double table_of_osobniki[attributes][population];
	int generations = 0;
	double srednia = 0;
	bool if_end = true;
	srand(time(NULL));
	int check_if_plac_eq = 0;//sprawdza czy jest rowne miejsca;
							 //wkladam wartosci poczatkowe
	for (int input_iter = 0; input_iter < population; input_iter++) {
		table_of_osobniki[numbers][input_iter] = starting_bg;
	}
	fstream files;
	files.open("db.csv", ios::out);
	fstream fileinfo;
	files << "ID_OSOBNIKA,GENERACJA,WARTOSC_OSOBNIKA,EWALUACJA,FITNESS" << endl;
	fileinfo.open("details_of_symulation.csv", ios::out);
	fileinfo << "Pokolenie,Zamierzona Wartosc,Mutacja"<<endl;
	fileinfo << generations << "," << wanted_bg << "," << mutarate<< endl;
	vector<int>bg;
	//files << "," << "Generacja,Wartosc_osobnika,Ewaluacja,Fitness" << endl;
	//licze ewaluacje liczb
	int rand_num_wanted;
	int rand_mut_rate;
	while (if_end) {

		evaluation_input(table_of_osobniki);
		fitness_count(table_of_osobniki);
		places_to_give(table_of_osobniki, &check_if_plac_eq);
		sort(table_of_osobniki);
		equal_places(table_of_osobniki, &check_if_plac_eq);
		agamic_replication(table_of_osobniki);
		mutation(table_of_osobniki);
		generations++;
		system("cls");
		cout << " Ilosc generacji: " << generations << endl;
		cout << " Wartosc genetyczna najlepsza w danym okresie: " << wanted_bg << endl;
		cout << " Procent mutacji: " << mutarate << endl;
		for (int i = 0; i < population; i++) {
			id_osobnika++;
			cout << table_of_osobniki[numbers][i] << " ";
			files << id_osobnika<<"," <<generations << "," << table_of_osobniki[numbers][i] << "," << table_of_osobniki[evaluation][i] << "," << table_of_osobniki[fitness][i] << endl;
			/*cout << table_of_osobniki[evaluation][i] << endl;
			cout << table_of_osobniki[fitness][i] << endl;
			cout << table_of_osobniki[places][i] << endl;*/

		}
		if (generations % 25 == 0) {
			rand_mut_rate = rand() % 10;
			rand_num_wanted = rand() % 255;
			mutarate = rand_mut_rate;
			wanted_bg = rand_num_wanted;
			fileinfo << generations << "," << wanted_bg << "," << mutarate << endl;
		}
		check_if_plac_eq = 0;
		if (generations == max_am_of_gen) {
			if_end = false;
		}
	}
	files.close();
	fileinfo.close();
	string filename = get_directory();
	filename.append("\\Baza_danych-OSOBNIKOW_genetycznych.accdb");
	const char * c = filename.c_str();
	system(c);

	system("pause");
	return 0;
}
void reverse_name(char buffer[], string name) {
	int i = 0;
	int j = name.size() - 1;
	char tmp;
	while (i < j) {
		tmp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = tmp;
		i++;
		j--;
	}
}
string get_directory() {

	char buffer[MAX_PATH];
	string name = "";
	GetModuleFileName(NULL, buffer, sizeof(buffer));
	name.append(buffer);

	reverse_name(buffer, name);
	name = "";
	name.append(buffer);
	int end = name.find("\\", 0);
	name = name.substr(end + 1, name.size());
	strcpy_s(buffer, name.c_str());
	reverse_name(buffer, name);
	name = "";
	name.append(buffer);

	return name;
}
void centerstring(char* s)//centrowanie tekstu
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD NewSBSize;
	NewSBSize = GetLargestConsoleWindowSize(hOut);
	int l = strlen(s);
	int pos = (int)((NewSBSize.X - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";


}


void evaluation_input(double tab[attributes][population]) {
	double evaluation_of_one_number;
	for (int iter_count = 0; iter_count < population; iter_count++) {
		//evaluation_of_one_number = 1/(double(1/255) + pow(( tab[numbers][iter_count] - wanted_bg),2));
		evaluation_of_one_number = 1 / (0.1 + 0.001*double(pow((tab[numbers][iter_count] - wanted_bg), 2)));
		tab[evaluation][iter_count] = evaluation_of_one_number;
		evaluation_of_one_number = 0;
	}


}
void fitness_count(double tab_fit[attributes][population]) {
	double all_suma = 0;
	double one_fitness = 0;
	for (int i_suma = 0; i_suma < population; i_suma++) {
		all_suma = all_suma + tab_fit[evaluation][i_suma];
	}
	//liczenie fitnessu i wkladanie
	for (int i_licz = 0; i_licz < population; i_licz++) {
		one_fitness = tab_fit[evaluation][i_licz] / all_suma;
		tab_fit[fitness][i_licz] = one_fitness;
	}

}
//licze ile miejsc przydzielic
void places_to_give(double tab_place[attributes][population], int *plac) {
	int place;
	for (int ava_plac = 0; ava_plac < population; ava_plac++) {
		place = round(population * tab_place[fitness][ava_plac]);
		tab_place[places][ava_plac] = place;
		*plac += place;
	}
}
void sort(double tab_place[attributes][population]) {//sortuje wzgledem miejsc
	float temp = 0;
	float zmiana = 0;
	int j = 0;
	float ile_liczb = population;

	do
	{
		zmiana = 0;
		j = ile_liczb - 1;
		do
		{
			j--;
			if (tab_place[3][j + 1] > tab_place[3][j])
			{
				swap(tab_place[places][j], tab_place[places][j + 1]);
				swap(tab_place[fitness][j], tab_place[fitness][j + 1]);
				swap(tab_place[evaluation][j], tab_place[evaluation][j + 1]);
				swap(tab_place[numbers][j], tab_place[numbers][j + 1]);


				zmiana = 1;
			}
		} while (j != 0);
	} while (zmiana != 0);
}

void equal_places(double tab_place_eq[attributes][population], int *plac_eq) {
	int simple_int = 0;
	if (*plac_eq != population) {
		while (*plac_eq != population) {
			if (*plac_eq > population) {
				tab_place_eq[places][simple_int]--;
				*plac_eq -= 1;
			}
			else {
				tab_place_eq[places][simple_int]++;
				*plac_eq += 1;
			}
		}
		simple_int++;
	}


}


void agamic_replication(double tab_place_rep[attributes][population]) {
	int size = 0;
	vector<int>mid_pop;

	while (size != population) {
		if (tab_place_rep[places][size] > 0) {
			for (int rep_int = 0; rep_int < (int)tab_place_rep[places][size]; rep_int++) {
				mid_pop.push_back(tab_place_rep[numbers][size]);
			}
		}
		size++;
	}
	for (int in_oryg = 0; in_oryg < population; in_oryg++) {
		tab_place_rep[numbers][in_oryg] = mid_pop[in_oryg];
	}

	mid_pop.clear();

}
void mutation(double tab_place_mut[attributes][population]) {
	///zmienne
	int rand_number;
	int to_mutate = 0;//rzutowanie by stworzyc integer
					  //KONWERSJA NA BINARNA/////////////////////////////////////////////////////																			// counter for binary array
	int itera_convert_from_dec_to_bin;
	int binaryNum[8];
	int mutr = mutarate;
	double temp_val = 0;


	/////////////////MUTACJA
	for (int in_mut = 0; in_mut < population; in_mut++) {

		//konwersja na binarna
		to_mutate = (int)tab_place_mut[numbers][in_mut];
		itera_convert_from_dec_to_bin = 0;

		while (to_mutate > 0) {
			binaryNum[itera_convert_from_dec_to_bin] = to_mutate % 2;
			to_mutate = to_mutate / 2;
			itera_convert_from_dec_to_bin++;
		}
		///zakonczenie konwersji na binarna
		for (int on_each_gen = 0; on_each_gen < 8; on_each_gen++) {
			rand_number = rand() % 100;
			if (mutr > rand_number) {
				if (binaryNum[on_each_gen] == 0) {
					binaryNum[on_each_gen] = 1;
				}
				else {
					binaryNum[on_each_gen] = 0;
				}

			}

		}
		temp_val = 0;
		for (int i = 7; i >= 0; i--) {
			if (binaryNum[i] == 1)
				temp_val += pow(2, i);
		}
		tab_place_mut[numbers][in_mut] = temp_val;

	}
}