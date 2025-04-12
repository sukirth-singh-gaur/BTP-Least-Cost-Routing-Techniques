#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include<bits/stdc++.h>
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
using namespace std;

time_t RandGlob=time(NULL);//used to generate random number
float randomgeneration(long);//used to generate random numbers (program is obtained from book numerical recipes )

float r;//used to store random number
float r2;
static long seed=time(NULL);// different seeds are used for generating random number

// Function to compute the cost for one destination node with two intermediate nodes
float hop_2_dest_1_route_2(vector<float> &p) {
    float x = 0.00;
    x = (1 - 1 /p[0] - 1 /p[1] + 1/(p[0] * p[1])
        +((1 - 1/p[0]) * (1/p[1]) *(1 + p[3]))
        +((1/p[0]) * (1 - 1/p[1]) * (1 + p[2]))
        +((1/p[0]) * (1/p[1]) * (1 + min(p[2],p[3]))))/(1 /p[0] + 1/p[1] - 1/(p[0] * p[1]));
    return x;
}

//Function to compute the cost for two destination node from one source node
float dest2(vector<float> &p){                       
    float x = 0.00;
    x = (1 - 1 /p[0] - 1 /p[1] + 1/(p[0] * p[1])
        +((1 - 1/p[0]) * (1/p[1]) * (1 + p[0]))
        +((1/p[0]) * (1 - 1/p[1]) * (1 + p[1]))
        +((1/p[0]) * (1/p[1]) * (1))) / (1 /p[0] + 1/p[1] - 1/(p[0] * p[1]));
    return x;
}

//Function to compute the cost for (1) as intermediate nodes
float set_1(vector<vector<float>> &m){
    vector<float> cost1_34 = {m[1][3],m[1][4]};
    float x = 0.0;
    x = (m[0][1]) + dest2(cost1_34);
    return x;
}

//Function to compute the cost for (2) as intermediate nodes
float set_2(vector<vector<float>> &m){
    vector<float> cost2_34 = {m[2][3],m[2][4]};
    float x = 0.0;
    x = (m[0][2]) + dest2(cost2_34);
    return x;
}

//Function to compute the cost for (1,2) as intermediate nodes
float set_1_2(vector<vector<float>> &m){
    vector<float> cost1_34 = {m[1][3],m[1][4]};
    vector<float> cost2_34 = {m[2][3],m[2][4]};
    float x = 0.0;
    //cout<< min(min(min(dest2(cost1_34),dest2(cost2_34)),m[1][3] + m[2][4]),m[1][4] + m[2][3]) <<endl;
    x = ((1 - 1 /m[0][1] - 1 /m[0][2] + 1/(m[0][1] * m[0][2]))
        +((1 - 1/m[0][1]) * (1/m[0][2]) * (1 + dest2(cost2_34)))
        +((1/m[0][1]) * (1 - 1/m[0][2]) * (1 + dest2(cost1_34)))
        +((1/m[0][1]) * (1/m[0][2]) * (1 + min(min(min(dest2(cost1_34),dest2(cost2_34)),m[1][3] + m[2][4]),m[1][4] + m[2][3]))))
        /(1 /m[0][1] + 1 /m[0][2] - 1/(m[0][1] * m[0][2]));
    return x;
}

