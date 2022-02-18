#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct WORD_PAGES {
    string word;
    int pages[101] = {};
    int apperances_on_pages = 0;
};

int main() {
    string file_name = "/Users/user/CLionProjects/MPP_Lab1/text.txt";
    string skip[] =
            {"the", "for", "in", "into", "onto", "as",
             "are", "but", "is", "on",
             "a", "an", "of", "to", "at",
             "by", "and", "not", "or"};
    int SIZE_OF_SKIP = 18;
    int ROWS_ON_PAGE = 45;
    int words_count = 0;
    string row;
    string store;
    string word;

    char space = ' ';
    int rows_number;
    int row_length;
    int page_number = 0;
    int words_in_dictionary = 50;
    WORD_PAGES* dictionary = new WORD_PAGES [words_in_dictionary];

    int i = 0;
    int row_index = 0;

    ifstream book(file_name);
    book_scanner:
        if(book.peek() == EOF){
            goto sort;
        }
        page_number++;
        rows_number = 0;

        page_scanner:
            rows_number++;
            if( rows_number > ROWS_ON_PAGE || book.peek() == EOF) {
                goto page_scanner_end;
            }
            getline(book, row);
            row_length = 0;

    if (row[0] == '\0') {
        goto page_scanner;
    }
            row_read:

            store = "";
            count_row_length:
                if(row[row_length]) {
                    row_length++;
                    goto count_row_length;
                }
                word = "";
                i = 0;
                 read_word:
                if(row_index  < row_length){
                    if(row[row_index+i] == space or row[row_index+i] == '\0'){
                        goto read_word_end;
                    } else {
                        store += row[row_index+i];
                        i++;

                        goto read_word;
                    }
                    read_word_end:
                    int word_length = i;
                    row_index += i;
                    i = 0;
                    if (store[word_length-1] == '.' || store[word_length-1] == ','
                        || store[word_length-1] == '!' || store[word_length-1] == '?'
                        || store[word_length-1] == ':' || store[word_length-1] == ';'
                        || store[word_length-1] == '"' || store[word_length-1] == '\'') {
                        string new_word = "";
                        copy_word:
                        if (i >= word_length - 1) {
                            goto deletion_end;
                        }
                         new_word += store[i];
                        i++;
                        goto copy_word;

                        deletion_end:
                        word = new_word;
//                    word = new_word;
                        word_length--;
                    } else {
                        word = store;
                    }

                search_word:


                    bool to_skip = false;
                        int index = 0;
                        check_letters:
                            if(index >= word_length) {
                                goto check_letters_end;
                            }

                            if( !(word[index] >= 'A' and word[index] <= 'Z')
                                or (word[index] >= 'a' and word[index] <= 'z')) {
//                                to_skip = true;
                            }

                        index++;
                        goto check_letters;

                    check_letters_end:
                    index = 0;

                    word_to_lowercase:
                        if(index >= word_length){
                            goto word_to_lowercase_end;
                        }
                        if(word[index] >= 'A' and word[index] <= 'Z'){
                            word[index] += 32;
                        }
                        index++;
                        goto word_to_lowercase;

                    word_to_lowercase_end:
                    index = 0;

                    filter_skip:
                        if(index >= SIZE_OF_SKIP){
                            goto add_to_dictionary;
                        }

                        if(skip[index] == word) {
                            to_skip = true;
                            goto add_to_dictionary;
                        }
                        index++;
                        goto filter_skip;

                    add_to_dictionary:
                    if(!to_skip){
                        int count = 0;
                        search_through_dictionary:
                        if(count >= words_count){
                            goto add_new;
                        }
                        if(dictionary[count].word == word){
                            if(dictionary[count].apperances_on_pages != 101){
                                dictionary[count].pages[dictionary[count].apperances_on_pages] = page_number;
                                dictionary[count].apperances_on_pages++;
                                goto adding_end;
                            }
                        } else {
                            count++;
                            goto search_through_dictionary;
                        }

                        add_new:
                        if(words_count == words_in_dictionary){
                            WORD_PAGES* dictionary_extended = new WORD_PAGES[words_in_dictionary*2];
                            int s = 0;
                            copy_words:
                            if(s >= words_in_dictionary){
                                goto end_copy;
                            }
                            dictionary_extended[s] = dictionary[s];
                            s++;
                            goto copy_words;
                            end_copy:
                            words_in_dictionary *= 2;
                            dictionary = dictionary_extended;
                        }

                        dictionary[words_count].word = word;
                        dictionary[words_count].pages[0] = page_number;
                        dictionary[words_count].apperances_on_pages = 1;
                        words_count++;

                    }


                }
                adding_end:
                row_index++;
                if(row_index <= row_length){
                    goto row_read;
                }

                row_index = 0;
                goto page_scanner;
            page_scanner_end:
    goto book_scanner;



    sort:
    output:
    if (i < words_in_dictionary) {
        cout << dictionary[i].word << endl;
        i++;
        goto output;
    }
    book.close();

    return 0;
}