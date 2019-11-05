#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

vector<string> getText(string file_name) {
  vector<string> lines_of_text;
  try {
    ifstream my_file(file_name);
    my_file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
    string line;
    while (getline(my_file, line)) {
      lines_of_text.push_back(line);
    }
    my_file.close();
  } catch (std::exception const &e) {
    cerr << "There was an error: " << e.what() << endl;
  }
  return lines_of_text;
}

int main() {

  vector<string> lines_of_text = getText("test.txt");
  for (auto const &i : lines_of_text) {
    cout << i << " " << endl;
  }

  cout << "Koniec! " << endl;

  return 0;
}
