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
float r2,r3;
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

//Function to compute the cost for (2) as intermediate nodes
float set_2(vector<vector<float>> &m){
    vector<float> cost2_45 = {m[2][4],m[2][5]}; 
    float x = (m[0][2]) + dest2(cost2_45);
    //cout<<"Cost for forwarder set (2) ";
    return x;
}

//Function to compute the cost for (1,2) as intermediate nodes
float set_1_2(vector<vector<float>> &m){
    vector<float> cost2_45 = {m[2][4],m[2][5]}; 
    float x = ((1 - 1/m[0][2] -1/m[0][1] + 1/(m[0][1] * m[0][2]))
            + ((1 - 1/ m[0][1]) * (1 / m[0][2]) * ( 1 + dest2(cost2_45)))
            + ((1/ m[0][1]) * (1 - 1 / m[0][2]) * ( 1 + m[1][4] + m[0][2] + m[2][5]))
            + ((1/ m[0][1]) * (1 / m[0][2]) * ( 1 + min(m[1][4] + m[2][5],dest2(cost2_45)))))
            / ((1/m[0][2] + 1/m[0][1] - 1/(m[0][1] * m[0][2])));
    //cout<<"Cost for forwarder set (1,2) ";
    return x;
}

//Function to compute the cost for (2,3) as intermediate nodes
float set_2_3(vector<vector<float>> &m){
    vector<float> cost2_45 = {m[2][4],m[2][5]}; 
    float x = ((1 - 1/m[0][2] - 1/m[0][3] + 1/(m[0][3] * m[0][2]))
            + ((1 - 1/ m[0][3]) * (1 / m[0][2]) * ( 1 + dest2(cost2_45)))
            + ((1/ m[0][3]) * (1 - 1 / m[0][2]) * ( 1 + m[3][5] + m[0][2] + m[2][4]))
            + ((1/ m[0][3]) * (1 / m[0][2]) * ( 1 + min(m[3][5] + m[2][4],dest2(cost2_45)))))
            / ((1/m[0][2] + 1/m[0][3] - 1/(m[0][3] * m[0][2])));
    //cout<<"Cost for forwarder set (2,3) ";
    return x;
}

//Function to compute the cost for (1,3) as intermediate nodes
float set_1_3(vector<vector<float>> &m){
    float x = ((1 - 1/m[0][1] - 1/m[0][3] + 1/(m[0][3] * m[0][1]))
            + ((1 - 1/ m[0][3]) * (1 / m[0][1]) * ( 1 + m[1][4] + m[0][3] + m[3][5]))
            + ((1/ m[0][3]) * (1 - 1 / m[0][1]) * ( 1 + m[3][5] + m[0][1] + m[1][4]))
            + ((1/ m[0][3]) * (1 / m[0][1]) * ( 1 + m[1][4] + m[3][5])))
            / ((1/m[0][1] + 1/m[0][3] - 1/(m[0][3] * m[0][1])));
    //cout<<"Cost for forwarder set (1,3) ";
    return x;
}

//Function to compute the cost for (1,2,3) as intermediate nodes
float set_1_2_3(vector<vector<float>> &m){
    float x = 0.0;

    vector<float> cost0_4 = {m[0][1],m[0][2],m[1][4],m[2][4]};
    vector<float> cost0_5 = {m[0][2],m[0][3],m[2][5],m[3][5]};
    vector<float> cost2_45 = {m[2][4],m[2][5]};  

    x = (1 - 1 / m[0][3] - 1 / m[0][2] + 1 / ( m[0][2] * m[0][3]) - 1 / m[0][1] + 1 / (m[0][1] * m[0][3]) + 1 / (m[0][1] * m[0][2]) - 1 / (m[0][1] * m[0][2] * m[0][3])
        +((1 - 1/m[0][1]) * (1 - 1/m[0][2]) * (1/m[0][3]) * (1 + m[3][5] + hop_2_dest_1_route_2(cost0_4)))
        +((1 - 1/m[0][1]) * (1/m[0][2]) * (1 - 1/m[0][3]) * (1 + dest2(cost2_45)))
        +((1/m[0][1])  * (1 - 1/m[0][2]) * (1 - 1/m[0][3]) * (1 + m[1][4] + hop_2_dest_1_route_2(cost0_5)))
        +((1 - 1/m[0][1]) * (1/m[0][2]) * (1/m[0][3]) * (1+min(dest2(cost2_45),(m[2][4] + m[3][5]))))
        +((1/m[0][1]) * (1/m[0][2]) * (1 - 1/m[0][3]) * (1+min(dest2(cost2_45),(m[1][4] + m[2][5]))))
        +((1/m[0][1]) * (1 - 1/m[0][2]) * (1/m[0][3]) * (1 + m[1][4] + m[3][5]))
        +((1/m[0][1]) * (1/m[0][2]) * (1/m[0][3]) * (1 + min(min(m[1][4] + m[3][5],min(m[1][4]+m[2][5],m[2][4] + m[3][5])), (dest2(cost2_45)))))) 
        / (1 / m[0][3] + 1 / m[0][2] - 1/(m[0][3]* m[0][2]) + 1 / m[0][1] - 1 /(m[0][1] * m[0][3]) - 1 /(m[0][1] * m[0][2]) + 1/(m[0][1] * m[0][2] * m[0][3]));
    
    //cout<<"Cost for forwarder set (1,2,3) ";
    return x;
}

