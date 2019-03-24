/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#define _CRT_SECURE_NO_WARNINGS
#define SMALL_TALK_FILE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "chat1002.h"


 /*
  * Get the name of the chatbot.
  *
  * Returns: the name of the chatbot as a null-terminated string
  */
const char *chatbot_botname() {

	return "Megan";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {

	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}
	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
        return  chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		return chatbot_do_smalltalk(inc, inv, response, n);
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0 || compare_token(intent, "bye") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {

	//if intent is load
	if (compare_token(intent, "load") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {

	/* to be implemented */

	return 0;

}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {

	//if intent is where, who or what
	if (compare_token(intent, "where") == 0 || compare_token(intent, "what") == 0 || compare_token(intent, "who") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
	
	//create crafted response string
	char * crafted_response = calloc(n, sizeof(char));
    char * response_temp = calloc(n, sizeof(char));
	// check for heap overflow
	if (crafted_response == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	// create the entity object - array of strings
	char ** entity = (char **) calloc(inc - 2, sizeof(char *));
	
	// check for heap overflow
	if (entity == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}
    int len_sentence=0;
    int array_size=0;

	//check if second word is 'is'/'are'


	if (compare_token(inv[1],"is")==0 || compare_token(inv[1],"are")==0) {



        for (int i = 0; i < inc - 2; i++) { //taking all the values after entity [is]


            int length_of_str = strlen(inv[i + 2]) + 1;
            entity[i] = (char *) calloc(length_of_str, sizeof(char)); //allocate memory for individual strings
            if (entity[i] == NULL) { //check for heap overflow
                printf("Out of memory.\n");
                exit(1);
            }

            len_sentence = len_sentence + strlen(inv[i + 2]) + 1;// adding 1 to the end to take in account of spaces
            array_size++;
            strncpy(entity[i], inv[i + 2], length_of_str); //copy value from user input to entity
        }


        char *f_entity = (char *) calloc(len_sentence, sizeof(char));

        for (int j = 0; j < array_size; ++j) {

            strcat(f_entity, entity[j]);
            strcat(f_entity, " ");
        }
        f_entity[len_sentence] = '\0';
        f_entity[len_sentence - 1] = '\0';




        //gets return value from knowledge bank
        int knowledge_return = knowledge_get(inv[0], f_entity, response, n);
        switch (knowledge_return) {
            case KB_NOTFOUND: //if cannot find intent
                strcat(response_temp, chatbot_botname());
                strcat(response_temp, ": I don't know."); //copy values to buffer
                for (int i = 0; i < inc; i++) {
                    strcat(response_temp, " ");
                    strcat(response_temp, inv[i]);
                }
                strcat(response_temp, "?");
				printf("%s",response_temp);



              int kout = knowledge_put(inv[0],f_entity,response,n);

                strcat(crafted_response, "Thank you"); //copy values to buffer
                snprintf(response, n, "%s", crafted_response);
                return kout;



			case KB_OK:


            default:
                break;
        }

        return 0;
    }else{
		strcat(crafted_response, "Please include is/are"); //copy values to buffer
		snprintf(response, n, "%s", crafted_response); //put this to response

		return 0;
	}


}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {

	//if intent is reset
	if (compare_token(intent, "reset") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {

	/* to be implemented */

	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "save"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {

	//if intent is save
	if (compare_token(intent, "save") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {

	/* to be implemented */

	return 0;

}



/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot ran out of responses for some reason (and should theoretically never come here)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {

	/* Initialize local variables to be used*/
	int index_of_word; //index of word found in inv
	int index_of_keyword; //index of hardcoded keyword
	int * returnarray = calloc(2, sizeof(int)); //return array to retrieve position of indexes from findpos

	if (returnarray == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	//create crafted response string
	char * crafted_response = calloc(n, sizeof(char));

	// check for heap overflow
	if (crafted_response == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	/* create temp input to put to lowercase in order to match with chatbot words */
	char ** temp_input = (char **)calloc(inc, sizeof(char *));

	for (int word_index = 0; word_index < inc; word_index++) { //iterate through to put all to words to lower case
		temp_input[word_index] = (char *)calloc(30, sizeof(char)); //allocate memory for individual strings (max value 30)
		strncpy(temp_input[word_index], inv[word_index], 30); //copy inv value to temp_input
		for (int char_index = 0; char_index < strlen(inv[word_index]); char_index++) {
			temp_input[word_index][char_index] = tolower(temp_input[word_index][char_index]); //lowercase
		}
	}

	memcpy(returnarray, findpos(inc, temp_input), sizeof(int)*2); //copy the results from findpos to return array
	index_of_word = returnarray[0];
	index_of_keyword = returnarray[1];

	strncpy(crafted_response, responses[index_of_keyword][replycount[index_of_keyword] % responsesperkeyword[index_of_keyword]], n);
	// copies the response based on keyword to crafted response

	if (crafted_response[strlen(crafted_response) - 1] == '*') {
		// strip * from the response
		crafted_response[strcspn(crafted_response, "*")] = 0;

		// swaps all other words with appropriate responses
		for (int after_keyword = index_of_word + 1; after_keyword < inc; after_keyword++) { //iterate through rest of words
			for (int swap_index = 0; swap_index < SWAP_TOTAL; swap_index++) { //iterate through swap list
				if (strcmp(temp_input[after_keyword], swaps[swap_index][0]) == 0) {
					temp_input[after_keyword] = (char *)swaps[swap_index][1]; //swap word
				}
			}
			strcat(crafted_response, " ");
			strcat(crafted_response, temp_input[after_keyword]); //formats and puts word into crafted response
		}

	}
	

	snprintf(response, n, "%s", crafted_response); //put this to response

	replycount[index_of_keyword]++; //increment to get a different response from same category

	return 0;

}


/*
 * Creates the arrays to be used in smalltalk
 *
 *	Input:
 *  inc - number of strings
 *	temp_input - input strings
 *
 * Returns:
 *   int *, position of word and position of keyword
 */
int * findpos(int inc, char ** temp_input) {

	//creates local variables for this function
	int index_of_keyword = KEYWORDS_TOTAL - 1;
	int index_of_word = -1;
	int * returnarray = malloc(2 * sizeof(int));
	if (returnarray == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	returnarray[0] = index_of_word;
	returnarray[1] = index_of_keyword;

	for (int keyword_index = 0; keyword_index < KEYWORDS_TOTAL; keyword_index++) {
		for (int word_index = 0; word_index < inc; word_index++) {

			//create string to checked with for 2 words
			char * two_chk_string = calloc(30, sizeof(char));

			// check for heap overflow
			if (two_chk_string == NULL) {
				printf("Out of memory.\n");
				exit(1);
			}

			//create string to checked with for 3 words
			char * three_chk_string = calloc(30, sizeof(char));

			// check for heap overflow
			if (three_chk_string == NULL) {
				printf("Out of memory.\n");
				exit(1);
			}

			//if there can be phrase of 2 words formed, combine them together
			int max_index_two = word_index + 2; //check if a phrase of 2 char from point of index will not exceed word array range
			if (max_index_two < inc) {
				strncpy(two_chk_string, temp_input[word_index], sizeof(temp_input[word_index]));
				strcat(two_chk_string, " ");
				strcat(two_chk_string, temp_input[word_index + 1]);
			}

			//if there can be phrase of 3 words formed, combine them together
			int max_index_three = word_index + 3; //check if a phrase of 3 char from point of index will not exceed word array range
			if (max_index_three < inc) {
				strncpy(three_chk_string, temp_input[word_index], sizeof(temp_input[word_index]));
				strcat(three_chk_string, " ");
				strcat(three_chk_string, temp_input[word_index + 1]);
				strcat(three_chk_string, " ");
				strcat(three_chk_string, temp_input[word_index + 2]);
			}

			if (strcmp(three_chk_string, keywords[keyword_index]) == 0) { //if there are a list of 3 words in inv that matches a hardcoded keyword
				returnarray[0] = max_index_three - 1; //set word index as a var, minus 1 to position it properly in array
				returnarray[1] = keyword_index; //set keyword index as a var
				return returnarray;
			}
			else if (strcmp(two_chk_string, keywords[keyword_index]) == 0) { //if there are a list of 2 words in inv that matches a hardcoded keyword
				returnarray[0] = max_index_two - 1;
				returnarray[1] = keyword_index;
				return returnarray;
			}
			else if (strcmp(temp_input[word_index], keywords[keyword_index]) == 0) { //if there is a word in inv that matches a hardcoded keyword
				returnarray[0] = word_index;
				returnarray[1] = keyword_index;
				return returnarray;
			}
		}
	}

	return returnarray;
}

/*
 * Creates the arrays to be used in smalltalk
 *
 *
 *
 * Returns:
 *   NULL
 */
void init_keywordcounters() {
	replycount = calloc(KEYWORDS_TOTAL, sizeof(int)); //allocate memory for int *
	if (replycount == NULL) { //if cannot allocate memory
		printf("Out of Memory. Bye");
		exit(1); //exit unhappily
	}
}
