// Do NOT add any other includes
#include "search.h"

// will use three hash functions annd check if all values are same

unsigned long hash4(const unsigned char *word) {
    unsigned long hash = 17;
    int c;

    while (c = *word++) {
        hash = (hash * 101) + c; 
    }

    return hash;
}

unsigned long hash2(const unsigned char *word) {
    unsigned long hash = 0;
    int c;

    while (c = *word++) {
        hash = c + (hash << 7) - (hash >> 3); 
    }

    return hash;
}

unsigned long hash3(const unsigned char *word) {
    unsigned long hash = 0;
    int c;

    while ((c = *word++)) {
        hash = (hash * 31) - (hash >> 5) + c; 
    }

    return hash;
}

unsigned long hash1(const unsigned char *word) {
    unsigned long hash = 5381; 
    int c;

    while ((c = *word++)) {
        hash = ((hash * 32) + hash) ^ c;
    }

    return hash;
}

SearchEngine::SearchEngine(){
    // Implement your function here 
    sentences = {}; 
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    Sentence temp;
    temp.book_code = book_code;
    temp.page = page;
    temp.paragraph = paragraph;
    temp.sentence_no = sentence_no;
    for (char &c : sentence) {
        c = tolower(c);
    }
    temp.s = sentence;
    sentences.push_back(temp);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here  
    // have to look out for pattern in the entire doc, i.e. the vector
    // as the patterns wont span the sentence boundary
    int i = 0;
    Node* head = nullptr;
    Node* current = nullptr;
    while(i<sentences.size()){
        if(sentences[i].s.length()>=pattern.length()){
            for(int j = 0; j<sentences[i].s.length()-pattern.length()+1; j++){
                //cout<<j<<" j"<<endl;
                //cout<<pattern.length()<<" patt len"<<endl;
                //cout<<j<<" j"<<pattern.length()+j-1<<" patt"<<endl;
                string str = sentences[i].s.substr(j, pattern.length());
                //cout<<str<<" str"<<endl;
                if (
                    hash1(reinterpret_cast<const unsigned char*>(pattern.c_str())) == hash1(reinterpret_cast<const unsigned char*>(str.c_str())) &&
                    hash2(reinterpret_cast<const unsigned char*>(pattern.c_str())) == hash2(reinterpret_cast<const unsigned char*>(str.c_str())) &&
                    hash3(reinterpret_cast<const unsigned char*>(pattern.c_str())) == hash3(reinterpret_cast<const unsigned char*>(str.c_str())) &&
                    hash4(reinterpret_cast<const unsigned char*>(pattern.c_str())) == hash4(reinterpret_cast<const unsigned char*>(str.c_str()))
                ){  
                    n_matches++;
                    Node* node = new Node(sentences[i].book_code, sentences[i].page, sentences[i].paragraph, sentences[i].sentence_no, j);
                    // j is the offset
                    if(n_matches == 1){
                        // first node
                        //cout<<"lessgo"<<endl;
                        head = node;
                        current = head;
                    }
                    else{
                        current->right = node;
                        node->left = current;
                        current = node;
                    }
                }
            }
        }
        i++;
    }
    return head;
}
// int main(){
//     SearchEngine eng;
//     eng.insert_sentence(1,1,1,1, "i am tanya fro jaipur i am");
//     eng.insert_sentence(1,1,1,2, "i am tanya fro jaipu");
//     //for(int i = 0; i<eng.sentences.size(); i++) cout<<eng.sentences[i].s<<" ";
//     //cout<<endl;
//     int n = 0;
//     Node* node = eng.search("i", n);
//     cout<<n<<" number"<<endl;
//     cout<<node->right->offset<<endl;
//     return 0;
// }
