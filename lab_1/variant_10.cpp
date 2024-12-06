#include <iostream>
#include <fstream>
#include <cctype>
#include <locale>

using namespace std;

// Функция для обработки термина - перевод в нижний регистр и обертывание в кавычки
string processTerm(string term) {
	bool allCaps = true;
	for (char c : term) {
		if (isalpha(c) && !isupper(c)) {
			allCaps = false;
			break;
		}
	}

	if (allCaps && term.length() >= 2) {
		for (int i = 0; i < term.length(); ++i) {
			term[i] = tolower(term[i]);
		}
		return "'" + term + "'";
	}
	else {
		return term;
	}
}

int main() {
	setlocale(LC_ALL, "ru-RU");

	string inputFileName, outputFileName;
	cout << "Введите имя входного файла: ";
	cin >> inputFileName;
	cout << "Введите имя выходного файла: ";
	cin >> outputFileName;

	ifstream input;
	ofstream output;
	input.open(inputFileName);
	output.open(outputFileName);

	if (!input.is_open() || !output.is_open()) {
		cout << "Ошибка открытия файлов." << endl;
		return 1;
	}

	string term;
	bool inSpecialTerm = false;

	while (input >> term) {
		for (char& c : term) {
			if (isupper(c)) {
				inSpecialTerm = true;
				break;
			}
		}

		if (inSpecialTerm) {
			output << processTerm(term) << " ";
		}
		else {
			output << term << " ";
		}
		inSpecialTerm = false;
	}

	input.close();
	output.close();

	cout << "Succeeded " << endl;

	return 0;
}












// ТУТ РАБОТАЮТ КАВЫЧКИ
//#include <iostream>
//#include <fstream>
//#include <cctype> // для функции isupper
//#include <locale> // для работы с русскими символами
//
//using namespace std;
//
//// Функция для преобразования буквы в нижний регистр
//char toLowerCaseChar(char c) {
//	if (isupper(c)) {
//		return tolower(c);
//	}
//	return c;
//}
//
//int main() {
//	setlocale(LC_ALL, "Russian"); // установка русской локали
//
//	string inputFileName, outputFileName;
//	cout << "Введите имя входного файла: ";
//	cin >> inputFileName;
//	cout << "Введите имя выходного файла: ";
//	cin >> outputFileName;
//
//	ifstream input;
//	ofstream output;
//	input.open(inputFileName);
//	output.open(outputFileName);
//
//	if (!input.is_open() || !output.is_open()) {
//		cout << "Ошибка открытия файлов." << endl;
//		return 1;
//	}
//
//	char c;
//	bool insideTerm = false;
//
//	while (input.get(c)) {
//		if (isupper(c)) {
//			if (!insideTerm) {
//				output << '"';
//				insideTerm = true;
//			}
//			output << toLowerCaseChar(c);
//		}
//		else {
//			if (insideTerm) {
//				output << '"';
//				insideTerm = false;
//			}
//			output << c;
//		}
//	}
//
//	if (insideTerm) {
//		output << '"';
//	}
//
//	input.close();
//	output.close();
//
//	cout << "Термины в нижнем регистре обернуты в кавычки в файле " << outputFileName << endl;
//
//	return 0;
//}







// ТУТ РАБОТАЛА toLowerCase
//#include <iostream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//string toLowerCase(const string& str) {
//	string result = str;
//
//	for (int i = 0; i < result.length(); i++) {
//		if (result[i] >= 'A' && result[i] <= 'Z') {
//			result[i] = result[i] - 'A' + 'a';
//		}
//	}
//
//	return result;
//}
//
//int main() {
//	string inputFileName, outputFileName;
//
//	cout << "Enter input file name: ";
//	cin >> inputFileName;
//
//	cout << "Enter output file name: ";
//	cin >> outputFileName;
//
//	ifstream inputFile(inputFileName);
//	if (!inputFile.is_open()) {
//		cerr << "Error opening input file" << endl;
//		return 1;
//	}
//
//	ofstream outputFile(outputFileName);
//	if (!outputFile.is_open()) {
//		cerr << "Error opening output file" << endl;
//		inputFile.close();
//		return 1;
//	}
//
//	string word;
//	bool inTerm = false;
//
//	while (inputFile >> word) {
//		string lowerWord = toLowerCase(word);
//
//		if (inTerm) {
//			if (word.length() >= 2 && word != lowerWord) {
//				outputFile << "\"" << lowerWord << "\" ";
//			}
//			else {
//				outputFile << word << " ";
//				inTerm = false;
//			}
//		}
//		else {
//			if (word.length() >= 2 && word == lowerWord) {
//				inTerm = true;
//				outputFile << "\"" << word << "\" ";
//			}
//			else {
//				outputFile << word << " ";
//			}
//		}
//	}
//
//	inputFile.close();
//	outputFile.close();
//
//	cout << "File has been successfully processed." << endl;
//
//	return 0;
//}



