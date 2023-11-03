/* Implementation of Recursive-Descent Parser
 * parserInt.cpp
 * Programming Assignment 3
 * Spring 2023
*/

#include "parserInt.h"

map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; //Container of temporary locations of Value objects for results of expressions, variables values and constants 
queue <Value> * ValQue; //declare a pointer variable to a queue of Value objects

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line # " << line << ": " << msg << endl;
}

bool IdentList(istream& in, int& line);


//Program is: Prog ::= StmtList
bool Prog(istream& in, int& line)
{
	bool f1;
	LexItem tok = Parser::GetNextToken(in, line);
	
	if(tok.GetToken() == DONE && tok.GetLinenum() <= 1){
		ParseError(line, "Empty File");
		return true;
	}
	Parser::PushBackToken(tok);
	f1 = StmtList(in, line); 
			
	if(!f1) 
	{
		ParseError(line, "Missing Program");
		return false;
	}
	else 
		return true;
}//End of Prog

//StmtList ::= Stmt; { Stmt; }
bool StmtList(istream& in, int& line){
	bool status;
		
	LexItem tok;
	
	status = Stmt(in, line);
	while(status)
	{
		tok = Parser::GetNextToken(in, line);
		if(tok == DONE)
		{
            cout << endl;
            cout << "(" << "DONE" << ")" << endl;
			Parser::PushBackToken(tok);
			return true;
		}
		else if(tok == RBRACES)
		{
			Parser::PushBackToken(tok);
			return true;
		}
		
		if(tok != SEMICOL)
		{
			ParseError(line, "Missing semicolon at end of Statement.");
			return false;
		}
		
		status = Stmt(in, line);
		
	}
			
	tok = Parser::GetNextToken(in, line);
	if(tok == ELSE )
	{
		ParseError(line, "Missing right brace.");
		return false;
	}
	else if(tok == RBRACES)
	{
		Parser::PushBackToken(tok);
		return false;
	}
	
	else 
	{
		ParseError(line, "Syntactic error in Program Body.");
		return false;
	}
	
}//End of StmtList function

//Stmt ::= AssignStme | WriteLnStmt | IfStmt  
bool Stmt(istream& in, int& line){
	bool status=false;
	
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {
	case SIDENT: case NIDENT: 
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		if(!status)
		{
			ParseError(line, "Incorrect Assignment Statement.");
			return status;
		}
		break;
	case WRITELN:
		
		status = WritelnStmt(in, line);
		
		if(!status)
		{
			ParseError(line, "Incorrect Writeln Statement.");
			return status;
		}
		break;
	case IF:  
		status = IfStmt(in, line);
		
		if(!status)
		{
			ParseError(line, "Incorrect If-Statement.");
			return status;
		}
		break;
	case ELSE:
		Parser::PushBackToken(t);
		return false;
		break;
	case IDENT:
		ParseError(line, "Invalid variable name");
	
		Parser::PushBackToken(t);
		return false;
		break;
	default:
		Parser::PushBackToken(t);
		return true;
	}
	return status;
}//End of Stmt function

//WritelnStmt:= WRITELN (ExpreList) 
bool WritelnStmt(istream& in, int& line) {
	LexItem t;
	ValQue = new queue<Value>;
		
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression list after Print");
		while(!(*ValQue).empty())
		{
			ValQue->pop();		
		}
		delete ValQue;
		return false;
	}
	
	//Evaluate: writeln by printing out the list of expressions' values
	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	return true;
}//End of WritelnStmt

//IfStmt:= IF (Expr) '{' StmtList '}' [ Else '{' StmtList '}' ] 
bool IfStmt(istream& in, int& line) {
	bool ex = false, status ; 
	LexItem t;
    
    Value retVal;
	
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis of If condition");
		return false;
	}
	
	ex = Expr(in, line, retVal);
	if( !ex ) {
		ParseError(line, "Missing if statement Logic Expression");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis of If condition");
		return false;
	}
	
    if(retVal.GetType() != VBOOL)
    {
        ParseError(line, "If Statement Expression is not of type boolean");
        return false;
    }

	t = Parser::GetNextToken(in, line);
	if(t != LBRACES)
	{
		ParseError(line, "If Statement Syntax Error: Missing left brace");
		return false;
	}

    if(retVal.GetBool())
    {
        status = StmtList(in, line);
	    if(!status)
	    {
            ParseError(line, "Missing Statement for If-Stmt Clause");
            return false;
        }
        t = Parser::GetNextToken(in, line);
        if( t != RBRACES)
        {
            ParseError(line, "If Statement Syntax Error: Missing right brace.");
            return false;
        }
        
        t = Parser::GetNextToken(in, line);
	    if( t == ELSE ) {
            t = Parser::GetNextToken(in, line);
            if(t != LBRACES)
            {
                ParseError(line, "If Statement Syntax Error: Missing left brace");
                return false;
            }
            while(t != RBRACES)
            {
                t = Parser::GetNextToken(in, line);
            }
        }
        else
        {
            Parser::PushBackToken(t);
        }
    }
    else
    {
        while(t != RBRACES)
        {
            t = Parser::GetNextToken(in, line);
        }

        t = Parser::GetNextToken(in, line);
		if( t == ELSE ) {
			t = Parser::GetNextToken(in, line);
			if(t != LBRACES) {
				ParseError(line, "If Statement Syntax Error: Missing left brace");
				return false;
			}
			status = StmtList(in, line);
			if(!status) {
				ParseError(line, "Missing Statement for Else-Clause");
				return false;
			}
			t = Parser::GetNextToken(in, line);
			if( t != RBRACES) {
				ParseError(line, "If Statement Syntax Error: Missing right brace.");
				return false;
			}
		}
		else {
			Parser::PushBackToken(t);
		}
    }

	return true;
}//End of IfStmt function

