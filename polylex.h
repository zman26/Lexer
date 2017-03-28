/*
 * polylex.h
 *
 *  Created on: Feb 20, 2017
 *      Author: gerardryan
 */

#ifndef POLYLEX_H_
#define POLYLEX_H_

#include <istream>
#include <string>

extern int	currentLine;	// in ONE PLACE in your program, you must have the following line:
							// int currentLine = 0;
							// each time you see a '\n', add one to currentLine

enum TokenTypes {
	ID,
	ICONST,
	FCONST,
	STRING,
	PRINT,
	SET,
	PLUS,
	MINUS,
	STAR,
	COMMA,
	LBR,
	RBR,
	LSQ,
	RSQ,
	LPAREN,
	RPAREN,
	SC,
	ERR,
	DONE
};

class Token {
private:
	TokenTypes	t;
	std::string	lexeme = "";
	int			line = 0;

public:
	Token()
	{
		this->t = ERR;
		this->lexeme = "";
		this->line = 0;
	}
	Token(TokenTypes t, std::string lexeme, int currentLine) {
		this->t = t;
		this->lexeme = lexeme;
		this->line = currentLine;
	}

 void setLexeme (std:: string lex)
 {this ->lexeme = lex;}
 void setTokenTypes (TokenTypes tok)
 {this ->t = tok;}
 void setLine(int currentLine)
 {this ->line = currentLine;}
	TokenTypes getType() const { return t; }
	std::string getLexeme() const { return lexeme; }
	int getLine() const { return line; }

	bool operator==(const TokenTypes& tt) { return t == tt; }
	bool operator!=(const TokenTypes& tt) { return t != tt; }
};

extern Token getToken(std::istream& source);



#endif /* POLYLEX_H_ */
