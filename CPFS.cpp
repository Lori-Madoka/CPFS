//hmmm no idea how to make this 
//g++ -o equation equation.cpp -lstdc++

#include <iostream>
#include <vector>
#include <string>

int variablechecker(char x){
	switch(x){
		case '1':
			return 0;
		case '2':
			return 0;
		case '3':
			return 0;
		case '4':
			return 0;		
		case '5':
			return 0;
		case '6':
			return 0;
		case '7':
			return 0;
		case '8':
			return 0;
		case '9':
			return 0;
		case '0':
			return 0;
		case 'e':
			return 10;
		case '+':
			return 2;		
		case '-':
			return 3;
		case '*':
			return 4;
		case '/':
			return 5;
		case '(':
			return 6;
		case ')':
			return 7;
		case '^':
			return 8;
		case ' ':
			return 9;
		case '.':
			return 1;
		default:
			return 1;		
	}
}

int getlength(std::string input){
	int count = 0;
	while (input[count]!=0){
		count+=1;
	}
	std::cout << "string length is: " << count << std::endl;
	return count;
}

int checkmathfunc(std::string input, int counter){
	//checks the next few characters in the string and forwards the counter however far to skip.
	if ((input[counter] == 'e')){
		return 1;
	}
	else if ((input[counter] == 'c') && (input[counter+1] == 'o')){
		return 3;
	}
	else if ((input[counter] == 's') && (input[counter+1] == 'i')){
		return 3;
	}
	else if ((input[counter] == 't') && (input[counter+1] == 'a')){
		return 3;
	}
	else{
		return 0;	
	}
}

std::string formatter(std::string input, int length) {
	int counter = 0;
	int compcount = 0;
	std::string formattedexpression = "(";
	while (counter < length) {
		//check if the 
		if((variablechecker(input[counter]) == 0) || (variablechecker(input[counter]) == 1)) {
			if (checkmathfunc(input, counter) != 0){
				int trigcounter = counter;
				while (trigcounter < (counter+checkmathfunc(input, counter))){
					formattedexpression+=input[trigcounter];
					trigcounter+=1;
				}
				counter+=checkmathfunc(input, counter);
			}
			else {	
				formattedexpression+= "(";
				compcount = counter;
				while (compcount < length && (variablechecker(input[compcount]) == 0 || variablechecker(input[compcount]) == 1)) {
					formattedexpression+=input[compcount];
					compcount+=1;
				}
				formattedexpression+=")";
				counter = compcount;
			}
		}
		formattedexpression+=input[counter];
		counter+=1;
	}
	formattedexpression+=")";
	return formattedexpression;
}

std::string ordergrabber(std::string input, int length) { 
	int counter = 0;
	std::string operatororder;
	while (counter < length) {
		//std::cout << "Youre not supposed to be here yet" << std::endl;
		if (variablechecker(input[counter]) == 2 || variablechecker(input[counter]) == 3 || variablechecker(input[counter]) == 4 || variablechecker(input[counter]) == 5) {
			operatororder+=input[counter];
			std::cout << "found an operator and added to string" << std::endl;
		}
		std::cout << "iterate +1" << std::endl;
		counter+=1;
	}
	return operatororder;
}

int calculator(std::string subbed){
	return 0;
}


std::string substitutor(std::string formatted, int length, std::vector<char> existingvar, std::vector<char> existingvarval) {
	int counter = 0;
	int flag = 0;
	std::string substituted;
	// how tf do you make temporary variables
	// could do linked list but linked list just for this is a bit dead 
	while (counter < length) {
		int charcount = 0;
		int tempcharcount = 0;
		//go through the string and for each character do a check for the variables to be subbed
		for (char i : existingvar) {
			if (formatted[counter] == i) {
				flag = 1;
				std::cout << "found a character that needs substituting: " << i << std::endl;
				std::cout << "flag recognised" << std::endl;
				for (char i : existingvarval) {
					if (tempcharcount == charcount) {
						std::cout << "value to substitute found: #" << existingvarval[tempcharcount] << "#" <<  std::endl;
						if (formatted[counter-1] != '('){	
							substituted+="(";
							substituted+=existingvarval[tempcharcount];
							substituted+=")";
						}
						else {
							substituted+=existingvarval[tempcharcount];
						}
						break;
					}
					else {
						std::cout << "iterating through val list" << std::endl;
						tempcharcount++;
						std::cout << "tempcharcount is now: " << tempcharcount << std::endl;
					}
				}
				break;
			}
			else {
				std::cout << "iterating through var list" << std::endl;
				charcount++;
				std::cout << "charcount is now: " << charcount << std::endl;
			}
		}
		std::cout << "charcount in outside scope is" << charcount << std::endl;
		if (flag == 1) {	
			counter++;
			flag = 0;
		}
		else {
			substituted+=formatted[counter];
			counter++;
		}
	}	
	substituted+=")";	
	return substituted;
}


