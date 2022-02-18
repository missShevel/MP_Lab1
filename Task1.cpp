//#include <iostream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//struct WORD_NUMBER {
//    string word;
//    int amount;
//};
//
////int main() {
//    int words_in_map = 0;
//    string file_name = "/Users/user/CLionProjects/MPP_Lab1/text.txt";
//    cout << "Enter the file name: ";
//    cin >> file_name;
//    int n;
//    cout << "Enter number of words: ";
//    cin >> n;
//    WORD_NUMBER word_number_map[100];
//    ifstream file(file_name);
//    string curr_word;
//    string skip[] =
//            {"the", "for", "in", "into", "as",
//             "are", "but", "is", "on",
//             "a", "an", "of", "to", "at",
//             "by", "and", "not", "or"};
//    int size_of_skip = 18;
//    string storage;
//    int i;
//    int index;
//
//
//    readingFile:
//    if (!(file >> curr_word)) {
//        goto after_file_reading;
//    }
//
//    index = 0;
//
//    word_to_lower_cycle:
//    if (curr_word[index] != '\0') {
//        if (curr_word[index] <= 'Z' and curr_word[index] >= 'A') {
//            curr_word[index] += 32;
//        }
//        index++;
//        goto word_to_lower_cycle;
//    } else {
//        if (!(curr_word[index - 1] >= 'A' and curr_word[index - 1] <= 'Z')
//            && !(curr_word[index - 1] >= 'a' and curr_word[index - 1] <= 'z')) {
//            curr_word[index - 1] = '\0';
//        }
//    }
//        i = 0;
//        word_to_temp_loop:
//        if (i >= index) {
//            goto word_to_temp_end;
//        }
//        storage += curr_word[i];
//        i++;
//        goto word_to_temp_loop;
//
//        word_to_temp_end:
//        i = 0;
//
//    check_skip:
//    if (i >= size_of_skip) {
//        goto check_skip_end;
//    }
//    if (curr_word == skip[i]) {
//        goto readingFile;
//    } else {
//        i++;
//        goto check_skip;
//    }
//
//    check_skip_end:
//    i = 0;
//
//    search_for_similar:
//    storage = word_number_map[i].word;
//    if (i > words_in_map) {
//        goto search_for_similar_end;
//    }
//    if (storage == curr_word) {
//        word_number_map[i].amount++;
//        goto readingFile;
//    } else {
//        i++;
//        goto search_for_similar;
//    }
//    search_for_similar_end:
//    word_number_map[words_in_map++] = {curr_word, 1};
//    goto readingFile;
//
//    after_file_reading:
//    i = 0;
//    outer_loop:
//    if (i < words_in_map - 1) {
//        index = 0;
//        inner_loop:
//        if (index < words_in_map - i - 1) {
//            if (word_number_map[index].amount < word_number_map[index + 1].amount) {
//                WORD_NUMBER temp = word_number_map[index];
//                word_number_map[index] = word_number_map[index + 1];
//                word_number_map[index + 1] = temp;
//            }
//            index++;
//            goto inner_loop;
//        }
//        i++;
//        goto outer_loop;
//    }
//
//    i = 0;
//    output:
//    if (i < n) {
//        cout << word_number_map[i].word << " - " << word_number_map[i].amount << endl;
//        i++;
//        goto output;
//    }
//    return 0;
//}