void sendPackets(vector<vector<float>> &m,int intermediate){ // Find the min path from the o/p generated to begin sending packets of data
    /*
    In this function there are two hops
        - 0 to either 1 or 2
        - from 1 or 2 to 3 and 4
    */
    int trans = 0;
    cout<<"Enter the number of packets to be transmitted: ";
    cin>> trans;

    // checkpoints on the number line for the first layer
    float chkptLayer1_1 = 0.0;
    float chkptLayer1_2 = 0.0;
    if(intermediate == 1){
        chkptLayer1_1 = 1 - 1 / m[0][1];
        chkptLayer1_2 = chkptLayer1_1 + 1 / m[0][1];
    } 
    else{
        chkptLayer1_1 = 1 - 1 / m[0][2];
        chkptLayer1_2 = chkptLayer1_1 + 1 / m[0][2];
    }
     
    // checkpoints on the number line for the second layer
    float chkptLayer2_1 = 0.0;
    float chkptLayer2_2 = 0.0;
    float chkptLayer2_3 = 0.0;
    float chkptLayer2_4 = 0.0;
    if(intermediate == 1){
        chkptLayer2_1 = (1 - 1 / m[1][3]) * (1 - 1 / m[1][4]);
        chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[1][3]) * (1 / m[1][4]);
        chkptLayer2_3 = chkptLayer2_2 + (1 / m[1][3]) * (1 - 1 / m[1][4]);
        chkptLayer2_4 = chkptLayer2_3 + (1 / m[1][3]) * (1 / m[1][4]);
    }
    else{
        chkptLayer2_1 = (1 - 1 / m[2][3]) * (1 - 1 / m[2][4]);
        chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][3]) * (1 / m[2][4]);
        chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][3]) * (1 - 1 / m[2][4]);
        chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][3]) * (1 / m[2][4]);
    }
    
    //Number of packets that has reached dest nodes 3 and 4
    int packetCount3 = 0;
    int packetCount4 = 0;
    int packetCountTotal = 0;

    for(int i = 1 ; i <= trans ;){
        r=randomgeneration(seed); // Generates random number by calling function
        //cout<<"r "<<r<<endl;
        seed=seed+time(NULL);//different seed is used to generate random numbers
        if(r > chkptLayer1_1 && r < chkptLayer1_2){// this means that the packet successfully reached the intermediate node 1 or  2
            // now we start sending packets to the destnodes 3 and 4
            packetCountTotal ++;
            while(packetCount3 != i || packetCount4 != i){
                r2=randomgeneration(seed);
                seed=seed+time(NULL);
                //cout<<"r2 "<<r2<<endl;
                if(r2 > chkptLayer2_1 && r2 <= chkptLayer2_2){ // packet reached node 4
                    if(packetCount4 < i) packetCount4++;
                }
                else if(r2 > chkptLayer2_2 && r2 <= chkptLayer2_3){ // packet reached node 3
                    if(packetCount3 < i) packetCount3++;
                }
                else if(r2 > chkptLayer2_3 && r2 <= chkptLayer2_4){ // packet reahced node 4 and 3 both
                    if(packetCount3 < i) packetCount3++; 
                    if(packetCount4 < i) packetCount4++;
                }

                packetCountTotal ++;
                //cout<<"packetcount3 "<<packetCount3<<endl;
                //cout<<"packetcount4 "<<packetCount4<<endl;
                //cout<<"total "<<packetCountTotal<<endl;
            }
            i++;
        }
        else{
            packetCountTotal ++;
            //cout<<"total"<<packetCountTotal<<endl;
        }
    }
    cout <<"Total Transmissions Made: " <<packetCountTotal<< endl;
}

