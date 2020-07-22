#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <regex>
#include <pwd.h>
#include <unistd.h>
#include "UniqueWord.h"

std::string PATH = ""; // Will store the path of the file to be read

/** Tests if a word has already been found the increments it's count
 * @param uniqueWords The vector of existing unique words found
 * @param word The word that is being tested
 * @return A boolean, true if a word already exists, false otherwise
 */
bool inUniqueWords(std::vector<UniqueWord> &uniqueWords, const std::string &word)
{
  // Loop unique words, if word exists increment it's count
  for(auto &w : uniqueWords)
  {
    if(word == w.getWord())
    {
      w.incrementCount();
      return true;
    }
  }

  return false;
}

/** Writes the unique words to an output file "UniqueWords.txt"
 * @param uniqueWords The vector of unique words to be written to the file
 * @return no return value
 */
void writeUniqueWordsToFile(const std::vector<UniqueWord> &uniqueWords)
{
  // Try to open the output file
  std::ofstream file("output.txt");
  if(!file.is_open())
  {
    std::cout << "Error opening file \"output.txt\", exiting ..." << std::endl;
    return;
  }

  // Header of output file
  file << "Word" << std::setw(FIELD_WIDTH) << "Usage" << std::endl << std::endl;

  int fieldWidth = 10;

  // To write words in descending order need to loop vector in reverse
  for(auto w = uniqueWords.rbegin(); w != uniqueWords.rend(); ++w)
  {
    // Format the output to align count values
    fieldWidth = FIELD_WIDTH-(int)w->getWord().length();
    if(fieldWidth <= 1) file << w->getWord() << " " << w->getCount() << std::endl;
    else file << w->getWord() << std::setw(fieldWidth) << w->getCount() << std::endl;
  }

  file.close();

  std::cout << "Words successfully saved in \"output.txt\"" << std::endl;

  return;
}

int main(int argc, char const **argv)
{
  std::vector<UniqueWord> uniqueWords; // Stores words and counts as objects in a vector

  // Check a file path has been provided as an argument on cl
  if(argc < 2)
  {
    std::cout << "Please provide a path to the file to be read, or q to exit:" << std::endl;
    std::cin >> PATH;
    if(PATH == "q") return 0;
  }

  else PATH = argv[1];

  // Try to open file from given path
  std::ifstream file(PATH);
  if(!file.is_open())
  {
    std::cout << "Error opening file \"" + PATH + "\", exiting ..." << std::endl;
    return 1;
  }
  
  std::cout << "Reading file \"" + PATH + "\"" << std::endl;

  std::string word;

  // Loop file word by word, reads characters separated by spaces
  while(file >> word)
  {
    // Loop punctuation characters and using regex replace 1 or more occurrences with ""
    for(const char &p : PUNCTUATION)
    {
      std::string expression = "[\\"+std::string(1,p)+"]+";
      word = std::regex_replace(word, std::regex(expression), "");
    }

    // Convert all letters to lower case
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Now read all words hyphen separated
    std::istringstream ss(word);
    std::string wordWithoutHyphens;
    while(std::getline(ss, wordWithoutHyphens, '-'))
    {
      // Skip words less than 5 characters
      if(wordWithoutHyphens.length() < 5) continue;

      // Else if not in found words already, create new word
      if(!inUniqueWords(uniqueWords,wordWithoutHyphens))
      {
        auto newWord = UniqueWord(wordWithoutHyphens,1);
        uniqueWords.push_back(newWord);
      }
    }
  }

  file.close();

  // Sort Vector by count (In ascending order after this line)
  std::sort(uniqueWords.begin(),uniqueWords.end());

  // Print to terminal if added as argument
  if(argc > 2)
  {
    if(std::string(argv[2]) == "print")
    {
      for(auto w = uniqueWords.rbegin(); w != uniqueWords.rend(); ++w)
      {
        std::cout << w->getWord() << " - " << w->getCount() << std::endl;
      }
    }
  }

  writeUniqueWordsToFile(uniqueWords); // Found in "output.txt"

  return 0;
}