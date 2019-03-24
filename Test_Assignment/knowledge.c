/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#define KNOWLEDGE_NODES
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"


/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, char *entity, char *response, int n) {


    if (compare_token(intent, "where") == 0) {


        char *crafted_response = calloc(n, sizeof(char));

        if (where_intent->next != NULL) {

            EntityNode *head = where_intent->next;

            head = Entitysearch_list(head, entity);

            if (head != NULL) {

                strcat(crafted_response, head->answer);
                snprintf(response, n, "%s", crafted_response);
                return KB_OK;

            } else {
                return KB_NOTFOUND;
            }


        } else {
//
            return KB_NOTFOUND;
        }


    } else if (compare_token(intent, "what") == 0) {


        char *crafted_response = calloc(n, sizeof(char));

        if (what_intent->next != NULL) {

            EntityNode *head = what_intent->next;

            head = Entitysearch_list(head, entity);

            if (head != NULL) {

                strcat(crafted_response, head->answer);
                snprintf(response, n, "%s", crafted_response);
                return KB_OK;

            } else {
                return KB_NOTFOUND;
            }


        } else {
//
            return KB_NOTFOUND;
        }


    } else if (compare_token(intent, "who") == 0) {
        char *crafted_response = calloc(n, sizeof(char));

        if (who_intent->next != NULL) {

            EntityNode *head = who_intent->next;

            head = Entitysearch_list(head, entity);

            if (head != NULL) {

                strcat(crafted_response, head->answer);
                snprintf(response, n, "%s", crafted_response);
                return KB_OK;

            } else {
                return KB_NOTFOUND;
            }


        } else {
//
            return KB_NOTFOUND;
        }


    } else {
        return KB_INVALID;
    }


}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response, int n) {

    /* to be implemented */



    char user_response[MAX_INPUT];

    prompt_user(user_response, n, "");

    char *tempChar = calloc(strlen(user_response) + 1, sizeof(char));
    strncpy(tempChar, user_response, sizeof(char) * strlen(user_response) + 1);


    if (compare_token(intent, "where") == 0) {

        EntityNode *head = EntityCreate_node((char *) entity, tempChar);

        if (where_intent->next == NULL) {
            where_intent->next = head;
        } else {
            Entity_insert_at_tail(where_intent->next, head);
        }
        return KB_OK;
    } else if (compare_token(intent, "what") == 0) {
        EntityNode *head = EntityCreate_node((char *) entity, tempChar);

        if (what_intent->next == NULL) {
            what_intent->next = head;
        } else {
            Entity_insert_at_tail(what_intent->next, head);
        }

        return KB_OK;
    } else if (compare_token(intent, "who") == 0) {
        EntityNode *head = EntityCreate_node((char *) entity, tempChar);

        if (who_intent->next == NULL) {
            who_intent->next = head;
        } else {
            Entity_insert_at_tail(who_intent->next, head);
        }
        return KB_OK;
    } else {
        return KB_INVALID;
    }


}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {

    /* to be implemented */

    return 0;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {

    /* to be implemented */

}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

    /* to be implemented */

}


/*
 * Creation of global intent nodes
 *
 * Returns:
 *	NULL
 */
void init_intentnodes() {

    //init of where intent
    where_intent = (IntentNode *) malloc(sizeof(IntentNode));
    if (where_intent == NULL) { //if memory not enough
        printf("Memory is full.");
        exit(1);
    }
    where_intent->intent_name = calloc(6, sizeof(char)); //got to malloc the string pointer first
    strncpy(where_intent->intent_name, "Where", sizeof(char) * 6);
    where_intent->next = NULL;

    //init of what intent
    what_intent = (IntentNode *) malloc(sizeof(IntentNode));
    if (what_intent == NULL) { //if memory not enough
        printf("Memory is full.");
        exit(1);
    }
    what_intent->intent_name = calloc(5, sizeof(char)); //got to malloc the string pointer first
    strncpy(what_intent->intent_name, "What", sizeof(char) * 5);
    what_intent->next = NULL;

    //init of who intent
    who_intent = (IntentNode *) malloc(sizeof(IntentNode));
    if (who_intent == NULL) { //if memory not enough
        printf("Memory is full.");
        exit(1);
    }
    who_intent->intent_name = calloc(4, sizeof(char)); //got to malloc the string pointer first
    strncpy(who_intent->intent_name, "Who", sizeof(char) * 4);
    who_intent->next = NULL;

// testing purpose only
/*
    EntityNode *cHead = NULL;

    EntityNode *where_entity = EntityCreate_node("sit", "it is at dover");
    EntityNode *where_entity2 = EntityCreate_node("nyp", "it is at yishun");

    where_intent->next = where_entity;

    cHead = where_intent->next;

    cHead = Entity_insert_at_tail(cHead, where_entity2);
*/

}


/*
 * EntityNode search for entity name
 *
 * Returns:
 *	EntityNode
 */

EntityNode *Entitysearch_list(EntityNode *head, char *target) {
    EntityNode *temp = head;
    while (temp != NULL && compare_token(temp->entity_name, target) != 0) {
        temp = temp->next;
    }

//
    return temp;
}

EntityNode *EntityCreate_node(char *entity, char *ans) {
    EntityNode *new_node = (EntityNode *) malloc(sizeof(EntityNode));

    if (new_node != NULL) {
        new_node->entity_name = calloc(strlen(entity) + 1, sizeof(char));
        new_node->answer = calloc(strlen(ans) + 1, sizeof(char));

        strncpy(new_node->entity_name, entity, sizeof(char) * strlen(entity) + 1);
        strncpy(new_node->answer, ans, sizeof(char) * strlen(ans) + 1);
        new_node->next = NULL;
    }
    return new_node;
}

EntityNode *Entity_insert_at_tail(EntityNode *head, EntityNode *new_node) {
    if (head == NULL) {
        return new_node;
    }
    EntityNode *temp = head;


    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("NEW DERE: %s", new_node->entity_name);
    temp->next = new_node;
    return head;
}