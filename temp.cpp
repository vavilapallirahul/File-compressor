#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include<fstream>
#include<unordered_map>

using namespace std;

class HuffTree{
    public:
    int val;
    char letter;
    HuffTree *right;
    HuffTree *left;

    HuffTree(int val , char c){
        this -> letter = c;
        this -> val = val;
        this -> left = NULL;
        this -> right = NULL;
    }
};

vector<pair<int , char>> frequencyDect(string s){
  map<char , int> mp;

   for(int i = 0; i < s.size(); i++)
   mp[s[i]]++;

   vector<pair<int , char>> freq;

   for(auto x : mp){
    freq.push_back(make_pair(x.second , x.first));
   }
   
   sort(freq.begin() , freq.end());

  // for(auto x : v)
  // cout << x.second << " -> " << x.first << endl;

  return freq;

}

class cmp{
    public:
    bool operator()(HuffTree *a , HuffTree *b){
       return (a -> val) > (b -> val);
    }
};

/* void print(priority_queue<HuffTree* , vector<HuffTree*> , cmp> &pq){
     while(pq.size()){
        cout << "yes" << endl;
        cout << pq.top() -> val << " -> " << pq.top() -> letter << endl;
        pq.pop();
     }
}*/

HuffTree* makeTree(vector<pair<int , char>> &freq){
    priority_queue<HuffTree* , vector<HuffTree*> , cmp> pq;
    
    for(int i = 0; i < freq.size(); i++){
        pq.push(new HuffTree(freq[i].first , freq[i].second));
    }
    

  //  print(pq);

  while(pq.size() > 1){
    HuffTree *left = pq.top();
    pq.pop();

    HuffTree *right = pq.top();
    pq.pop();

    HuffTree *new_node = new HuffTree(left -> val + right -> val , '~');

    new_node -> left = left;
    new_node -> right = right;

    pq.push(new_node);
  }
    
    return pq.top();
}

void get_values(HuffTree *root , string psf , unordered_map<char , string> &char_key){
   if(!root)
   return;

   if(root -> letter != '~'){
    char_key[root -> letter] = psf;
    return;
   }

   // else
   get_values(root -> left , psf + '0' , char_key);
   get_values(root -> right , psf + '1' , char_key);
}

void compress(string input_file_path , string output_file_path){
    ifstream file_in;
    file_in.open(input_file_path);

    string content;

    while(!file_in.eof()){
        string temp;
       getline(file_in , temp);

       content += temp;
       content += ' ';
    }
    
   // cout << content << endl;
    vector<pair<int , char>> freq = frequencyDect(content);

    HuffTree *root = makeTree(freq);
    
    unordered_map<char , string> char_key;
    get_values(root , "" , char_key);
    
   ofstream file_out;
   file_out.open(output_file_path);

   for(auto x : content)
   file_out << char_key[x];

   cout << "compressed sucessfully" << endl;

}



int main(){
    cout << "welcome" << endl;

    cout << "enter one of the following codes";

    cout << " press 1 -> for compressing the file" << endl;
    cout << "press 2  -> for decompressing the file" << endl;

    int input;

    cin >> input;

    if(input == 1){
        cout << "enter the file path for compression" << endl;
        string input_file_path;
        cin >> input_file_path;

        cout << "enter the destination file path" << endl;
        string destination_file_path;
        cin >> destination_file_path;

        compress(input_file_path , destination_file_path);
    }
}