#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cmath>
#include <iomanip>

using namespace std;

string preprocessWord(const string& word) {
    string result;
    for (size_t i = 0; i < word.length(); ++i) {
        if (isalnum(word[i])) {
            result += toupper(word[i]);
        }
    }
    return result;
}

bool isCommonWord(const string& word) {
    static const char* commonWordsArray[] = {"A", "AND", "AN", "OF", "IN", "THE"};
    static set<string> commonWords(commonWordsArray, commonWordsArray + sizeof(commonWordsArray) / sizeof(commonWordsArray[0]));
    return commonWords.find(word) != commonWords.end();
}

map<string, double> countWordFrequencies(const string& filename) {
    ifstream file(filename.c_str());
    map<string, int> wordCount;
    int totalWords = 0;
    string word;

    while (file >> word) {
        word = preprocessWord(word);
        if (!isCommonWord(word) && !word.empty()) {
            wordCount[word]++;
            totalWords++;
        }
    }

    map<string, double> normalizedFrequencies;
    map<string, int>::const_iterator it;
    for (it = wordCount.begin(); it != wordCount.end(); ++it) {
        normalizedFrequencies[it->first] = static_cast<double>(it->second) / totalWords;
    }

    return normalizedFrequencies;
}

vector<pair<string, double> > getTopFrequentWords(const map<string, double>& wordFreqs, int N) {
    vector<pair<string, double> > words(wordFreqs.begin(), wordFreqs.end());
    sort(words.begin(), words.end(), greater<pair<string, double> >());
    if (words.size() > N) {
        words.resize(N);
    }
    return words;
}

double calculateSimilarity(const vector<pair<string, double> >& topWords1, const vector<pair<string, double> >& topWords2) {
    map<string, double> freqMap1, freqMap2;
    vector<pair<string, double> >::const_iterator it;
    for (it = topWords1.begin(); it != topWords1.end(); ++it) {
        freqMap1[it->first] = it->second;
    }
    for (it = topWords2.begin(); it != topWords2.end(); ++it) {
        freqMap2[it->first] = it->second;
    }

    double similarity = 0.0;
    map<string, double>::const_iterator mapIt;
    for (mapIt = freqMap1.begin(); mapIt != freqMap1.end(); ++mapIt) {
        if (freqMap2.find(mapIt->first) != freqMap2.end()) {
            similarity += mapIt->second + freqMap2[mapIt->first];
        }
    }
    return similarity;
}

bool compareSimilarPairs(const pair<pair<int, int>, double>& a, const pair<pair<int, int>, double>& b) {
    return a.second > b.second;
}

