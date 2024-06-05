#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cmath>
#include <chrono>
using namespace std;

class Elem{

public:
  int id;
  string text;

  Elem(){}
  Elem(float index, string t){
    id = index;
    text = t;
  }

  void print(){
    //cout</*<id<<": "<*/<text/*<<": "*/<<endl;
    cout<<text<<endl;
  }

};



void shuffle(vector<Elem> &dane, int shuffles){

  Elem tmp;
  int randomPlace = 0;
  
  for(int i=0; i<shuffles; i++){
    for(int j=dane.size()-1; j>1; j--){
      randomPlace = rand()%j;
      swap(dane.at(randomPlace),dane.at(j));
       
    }
  }
 
  
}

void quickSort(vector<Elem> &dane, int low, int high){
  //Hoare partition scheme
  int pivot,i,j;
  if(low<high){
    
    //partition
    pivot = dane.at(low).id;
    i = low-1; j = high+1;
    while(1){
      do{
	i++;
      }while(dane.at(i).id<pivot);
      do{
	j--;
      }while(dane.at(j).id>pivot);

      if(i>=j){
	pivot = j;
	break;
      }
      swap(dane.at(i), dane.at(j));
    }
    
       
    quickSort(dane, low, pivot);
    quickSort(dane, pivot+1, high);
  }
 
}

int findMin(vector<Elem> &dane){
  int min = 2147483647;
  for(int i=0; i<(int)dane.size(); i++){
    if(min>dane.at(i).id)
      min=dane.at(i).id;
  }
  return min;
}
int findMax(vector<Elem> &dane){
  int max = 214748368*(-1);
  for(int i=0; i<(int)dane.size(); i++){
    if(max<dane.at(i).id)
      max=dane.at(i).id;
  }
  return max;
}

void bucketSort(vector<Elem> &dane){
  //n of buckets
  //find min and max
  int  max, min;
  int n;
  int M;
  min = findMin(dane);
  max = findMax(dane);
  n = (max-min)/2 + 1;
  
 
  if(n>1000)
    n=1000;
  vector<vector<Elem>> buckets(n);
  M = max+1;
  for (int i = 0; i<(int)dane.size(); i++) 
    buckets[n * dane[i].id / M].push_back(dane.at(i));
  
  
  for (int i = 0; i< n; i++) 
    quickSort(buckets[i], 0, buckets[i].size() - 1);
  
  
  int k = 0;
  for (int i = 0; i < n; i++) 
    for (int j = 0; j <(int)buckets[i].size(); j++) {
      dane[k] = buckets[i][j];
      k++;
    }
  
  
}

void insertSort(vector<Elem> &dane){
  int j,i;
  int key;

  for(i = 1; i<(int)dane.size(); i++){
    key = dane.at(i).id;
    j = i - 1;
    while(j>=0 && dane.at(j).id>key){
      dane.at(j+1) = dane.at(j);
      j--;
    }
    dane.at(j+1).id = key;
  }
    
  
}
void heapify(vector<Elem> &dane, int n, int i){
  int bigest = i;
  int left = 2*i+1;
  int right = 2*i+2;

  if(left<n && dane.at(left).id>dane.at(bigest).id)
    bigest = left;
  if(right<n && dane.at(right).id>dane.at(bigest).id)
    bigest = right;

  if(bigest!=i){
    swap(dane.at(i), dane.at(bigest));
    heapify(dane,n,bigest);
  }
    
    
}
void heapSort(vector<Elem> &dane){
  for(int i = dane.size()/2 -1; i>=0; i--)
    heapify(dane, dane.size(), i);
  for(int i = dane.size()-1; i>0; i--){
    swap(dane[0], dane[i]);
    heapify(dane, i, 0);
  }
}
void introSort(vector<Elem> &dane){
  int maxDepth = (int)(abs(log(dane.size())));
  int n=dane.size();
  

  if(n<10){
    insertSort(dane);
  }
  else if(maxDepth == 0){
    heapSort(dane);
  }
  else{
    quickSort(dane, 0, dane.size()-1);
  }

  
  
}
int main(int argc, char**argv){

  fstream file;
  string line,col,header;
  string algoName(argv[4]);
  vector<string> fileString, row;
  vector<Elem> dane;
  int check = 0;
  int nOfElements = atoi(argv[3]), sortBy = atoi(argv[2]);
  int randomSeed[1] = {1};
  int seed;
  int flag = 0;
  char validNumberChars[12] = {'.', ',' , '0', '1','2','3','4','5','6','7','8','9'};
  
  file.open(argv[1], ios::in);
  //Sprawdzenie poprawnosci otworzenia pliku
  if(!file.is_open()){
    perror("nie udalo sie otworzyc pliku\n");
    exit(-1);
  }
 
  //jesli potrzebne losowanie ziarna
  if(argc>=6){
    seed = randomSeed[1];
    if(seed<0)seed=seed*-1;
    if(argv[6]){
      seed = atoi(argv[6]);
    }
   
    srand(seed);
  }

  //wczytywanie danych 
  while(getline(file, line)){
    if(check>nOfElements)
       break;
    fileString.push_back(line);
    check++;
    //stwórz indeks
    
    istringstream isline(line);
    while(getline(isline, col, '^')){
      row.push_back(col);
    }

    try {
      for(int i=0; i<(int)row.at(sortBy).size(); i++){
	flag = 0;
	for(int j=0; j<12;j++){
	  
	  if(row.at(sortBy)[i]!=validNumberChars[j]){
	    flag++;
	    if(flag==12)
	      goto flag;
	  }
	}
      }
    flag:
      if(flag>=12)
	row.at(sortBy) = "a";
      
      int tmpnum = stof(row.at(sortBy));
      // if(to_string(tmpnum)==row.at(sortBy)){
	Elem tmp(tmpnum, line);
	dane.push_back(tmp);
	//	}
    }
    catch(...){}
    

    row.clear();
  }

  
  //cout<<"Dane: \n";
  /*for(int i=0; i<(int)dane.size(); i++)
    dane.at(i).print();*/
  

  if(argc>5)
    shuffle(dane,atoi(argv[5]));
  // cout<<"Shuffle: \n";  
  /*for(int i=0; i<(int)dane.size(); i++)
    dane.at(i).print();*/

  //cout<<algoName<<endl;
  auto start = std::chrono::high_resolution_clock::now();
  if(algoName=="QUICK"){
    quickSort(dane, 0, dane.size()-1);
  }
  else if(algoName=="BUCKET"){
    bucketSort(dane);
  }
  else if(algoName=="INTRO"){
    introSort(dane);
  }
  else{
    perror("bledna nazwa algorytmu \n");
    exit(-1);
  }

  auto stop =  std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  

  
  // cout<<"posortowane dane: "<<endl;
  for(int i=0; i<(int)dane.size(); i++)
    dane.at(i).print();
  perror("time: ");
  perror(to_string(time.count()).c_str());
  perror("microseconds");
    
  if(argc>=6)
    perror(to_string(seed).c_str());
  return 0;
}
