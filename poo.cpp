#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#define SUCCESS 0

using namespace std;

//implemented to recursively randomize hash before compiling
string randomizeString(string inputString){
    srand((unsigned) time(0));
    string randomIs;
    for(int i = 0; i < inputString.size(); i++){
      int randomIndex = rand() % inputString.size();
      char randomChar = inputString[randomIndex];
      randomIs += randomChar;
    };
    return randomIs;
};

//generate random hash with user predef length
string createMockHash(int hashLength){
  srand((unsigned) time(0));
  string availableChars = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int stringSize = availableChars.size();
  string mockToken;
  while(mockToken.size() < hashLength){
      char randomCharacter = availableChars[rand() % stringSize];
      mockToken += randomCharacter;
  };
  return mockToken;
};

class Transaction{
public:
    string from;
    string to;
    double amount;

    Transaction(string _from,string _to, double _amount){
        this->from = _from;
        this->to = _to;
        this->amount = _amount;
    };
    ~Transaction(){};

    string getTransaction(){
        stringstream sData;
        sData << "From: " << from << "\n"
            << "To: " << to << "\n"
            << "Amount: " << amount << "\n";
        return sData.str();
    };
};

class Block{
public:
    string hash;
    string previousHash;
    vector<Transaction> transactions;
    int nonce;

    //constructor calling constructor
    Block(){};
    Block(string _hash = "placeholder00",string _previousHash = "placeholder01",int _nonce = 0){
        (*this).hash = _hash;
        (*this).previousHash = _previousHash;
        (*this).nonce = _nonce;
    };
    //destructor
    ~Block(){};

    //string stream concat
    string getFullBlockData(){
        stringstream block;
        block << "{\n "
              << "hash: "<< hash << ",\n "
              << "previousHash: " << previousHash << ",\n "
              << "from: " << transactions[0].from << ",\n "
              << "to: "   << transactions[0].to << ",\n "
              << "amount: " << transactions[0].amount << ",\n "
              << "nonce: " << nonce << "\n"
              << "}";
        return block.str();
    };

    void insertTransaction(Transaction t){
        (*this).transactions.push_back(t);
    };
};

class Blockchain{
public:
    vector<Block> blocks;

    Blockchain(){};
    ~Blockchain(){};

    vector<Block> insertNewBlock(Block b){
        if(checkBlockchainLength() > 0){
            (*this).blocks.push_back(b);
        }else{
            b.previousHash = "";
            (*this).blocks.push_back(b);
        };
    };

    int checkBlockchainLength(){
        return this->blocks.size();
    };

    string getFullBlockchain(){
      stringstream blockchainData;
        blockchainData << "Blockchain" << "\n"
                       << "{\n"
                       << "  Blocks: " << "\n"
                       << "    [\n"
                       << "\t{\n"
                       << "\t  previousHash: " << this->blocks[0].previousHash << ",\n"
                       << "\t  hash: " << this->blocks[0].hash << ",\n"
                       << "\t  from: " << this->blocks[0].transactions[0].from << ",\n"
                       << "\t  to: " << this->blocks[0].transactions[0].to << ",\n"
                       << "\t  amount: " << this->blocks[0].transactions[0].amount << "\n"
                       << "\t}\n"
                       << "    ]\n"
                       << "}";
      return blockchainData.str();
    };
};

int main(int argc, char* argv[]){

Transaction credit("Adriano","Arthur",1200);
Transaction credit3("John","Yanna",25000);

Block one(createMockHash(50),randomizeString(createMockHash(64)));
one.insertTransaction(credit);
Block two(createMockHash(50),randomizeString(createMockHash(64)));

Blockchain newChain;
newChain.insertNewBlock(one);

cout << newChain.getFullBlockchain() << endl;

#ifdef SUCCESS
    return SUCCESS;
#else
    return 1;
#endif
};
