// sudoku.cpp : Defines the entry point for the console application.
//

/* Karmen Unuk
OA_N0000819_sklop5_naloga1: Sudoku */

/* Napišite program za nalogo sudoku. */


#include "stdafx.h"
#include <stack>
#include <iostream>
#include <fstream>
using namespace std;

class CElement
{
public:
	CElement(int aI, int aJ);
	~CElement(void);
	int i;
	int j;
	int vr;
	void Vrednost(int aV);
	void Izpis();
};

class CSudokuNov
{
public:
	CSudokuNov(void);
	~CSudokuNov(void);
	void ustvariSudoku(char *ime);
	void matrika(char *ime);
	int polnaVrstica(int aI);
	CElement *izberiNaslednje(int aI);
	bool resitevCela();
	void vrsticaInStolpec(int aI, int aJ, int aV);
	bool velja();
	void zapolni(char *ime);
	void napolniSudoku(int **aM);
	void zapolni1(int **aM);
	int dolociVrednost(int aV);
	bool veljavnost(int aV, int aI, int aJ);
	void izpisMatrike();

	int **sudoku;
	stack<CElement* > sklad;
};

CElement::CElement(int aI, int aJ)
{
	i = aI;
	j = aJ;
	vr = 0;
}

CElement::~CElement(void)
{
}

void CElement:: Vrednost(int aV)
{
	vr = aV;
}
void CElement:: Izpis()
{
	cout << i << " " << j << " " << vr << " " << endl ;
}

CSudokuNov::CSudokuNov(void)
{
	sudoku = new int*[9];			//ustvariš matriko oz. sukodu
	for(int i = 0; i< 9; i++){
		sudoku[i] = new int[9]; 
	}
	stack<CElement* > sklad;
}

CSudokuNov::~CSudokuNov(void)
{
}

void CSudokuNov:: matrika(char* ime)
{
	for(int i = 0; i< 9; i++){
		for(int j = 0; j< 9; j++){
			sudoku[i][j] = 0;
		}
	}
	ustvariSudoku(ime);
}

void CSudokuNov:: ustvariSudoku(char* ime)		
{
	ifstream dat(ime);
	if(dat.is_open()){
		int aI;
		int aJ;
		int aV;
		while(!dat.eof()){
			dat >> aI >> aJ >> aV;
			sudoku[aI][aJ] = aV;
		}
	}else
		cout << "Napaka!" << endl;
}

int CSudokuNov:: polnaVrstica(int aI)
{
	int aJ = -1;
	for(int j = 0; j < 9; j++){
		if(sudoku[aI][j] == 0){
			aJ = j;
			break;
		}
	}
	return aJ;
}

CElement* CSudokuNov:: izberiNaslednje(int aI)
{
	CElement* aE;
	int aJ = polnaVrstica(aI);
	if(aJ == -1){
		aI++;
		while(true){
			aJ = polnaVrstica(aI);
			if(aJ == -1 && aI >= 9)
				return aE = new CElement(-1,-1);
			else{
				if(aJ != -1)
					break;
			}
			aI++;
		}
	}
	aE = new CElement(aI, aJ);
	return aE;
}

bool CSudokuNov:: resitevCela()
{
	for(int i = 0; i< 9; i++){
		for(int j = 0; j< 9; j++){
			if(sudoku[i][j] == 0)
				return false;
		}
	}
		return true;
}

void CSudokuNov:: vrsticaInStolpec(int aI, int aJ, int aV)
{
	sudoku[aI][aJ] = aV;
}

bool CSudokuNov::velja()
{
	if(!veljavnost(sudoku[8][8], 8, 8) && sudoku[8][8] != 0)
		return false;
	
	return true;
}

void CSudokuNov:: zapolni(char * ime)
{
	matrika(ime);
	cout << "Neresen sudoku: " << endl;
	izpisMatrike();
	cout << endl << endl;
	int aI = 0;
	int aVr = 0;
	CElement* aE =izberiNaslednje(aI);
	cout << "Resen sudoku: " << endl;
while(true){
		aVr = dolociVrednost(aVr);
		if(veljavnost(aVr, aE->i, aE->j) && aVr < 10){
			aE->Vrednost(aVr);
			vrsticaInStolpec(aE->i, aE->j, aE->vr);
			sklad.push(aE);
			aVr = 0;
			if(!resitevCela()){
				aE = izberiNaslednje(aI);
			}else{
				izpisMatrike();
				break;
			}
			continue;
		}else{
			if(!veljavnost(aVr, aE->i, aE->j) && aVr < 10){
				continue;
			}else{
				vrsticaInStolpec(aE->i, aE->j, 0);
				if(!sklad.empty()){
					aE = sklad.top();
					aVr = aE->vr;
					sklad.pop();
				}else{
					cout << "Ni resitve!!!" << endl;
					break;
				}
			}
	}
}

}

void CSudokuNov:: napolniSudoku(int** aM)
{
	for(int i = 0; i< 9; i++){
		for(int j = 0; j< 9; j++){
			sudoku[i][j] = aM[i][j];
		}
	}
}