void sendPackets12(vector<vector<float>> &m){
    /*
    the possible combinations for paths is 
    if the min is using intermediate node 1 and node 2 ie) the x returned by set_1_2() is minimum
        then we have more possible combinations like 
            if the min path is dest2(1_34)
                then min is "forwarderset(1,2)dest2(1_34)"
            if the min path is dest2(2_34)
                then min is "forwarderset(1,2)dest2(2_34)"
            if the min path is m13 + m24
                then min is "forwarderset(1,2)m13m24"
            if the min path is m14 + m23
                then min is "forwarderset(1,2)m13m24"
    */
    int trans = 0;
    cout<<"Enter the number of packets to be transmitted: ";
    cin>> trans;
    float chkptLayer1_1 = (1 - 1 / m[0][1]) * (1 - 1 / m[0][2]);;
    float chkptLayer1_2 = chkptLayer1_1 + (1 / m[0][1]) * (1 - 1 / m[0][2]);;
    float chkptLayer1_3 = chkptLayer1_2 + (1 - 1 / m[0][1]) * (1 / m[0][2]);;
    float chkptLayer1_4 = chkptLayer1_3 + (1 / m[0][1]) * (1 / m[0][2]);
    
    int packetCount3 = 0;
    int packetCount4 = 0;
    int packetCountTotal = 0 ;
    for(int i = 0 ; i <= trans ;){

        r=randomgeneration(seed); // Generates random number by calling function
        seed=seed+time(NULL);//different seed is used to generate random numbers
        
        if(r > chkptLayer1_1 && r <=chkptLayer1_2){ // packet reached the node 1
            float chkptLayer2_1 = (1 - 1 / m[1][3]) * (1 - 1 / m[1][4]);
            float chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[1][3]) * (1 / m[1][4]);
            float chkptLayer2_3 = chkptLayer2_2 + (1 / m[1][3]) * (1 - 1 / m[1][4]);
            float chkptLayer2_4 = chkptLayer2_3 + (1 / m[1][3]) * (1 / m[1][4]);
            packetCountTotal ++;
            while(packetCount3 != i || packetCount4 != i){
                r2=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers

                if(r2 > chkptLayer2_1 && r2 <=chkptLayer2_2){
                    if(packetCount4 < i) packetCount4++;
                }   
                else if(r2 > chkptLayer2_2 && r2 <=chkptLayer2_3){
                    if(packetCount3 < i) packetCount3++;
                }
                else if(r2 > chkptLayer2_3 && r2 <=chkptLayer2_4){
                    if(packetCount4 < i) packetCount4++;
                    if(packetCount3 < i) packetCount3++;
                }
                packetCountTotal ++;
            }
            i++;
        }
        else if(r > chkptLayer1_2 && r <=chkptLayer1_3){ // packet reached the node 2
            float chkptLayer2_1 = (1 - 1 / m[2][3]) * (1 - 1 / m[2][4]);
            float chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][3]) * (1 / m[2][4]);
            float chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][3]) * (1 - 1 / m[2][4]);
            float chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][3]) * (1 / m[2][4]);
            packetCountTotal ++;
            while(packetCount3 != i || packetCount4 != i){
                r2=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers

                if(r2 > chkptLayer2_1 && r2 <=chkptLayer2_2){
                    if(packetCount4 < i) packetCount4++;
                }   
                else if(r2 > chkptLayer2_2 && r2 <=chkptLayer2_3){
                    if(packetCount3 < i) packetCount3++;
                }
                else if(r2 > chkptLayer2_3 && r2 <=chkptLayer2_4){
                    if(packetCount4 < i) packetCount4++;
                    if(packetCount3 < i) packetCount3++;
                }
                packetCountTotal ++;
            }
            i++;
        }
        else if(r > chkptLayer1_3 && r <=chkptLayer1_4){ // packet reached both nodes 1 and 2
            /*
            We now have 4 possible paths
            1 sends to both 3 and 4
            2 sends to both 3 and 4
            1 send to 3 and 2 send to 4
            1 send to 4 and 2 send to 3
            */
            
            vector<float> cost1_34 = {m[1][3],m[1][4]};// cost of 1 sending to both 3 and 4
            float option1 = dest2(cost1_34);

            vector<float> cost2_34 = {m[2][3],m[2][4]};// cost of 2 sending to both 3 and 4
            float option2 = dest2(cost2_34);

            float option3 = m[1][3] + m[2][4]; // cost of 1 sending to 3 and 2 sending to 4

            float option4 = m[1][4] + m[2][3]; // cost of 2 sending to 3 and 1 sending to 4

            float mini = min(min(min(option1,option2),option3),option4);
            
            // checkpoints on the number line for the second layer
            float chkptLayer2_1 = 0.0;
            float chkptLayer2_2 = 0.0;
            float chkptLayer2_3 = 0.0;
            float chkptLayer2_4 = 0.0;

            if(mini == option1){ // cost of sending from 1 to 3 and 4 is minimum
                chkptLayer2_1 = (1 - 1 / m[1][3]) * (1 - 1 / m[1][4]);
                chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[1][3]) * (1 / m[1][4]);
                chkptLayer2_3 = chkptLayer2_2 + (1 / m[1][3]) * (1 - 1 / m[1][4]);
                chkptLayer2_4 = chkptLayer2_3 + (1 / m[1][3]) * (1 / m[1][4]);
            }
            else if(mini == option2){// cost of sending from 2 to 3 and 4 is minimum
                chkptLayer2_1 = (1 - 1 / m[2][3]) * (1 - 1 / m[2][4]);
                chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][3]) * (1 / m[2][4]);
                chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][3]) * (1 - 1 / m[2][4]);
                chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][3]) * (1 / m[2][4]);
            }
            else if(mini == option3){// cost of 1 sending to 3 and 2 sending to 4 is minimum
                chkptLayer2_1 = (1 - 1 / m[1][3]) * (1 - 1 / m[2][4]);
                chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[1][3]) * (1 / m[2][4]);
                chkptLayer2_3 = chkptLayer2_2 + (1 / m[1][3]) * (1 - 1 / m[2][4]);
                chkptLayer2_4 = chkptLayer2_3 + (1 / m[1][3]) * (1 / m[2][4]);
            }
            else if(mini == option4){// cost of 1 sending to 4 and 2 sending to 3 is minimum
                chkptLayer2_1 = (1 - 1 / m[2][3]) * (1 - 1 / m[1][4]);
                chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][3]) * (1 / m[1][4]);
                chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][3]) * (1 - 1 / m[1][4]);
                chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][3]) * (1 / m[1][4]);
            }
            packetCountTotal ++;
            while(packetCount3 != i || packetCount4 != i){
                r2=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers

                if(r2 > chkptLayer2_1 && r2 <=chkptLayer2_2){
                    if(packetCount4 < i) packetCount4++;
                }   
                else if(r2 > chkptLayer2_2 && r2 <=chkptLayer2_3){
                    if(packetCount3 < i) packetCount3++;
                }
                else if(r2 > chkptLayer2_3 && r2 <=chkptLayer2_4){
                    if(packetCount4 < i) packetCount4++;
                    if(packetCount3 < i) packetCount3++;
                }
                packetCountTotal ++;
            }
            i++;
        }
        else{
            packetCountTotal ++;
        }
    }
    cout<< "Total Transmissions Made: " << packetCountTotal << endl;
}

