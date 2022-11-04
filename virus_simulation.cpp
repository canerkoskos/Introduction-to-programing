#include<iostream>
#include<string>
#include<fstream>
using namespace std;
bool infect(string gates) {
    bool result=false;
    for (int i = 0; i < 5; i++) {
        if (gates[i] == 'A' || gates[i] == 'B') {
            result = true;
        
        }
    }
    return (result);
}
bool dead(string gates) {
    bool result = false;
    int sayac = 0;
    for (int i = 0; i < 5; i++) {
        if (gates[i] == 'A' || gates[i] == 'B'||gates[i]=='C'||gates[i]=='D') {
            sayac++;

        }
        if (sayac >= 3) {
            result = true;
        }
        
    }
    return (result);
}


int main() {

    int entC = 1;
    string entGates[50];
    string entKonum[50];
    char entDurum[50];
    string turn[50][50];

    int size = 0;
    int turn_count = 0;

    ifstream file;
    file.open("INPUT.txt");
    string word;


    while (file >> word) {
        if (word == "size") {
            file >> word;
            size = stoi(word);

        }
        else if (word == "turn_count") {
            file >> word;
            turn_count = stoi(word);

        }

        else if (word == "entity") {
           
            file >> word;
            file >> word;
            entGates[entC] = word;
            file >> word;
            entKonum[entC] = word;
            entDurum[entC] = 'O';
            entC++;
            

        }
        else if (word == "infected")
        {
            entDurum[entC - 1] = 'X';
        }
        else if (word == "turn") {
            for (int i = 1; i < turn_count+1; i++) {

                for (int t = 0; t < entC+1; t++) {
                    file >> word;
                    if (word != "turn") {
                        turn[i][t] = word;
                       
                    }
                }

            }

        }

    }

    file.close();
    
    int bosluk = 0;
    
    ofstream turns("TURNS.txt", ios::out, ios::trunc);
    if (turns.is_open()) {
        for (int a = 1; a <= turn_count; a++) {

            for (int e = 1; e < entC; e++) {

                int sayac = 0;
                string x = "";
                string y = "";
                string xe = "";
                string ye = "";
               

                for (int z = 0; z < entKonum[e].length();z++) {
                    
                    
                    if (entKonum[e][z] == 'x') {
                        sayac = 1;
                        continue;
                    }
                    if (sayac == 0) {
                        x += entKonum[e][z];

                    }
                    if (sayac == 1) {
                        y += entKonum[e][z];
                    }

                            
                            
                            
                }
                for (int i = 1; i < entC; i++) {
                    int sayac = 0;
                    if (entDurum[i] == 'X') {
                        
                        for (int p = 0; p < entKonum[i].length(); p++) {
                            

                            if (entKonum[i][p] == 'x') {
                                sayac = 1;
                                continue;
                            }
                            if (sayac == 0) {
                                xe += entKonum[i][p];

                            }
                            if (sayac == 1) {
                                ye += entKonum[i][p];
                            }


                        }

                    }
                   
                    
                }
                
               if (xe!=""&&ye!="") {
                    if (abs(stoi(xe) - stoi(x)) <= 3 && abs(stoi(ye) - stoi(y)) <= 3 && infect(entGates[e]) == true) {

                        entDurum[e] = 'X';
                        

                    }
               }

               

            }
            for (int d = 1; d <= entC; d++) {



                if (entDurum[d] == 'X' && dead(entGates[d]) == true) {
                    entDurum[d] = 'D';
                   
                }
                
            }
            turns << "Turn" << " " << a << ":" << endl;

            for (int i = 0; i <= size + 1; i++) {

                for (int j = 0; j <= size + 1; j++) {


                    for (int k = 1; k < entC; k++) {
                        int sayac = 0;
                        string x = "";
                        string y = "";

                        for (int z = 0; z < turn[a][k].length();z++) {
                            if (turn[a][k][z] == 'x') {
                                sayac = 1;
                                continue;
                            }
                            if (sayac==0) {
                                x += turn[a][k][z];
                                
                            }
                            if (sayac ==1) {
                                y += turn[a][k][z];
                            }
                            
                        }
                       

                        if (stoi(x) == i && stoi(y) == j) {

                            turns<< entDurum[k];
                            bosluk = 1;
                        }

                    }

                    if (i == 0 || i == (size + 1) || j == 0 || j == (size + 1)) {
                        turns << "-";
                    }

                    else if (bosluk == 0) {
                       turns << " ";
                    }
                    if (bosluk == 1) {
                        bosluk = 0;
                    }


                }
                turns << endl;

            }

        }

    }

    
    ofstream output("OUTPUT.txt", ios::out, ios::trunc);
    if (output.is_open()) {
        int normal = 0;
        int hasta = 0;
        int olu = 0;
        int iyilesen = 0;
        for (int i = 1; i < entC; i++) {
            if (entDurum[i] == 'O')
                normal++;
            else if (entDurum[i] == 'X')
                hasta++;
            else if (entDurum[i] == 'D')
                olu++;
            else
                iyilesen++;
        }
        output << "Normal    :" <<normal<< endl;
        output << "Infected  :" <<hasta<< endl;
        output << "Dead      :" <<olu<< endl;
        output << "Recovered :" <<iyilesen<< endl;
        for (int i = 1; i < entC; i++) {
            string hastaDurumu;
            if (entDurum[i] == 'O')
                hastaDurumu = "normal";
            else if (entDurum[i] == 'X')
                hastaDurumu = "infected";
            else if (entDurum[i] == 'D')
                hastaDurumu = "dead";
                
            output << "entity" << " " << i <<" "<< turn[turn_count][i] <<" "<<hastaDurumu<< endl;
        }
    }
   
    return 0;
   
}
