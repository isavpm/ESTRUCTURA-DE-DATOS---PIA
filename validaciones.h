#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <regex>

using namespace std;

bool validarMatricula(const string& matricula)
{
    regex pattern("^\\d{7}$");
    return regex_match(matricula, pattern);
}

bool validarNombre(const string& str)
{
    // This version only allows single space between names
    regex pattern("^[A-Za-z]+ [A-Za-z]+$");
    
    return regex_match(str, pattern);
}

bool validarDireccion(const string & str)
{
	regex pattern("^[A-Za-z0-9 ]+$");
	return regex_match(str, pattern);
	
}
bool validarTelefono(const string& str)
{
    regex pattern("^\\d{10}$");
    return regex_match(str, pattern);
}