int main() {
    char c;
    cout << "Would You Like to Take input MTX from input.txt? (Y/N): ";
    cin >> c;

    vector<vector<float>> mtx;

    if (c == 'Y') {
        ifstream inputFile("inputNew.txt");
        if (!inputFile) {
            cerr << "Error: Unable to open file!" << endl;
            return 1;
        }

        int rows, cols;
        inputFile >> rows >> cols; 

        mtx.assign(rows, vector<float>(cols)); 

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                inputFile >> mtx[i][j];
            }
        }

        inputFile.close();
    } else if (c == 'N') {
        int n;
        cout << "Enter number of nodes: ";
        cin >> n;

        if (n < 1) {
            cout << "Invalid number of nodes.\n";
            return 0;
        }

        mtx.assign(n, vector<float>(n, 0));

        while (true) {
            int from, to;
            float etx;
            cout << "Enter the nodes to connect (0 to " << n - 1 << ") or (-1 to exit):\n";
            cout << "From node: ";
            cin >> from;

            if (from == -1) break;

            cout << "To node: ";
            cin >> to;
            if (to == -1) break;

            if (from >= n || to >= n || from < 0 || to < 0) {
                cout << "Invalid node numbers. Try again.\n";
                continue;
            }

            cout << "Enter the ETX value (> 0): ";
            cin >> etx;

            if (etx <= 0) {
                cout << "Invalid ETX value. Must be greater than 0.\n";
                continue;
            }

            mtx[from][to] = etx;
            mtx[to][from] = etx;
        }
    } else {
        cout << "Enter Y or N" << endl;
        return 1;
    }

    ofstream outputFile("outputNew.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create output.txt!" << endl;
        return 1;
    }
    vector<float> cost1_34 = {mtx[1][3],mtx[1][4]};
    vector<float> cost2_34 = {mtx[2][3],mtx[2][4]};
    vector<float> cost0_12 = {mtx[0][1],mtx[0][2]};
    float intermediate1 = set_1(mtx);
    float intermediate2 = set_2(mtx);
    float intermediate12 = set_1_2(mtx);
    float mini = FLT_MAX;
    mini = min(min(intermediate1,intermediate2),intermediate12);
    outputFile << "Source  Intermediate  Destination  Cost"<<endl;
    outputFile << "  (0)       (1)          (3,4)     " << intermediate1 << endl;
    outputFile << "  (0)       (2)          (3,4)     " << intermediate2 << endl;
    outputFile << "  (0)      (1,2)         (3,4)     " << intermediate12 <<endl;
    outputFile << "  (0)       (-)          (1,2)     " << dest2(cost0_12) <<endl;
    outputFile << "  (1)       (-)          (3,4)     " << dest2(cost1_34) <<endl;
    outputFile << "  (2)       (-)          (3,4)     " << dest2(cost2_34) <<endl;
    outputFile << endl;
    outputFile << "The min cost to travel from (0) to (4,5): "<< mini;
    if(intermediate1 == mini){
        outputFile << " using the intermediate node 1" << endl;
        sendPackets(mtx,1);
    }else if (intermediate2 == mini){
        outputFile << " using the intermediate node 2" << endl;
        sendPackets(mtx,2);
    }else if(intermediate12 == mini){
        outputFile << " using the intermediate node 1 and 2" << endl;
        sendPackets12(mtx);
    }
    sendPackets12(mtx);
    outputFile.close();
    cout << "Results written to outputNew.txt" << endl;
    
    return 0;
}

float randomgeneration(long idum){
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    float temp;
    if (idum <= 0){//Initialize.
        if (-(idum) < 1)
            idum=1;//Be sure to prevent idum=0.
        else 
            idum = -(idum);
        idum2=(idum);
        for (j=NTAB+7;j>=0;j--){
           k=(idum)/IQ1;
           idum=IA1*(idum-k*IQ1)-k*IR1;
           if (idum < 0)
               idum += IM1;
           if (j < NTAB)
               iv[j] = idum;
        }   
        iy=iv[0];
    }
    k =(idum)/IQ1; //Start here when not initializing.
    idum=IA1*(idum-k*IQ1)-k*IR1; //Computeidum=(IA1*idum) % IM1without overflows by Schrage's method.
    if (idum < 0)
        idum += IM1;
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2; //Computeidum2=(IA2*idum) % IM2likewise.
    if (idum2 < 0) 
        idum2 += IM2;
    j=iy/NDIV; //Will be in the range0..NTAB-1.
    iy=iv[j]-idum2; //Hereidumis shued, idumandidum2are combined to generate output.
    iv[j] = idum;
    if (iy < 1) 
        iy += IMM1;
    if ((temp=AM*iy) > RNMX) 
        return RNMX; //Because users don't expect endpoint values.
    else 
        return temp;
}