//AssignStmt:= Var = Expr
bool AssignStmt(istream& in, int& line) {
	bool varstatus = false, status = false;
	LexItem t;

    Value retVal;

	varstatus = Var(in, line, t);
	
	if (varstatus){
        
        string var = t.GetLexeme();
        Token type = t.GetToken();

        if(TempsResults.find(var) == TempsResults.end())
        {
            TempsResults[var] = retVal;
        }
        
		t = Parser::GetNextToken(in, line);
		
		if (t == ASSOP){
			status = Expr(in, line, retVal);
			
			if(!status) {
				ParseError(line, "Missing Expression in Assignment Statement");
				return status;
			}

            if(type == NIDENT && (retVal.GetType() == VINT || retVal.GetType() == VREAL))
            {
                TempsResults[var] = retVal;
            }
            else if(type == SIDENT && retVal.GetType() == VSTRING)
            {
                TempsResults[var] = retVal;
            }
            else if(type == SIDENT && (retVal.GetType() == VINT || retVal.GetType() == VREAL))
            {
                TempsResults[var] = retVal;
            }
            else
            {
                ParseError(line, "Invalid assignment statement conversion of a string value to a double variable.");
                return false;
            }
			
		}
		else if(t.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << t.GetLexeme() << ")" << endl;
			return false;
		}
		else {
			ParseError(line, "Missing Assignment Operator");
			return false;
		}
	}
	else {
		ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
		return false;
	}
	return status;	
}//End of AssignStmt

//Var ::= NIDENT | SIDENT
bool Var(istream& in, int& line, LexItem & idtok)
{
	string identstr;
	
	idtok = Parser::GetNextToken(in, line);
	
	if (idtok == NIDENT || idtok == SIDENT){
		identstr = idtok.GetLexeme();
		
		if (!(defVar.find(identstr)->second))
		{
			defVar[identstr] = true;
			SymTable[identstr] = idtok.GetToken();
		}	
		return true;
	}
	else if(idtok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		
		return false;
	}
	
	return false;
}//End of Var

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	Value retVal;
	
	status = Expr(in, line, retVal);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	ValQue->push(retVal);
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		status = ExprList(in, line);
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}//End of ExprList