void send_Packet_When_Reached_2_Nodes(vector<vector<float>> &m,int intermediateNodeOne,int intermediateNodeTwo,int &packetCountTotal,int &packetCount4,int &packetCount5,int &i){
    /*
    We now have 4 possible paths
    if intermediate1 or intermediate2 == 2
        then from 2 to 4 and 5 
        or   from 1 to 4 and 2 to 5
        or   from 3 to 5 and 2 to 5
    else from 1 to 4 and 3 to 5
    */

    float option1 = FLT_MAX;
    float option2 = FLT_MAX;
    float option3 = FLT_MAX;

    if(intermediateNodeOne == 2 ){
        vector<float> cost2_45 = {{m[2][4], m[2][5]}};
        option1 = dest2(cost2_45);
        if(intermediateNodeTwo == 1){
            option2 = m[1][4] + m[2][5];
        }
        else if(intermediateNodeTwo == 3){
            option2 = m[3][5] + m[2][4];
        }
    } else {
        option3 = m[1][4] + m[3][5];
    }
    float mini = min(option3,min(option1,option2));
    // cout<<"Options: "<<endl;
    // cout<< option1<<" "<< option2<< " "<< option3 <<endl;
    if(mini == option1){
        float chkptLayer2_1 = (1 - 1 / m[2][4]) * (1 - 1 / m[2][5]);
        float chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][4]) * (1 / m[2][5]);
        float chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][4]) * (1 - 1 / m[2][5]);
        float chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][4]) * (1 / m[2][5]);
        while(packetCount4 != i || packetCount5 != i){ 
            r2=randomgeneration(seed); // Generates random number by calling function
            seed=seed+time(NULL);//different seed is used to generate random numbers
            packetCountTotal ++;
            //cout<<"random number 2 "<<r2<<endl;
            if(r2 > chkptLayer2_1 && r2 <=chkptLayer2_2){
                if(packetCount5 < i) packetCount5++;
            }   
            else if(r2 > chkptLayer2_2 && r2 <=chkptLayer2_3){
                if(packetCount4 < i) packetCount4++;
            }
            else if(r2 > chkptLayer2_3 && r2 <=chkptLayer2_4){
                if(packetCount4 < i) packetCount4++;
                if(packetCount5 < i) packetCount5++;
            }
            //cout<<"pktcount4: "<<packetCount4<<"pktcount5: "<<packetCount5<<endl;
            //cout<<"total packets: "<<packetCountTotal<<endl;
        }
        i++;
    }
    else if(mini == option2){
        if (intermediateNodeTwo == 1){

            float chkptLayer2_1_Intermediate_One = (1 - 1 / m[1][4]);
            float chkptLayer2_2_Intermediate_One = chkptLayer2_1_Intermediate_One + (1 / m[1][4]);
            float chkptLayer2_1_Intermediate_Two = (1 - 1 / m[2][5]);
            float chkptLayer2_2_Intermediate_Two = chkptLayer2_1_Intermediate_Two + (1 / m[2][5]);

            while(packetCount4 != i || packetCount5 != i){ 

                r2=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers
                packetCountTotal ++;
                r3=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers
                packetCountTotal ++;

                if(r2 > chkptLayer2_1_Intermediate_One && r2 <= chkptLayer2_2_Intermediate_One){
                    if(packetCount4 < i) packetCount4++;
                } 
                if(r3 > chkptLayer2_1_Intermediate_Two && r3 <= chkptLayer2_2_Intermediate_Two){
                    if(packetCount5 < i) packetCount5++;
                } 
            }
            i++;
        }
        else if(intermediateNodeTwo == 2){
            float chkptLayer2_1_Intermediate_One = (1 - 1 / m[1][4]);
            float chkptLayer2_2_Intermediate_One = chkptLayer2_1_Intermediate_One + (1 / m[1][4]);

            float chkptLayer2_1_Intermediate_Two = (1 - 1 / m[3][5]);
            float chkptLayer2_2_Intermediate_Two = chkptLayer2_1_Intermediate_Two + (1 / m[3][5]);

            while(packetCount4 != i){ 
                r2=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers
                packetCountTotal ++;
                if(r2 > chkptLayer2_1_Intermediate_One && r2 <= chkptLayer2_2_Intermediate_One){
                    if(packetCount4 < i) packetCount4++;
                } 
            }
            while(packetCount5 != i){
                r3=randomgeneration(seed); // Generates random number by calling function
                seed=seed+time(NULL);//different seed is used to generate random numbers
                packetCountTotal ++;
                if(r3 > chkptLayer2_1_Intermediate_Two && r3 <= chkptLayer2_2_Intermediate_Two){
                    if(packetCount5 < i) packetCount5++;
                }  
            }
            i++;
        }
    }
    else if(mini == option3){
        float chkptLayer2_1_Intermediate_One = (1 - 1 / m[1][4]);
        float chkptLayer2_2_Intermediate_One = chkptLayer2_1_Intermediate_One + (1 / m[1][4]);

        float chkptLayer2_1_Intermediate_Two = (1 - 1 / m[3][5]);
        float chkptLayer2_2_Intermediate_Two = chkptLayer2_1_Intermediate_Two + (1 / m[3][5]);

        while(packetCount4 != i){ 
            r2=randomgeneration(seed); // Generates random number by calling function
            seed=seed+time(NULL);//different seed is used to generate random numbers
            packetCountTotal ++;
            if(r2 > chkptLayer2_1_Intermediate_One && r2 <= chkptLayer2_2_Intermediate_One){
                if(packetCount4 < i) packetCount4++;
            } 
        }
        while(packetCount5 != i){
            r3=randomgeneration(seed); // Generates random number by calling function
            seed=seed+time(NULL);//different seed is used to generate random numbers
            packetCountTotal ++;
            if(r3 > chkptLayer2_1_Intermediate_Two && r3 <= chkptLayer2_2_Intermediate_Two){
                if(packetCount5 < i) packetCount5++;
            }  
        }
        i++;
    } 
}

