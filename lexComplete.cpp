#include <fstream>
#include <iostream>
#include <string>
#include "polylex.h"
#include <map>
#include <istream>
using namespace std;


void checkErr(string file_or_command)
{

//bool y=false;
if (file_or_command[0] == '-')
        {
	     if (file_or_command.compare("-v") && file_or_command.compare("-stats") && file_or_command.compare("-sum"))
		{cerr << "Invalid argument " << file_or_command << endl; exit(1);}
	}
else
	{
		ifstream File(file_or_command);
		if (!File.is_open())
		{cout << "Could not open "<< file_or_command << endl;
	 	exit(1);}
		 if(File.fail()) {
		 cerr << "Somethin' ain't right. SeeYa! (or try again if you want)" << endl;
			exit(1);}
	//		y = true; //it made it this far which means if there is a file, its good
			 }         //so, ideally, if i check to see if there are NO files, I can
				     //return y; //take from cin if indeed there are no files
}    				     // checking this by I'm guessing a loop of somekind
//return y;
Token getToken (istream& source)
{
  //cout << " made it to the gettoken function" << endl;
  bool tokenFound = false;
  char ch = 0;
  char c2 = 0;
  bool letter = false;
  bool number = false;
  bool comment = false;
  int strinG = 0;
  bool id = false;
  string eme = "";
  int lineCounter = 1;
  TokenTypes type = ERR;
//cout << "do" << endl;
  do

 {
  ch = source.peek();
  // cerr << "just peeked and found '"<<ch<<"'"<<endl;
  if (ch == '#')  //comment finder
  {
  //  lineCounter++;
    ch = source.get();
    eme = ch;
    ch = source.peek();
    for (;ch != '\n';)
    {
      ch = source.get();

      ch = source.peek(); // end of comment finder
      if(ch == EOF)
      {
        lineCounter ++;
        tokenFound = true;
        type = DONE;
        break;
      }
    }

    //continue;
  }

  for (;ch == '\n';)   //line counter
  {  ch = source.get();
    ch = source.peek();
   lineCounter ++;

   //continue;
  }
  if (ch == '#')  //comment finder
  {
 comment = true;
    lineCounter++;
    ch = source.get();
    eme = ch;
    ch = source.peek();
    for (;ch != '\n';)
    {
      ch = source.get();

      if(ch == EOF)
      {
        tokenFound = true;
        type = DONE;
        break;
      }
      //ch = source.peek(); // end of comment finder
    }

    //continue;
  }

//------------------------------------STRING FINDER ATTEMPT 2-----------------

//STRING FINDER START
if (ch == '\"')
{
  ch = source.get();
  eme = ch;
  ch = source.peek();
  for (;ch != '\"';)
  {
    ch = source.get();
    if (ch == '\n')
      {
        tokenFound = true;
        type = ERR;

        break;
      }        // next character is not a "
      //if (!isspace(ch))
    eme += ch;
  }
  if (!tokenFound)
  {
    tokenFound = true;
    type = STRING;
  }
  //if (ch == '"')
//  {
    //ch = source.get();
    //if (!isspace(ch))                  //character is the last "
  //  eme += ch;
  //  type = STRING;
//    tokenFound = true;
    //continue;
  //}

  if (tokenFound)
  break;
  //ch = source.peek();
  continue;
}
//-----------------------------end of string finder atttempt 2-------------

if (isalpha(ch))       //start of ID finder
{
  ch = source.get();
  eme = ch;
  ch = source.peek();
  for (;isalnum(ch);)
  {
    ch = source.get();
    eme += ch;
    ch = source.peek();
  }
  type = ID;
  tokenFound = true;  //end of ID finder
  continue;
}

if (isdigit(ch))      //start of ICONST or FCONST finder
{
  ch = source.get();
  eme = ch;
  ch = source.peek();
  for(;isdigit(ch);)
  {
    ch = source.get();
    eme += ch;
    ch = source.peek();
  }
  if (ch != '.')
  {
    tokenFound = true;
    type = ICONST;  //if this stuff happens it should be ICONST
  }
  else
  {
    ch = source.get();
    eme += ch;
    ch = source.peek();
    if (!isdigit(ch))
    {
      tokenFound = true;
      type = ERR;
      break;
    }
    for(;isdigit(ch);)
    {
      ch = source.get();
      eme += ch;    //if this stuff happens it should be a FCONST
      ch = source.peek();
    }
    tokenFound = true;
    type = FCONST;
  }
  break;
  continue;
}


  if (ch == '+')    //plus finder
  {
    ch = source.get();
    type = PLUS;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == '*')  //star finder
  {
    ch = source.get();
    type = STAR;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == ',') //comma finder
  {
    ch = source.get();
    type = COMMA;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == '{')  //bracket finder
  {
    ch = source.get();
    type = LBR;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == '}')  //bracket finder
  {
    ch = source.get();
    type = RBR;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == '[')   //square br finder
  {
    ch = source.get();
    type = LSQ;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == ']') //square br finder
  {
    ch = source.get();
    type = RSQ;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if ( ch == '(') //paren finder
  {
    ch = source.get();
    type = LPAREN;
    tokenFound = true;
    eme =  ch;
    //continue;
    break;
  }
  if (ch == ')')   //paren finder
  {
    ch = source.get();
    type = RPAREN;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == ';') //semi finder
  {
    ch = source.get();
    type = SC;
    tokenFound = true;
    eme = ch;
    //continue;
    break;
  }
  if (ch == '.')
  {
      tokenFound = true;
      type = ERR;
      eme = ch;
      /*
    ch = source.get();
    eme = ch;
    ch = source.peek();
    if (isdigit(ch))
    {
      for(;(isdigit(ch));)
      {
        ch = source.get();
        eme += ch;
        ch = source.peek();
      }
      tokenFound = true;
      type = FCONST;
      break;
    }
    else
    {
      tokenFound = true;
      type = ERR;
    }
      */
  }
  if (ch == '-')
  {
    ch = source.get();
    tokenFound = true;
    type = MINUS;
  }
  if (ch == EOF)   ///DONE
  {
    ch= source.get();
    eme = "DONE";
    type = DONE;
    tokenFound = true;
    continue;
  }
if (!tokenFound)
{
  if(!comment)
  {
    ch = source.get();
  }
}
comment = false;
} while (!tokenFound);
Token token(type, eme, lineCounter);
return token;
};

int main(int argc, char *argv[])
{
bool stats = false;
bool sum = false;
bool v = false;
int num_of_files=0;
string s = "";
int tokLineCount = 1;
int holder = 0;

for (int i=1; i<argc; i++)
{
  string cheks = argv[i];
checkErr(argv[i]);
if (argv[i][0] != '-')
{
  num_of_files++;
  s = argv[i];
}
if (cheks == "-v")
 {v = true;}

if (cheks == "-sum")
sum = true;
if (cheks == "-stats")
{stats = true;}
}
if (num_of_files > 1)
{
cout << "Too many file names" << endl;
exit (1);
}
int commentLines = 0;
if( !v && !sum && !stats)
{
/*
//-------------------------------------------------------------------------------
for (int i=1; i<argc; i++)
{
if (argv[i][0] == '-')
{continue;}
else
	{
	char ch;
	 ifstream file (argv[i]);
	 ch = file.get();
	 	if (ch == EOF)
		cout << "Total Lines: 0\nTotal tokens: 0" << endl;

		else
		{
		 string line;
		 commentLines=0;
		 while (getline(file, line)) //only until i understand lexemes n shit
			{
			 commentLines ++;
			}
			cout << "Total Lines: " << commentLines << "\nTotal tokens: 0" << endl;
		}
file.close();
	}
}
//------------------------------SAVEFORLATER-------------------------------------
*/
}

map <TokenTypes, string> typemap;
typemap[ID] = "ID";
typemap[ICONST] = "ICONST";
typemap[FCONST] = "FCONST";
typemap[STRING] = "STRING";
typemap[PRINT] = "PRINT";
typemap[SET] = "SET";
typemap[PLUS] = "PLUS";
typemap[MINUS] = "MINUS";
typemap[STAR] = "STAR";
typemap[COMMA] = "COMMA";
typemap[LBR] = "LBR";
typemap[RBR] = "RBR";
typemap[LSQ] = "LSQ";
typemap[RSQ] = "RSQ";
typemap[LPAREN] = "LPAREN";
typemap[RPAREN] = "RPAREN";
typemap[SC] = "SC";
typemap[ERR] = "ERR";
typemap[DONE] = "DONE";

  int tokenCounter[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int frequencyCount = 0;
if (num_of_files == 0) //should read from cin here
{
  Token t;
 map <string, int> IDList;     //for stats and sum
 int idLex = 0;
 int tokCountMINUSONE = -1;
 map <TokenTypes, int> tokCounter;

  while (t != DONE)
  {

    t = getToken(cin);

    holder = t.getLine();
    if (holder != 1)
    {

      tokLineCount += t.getLine()-1;
      t.setLine(tokLineCount);
    }
    else
    t.setLine(tokLineCount);


        if (t.getType() == ERR)
        {
          cout << "Error on line " << t.getLine() << " (" << t.getLexeme() << ")" << endl;
          break;
        }
        if (v == true)
        {
          if (t.getType() <= STRING)
          cout << typemap[t.getType()] << " (" << t.getLexeme() << ")" << endl;
          else
          {
            if( t != DONE)
            cout << typemap[t.getType()] << endl;
          }

        }

        if (t == ID)
        {

          IDList [t.getLexeme()] = idLex;
            idLex ++;
        }
        tokCountMINUSONE ++;
        tokCounter[t.getType()] ++;
      }
      if (stats && t != ERR)
      {
        cout << "Total IDs: " << idLex << endl;
        if (idLex != 0)
        {
          cout << "List of IDs: ";
        }
        for (std::map<string,int>::iterator it=IDList.begin(); it!=IDList.end(); ++it)
        {
          if (it!= --IDList.end())
          cout << it ->first << ", ";
          else
          cout << it -> first << endl;
        }
      }
      if(sum && t != ERR)
      {

    int highestFrequency=0;
    int freqthresh = 0;
        cout << "Total Lines: " << t.getLine()-1 << endl;
        cout << "Total tokens: " << tokCountMINUSONE << endl;
        if (tokCountMINUSONE != 0)
        cout << "Most frequently used tokens: ";
        for (std::map<TokenTypes,int>::iterator it=tokCounter.begin(); it!=tokCounter.end(); ++it)
        {
          if(it->second > highestFrequency)
          {highestFrequency = it ->second;}
        }
        for (std::map<TokenTypes,int>::iterator it=tokCounter.begin(); it!=tokCounter.end(); ++it)
        {
          if (it->second == highestFrequency)
          {frequencyCount++;}
        }
        for (std::map<TokenTypes,int>::iterator it=tokCounter.begin(); it!=tokCounter.end(); ++it)
        {
          if (it -> second == highestFrequency)
          {
            freqthresh++;
            if (frequencyCount != freqthresh)
            cout << typemap[it->first] << ", ";
            else
            if(it ->first != DONE)
            cout << typemap[it->first] << endl;
          }
        }
      }
/*
    if ( !v && !sum && !stats && t != ERR)
    {
      cout << "Total Lines: " << t.getLine()-1 << endl;
      cout << "Total tokens: " << tokCountMINUSONE << endl;
    }
*/
}
if (num_of_files == 1) //should read from file here
{
  ifstream file (s);
  Token t;
 map <string, int> IDList;     //for stats and sum
 int idLex = 0;
 int tokCountMINUSONE = -1;
 map <TokenTypes, int> tokCounter;

  while (t != DONE)
  {

t = getToken(file);

holder = t.getLine();
if (holder != 1)
{

  tokLineCount += t.getLine()-1;
  t.setLine(tokLineCount);
}
else
t.setLine(tokLineCount);


    if (t.getType() == ERR)
    {
      cout << "Error on line " << t.getLine() << " (" << t.getLexeme() << ")" << endl;
      break;
    }
    if (v == true)
    {
      if (t.getType() <= STRING)
      cout << typemap[t.getType()] << " (" << t.getLexeme() << ")" << endl;
      else
      {
        if( t != DONE)
        cout << typemap[t.getType()] << endl;
      }

    }

    if (t == ID)
    {
      idLex ++;
      if( IDList.find(t.getLexeme()) == IDList.end() )

      IDList [t.getLexeme()] = idLex;
    }
    tokCountMINUSONE ++;
    tokCounter[t.getType()] ++;
  }
  if (stats && t != ERR)
  {
    cout << "Total IDs: " << idLex << endl;
    if (idLex != 0)
    {
      cout << "List of IDs: ";
    }

      for (std::map<string,int>::iterator it=IDList.begin(); it!=IDList.end(); ++it)
      {
        if (it!= --IDList.end())
        cout << it ->first << ", ";
        else
        cout << it -> first << endl;


      }

  }
  if(sum && t != ERR)
  {

int highestFrequency=0;
int freqthresh = 0;
    cout << "Total Lines: " << t.getLine()-1 << endl;
    cout << "Total tokens: " << tokCountMINUSONE << endl;
    if (tokCountMINUSONE != 0)
    cout << "Most frequently used tokens: ";
    for (std::map<TokenTypes,int>::iterator it=tokCounter.begin(); it!=tokCounter.end(); ++it)
    {
      if(it->second > highestFrequency)
      {highestFrequency = it ->second;}
    }
    for (std::map<TokenTypes,int>::iterator it=tokCounter.begin(); it!=tokCounter.end(); ++it)
    {
      if (it->second == highestFrequency)
      {frequencyCount++;}
    }
    for (std::map<TokenTypes,int>::iterator it=tokCounter.begin(); it!=tokCounter.end(); ++it)
    {
      if (it -> second == highestFrequency)
      {
        freqthresh++;
        if (frequencyCount != freqthresh)
        cout << typemap[it->first] << ", ";
        else
        if (it ->first != DONE)
        cout << typemap[it->first] << endl;
      }
    }
  }
  /*
if ( !v && !sum && !stats && t != ERR)
{
  cout << "Total Lines: " << t.getLine()-1 << endl;
  cout << "Total tokens: " << tokCountMINUSONE << endl;
}
*/

}


exit (0);
}
