// typing_test.cpp
// Typing Speed Test in C++
// Measures WPM, accuracy, and saves results to typing_results.csv

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cctype>

using namespace std;
using namespace std::chrono;

int countWords(const string &s) {
    bool inWord = false;
    int words = 0;
    for (char ch : s) {
        if (!isspace((unsigned char)ch) && !inWord) {
            inWord = true;
            ++words;
        } else if (isspace((unsigned char)ch)) {
            inWord = false;
        }
    }
    return words;
}

double calculateAccuracy(const string &target, const string &input) {
    size_t n = min(target.size(), input.size());
    size_t correct = 0;
    for (size_t i = 0; i < n; ++i) {
        if (target[i] == input[i]) ++correct;
    }
    size_t total = max(target.size(), input.size());
    if (total == 0) return 100.0;
    return (100.0 * (double)correct) / (double)total;
}

string ratingFromWPMAndAccuracy(double wpm, double acc) {
    if (acc < 50.0) return "Poor";
    if (wpm >= 80 && acc >= 95.0) return "Expert";
    if (wpm >= 60 && acc >= 90.0) return "Advanced";
    if (wpm >= 40 && acc >= 80.0) return "Intermediate";
    return "Beginner";
}

string currentDateTime() {
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm local_tm;
#if defined(_MSC_VER)
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
    return string(buf);
}

void appendResultToCSV(const string &filename, const string &datetime,
                       double wpm, double accuracy, const string &rating,
                       int wordsTyped, double secondsTaken) {
    ofstream ofs(filename, ios::out | ios::app);
    if (!ofs.is_open()) {
        cerr << "Error opening results file.\n";
        return;
    }
    // Write header if file empty
    if (ofs.tellp() == 0) {
        ofs << "datetime,wpm,accuracy_percent,rating,words_typed,seconds_taken\n";
    }
    ofs << "\"" << datetime << "\"," 
        << wpm << "," 
        << accuracy << "," 
        << "\"" << rating << "\"," 
        << wordsTyped << "," 
        << secondsTaken << "\n";
    ofs.close();
}

int main() {
    const string targetText =
        "Typing is a fundamental skill in the digital age. "
        "Being able to type quickly and accurately saves time and improves productivity. "
        "Practice every day to build muscle memory and enhance your focus. "
        "Remember, consistency is the key to becoming a fast and confident typist.";

    cout << "=== Typing Speed Test ===\n\n";
    cout << "Type the following paragraph exactly as shown:\n\n";
    cout << targetText << "\n\n";

    cout << "Press Enter when you're ready to start...";
    string dummy;
    getline(cin, dummy);

    cout << "\nStart typing below, then press Enter when done:\n";
    auto t0 = high_resolution_clock::now();

    string userInput;
    getline(cin, userInput);

    auto t1 = high_resolution_clock::now();
    duration<double> elapsed = t1 - t0;
    double seconds = elapsed.count();
    int wordsTyped = countWords(userInput);
    double minutes = seconds / 60.0;
    double wpm = (minutes > 0.0) ? (wordsTyped / minutes) : 0.0;
    double accuracy = calculateAccuracy(targetText, userInput);
    string rating = ratingFromWPMAndAccuracy(wpm, accuracy);

    cout.setf(std::ios::fixed);
    cout.precision(2);

    cout << "\n--- Results ---\n";
    cout << "Time taken: " << seconds << " seconds\n";
    cout << "Words typed: " << wordsTyped << "\n";
    cout << "Words per minute (WPM): " << wpm << "\n";
    cout << "Accuracy: " << accuracy << " %\n";
    cout << "Rating: " << rating << "\n";

    string datetime = currentDateTime();
    appendResultToCSV("typing_results.csv", datetime, wpm, accuracy, rating, wordsTyped, seconds);

    cout << "\nYour result has been saved to typing_results.csv\n";
    cout << "Thank you for using the program!\n";
    return 0;
}
