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
static long seed=time(NULL);// different seeds are used for generating random number

int main(){
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;
    
    if (n < 1) exit(0);

    vector<vector<float>> mtx(n, vector<float>(n, 0)); // Initialize adjacency matrix with 0

    while (true) {
        int from, to;
        float prob;
        cout << "Enter the nodes to connect (0 to " << n - 1 << ") or (-1 to exit):" << endl;
        
        cout << "From node: ";
        cin >> from;
        if (from == -1) break;

        cout << "To node: ";
        cin >> to;
        if (to == -1) break;

        if (from >= n || to >= n || from < 0 || to < 0) {
            cout << "\nNot within the limits\n";
            continue;
        }

        cout << "Enter the ETX ( > 1 ): ";
        cin >> prob;

        if (prob < 1 ) {
            cout << "\nNot within the limits\n";
            continue;
        }

        mtx[from][to] = prob;
    }

    int s;
    cout << "Enter the source node: ";
    cin >> s;

    while (s < 0 || s >= n) {
        cout << "Enter the source node again: ";
        cin >> s;
    }

    vector<float> arr;
    
    for (int i = 0; i < n; i++) {
        if (mtx[s][i] > 0) {
            arr.push_back(mtx[s][i]);
        }
    }
    cout << setprecision(3);
    cout << "\nAdjacency Matrix\n";
    for (const auto& row : mtx) {
        for (float val : row) {
            cout << fixed << setprecision(3) << val << " ";
        }
        cout << endl;
    }

    float chkpt1 =   (1 - 1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 - 1 / mtx[0][3]);
    cout<<chkpt1<<endl;
    float chkpt2 = chkpt1 +  (1 - 1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * ( 1 / mtx[0][3]) ;
    cout<<chkpt2<<endl;
    float chkpt3 = chkpt2 +  (1 - 1 / mtx[0][1]) * ( 1 / mtx[0][2]) * (1 - 1 / mtx[0][3]) ;
    cout<<chkpt3<<endl;
    float chkpt4 = chkpt3 +  (1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 - 1 / mtx[0][3]);
    cout<<chkpt4<<endl;
    float chkpt5 = chkpt4 +  (1 - 1 / mtx[0][1]) * (1 / mtx[0][2]) * (1 / mtx[0][3]);
    cout<<chkpt5<<endl;
    float chkpt6 = chkpt5 +  (1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 / mtx[0][3]);
    cout<<chkpt6<<endl;
    float chkpt7 = chkpt6 +  (1 / mtx[0][1]) * (1 / mtx[0][2]) * (1 - 1 / mtx[0][3]) ;
    cout<<chkpt7<<endl;
    float chkpt8 = chkpt7 +  (1 / mtx[0][1]) * (1 / mtx[0][2]) * (1 / mtx[0][3]);
    cout<<chkpt8<<endl;
    int trans = 0;
    cout << "Enter the number of Packets to be Transmitted : ";
    cin >> trans;
    int packetCount1 = 0;
    int packetCount2 = 0;
    int packetCount3 = 0;
    int packetCountTotal = 0;

    for(int i = 0 ; i <= trans ; i++){
        while(packetCount1 != i || packetCount2 != i || packetCount3 != i){
            r=randomgeneration(seed); // Generates random number by calling function
            seed=seed+time(NULL);//different seed is used to generate random numbers
            if(r > chkpt1 && r <= chkpt2){
                if(packetCount3 < i)packetCount3++; 
            }
            else if(r > chkpt2 && r <= chkpt3){
                if(packetCount2 < i)packetCount2++; 
            }
            else if(r > chkpt3 && r <= chkpt4){
                if(packetCount1 < i)packetCount1++; 
            }
            else if(r > chkpt4 && r <= chkpt5){
                if(packetCount2 < i)packetCount2++; 
                if(packetCount3 < i)packetCount3++;
            }
            else if(r > chkpt4 && r <= chkpt5){
                if(packetCount2 < i) packetCount2++; 
                if(packetCount3 < i) packetCount3++;
            }
            else if(r > chkpt5 && r <= chkpt6){
                if(packetCount1 < i) packetCount1++; 
                if(packetCount3 < i) packetCount3++;
            }
            else if(r > chkpt6 && r <= chkpt7){
                if(packetCount1 < i) packetCount1++; 
                if(packetCount2 < i) packetCount2++;
            }
            else if(r > chkpt7){
                if(packetCount1 < i) packetCount1++; 
                if(packetCount2 < i) packetCount2++;
                if(packetCount3 < i) packetCount3++;
            }
            packetCountTotal++;
        }
    }

    cout<< packetCountTotal << endl;
    //cout<< chkpt1 << " " << chkpt2 << " " << chkpt3 << " "<< chkpt4<< " val check" << endl;
    // for(int i = 0 ; i < 100 ; i ++){
    //     r=randomgeneration(seed); // Generates random number by calling function
    //     seed=seed+time(NULL);//different seed is used to generate random numbers
    //     cout<< setprecision(3) << r << " ";
    // }
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