int main() {
    const int topWordCount = 100;
    vector<string> filenames;

    string folderPath = "books"; 
    filenames.push_back("books/Cats by Moncrif.txt");
    filenames.push_back("books/Foxes Book of Martyrs Part 1.txt");
    filenames.push_back("books/Foxes Book of Martyrs Part 2.txt");
    filenames.push_back("books/Foxes Book of Martyrs Part 3.txt");
    filenames.push_back("books/Foxes Book of Martyrs Part 4.txt");
    filenames.push_back("books/Foxes Book of Martyrs Part 5.txt");
    filenames.push_back("books/Foxes Book of Martyrs Part 6.txt");
    filenames.push_back("books/Gerard's Herbal Vol. 3.txt");
    filenames.push_back("books/Gerards Herbal Vol. 1.txt");
    filenames.push_back("books/Gerards Herbal Vol. 2.txt");
    filenames.push_back("books/Gerards Herbal Vol.4.txt");
    filenames.push_back("books/Gil Blas.txt");
    filenames.push_back("books/Gossip in a Library.txt");
    filenames.push_back("books/Hudibras.txt");
    filenames.push_back("books/King of the Beggars.txt");
    filenames.push_back("books/Knocknagow.txt");
    filenames.push_back("books/Les Chats par Moncrif.txt");
    filenames.push_back("books/Lives and Anecdotes of Misers.txt");
    filenames.push_back("books/Love and Madness - Herbert Croft.txt");
    filenames.push_back("books/Memoirs of Laetitia Pilkington V 1.txt");
    filenames.push_back("books/Memoirs of Laetitia Pilkington V 2.txt");
    filenames.push_back("books/Memoirs of Laetitia Pilkington V 3.txt");
    filenames.push_back("books/Memoirs of Mrs Margaret Leeson - Peg Plunkett.txt");
    filenames.push_back("books/Monro his Expedition.txt");
    filenames.push_back("books/Mrs Beetons Book of Household Management.txt");
    filenames.push_back("books/Out of the Hurly-Burly.txt");
    filenames.push_back("books/Percys Reliques.txt");
    filenames.push_back("books/Pompey The Little.txt");
    filenames.push_back("books/Radical Pamphlets from the English Civil War.txt");
    filenames.push_back("books/Scepsis Scientifica.txt");
    filenames.push_back("books/The Anatomy of Melancholy Part 1.txt");
    filenames.push_back("books/The Anatomy of Melancholy Part 2.txt");
    filenames.push_back("books/The Anatomy of Melancholy Part 3.txt");
    filenames.push_back("books/The Complete Cony-catching.txt");
    filenames.push_back("books/The Consolation of Philosophy.txt");
    filenames.push_back("books/The Covent Garden Calendar.txt");
    filenames.push_back("books/The Devil on Two Sticks.txt");
    filenames.push_back("books/The Diary of a Lover of Literature.txt");
    filenames.push_back("books/The History Of Ireland - Geoffrey Keating.txt");
    filenames.push_back("books/The History of the Human Heart.txt");
    filenames.push_back("books/The Ingoldsby Legends.txt");
    filenames.push_back("books/The Life of Beau Nash.txt");
    filenames.push_back("books/The Life of John Buncle by Thomas Amory.txt");
    filenames.push_back("books/The Life of King Richard III.txt");
    filenames.push_back("books/The Life of Pico della Mirandola.txt");
    filenames.push_back("books/The Martyrdom of Man.txt");
    filenames.push_back("books/The Masterpiece of Aristotle.txt");
    filenames.push_back("books/The Memoirs of Count Boruwlaski.txt");
    filenames.push_back("books/The Metamorphosis of Ajax.txt");
    filenames.push_back("books/The Newgate Calendar - Supplement 3.txt");
    filenames.push_back("books/The Newgate Calendar Supplement 2.txt");
    filenames.push_back("books/The Newgate Calendar Supplement.txt");
    filenames.push_back("books/The Newgate Calendar V 1.txt");
    filenames.push_back("books/The Newgate Calendar V 2.txt");
    filenames.push_back("books/The Newgate Calendar V 3.txt");
    filenames.push_back("books/The Newgate Calendar V 4.txt");
    filenames.push_back("books/The Newgate Calendar V 5.txt");
    filenames.push_back("books/The Newgate Calendar V 6.txt");
    filenames.push_back("books/The Poems of Ossian.txt");
    filenames.push_back("books/The Poetical Works of John Skelton.txt");
    filenames.push_back("books/The Protestant Reformation.txt");
    filenames.push_back("books/The Real Story of John Carteret Pilkington.txt");
    filenames.push_back("books/The Rowley Poems.txt");
    filenames.push_back("books/The SIlver Fox.txt");
    filenames.push_back("Cats by Moncrif.txt");   


    int numBooks = filenames.size();
    if (numBooks < 2) {
        cerr << "Not enough files in the directory for comparison." << endl;
        return 1;
    }

    vector<vector<pair<string, double> > > bookTopWords(numBooks);
    for (int i = 0; i < numBooks; ++i) {
        map<string, double> wordFreqs = countWordFrequencies(filenames[i]);
        bookTopWords[i] = getTopFrequentWords(wordFreqs, topWordCount);
    }

    vector<vector<double> > similarityMatrix(numBooks, vector<double>(numBooks, 0.0));

    for (int i = 0; i < numBooks; ++i) {
        for (int j = i + 1; j < numBooks; ++j) {
            double similarity = calculateSimilarity(bookTopWords[i], bookTopWords[j]);
            similarityMatrix[i][j] = similarity;
            similarityMatrix[j][i] = similarity;  // Symmetric matrix
        }
    }

    vector<pair<pair<int, int>, double> > similarPairs;
    for (int i = 0; i < numBooks; ++i) {
        for (int j = i + 1; j < numBooks; ++j) {
            similarPairs.push_back(make_pair(make_pair(i, j), similarityMatrix[i][j]));
        }
    }

    sort(similarPairs.begin(), similarPairs.end(), compareSimilarPairs);

    cout << "Top 10 Similar Pairs of Books:" << endl;
    for (int i = 0; i < 10 && i < static_cast<int>(similarPairs.size()); ++i) {
        int book1 = similarPairs[i].first.first;
        int book2 = similarPairs[i].first.second;
        double similarity = similarPairs[i].second;
        cout << "Book \"" << filenames[book1] << "\" and Book \"" << filenames[book2] << "\" with similarity " << fixed << setprecision(4) << similarity << endl;
    }

    return 0;
}   