void CSudokuNov:: zapolni1(int** aM)
{
	napolniSudoku(aM);
	izpisMatrike();
	int aI = 0;
	int aVr = 0;
	CElement* aE = izberiNaslednje(aI);
while(true){
		aVr = dolociVrednost(aVr);
		if(veljavnost(aVr, aE->i, aE->j) && aVr < 10){
			aE->Vrednost(aVr);
			vrsticaInStolpec(aE->i, aE->j, aE->vr);
			sklad.push(aE);
			aVr = 0;
			if(!resitevCela()){
				aE = izberiNaslednje(aI);
			}else{
				izpisMatrike();
				break;
			}
			continue;
		}else{
			if(!veljavnost(aVr, aE->i, aE->j) && aVr < 10){
				continue;
			}else{
				vrsticaInStolpec(aE->i, aE->j, 0);
				if(!sklad.empty()){
					aE = sklad.top();
					aVr = aE->vr;
					sklad.pop();
				}else{
					cout << "Ni resitve!!!" << endl;
					break;
				}
			}
	}
}

}
int CSudokuNov::dolociVrednost(int aV)
{
	aV++;
	return aV;
}
bool CSudokuNov:: veljavnost(int aV, int aI, int aJ)
{
	int aK = 1;
	for(int i = 0; i < 9; i++){	
		if(aV == sudoku[i][aJ]){
			return false;
		}
	}
	
	for(int j = 0; j < 9; j++){	
		if(aV == sudoku[aI][j]){
			return false;
		}
	}

		if(0<=aI && aI<=2){
			if(0 <= aJ && aJ <= 2){
				for(int k = 0; k < 3; k++){
					for(int l = 0; l < 3; l++){
						if(aV == sudoku[k][l]){
							return false;
						}
					}
				}
			}else{
				if(3<=aJ && aJ<= 5){
					for(int k = 0; k < 3; k++){
						for(int l = 3; l < 6; l++){
							if(aV == sudoku[k][l]){
								return false;
							}
						}
					}
				}else{
					for(int k = 0; k < 3; k++){
						for(int l = 6; l < 9; l++){
							if(aV == sudoku[k][l]){
								return false;
							}
						}
					}
				}
			}
		}else{
			if(3 <= aI && aI <= 5){
				if(0 <= aJ && aJ <= 2){
					for(int k = 3; k < 6; k++){
						for(int l = 0; l < 3; l++){
							if(aV == sudoku[k][l]){
								return false;
							}
						}
					}
				}else{
					if(3 <= aJ && aJ <= 5){
						for(int k = 3; k < 6; k++){
							for(int l = 3; l < 6; l++){
								if(aV == sudoku[k][l]){
									return false;
								}
							}
						}
					}else{
						for(int k = 3; k < 6; k++){
							for(int l = 6; l < 9; l++){
								if(aV == sudoku[k][l]){
									return false;
								}
							}
						}
					}
				}
			}else{
				if(0 <= aJ && aJ <= 2){
					for(int k = 6; k < 9; k++){
						for(int l = 0; l < 3; l++){
							if(aV == sudoku[k][l]){
								return false;
							}
						}
					}
				}else{
					if(3 <= aJ && aJ <= 5){
						for(int k = 6; k < 9; k++){
							for(int l = 3; l < 6; l++){
								if(aV == sudoku[k][l]){
									return false;
								}
							}
						}
					}else{
						for(int k = 6; k < 9; k++){
							for(int l = 6; l < 9; l++){
								if(aV == sudoku[k][l]){
									return false;
								}
							}
						}
					}
				}
			}
		}
		return true;
}
void CSudokuNov:: izpisMatrike()
{
	for(int i = 0; i< 9; i++){
		for(int j = 0; j<9; j++){
			cout << sudoku[i][j] << " ";
			if((j+1)%3 == 0)
				cout << " |  ";
		}
		cout << endl;
		if((i+1)%3 == 0){
			cout << "__________________________";
			cout << endl;
		}
	}
}

void IzpisM(int ** aM)
{
	for(int i = 0; i< 9; i++){
		for(int j = 0; j<9; j++){
			cout << aM[i][j] << " ";
			if((j+1)%3 == 0)
				cout << " |  ";
		}
		cout << endl;
		if((i+1)%3 == 0){
			cout << "__________________________";
			cout << endl;
		}
	}
}
int** Ustvari()
{
	int** aS = new int*[9];
	for(int k = 0; k< 9; k++){
		aS[k]= new int[9];
	}
	cout << "zaporedoma vnasaj elemente: " << endl;
	int aR;
	for(int i = 0; i< 9; i++){
		for(int j = 0; j< 9; j++){
			cin >> aR;
			aS[i][j]=aR;
		}
	}
	IzpisM(aS);
	return aS;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CSudokuNov* aS = new CSudokuNov();
	cout << endl << "Zapolni(prebere preko tekstovne datoteke): " << endl;
	aS->zapolni("Sudoku.txt");
	/*CSudokuNov* aS1 = new CSudokuNov();
	cout << endl << "Zapolni(prebere preko tipkovnice): " << endl;
	cout << endl;
	int** aM = Ustvari();
	aS1->zapolni1(aM);*/

	cin.ignore();
	cin.get();

	return 0;
}

