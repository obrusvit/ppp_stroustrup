#include <string>

//------------------------------------------------------------------------------
// Marks used in Tokens
const char number = '8'; //t.kind==number means t is a number Token
const char print = ';'; //t.kind==print means t is a print Token
const char quit = 'q'; //t.king==quit means t is quit Token
const char let = 'L'; //t.kind==let means t is 'let' keyword and name is expected
const char sqrt_c = 'S'; //t.kind==sqrt_c means t is 'sqrt' command
const char pow_c = 'P'; //t.kind==pow_c means t is 'pow' command
const char name = 'a'; //t.kind==name means Token is a name

//------------------------------------------------------------------------------
// Symbols used in UI
const std::string prompt = ">"; //string that indicates user prompt is awaited
const std::string result = "="; //string that indicates that result follows

//------------------------------------------------------------------------------
// Keywords
const std::string declcommand = "let"; //definition of new variable
const std::string sqrtcommand = "sqrt"; //command to compute sqrt of next expression
const std::string powcommand = "pow"; //command to compute the exp1^exp2

//------------------------------------------------------------------------------