std::string simplifier(std::string substituted, std::string operatororder, int orderlength) {
	//this should make it possible for integer conversion
	int stringcount = 0; //position in string
	int counter = 0; //counter to make sure overindexing doesnt occur
	std::string simplified;
	int inside = 0;
	while (stringcount < orderlength) {
		if (variablechecker(substituted[stringcount]) == 0 && variablechecker(substituted[stringcount+1]) == 6){
			simplified += substituted[stringcount];
			simplified += "*";
			stringcount+= 1;
		}
		else if (variablechecker(substituted[stringcount]) == 7 && variablechecker(substituted[stringcount+1]) == 6) {
			simplified += substituted[stringcount];
			simplified += "*";
			stringcount+= 1;
		}
		else {
			simplified+=substituted[stringcount];
			stringcount+= 1;
		}
	}
	return simplified;
}

int euler(std::string equation, int length, int h, int x, int y, int finalx, char lettertosub, std::vector<char> existingvar) {
	//take value and sub into the equation to get new y
	//std::vector<char> existingval = [lettertosub];
	for (int i; i<((finalx-x)/h); ++i){
		//make eulers method fr
		std::vector<char> tempvals = {' '};
		tempvals.push_back(x);
		tempvals.push_back(y);
		int func = (calculator(substitutor(equation, length, existingvar, tempvals)));
		y = y+(h*func);
		x = x+h;
		
	}

	return y;						
}



int main(){
	//grab equation from the user
	std::vector<char> existingvar = {' '};
	std::vector<char> existingvarval = {' '};
	std::string input;
	std::cout << "Enter equation: " << std::endl;
	std::cin >> input;

	//check for any variables
	int counter = 0;
	bool varinlist = true;
	char x;
	int length;
	char xval;
	length = getlength(input);
	while (counter < (length)){
		x = input[counter];
		if (variablechecker(x)==1){
			if (checkmathfunc(input, counter) != 0){
				counter+=checkmathfunc(input, counter);
			}
			else{		
				for (char i : existingvar){
					if (x == i){
						varinlist = true;
						break;
					}
					else {
						varinlist = false;
					}
				}
				if (varinlist == false) {
					std::cout << "Imposter: " << x << std::endl;
					existingvar.push_back(x);
					std::cout << "Gimme Gimme " << x << " value" << std::endl;
					//xval used to listed as an int so its wrong data type
					std::cin >> xval; 
					existingvarval.push_back(xval);
					std::cout << "existingvar: " << std::endl;
					for (char num : existingvar) {
					        std::cout << num << " ";
					    }
					std::cout << std::endl;
					std::cout << "existingvarval: " << std::endl;
					for (char num : existingvarval) {
					        std::cout << num << " ";
					    }
					std::cout << std::endl;
					
				}// use thesame ethod but construct a string instead. 
			counter+=1;
			varinlist = true;
			}
		}
		else{
			counter+=1;	
		}
	}
	// now has scanned list and found the non numeric and operators. 
	std::string formatted = formatter(input, length);
	std::cout << formatted << std::endl;
	// now have a string formatted with all of the numbers and constants to replace in parenthesis 
	// also need a new length
	int newlength = getlength(formatted);
	std::string operatororder = ordergrabber(formatted, newlength);
	std::cout << operatororder << std::endl;
	int orderlength = getlength(operatororder);
	// now have a string of operators
	// to substitute in all of the operators you can 
	std::string substitutedstring = substitutor(formatted, newlength, existingvar, existingvarval);
	std::cout << substitutedstring << std::endl;
	int substringlength = getlength(substitutedstring);
	std::string simplified = simplifier(substitutedstring, operatororder, substringlength);
	std::cout << "simplified expression for calculation: " << simplified << std::endl;
	//int finalval = stoi(substitutedstring);
	//std::cout << "final value = " << finalval << std::endl;
	
}



/* todo list:
- make the formatter do variables correclty to isolate from int components **fixed
- fix decimals (presumably they dont work) **fixed
- fix brackets not working **fixed
- do euler's method **in progress 
- make exponents work properly
- make trig functions get parsed properly **fixed
*/