void sendPackets_1Node(vector<vector<float>> &m){ // Find the min path from the o/p generated to begin sending packets of data
    /*
    In this function there are two hops
        - 0 to 2
        - from 2 to 3 and 4
    */
    int trans = 0;
    cout<<"Enter the number of packets to be transmitted: ";
    cin>> trans;

    // checkpoints on the number line for the first layer
    float chkptLayer1_1 = 0.0;
    float chkptLayer1_2 = 0.0;

    chkptLayer1_1 = 1 - 1 / m[0][2];
    chkptLayer1_2 = chkptLayer1_1 + 1 / m[0][2];

    // checkpoints on the number line for the second layer
    float chkptLayer2_1 = 0.0;
    float chkptLayer2_2 = 0.0;
    float chkptLayer2_3 = 0.0;
    float chkptLayer2_4 = 0.0;
 
    chkptLayer2_1 = (1 - 1 / m[2][4]) * (1 - 1 / m[2][5]);
    chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][4]) * (1 / m[2][5]);
    chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][4]) * (1 - 1 / m[2][5]);
    chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][4]) * (1 / m[2][5]);
    
    //Number of packets that has reached dest nodes 4 and 5
    int packetCount4 = 0;
    int packetCount5 = 0;
    int packetCountTotal = 0;

    for(int i = 1 ; i <= trans ;){
        r=randomgeneration(seed); // Generates random number by calling function
        seed=seed+time(NULL);//different seed is used to generate random numbers
        packetCountTotal ++;
        if(r > chkptLayer1_1 && r < chkptLayer1_2){// this means that the packet successfully reached the intermediate node 1 or 2
            while(packetCount4 != i || packetCount5 != i){
                r2=randomgeneration(seed);
                seed=seed+time(NULL);
                packetCountTotal ++;
                if(r2 > chkptLayer2_1 && r2 <= chkptLayer2_2){ // packet reached node 5
                    if(packetCount5 < i) packetCount5++;
                }
                else if(r2 > chkptLayer2_2 && r2 <= chkptLayer2_3){ // packet reached node 4
                    if(packetCount4 < i) packetCount4++;
                }
                else if(r2 > chkptLayer2_3 && r2 <= chkptLayer2_4){ // packet reahced node 4 and 5 both
                    if(packetCount4 < i) packetCount4++; 
                    if(packetCount5 < i) packetCount5++;
                }
            }
            i++;
        }
    }
    cout <<"Total Transmissions Made: " <<packetCountTotal<< endl;
}