/*	for (int i = 0; i < result.length(); i++) {

		if ((result[i] >= 'А') && (result[i] <= 'Я')) {
			result[i] += 'а' - 'А';
			        }
			        else if ((result[i] >= 'A') && (result[i] <= 'Z')) {
			result[i] += 'а' - 'А';
		*/	        











//#include <iostream>
//#include <fstream>
//using namespace std;
//
//bool isUpper(char ch) {
//    return (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E' || ch == 'F' || ch == 'G' ||
//        ch == 'H' || ch == 'I' || ch == 'J' || ch == 'K' || ch == 'L' || ch == 'M' || ch == 'N' ||
//        ch == 'O' || ch == 'P' || ch == 'Q' || ch == 'R' || ch == 'S' || ch == 'T' || ch == 'U' ||
//        ch == 'V' || ch == 'W' || ch == 'X' || ch == 'Y' || ch == 'Z' || ch == 'А' || ch == 'Б' ||
//        ch == 'V' || ch == 'W' || ch == 'X' || ch == 'Y' || ch == 'Z' || ch == 'А' || ch == 'Б' ||
//        ch == 'В' || ch == 'Г' || ch == 'Д' || ch == 'Е' || ch == 'Ё' || ch == 'Ж' || ch == 'З' ||
//        ch == 'И' || ch == 'Й' || ch == 'К' || ch == 'Л' || ch == 'М' || ch == 'Н' || ch == 'О' ||
//        ch == 'П' || ch == 'Р' || ch == 'С' || ch == 'Т' || ch == 'У' || ch == 'Ф' || ch == 'Х' ||
//        ch == 'Ц' || ch == 'Ч' || ch == 'Ш' || ch == 'Щ' || ch == 'Ъ' || ch == 'Ы' || ch == 'Ь' ||
//        ch == 'Э' || ch == 'Ю' || ch == 'Я');
//}
//
//string addQuot(string str) {
//    return "'" + str + "'";
//}
//
//void convertToLowerCase(char* str) {
//    for (int i = 0; str[i] != L'\0'; ++i) {
//        if ((str[i] >= 'А') && (str[i] <= 'Я')) {
//            str[i] += 'а' - 'А';
//        }
//        else if ((str[i] >= 'A') && (str[i] <= 'Z')) {
//            str[i] += 'а' - 'А';
//        }
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "ru-RU");
//    char input[] = "Hello, ДРУГ\nПривет FRIEND";
//    for (int i = 0; input[i] != '\0'; ++i) {
//        if (isUpper(input[i]) && isUpper(input[i + 1]))
//            convertToLowerCase(input);
//        cout << input[i];
//        addQuot(input);
//    }
//    return 0;
//}











//#include <iostream>
//#include <regex>
//#include <fstream>
//using namespace std;
//
//string StrToLowercase(string str)
//{
//    string result = "";
//    for (char ch : str) {
//        result += tolower(ch);
//    }
//    return result;
//}
//
//string addQuot(string str) {
//    return "'" + str + "'";
//}
//
//int main()
//{
//    setlocale(LC_ALL, "ru-RU");
//    ifstream input_file("test.txt");
//    string input((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
//    regex pattern("[А-Я]{2,}");
//
//    string result = regex_replace(input, pattern, addQuot("$1"));
//    string result2 = StrToLowercase(result);
//
//    cout << result2;
//}