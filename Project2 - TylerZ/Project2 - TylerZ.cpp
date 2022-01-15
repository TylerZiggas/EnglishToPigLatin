// Project2 - TylerZ.cpp

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

struct Word
{
	string english;
	string piglatin;
};

Word* wordArray = nullptr;
Word* splitSentence(const string, int &); //Splitting Sentence Up
void convertToPigLatin(Word[], int); // Convert from English to Pig Latin
void displayPigLatin(const Word[], int); // Display Pig Latin

int main()
{
	int wordCount = 1;
	string words;
	
	cout << "Please enter a string to convert to PigLatin: "; //Input your sentence
	getline(cin, words);
	wordArray = splitSentence(words, wordCount);
	convertToPigLatin(wordArray, wordCount);
	displayPigLatin(wordArray, wordCount);

	return 0;
}

Word* splitSentence(const string oldSentence, int &wordCount) //Splitting Sentence Up
{
	string tempSentence = oldSentence;
	string newSentence;

	for (int i = 0; i < oldSentence.length(); i++) // Gets rid of any capitalized letters and makes them lowercase, also gets rid of special characters
	{
		tempSentence[i] = tolower(oldSentence[i]);
		if (tempSentence[i] == ' ' || (tempSentence[i] >= 'a' && tempSentence[i] <= 'z'))
		{
			newSentence += tempSentence[i];
		}
	}

	int spaceNum = 0;
	bool firstWord = false;

	for (int k = 0; k < newSentence.length(); k++) // Counts the number of words
	{
		if ((newSentence[k] >= 'a') || firstWord == true) // Checks if the first word has started, do not want to count a space before the first word
		{
			firstWord = true; 
			if (spaceNum == 0) // Checks if there is a space recently
			{
				if (isspace(newSentence[k])) // Adds 1 to word count and adds 1 to make sure another space isn't counted after
				{
					wordCount++;
					spaceNum++;
				}
			}
			else if (newSentence[k] >= 'a') // Removes the space restriction once a new word has started
			{
				spaceNum = 0;
			}
		}
	}

	if (isspace(newSentence[newSentence.length() - 1])) // Checks to see if the last thing entered is a space and subtracts 1 to make the word count correct
	{
		wordCount--;
	}

	wordArray = new Word[wordCount];
	int x = 0;

	stringstream ssent(newSentence);
	while (ssent.good() && x < wordCount) // Separates the words into the wordArray
	{
		ssent >> wordArray[x].english;
		x++;
	}

	return wordArray;
}

void convertToPigLatin(Word wordArray[], int wordCount)
{
	for (int i = 0; i < wordCount; i++)
	{	
		// If vowel, translate for word starting with vowel
		if (wordArray[i].english[0] == 'a' || wordArray[i].english[0] == 'e' || wordArray[i].english[0] == 'i' || wordArray[i].english[0] == 'o' || wordArray[i].english[0] == 'u')
		{
			wordArray[i].piglatin = wordArray[i].english;
			wordArray[i].piglatin.append("way");
		}
		else if (wordArray[i].english == " ") // If space, just use a space
		{
			wordArray[i].piglatin = " ";
		}
		else if (wordArray[i].english != " ") // If not space (or vowel since that is already checked) translate the word as it starts with a constant 
		{	
			wordArray[i].piglatin.append(wordArray[i].english, 1, wordArray[i].english.length() - 1);
			wordArray[i].piglatin.append(wordArray[i].english, 0, 1);
			wordArray[i].piglatin.append("ay");
		}
	}
}

void displayPigLatin(const Word wordArray[], int wordCount)
{
	for (int i = 0; i < wordCount; i++) // Displays each individual word
	{
		cout << wordArray[i].piglatin << ' '; 
	}

	delete[] wordArray;
}