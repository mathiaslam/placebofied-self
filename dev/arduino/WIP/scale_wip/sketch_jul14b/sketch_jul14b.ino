#include <SoftwareSerial.h>
#include <Streaming.h>


int           lcdA=0,lcdB=0,lcdC=0,lcdD=0;
bool          lcd1,lcd2,lcd3,lcd4,lcd5,lcd6,lcd7,lcd8,lcd9;
unsigned int  SAn, SBn, SCn, SDn;
unsigned int  SA[9], SB[9], SC[9], SD[9];
bool          A[9], B[9], C[9], D[9];


//calculate weight
int getDigit(int d)
{
    // d=0,1,2,3
    int i = 2*d+0;
    int j = 2*d+1;

    if ( A[i] &&  A[j] && !B[i] &&  B[j] &&  C[i] &&  C[j] &&  D[i]) return 0; //ok
    if (!A[i] && !A[j] && !B[i] &&  B[j] && !C[i] &&  C[j] && !D[i]) return 1; //ok
    if (!A[i] &&  A[j] &&  B[i] &&  B[j] &&  C[i] && !C[j] &&  D[i]) return 2; //ok
    if (!A[i] &&  A[j] &&  B[i] &&  B[j] && !C[i] &&  C[j] &&  D[i]) return 3; //ok
    if ( A[i] && !A[j] &&  B[i] &&  B[j] && !C[i] &&  C[j] && !D[i]) return 4; //ok
    if ( A[i] &&  A[j] &&  B[i] && !B[j] && !C[i] &&  C[j] &&  D[i]) return 5; //ok
    if ( A[i] &&  A[j] &&  B[i] && !B[j] &&  C[i] &&  C[j] &&  D[i]) return 6; //ok
    if (!A[i] &&  A[j] && !B[i] &&  B[j] && !C[i] &&  C[j] && !D[i]) return 7; //ok
    if ( A[i] &&  A[j] &&  B[i] &&  B[j] &&  C[i] &&  C[j] &&  D[i]) return 8; //ok
    if ( A[i] &&  A[j] &&  B[i] &&  B[j] && !C[i] &&  C[j] &&  D[i]) return 9; //ok
    return 0;
}

void setup() {
  Serial.begin(57600);
}


void loop() {
    lcdA = analogRead(A0);
    lcdB = analogRead(A1);
    lcdC = analogRead(A2);
    lcdD = analogRead(A3);

    

//    Serial.print("ab hier gehts los: ABCD");
//        Serial.print('\n');
//    Serial.print(lcdA);
//    Serial.print(lcdB);
//    Serial.print(lcdC);

//    Serial.print('\n');

//define i as 0..8
    SAn = SBn = SCn = SDn = 0;
    for (int i=0; i<9; i++)
    SA[i] = SB[i] = SC[i] = SD[i] = 0;
    int i=0;


//run while backplanes are active
  while (lcdA!=0 || lcdB!=0 || lcdC!=0 || lcdD!=0) {

        lcdA = analogRead(A0);
        lcdB = analogRead(A1);
        lcdC = analogRead(A2);
        lcdD = analogRead(A3);
        
        //lcd1 = digitalRead(A5);
        lcd2 = digitalRead(A4);
        lcd3 = digitalRead(3);
        lcd4 = digitalRead(4);
        lcd5 = digitalRead(5);
        lcd6 = digitalRead(6);
        lcd7 = digitalRead(7);
        lcd8 = digitalRead(8);
       // lcd9 = digitalRead(9);

            if (lcdA==0)
            {                     
                SA[0] += lcd1;
                SA[1] += lcd2;
                SA[2] += lcd3;
                SA[3] += lcd4;
                SA[4] += lcd5;
                SA[5] += lcd6;
                SA[6] += lcd7;
                SA[7] += lcd8;
                SA[8] += lcd9;
                SAn++;
            }
            if (lcdB==0)
            {
                SB[0] += lcd1;
                SB[1] += lcd2;
                SB[2] += lcd3;
                SB[3] += lcd4;
                SB[4] += lcd5;
                SB[5] += lcd6;
                SB[6] += lcd7;
                SB[7] += lcd8;
                SB[8] += lcd9;
                SBn++;
            }
            if (lcdC==0)
            {
                SC[0] += lcd1;
                SC[1] += lcd2;
                SC[2] += lcd3;
                SC[3] += lcd4;
                SC[4] += lcd5;
                SC[5] += lcd6;
                SC[6] += lcd7;
                SC[7] += lcd8;
                SC[8] += lcd9;
                SCn++;
            }
            if (lcdD==0)
            {
                SD[0] += lcd1;
                SD[1] += lcd2;
                SD[2] += lcd3;
                SD[3] += lcd4;
                SD[4] += lcd5;
                SD[5] += lcd6;
                SD[6] += lcd7;
                SD[7] += lcd8;
                SD[8] += lcd9;
                SDn++;
            }

          i++;  


if (lcdA==0 && lcdB==0 && lcdC==0  && lcdD==0  && lcd9==0 && (SA[0]+SA[1]+SA[2]+SA[3]+SA[4]+SA[5]+SA[6]+SA[7]+SA[8]>0)) {

for (int i=0;i<9;i++)
{
    A[i] = (1.0 * SA[i] / SAn >0.5);
    B[i] = (1.0 * SB[i] / SBn >0.5);
    C[i] = (1.0 * SC[i] / SCn >0.5);
    D[i] = (1.0 * SD[i] / SDn >0.5);
 
}


// decoding
    float weight = 100.0*getDigit(0) + 10.0*getDigit(1) + 1.0*getDigit(2) + 0.1*getDigit(3);
    Serial.print("GEWICHT:");
    Serial.print(weight);
    Serial.print('\n');
    


} //end of if

} //end of while



//delay(200);

} //end of void loop