void sendPackets_2Node(vector<vector<float>> &m,int intermediateNodeOne,int intermediateNodeTwo){
    int trans = 0;
    cout<<"Enter the number of packets to be transmitted: ";
    cin>> trans;

    float chkptLayer1_1 = 0.0;
    float chkptLayer1_2 = 0.0;
    float chkptLayer1_3 = 0.0;
    float chkptLayer1_4 = 0.0;

    chkptLayer1_1 = (1 - 1 / m[0][intermediateNodeOne]) * (1 - 1 / m[0][intermediateNodeTwo]);
    chkptLayer1_2 = chkptLayer1_1 + (1 / m[0][intermediateNodeOne]) * (1 - 1 / m[0][intermediateNodeTwo]);
    chkptLayer1_3 = chkptLayer1_2 + (1 - 1 / m[0][intermediateNodeOne]) * (1 / m[0][intermediateNodeTwo]);
    chkptLayer1_4 = chkptLayer1_3 + (1 / m[0][intermediateNodeOne]) * (1 / m[0][intermediateNodeTwo]);
    
    // cout<<chkptLayer1_1<<endl;
    // cout<<chkptLayer1_2<<endl;
    // cout<<chkptLayer1_3<<endl;
    // cout<<chkptLayer1_4<<endl;

    int packetCount4 = 0;
    int packetCount5 = 0;
    int packetCountTotal = 0;
    for(int i = 1 ; i <= trans ;){
        r=randomgeneration(seed); // Generates random number by calling function
        seed=seed+time(NULL);//different seed is used to generate random numbers
        packetCountTotal ++;
        //cout<<"random number 1 "<<r<<endl;

        bool packetReachIntermediateOne = false;
        bool packetReachIntermediateTwo = false;

        if(r > chkptLayer1_1 && r <=chkptLayer1_2){ // packet reached the node intermediate1
            packetReachIntermediateOne = true;
            if(intermediateNodeOne == 2 && !packetReachIntermediateTwo){
                float chkptLayer2_1 = (1 - 1 / m[2][4]) * (1 - 1 / m[2][5]);
                float chkptLayer2_2 = chkptLayer2_1 + (1 - 1 / m[2][4]) * (1 / m[2][5]);
                float chkptLayer2_3 = chkptLayer2_2 + (1 / m[2][4]) * (1 - 1 / m[2][5]);
                float chkptLayer2_4 = chkptLayer2_3 + (1 / m[2][4]) * (1 / m[2][5]);
                //packetCountTotal ++;
                // cout<<"total packets: "<<packetCountTotal<<endl;
                // cout<<chkptLayer2_1<<endl;
                // cout<<chkptLayer2_2<<endl;
                // cout<<chkptLayer2_3<<endl;
                // cout<<chkptLayer2_4<<endl;

                while(packetCount4 != i || packetCount5 != i){ 
                    r2=randomgeneration(seed); // Generates random number by calling function
                    seed=seed+time(NULL);//different seed is used to generate random numbers
                    packetCountTotal ++;
                    // cout<<"random number 2 "<<r2<<endl;
                    if(r2 > chkptLayer2_1 && r2 <=chkptLayer2_2){
                        if(packetCount5 < i) packetCount5++;
                    }   
                    else if(r2 > chkptLayer2_2 && r2 <=chkptLayer2_3){
                        if(packetCount4 < i) packetCount4++;
                    }
                    else if(r2 > chkptLayer2_3 && r2 <=chkptLayer2_4){
                        if(packetCount4 < i) packetCount4++;
                        if(packetCount5 < i) packetCount5++;
                    }
                    // cout<<"pktcount4: "<<packetCount4<<"pktcount5: "<<packetCount5<<endl;
                    // cout<<"total packets: "<<packetCountTotal<<endl;
                }
                i++;
            }
            else if(packetReachIntermediateOne && packetReachIntermediateTwo){
                send_Packet_When_Reached_2_Nodes(m,intermediateNodeOne,intermediateNodeTwo,packetCountTotal,packetCount4,packetCount5,i);
                packetReachIntermediateOne = false;
                packetReachIntermediateTwo = false;
            }
        }
        else if(r > chkptLayer1_2 && r <=chkptLayer1_3){ // packet reached the node intermediateNodeTwo
            packetReachIntermediateTwo = true;
        }
        else if(r > chkptLayer1_3 && r <=chkptLayer1_4){ // packet reached both nodes intermediate1 and intermediate2
            send_Packet_When_Reached_2_Nodes(m,intermediateNodeOne,intermediateNodeTwo,packetCountTotal,packetCount4,packetCount5,i);
            packetReachIntermediateOne = false;
            packetReachIntermediateTwo = false;
        }
    }
    cout<< "Total Transmissions Made: " << packetCountTotal << endl;
}

