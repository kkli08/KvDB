//
// Created by Damian Li on 2024-08-26.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "api.h"



using namespace std;
int main(){
  auto MyDB = new kvdb::API(1e3);
  MyDB->Open("my_database");
  MyDB->Put(1, 100);
  MyDB->Close();

  return 0;

}