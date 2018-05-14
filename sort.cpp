// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>


using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  list<Data*>::iterator it;
  
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------
#include <queue>
#include <utility>
// You may add global variables, functions, and/or
// class defintions here if you wish.

bool compareone( const Data* first, const Data* second)
{
  return first->val1<second->val1;
}

bool comparetwo( const Data* first, const Data* second)
{
  return first->val2<second->val2;
}

bool comparethree( const Data* first, const Data* second)
{
	return first->val3<second->val3;
}

bool comparefour( const Data* first, const Data* second)
{
	return first->val4<second->val4;
}
///////////////////////////////////////INSERTION SORT /////////////////////// 
void insertionSort(list<Data*>::iterator begin,list<Data*>::iterator end)
{
	list<Data*>::iterator j;
	for( list<Data*>::iterator p = next(begin); p != end; ++p )
	{
		Data* tmp = move( *p );
		for( j = p; j != begin && compareone( tmp, *prev(j) ); --j )
			{
				*j = move( *prev(j) );	
			}
		*j = move( tmp );	
	}
}
void insertionSorto(list<Data*>::iterator begin,list<Data*>::iterator end)
{
	list<Data*>::iterator j;
	for( list<Data*>::iterator p = next(begin); p != end; ++p )
	{
		Data* tmp = move( *p );
		for( j = p; j != begin && comparefour( tmp, *prev(j) ); --j )
			{
				*j = move( *prev(j) );	
			}
		*j = move( tmp );	
	}
}
///////////////////////////////////////BEST SORT ( Radix Sort base 2^8) //////////////////////////
void bsorto(list<Data*> &l){
	int i=0, modd;
	unsigned long int temp;
	double nn = 0;
	list<Data*>::iterator it;
    queue<Data*> bucket[0x100];  

    for (int shift = 0; shift < 32; shift += 8) {
        for ( it = l.begin(); it != l.end() ; it++)
            bucket[((*it)->val2 >> shift) & 0xFF].push(*it);
		
        it=l.begin();
		
        for (int j = 0; j < 0x100;j++){
            while (!bucket[j].empty()){
				*it = bucket[j].front();
				bucket[j].pop();
				it++;
			}
		}  
    }
}
///////////////////////////////////////Counting SORT //////////////////////////

void radixSort(list<Data*> &l){
	int i=0;
	list<Data*>::iterator it;
    queue<Data*> bucket[94];    
	for ( it=l.begin(); it != l.end(); it++){
		bucket[((*it)->val3)-33].push(*it);       
	}
	it=l.begin();
	for (int j = 0; j < 94; j++){
		while (!bucket[j].empty()){
			*it = bucket[j].front();
			bucket[j].pop();
			it++;
		}
	} 
}
///////////////////////////////////////RADIX SORT 2//////////////////////////
void radixSorto(list<Data*> &l){
	int i=0;
	int repeater = 2	;
	list<Data*>::iterator it;
    queue<Data*> bucket[94]; 
	//Ascend down from the least significant bit to the most important one
	for ( repeater ; repeater >= 0 ; repeater--){
		for ( it=l.begin(); it != l.end(); it++){
			bucket[((*it)->val4[repeater])-33].push(*it);       
		}
		it=l.begin();
		for (int j = 0; j < 94; j++){
			while (!bucket[j].empty()){
				*it = bucket[j].front();
				bucket[j].pop();
				it++;
			}
		} 
	}
	insertionSorto( l.begin(), l.end());
}
////////////////////////////////////////////////////// Times on my machine vs On the 2gb ram virtual machine
void sortDataList(list<Data *> &l, int field) {
	if(field == 1){
		insertionSort(l.begin(),l.end()); ///// 0.187 S //// 0.146941 s
	}
	if(field == 2){
		bsorto(l); ////// 0.6 s /////0.4? S
	}
	if(field == 3){
		radixSort(l); //// 0.094 s //// 0.07029 s
	}
	if(field == 4){
		radixSorto(l); ///// 0.672 s ////  0.589637 s
		
	}
}
/*
The times of my final program are as follows:
0.06147 0.219711 0.039124 0.278937 */