void sendPackets_3Node(vector<vector<float>> &m){
    
}

int main() {
    char c;
    cout << "Would You Like to Take input MTX from input.txt? (Y/N): ";
    cin >> c;

    vector<vector<float>> mtx;

    if (c == 'Y') {
        ifstream inputFile("input.txt");
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

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create output.txt!" << endl;
        return 1;
    }
    float mini = FLT_MIN;
   
    vector<float> cost0_4 = {mtx[0][1], mtx[0][2], mtx[1][4], mtx[2][4]};
    vector<float> cost0_5 = {mtx[0][2], mtx[0][3], mtx[2][5], mtx[3][5]};
    vector<float> cost2_45 = {{mtx[2][4], mtx[2][5]}};
    float intermediate2 = set_2(mtx);
    float intermediate12 = set_1_2(mtx);
    float intermediate23 = set_2_3(mtx);
    float intermediate13 = set_1_3(mtx);
    float intermediate123 = set_1_2_3(mtx);

    mini = min(intermediate12,min(intermediate13,min(intermediate23,min(intermediate2,intermediate123))));
    outputFile << "Source  Intermediate  Destination  Cost"<<endl;
    outputFile << "  (0)      (1,2)          (4)      " << hop_2_dest_1_route_2(cost0_4) << endl;
    outputFile << "  (0)      (2,3)          (5)      " << hop_2_dest_1_route_2(cost0_5) << endl;
    outputFile << "  (2)        ()          (4,5)     " << dest2(cost2_45) << endl;
    outputFile << "  (0)       (2)          (4,5)     " << set_2(mtx) << endl;
    outputFile << "  (0)      (1,2)         (4,5)     " << set_1_2(mtx) << endl;
    outputFile << "  (0)      (2,3)         (4,5)     " << set_2_3(mtx) <<endl;
    outputFile << "  (0)      (1,3)         (4,5)     " << set_1_3(mtx) << endl;
    outputFile << "  (0)     (1,2,3)        (4,5)     " << set_1_2_3(mtx) << endl;
    outputFile << endl;
    outputFile << "The min cost to travel from (0) to (4,5): "<< mini;

    if(intermediate2 == mini){
         outputFile << " using the intermediate node 2" << endl;
         sendPackets_1Node(mtx);
    }
    else if(intermediate12 == mini){
         outputFile << " using the intermediate node 1 and 2" << endl;
        sendPackets_2Node(mtx,1,2);
    }else if (intermediate23 == mini){
        outputFile << " using the intermediate node 2 and 3" << endl;
        sendPackets_2Node(mtx,2,3);
    }else if(intermediate13 == mini){
        outputFile << " using the intermediate node 1 and 3" << endl;
        sendPackets_2Node(mtx,1,3);
    }else if(intermediate123 == mini){
        outputFile << " using the intermediate node 1 , 2 and 3" << endl;
       sendPackets_3Node(mtx);
    }
    outputFile.close();
    cout << "Results written to output.txt " << endl;
    cout << "Calling Functions Manually : "<< endl;
    
    sendPackets_2Node(mtx,2,1);
    sendPackets_2Node(mtx,2,3);
    sendPackets_2Node(mtx,1,3);
    
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