#include<bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);
#define endl '\n'
#define pi acos(-1.0)
#define all(a) a.begin() , a.end()
typedef unsigned long long int ull;
typedef long long int ll;
using namespace std;



//debugger template
#define error(args...) { string _s = #args; replace(_s.begin() , _s.end() , ',',' ') ; stringstream _ss(_s) ; istream_iterator<string> _it(_ss) ; err(_it , args) ; }

void err(istream_iterator<string> it) {}
template<typename T , typename... Args>
void err(istream_iterator<string> it , T a , Args... args){
	cerr << *it << " = " << a << endl;
	err(++it , args...);
}


vector<int>books;
int id = 0;

class lib{
    public :
        int ID = 0;
        int total_score = 0;
        int books_in_lib = 0;
        int signup_time = 0;
        int books_per_day = 0;
        vector<int>book_list;
        void input(){
            cin >> books_in_lib >> signup_time >> books_per_day ;
            book_list.resize(books_in_lib);
            for(int i = 0 ;i < books_in_lib ; i++){
                cin >> book_list[i];
                total_score += books[book_list[i]];
            }
            ID = id;
            id++;
        }
        void print(){
            cout << books_in_lib << " " << signup_time << " " << books_per_day << endl;
            for(auto i : book_list){
                cout << i << " ";
            }
            cout << endl;
        }
};

int no_books = 0;
int no_lib = 0;
int no_days = 0;

vector<lib>libs;

void take_input(){
    cin >> no_books >> no_lib >> no_days ;
    books.resize(no_books);
    for(int i  =0 ;i < no_books ; i++){
        cin >> books[i];
    }

    libs.resize(no_lib);
    
    for(int i  =0 ;i  < no_lib ;i ++){
        libs[i].input();
    }
}


bool sort_as_score(lib a , lib b){
    return a.total_score >= b.total_score;    
}

bool sort_as_signup(lib a , lib b){
    return a.signup_time < b.signup_time;
}

bool sort_as_no_books(lib a , lib b){
    return a.books_in_lib > b.books_in_lib;
}

bool sort_as_books_rate(lib a , lib b){
    return a.books_per_day > b.books_per_day;
}

bool custom_sort(lib a , lib b){
    double first = (double)a.total_score / a.signup_time;
    double second =(double)b.total_score / b.signup_time;
    return first > second;
}


class ans{
    public : 
        int lib_num = 0;
        int no_books = 0;
        vector<int>order;
};

int main(){
    take_input();


    sort(libs.begin() , libs.end() , custom_sort);

    // for(auto i : libs){
    //     i.print();
    // }
    
    map<int , bool>visited;
    int final_score =0 ;
    int time = 0;
    int count_of_libs = 0;

    vector<ans>output;

    for(int i = 0 ;i  < no_lib ; i++){
        if(time + libs[i].signup_time <= no_days){
            time += libs[i].signup_time;
            count_of_libs ++;
            vector<pair<int , int>> unique_books;
            for(auto j : libs[i].book_list){
                if(!visited[j]){
                    unique_books.emplace_back(make_pair(books[j] , j));
                    // final_score += books[i];
                }
            }            
            sort(unique_books.begin() , unique_books.end());
            reverse(unique_books.begin() , unique_books.end());
            int remaining_days = no_days - time;
            int books_sent = remaining_days * libs[i].books_per_day;
            books_sent = min(books_sent , (int)unique_books.size());

            // ans uploding
            ans temp;
            temp.lib_num = libs[i].ID;
            temp.no_books = (int)unique_books.size();
            for(auto j : unique_books){
                visited[j.second] = true;
                final_score += j.first;
                temp.order.emplace_back(j.second);
            }
            output.emplace_back(temp);

        }
        else{
            break;
        }
    }



    for(auto i : output){
        if(i.no_books == 0){
            count_of_libs --;
        }
    }

    cout << count_of_libs << endl;

    for(auto i : output){
        if(i.no_books == 0){
            continue;
        }
        cout << i.lib_num << " " << i.no_books << endl;
        for(auto j : i.order){
            cout << j << " ";
        }
        cout << endl;
    }

    cerr << "final score : " << final_score << endl;

    return 0;
}