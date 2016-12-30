/*
 * party.h
 *
 *  Created on: 29-dec.-2016
 *      Author: wdedul01
 */

#ifndef PARTY_H_
#define PARTY_H_

typedef struct {
	char * first_name;
	char * last_name;
} Individual;

typedef struct {
	char name;
} Organization;

typedef union {
	Organization *organization;
	Individual *individual;
} PartyType;

typedef struct {
	char * partyId;
	PartyType *partyType;
} Party;

#endif /* PARTY_H_ */
