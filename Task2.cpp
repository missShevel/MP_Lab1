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
    string file_name = "/Users/user/CLionProjects/MPP_Lab1/book.txt";
    string skip[] =
            {"the", "for", "in", "into", "onto", "as",
             "are", "but", "is", "on",
             "a", "an", "of", "to", "at",
             "by", "and", "not", "or"};
    int SIZE_OF_SKIP = 19;
    int ROWS_ON_PAGE = 45;
    int words_count = 0;
    string row;
    string store;
    string word;

    char space = ' ';
    int rows_number;
    int row_length;
    int page_number = 0;
    int words_in_dictionary = 5;
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

                i = 0;
                 read_word:
                if(row_index < row_length){
                    if(!((row[row_index] >= 'A' and row[row_index] <= 'Z')
                         or (row[row_index] >= 'a' and row[row_index] <= 'z'))){
                        row_index++;
                        goto read_word;
                    }
                    if(row[row_index+i] == space or row[row_index+i] == '\0'){
                        goto read_word_end;
                    }
                        store += row[row_index+i];
                        i++;

                        goto read_word;

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
                        word_length--;
                    } else {
                        word = store;
                    }

                    bool to_skip = false;
                        int index = 0;
                        check_letters:
                            if(index >= word_length) {
                                goto check_letters_end;
                            }

                            if( word_length == 0 || !((word[index] >= 'A' and word[index] <= 'Z')
                                or (word[index] >= 'a' and word[index] <= 'z'))) {
                                to_skip = true;
                                goto add_to_dictionary;
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
                                int x = dictionary[count].apperances_on_pages;
                                if(x <= 100 and dictionary[count].pages[x - 1] != page_number) {
                                    dictionary[count].pages[x] = page_number;
                                    dictionary[count].apperances_on_pages++;
                                }
                                goto adding_end;
                        } else {
                            count++;
                            goto search_through_dictionary;
                        }

                        add_new:
                        if(words_count == words_in_dictionary){
                            WORD_PAGES* dictionary_copy = new WORD_PAGES[words_in_dictionary*2];
                            int s = 0;
                            copy_words:
                            if(s >= words_in_dictionary){
                                goto end_copy;
                            }
                            dictionary_copy[s] = dictionary[s];
                            s++;
                            goto copy_words;
                            end_copy:
                            words_in_dictionary *= 2;
                            dictionary = new WORD_PAGES[words_in_dictionary];

                            s = 0;
                            add_to_ex_d:
                            if(s >= words_in_dictionary){
                                goto new_word;
                            }
                            dictionary[s] = dictionary_copy[s];
                            s++;
                            goto add_to_ex_d;
                        }
                        new_word:
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
    i = 0;
    int j;
    outer_loop:
    if (i >= words_count - 1){
        goto outer_loop_end;
    }
    j = i + 1;
    inner_loop:
    if(j >= words_count){
        goto inner_loop_end;
    }
    if(dictionary[i].word > dictionary[j].word){
        WORD_PAGES temporary = dictionary[i];
        dictionary[i] = dictionary[j];
        dictionary[j] = temporary;
    }
    j++;
    goto inner_loop;

    inner_loop_end:
    i++;
goto outer_loop;

outer_loop_end:
    i = 0;

    ofstream result("/Users/user/CLionProjects/MPP_Lab1/result.txt");
    output:
    if (i >= words_count) {
        goto output_end;
    }
    if(dictionary[i].apperances_on_pages < 101){
        result << dictionary[i].word << " - ";
    }

    j = 0;
    print_page_numbers:
    if (j >= dictionary[i].apperances_on_pages){
        goto print_page_numbers_end;
    }
    result << dictionary[i].pages[j]<< ", ";

    j++;
    goto print_page_numbers;

    print_page_numbers_end:
    result << endl;

    i++;
    goto output;

    output_end:

    result.close();
    book.close();

    return 0;
}