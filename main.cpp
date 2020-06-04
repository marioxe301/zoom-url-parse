#include <regex>
#include <iostream>
#include <vector>

using namespace std;

auto tokenize_url(string url)->vector<string>{

    //lista de los tokens;
    vector<string>tokens;
    regex url_format("(https://){0,1}([aA0-zZ9]+).zoom.us/j/");
    regex id_format("([0-9])+[?]{1}");
    regex pass_format("pwd=([aA0-zZ9]+)");


    auto begin = sregex_iterator(url.begin(),url.end(),url_format);
    auto final = sregex_iterator();

    for(sregex_iterator i= begin; i!= final;++i){
        tokens.push_back((*i).str());
    }

    begin = sregex_iterator(url.begin(),url.end(),id_format);
    final = sregex_iterator();
    for(sregex_iterator i= begin; i!= final;++i){
        tokens.push_back((*i).str());
    }

    begin = sregex_iterator(url.begin(),url.end(),pass_format);
    final = sregex_iterator();
    for(sregex_iterator i= begin; i!= final;++i){
        tokens.push_back((*i).str());
    }

    return tokens;
}

auto print_credentials(vector<string>v)->void{
    auto max = v[1].find('?');
    string id = v[1].substr(0,max);
    string domain = v[0];
    string pass = v[2].substr(4);

    cout<<endl;
    cout<<"Domain: "<< domain<<endl;
    cout<<"ID: "<<id<<endl;
    cout<<"Password: "<<pass<<endl;
    cout<<endl;
}

int main(int argc, char **argv){

    if(argc == 2){
        try{
            print_credentials(tokenize_url(argv[1]));
        }
        catch(const exception& e){
            cerr << "Un error ha ocurrido" << endl;
        }
        
    }else{
        cerr<<"Porfavor ingrese una url"<<endl;
    }
    
    return 0;
}