//Expr ::= EqualExpr ::= RelExpr [(-EQ|==) RelExpr ]
bool Expr(istream& in, int& line, Value & retVal) {
	LexItem tok;
	bool t1 = RelExpr(in, line, retVal);
	
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if ( tok == NEQ || tok == SEQ ) 
	{
        Value lhs = retVal;
		t1 = RelExpr(in, line, retVal);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
        if(tok == NEQ)
        {
            retVal = lhs == retVal;
        }
        else if(tok == SEQ)
        {
            retVal = lhs.SEqual(retVal);
        }
        
        if(retVal.GetType() == VERR)
        {
            ParseError(line, "Illegal operand type for the operation. (expr)");
            return false;
        }
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Expr/EqualExpr

//RelExpr ::= AddExpr [ ( -LT | -GT | < | > )  AddExpr ]
bool RelExpr(istream& in, int& line, Value & retVal) {
	LexItem tok;
	bool t1 = AddExpr(in, line, retVal);
		
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}

	if ( tok == NGTHAN || tok == NLTHAN || tok == SGTHAN || tok == SLTHAN ) 
	{
        Value lhs = retVal;
		t1 = AddExpr(in, line, retVal);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

        if(tok == NGTHAN)
        {
            retVal = lhs > retVal;
        }
        else if(tok == NLTHAN)
        {
            retVal = lhs < retVal;
        }
        else if(tok == SGTHAN)
        {
            retVal = lhs.SGthan(retVal);
        }
        else if(tok == SLTHAN)
        {
            retVal = lhs.SLthan(retVal);
        }
        
        if(retVal.GetType() == VERR)
        {
            ParseError(line, "Illegal operand type for the operation. (relexpr)");
            return false;
        }
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of RelExpr

//AddExpr :: MultExpr { ( + | - | .) MultExpr }
bool AddExpr(istream& in, int& line, Value & retVal) {
	
	bool t1 = MultExpr(in, line, retVal);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}

	while (tok == PLUS || tok == MINUS || tok == CAT) 
	{
        Value lhs = retVal;
		t1 = MultExpr(in, line, retVal);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

        if(tok == PLUS)
        {
            retVal = lhs + retVal;
        }
        else if(tok == MINUS)
        {
            retVal = lhs - retVal;
        }
        else if(tok == CAT)
        {
            retVal = lhs.Catenate(retVal);
        }
        
        if(retVal.GetType() == VERR)
        {
            ParseError(line, "Illegal operand type for the operation. (add)");
            return false;
        }
		
		tok = Parser::GetNextToken(in, line);
        
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of AddExpr

//MultExpr ::= ExponExpr { ( * | / | **) ExponExpr }
bool MultExpr(istream& in, int& line, Value & retVal) {
	
	bool t1 = ExponExpr(in, line, retVal);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	
	tok	= Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
	}

	while ( tok == MULT || tok == DIV  || tok == SREPEAT)
	{
        Value lhs = retVal;
		t1 = ExponExpr(in, line, retVal);

		if( !t1 ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}

        if(tok == MULT)
        {
            retVal = lhs * retVal;
        }
        else if(tok == DIV)
        {
            retVal = lhs / retVal;
        }
        else if(tok == SREPEAT)
        {   
            retVal = lhs.Repeat(retVal);
        }
        
        if(retVal.GetType() == VERR)
        {
            ParseError(line, "Illegal operand type for the operation. (mult)");
            return false;
        }
		
		tok	= Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of MultExpr

//ExponExpr ::= UnaryExpr { ^ UnaryExpr }
//enforcing right associativity using right recursiveness
bool ExponExpr(istream& in, int& line, Value & retVal)
{
	bool status;
		
	status = UnaryExpr(in, line, retVal);
	if( !status ) {
		return false;
	}
	LexItem tok = Parser::GetNextToken(in, line);

    if(tok.GetToken() == ERR)
    {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
    }
	while (tok == EXPONENT)
	{
        Value lhs = retVal;
		status = ExponExpr(in, line, retVal);
		if( !status ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
        
		retVal = lhs^retVal;

        if(retVal.GetType() == VERR)
        {
            ParseError(line, "Illegal operand type for the operation. (expon)");
            return false;
        }

		tok	= Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of ExponExpr

//UnaryExpr ::= ( - | + ) PrimaryExpr | PrimaryExpr
bool UnaryExpr(istream& in, int& line, Value & retVal)
{
	LexItem t = Parser::GetNextToken(in, line);
	bool status;
	int sign = 0;
	if(t == MINUS)
	{
		sign = -1;
	}
	else if(t == PLUS)
	{
		sign = 1;
	}
	else
		Parser::PushBackToken(t);
		
	status = PrimaryExpr(in, line, sign, retVal);
	return status;
}//End of UnaryExpr


//PrimaryExpr ::= IDENT | NIDENT | SIDENT | ICONST | RCONST | SCONST | ( Expr )
bool PrimaryExpr(istream& in, int& line, int sign, Value & retVal) {
	LexItem tok = Parser::GetNextToken(in, line);
	string lexeme = tok.GetLexeme();

	if( tok == NIDENT || tok == SIDENT) {
		
		if (!(defVar.find(lexeme)->second))
		{
			ParseError(line, "Using Undefined Variable");
			return false;	
		}

        if (TempsResults.find(lexeme) == TempsResults.end()) 
        {
            ParseError(line, "Undefined Variable");
            return false;
        }
        
        if(tok == NIDENT)
        {
            retVal = TempsResults[lexeme];
            if(sign == -1)
            {
                retVal = retVal * -1;
            }
        }
        else if(tok == SIDENT)
        {
            retVal = TempsResults[lexeme];
        }

		return true;
	}
	else if( tok == ICONST ) {

        if(lexeme.back() == '.')
        {
            retVal.SetType(VINT);
            int val = stoi(lexeme);
            if(sign == -1)
            {
                val *= sign;
            }
            retVal.SetInt(val);
        }
        else
        {
            retVal.SetType(VREAL);
            double val = stod(lexeme);
            if(sign == -1)
            {
                val *= -1;
            }
            retVal.SetReal(val);
        }

		return true;
	}
	else if( tok == SCONST ) {
        retVal.SetType(VSTRING);
        if(sign != 0)
        {
            ParseError(line, "Illegal Operand Type for Sign Operator (primary)");
            return false;
        }
        retVal.SetString(lexeme);
		return true;
	}
	else if( tok == RCONST ) {

        if(lexeme.back() == '.')
        {
            retVal.SetType(VINT);
            int val = stoi(lexeme);
            if(sign == -1)
            {
                val *= sign;
            }
            retVal.SetInt(val);
        }
        else
        {
            retVal.SetType(VREAL);
		    double val = stod(lexeme);
            if(sign == -1)
            {
                val *= -1;
            }
            retVal.SetReal(val);
        }
		return true;
	}
	else if( tok == LPAREN ) {
		bool ex = Expr(in, line, retVal);
		if( !ex ) {
			ParseError(line, "Missing expression after Left Parenthesis");
			return false;
		}
		if( Parser::GetNextToken(in, line) == RPAREN )
			return ex;
		else 
		{
			Parser::PushBackToken(tok);
			ParseError(line, "Missing right Parenthesis after expression");
			return false;
		}
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}

	return false;
}

