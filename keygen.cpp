#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

char* kasp();
string getStr(int*, int);
void getHash(int*, int*);

int main() {
  //char email[16] = "gri_ponomarenko";
  char email[17] = "gri_ponomarenkog";
  
  unsigned int mail[4] = {0};
  unsigned int* pMail = (unsigned int*)email;
  for (int i = 0; i < 4; i++) {
    mail[i] = pMail[i];
  }

  unsigned int* pKas = (unsigned int*)kasp();
  unsigned int kas[44] = {0};
  for (int i = 0; i < 44; i++) {
    kas[i] = pKas[i];
  }

  int pass[4] = {0};

  unsigned int v6 = mail[0];
  unsigned int v3 = mail[1] + kas[0];
  unsigned int v7 = mail[2];
  unsigned int v20 = mail[3] + kas[1];

  unsigned int v37 = v20;
  unsigned int v36 = v3;

  unsigned int v5 = 0;

  unsigned int v9 = 0;
  unsigned int v10 = 0;
  unsigned int v11 = 0;
  unsigned int v12 = 0;

  unsigned int a = 0;
  unsigned int b = 0;

  unsigned int x = 0;
  unsigned int y = 0;

  int j = 2;
  for (int i = 0; i < 20; i++) {
    v36 = v3;
    v37 = v20;

    v10 = ((unsigned int)(v36 * (2 * v36 + 1)) >> 5) | ((v36 * (2 * v36 + 1)) << (32 - 5));
    v12 = ((unsigned int)(v37 * (2 * v37 + 1)) >> 5) | ((v37 * (2 * v37 + 1)) << (32 - 5));

    b = v7^v12;
    v9 = ((unsigned int)(b) >> (v10) | (b) << (32 - v10)) + kas[j + 1];

    a = v6^v10;
    v11 = ((unsigned int)(a) >> (v12) | (a) << (32 - v12)) + kas[j];

    j = j + 2;
    
    v5 = v11;
    v7 = v20;
    v6 = v3;
    v3 = v9;
    v20 = v5;
  }

  pass[0] = v6 + kas[42];
  pass[1] = v3;
  pass[2] = v7 + kas[43];
  pass[3] = v5;
  
  SYSTEMTIME stime;
  GetSystemTime(&stime);

  char* c_pass = (char*)pass;
  for (int i = 0; i < 16; i++) {
    //c_pass[i] = c_pass[i] ^ stime.wDay;
    c_pass[i] = c_pass[i] ^ 20;
  }
  string password = getStr(pass, 4);
  std::cout << getStr(pass, 4) << std::endl;

  free(pKas);
  return 0;
}

char* kasp() {
  char kasp[16] = "kaspersky\0\0\0\0\0\0";
  char res[176];

  int ar[63] = {0};
  //int temp[50] = {0};

  int *temp = (int*)malloc(176 * sizeof(char));
  ZeroMemory(temp, 176);

  int i = 0;
  int j = 0;
  int v5 = 0;
  do {
    v5 = kasp[i] | (v5 << 8);
    i++;
    if (!(i & 3)) {
      ar[j] = v5;
      j++;
      v5 = 0;
    }
  } while (i < 0x10);

  temp[0] = -1209970333;
  i = 1;

  do {
    temp[i] = temp[i - 1] - 1640531527;
    ++i;
  } while (i < 0x2C);

  j = 0;
  i = 0;
  int v12 = 0;
  int v13 = 0;
  int v14 = 0;
  int v16 = 0;
  int v17 = 0;
  int v18 = 132;

  int v3 = 4;

  do {
    v13 = (((unsigned int)(v12 + temp[i] + v13) >> 3) | ((v12 + temp[i] + v13) << 29));
    temp[i] = v13;
    v12 = ((unsigned int)(v13 + ar[j] + v12) >> (v12 + v13)) | ((v13 + ar[j] + v12) << (32 - (v12 + v13)));
    ar[j] = v12;

    i = (v16 + 1) % 0x2C;
    j = (v17 + 1) % 4;
    v14 = (v18 == 1);
    v18--;
    v16 = (v16 + 1) % 0x2C;
    v17 = (v17 + 1) % v3;
  } while (!v14);

  int k = 0;
  return (char*)temp;
}

string getStr(int* p, int n) {
  string str = "";
  int first = 0;
  int sec = 0;
  char* pC = (char*)p;

  for (int i = 0; i < n*4; i++) {
    first = (pC[i] & 0xF0) >> 4;
    sec = pC[i] & 0xF;
    
    if (first >= 0 && first <= 9) {
      str += std::to_string(first);
    } else {
      str += (char)(first + 55);
    }
    if (sec >= 0 && sec <= 9) {
      str += std::to_string(sec);
    } else {
      str += (char)(sec + 55);
    }
  }
  
  return str;
}