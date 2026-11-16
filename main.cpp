#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;
struct Book{int id;string title,author;bool issued=false;int memberId=0;};
struct Member{int id;string name;};
class Library{
 vector<Book> books;vector<Member> members;
 int number(const string&s){int x;while(cout<<s&&!(cin>>x)){cout<<"Enter a valid number.\n";cin.clear();cin.ignore(10000,'\n');}cin.ignore(10000,'\n');return x;}
 Book* book(int id){for(auto&b:books)if(b.id==id)return &b;return nullptr;}
 Member* member(int id){for(auto&m:members)if(m.id==id)return &m;return nullptr;}
 void load(){ifstream f("books.txt");Book b;while(f>>b.id>>quoted(b.title)>>quoted(b.author)>>b.issued>>b.memberId)books.push_back(b);ifstream m("members.txt");Member x;while(m>>x.id>>quoted(x.name))members.push_back(x);}
 bool saveBooks(){ofstream f("books.txt");if(!f)return false;for(auto&b:books)f<<b.id<<' '<<quoted(b.title)<<' '<<quoted(b.author)<<' '<<b.issued<<' '<<b.memberId<<'\n';return bool(f);}
 bool saveMembers(){ofstream f("members.txt");if(!f)return false;for(auto&m:members)f<<m.id<<' '<<quoted(m.name)<<'\n';return bool(f);}
public:
 Library(){load();}
 void addBook(){int id=number("Book ID: ");if(id<=0||book(id)){cout<<"Invalid/duplicate ID.\n";return;}Book b;b.id=id;cout<<"Title: ";getline(cin,b.title);cout<<"Author: ";getline(cin,b.author);if(b.title.empty()||b.author.empty()){cout<<"Both fields required.\n";return;}books.push_back(b);cout<<(saveBooks()?"Book added.\n":"Save failed.\n");}
 void addMember(){int id=number("Member ID: ");if(id<=0||member(id)){cout<<"Invalid/duplicate ID.\n";return;}Member m;m.id=id;cout<<"Member name: ";getline(cin,m.name);if(m.name.empty()){cout<<"Name required.\n";return;}members.push_back(m);cout<<(saveMembers()?"Member added.\n":"Save failed.\n");}
 void search(){string q;cout<<"Title/author keyword: ";getline(cin,q);transform(q.begin(),q.end(),q.begin(),::tolower);bool found=false;for(auto&b:books){string s=b.title+" "+b.author;transform(s.begin(),s.end(),s.begin(),::tolower);if(s.find(q)!=string::npos){cout<<b.id<<" | "<<b.title<<" | "<<b.author<<" | "<<(b.issued?"Issued":"Available")<<'\n';found=true;}}if(!found)cout<<"No matching books.\n";}
 void issue(){int id=number("Book ID: ");auto*b=book(id);if(!b){cout<<"Book not found.\n";return;}if(b->issued){cout<<"Already issued.\n";return;}int mid=number("Member ID: ");if(!member(mid)){cout<<"Member not found.\n";return;}b->issued=true;b->memberId=mid;cout<<(saveBooks()?"Book issued.\n":"Save failed.\n");}
 void giveBack(){int id=number("Book ID: ");auto*b=book(id);if(!b){cout<<"Book not found.\n";return;}if(!b->issued){cout<<"Book is not issued.\n";return;}b->issued=false;b->memberId=0;cout<<(saveBooks()?"Book returned.\n":"Save failed.\n");}
 void list(){if(books.empty())cout<<"No books.\n";for(auto&b:books)cout<<b.id<<" | "<<b.title<<" | "<<b.author<<" | "<<(b.issued?"Issued":"Available")<<'\n';}
 void run(){int c;do{cout<<"\n=== LIBRARY MANAGEMENT ===\n1.Add book\n2.Register member\n3.Search title/author\n4.Issue book\n5.Return book\n6.List books\n0.Exit\n";c=number("Choice: ");switch(c){case 1:addBook();break;case 2:addMember();break;case 3:search();break;case 4:issue();break;case 5:giveBack();break;case 6:list();break;case 0:cout<<"Goodbye.\n";break;default:cout<<"Invalid choice.\n";}}while(c!=0);}
};
int main(){Library l;l.run();}
