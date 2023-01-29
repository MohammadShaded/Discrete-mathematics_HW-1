#include <iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;
vector<vector<string>> vec;
vector<string>temp, vars;
vector<vector<bool>> cases;
vector <bool> cas;
int v;
string ResultForOption2 = " ";
void checker(ifstream& File);



int main()
{
	int option;

	do {
		string filename;
		cout << "\nPlease select from the following:\n1. Read expression from a file.\n2. Check loaded expression.\n3. Display all assignments that makes the output TRUE.\n4. Exit.\n";
		cin >> option;

		if (option == 1) {

			cout << "\nEnter file name:";
			cin >> filename;
			ifstream File(filename);

			cout << "loaded\n";
			if (File.is_open()) {
				vec.clear();
				vars.clear();
				temp.clear();
				cases.clear();
				cas.clear();
			}
			checker(File);
		}


		if (option == 2) {
			if (ResultForOption2 != " ")cout << ResultForOption2;
			else cout << "\nThere are no open files";
		}


		if (option == 3) {

			if (cases.empty())cout << "****There is No assignments that makes the output TRUE***\n";
			else {
				for (int i = 0; i < v; i++) {
					cout << vars[i];
				}
				cout << endl;
				for (int i = 0; i < cases.size(); i++) {
					for (int j = 0; j < cases[i].size(); j++) {
						cout << cases[i][j];
					}
					cout << endl;
				}
			}
		}

		if (option == 4) {
			cout << "bye";
			return 0;
		}
	} while (1);


}



void checker(ifstream& File) {
	int e;

	if (vec.empty()) {


		char ch;
		string var, m = "";
		File >> v;

		getline(File, var);
		getline(File, var);
		e = var.size();
		for (int i = 0; i < e; i++) {
			if (var[i] != ' ') {
				m += var[i];
				vars.push_back(m);
				m = "";
			}
		}

		File >> e;                 //reusing variable e to store #-of exp.
		
		for (int i = 0; i < e; i++) {
			temp.clear();
			while (File >> m) {

				File >> noskipws >> ch;
				temp.push_back(m);
				if (ch == '\n') { break; }

			}
			vec.push_back(temp);
			temp.clear();
		}
	}

	if (!vec.empty()) {


		int x = 0, f = 0, t = 0;
		bool val[4];
		bool res, line = false, anding = true;


		for (int q = 0; q < 2; q++) {
			val[0] = q;
			for (int w = 0; w < 2; w++) {
				val[1] = w;
				for (int a = 0; a < 2; a++) {
					val[2] = a;
					for (int s = 0; s < 2; s++) {
						val[3] = s;


						for (int r = 0; r < e; r++) {
							for (long int c = 0; c < vec[r].size(); c++) {


								for (int i = 0; i < vars.size(); i++) {
									if (vec[r][c] == vars[i]) {
										if (c > 0 && (vec[r][c - 1] == "not")) x = (2 * i) + 2;
										else x = (2 * i) + 1;
									}
								}

								switch (x) {
								case 1:res = val[0]; break;
								case 2:res = !val[0]; break;
								case 3:res = val[1]; break;
								case 4:res = !val[1]; break;
								case 5:res = val[2]; break;
								case 6:res = !val[2]; break;
								case 7:res = val[3]; break;
								case 8:res = !val[3]; break;
								}
								x = 0;
								line |= res;
								res = false;
							}
							anding &= line;
							line = false;
						}


						if (anding == false)f = 1;
						if (anding == true) {
							t = 1;
							for (int i = 0; i < v; i++) {
								cas.push_back(val[i]);
							}
							cases.push_back(cas);
							cas.clear();
						}


						anding = true;
						line = false;

					}
				}
			}
		}



		for (int i = 0; i < cases.size(); i++) {               //delete repeated cases
			for (int j = 0; j < cases.size(); j++) {
				if (cases[i] == cases[j]) {
					cases.erase(cases.begin() + i);

				}
			}
		}

		if (t == 0 && f == 1)ResultForOption2 = "Contradiction"; //or using --> if (cases.size() == 0) cout << "Contradiction";
		if (t == 1 && f == 1)ResultForOption2 = "Contingency";
		if (t == 1 && f == 0)ResultForOption2 = "Tautology,";
	}
	else { cout << "file is empty" << endl; }
}
